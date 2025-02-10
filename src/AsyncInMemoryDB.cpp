#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <ranges>
#include <iomanip>
#include <bitset>

using boost::asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection>
{
    enum class ResponseType
    {
        OK,
        ERROR
    };

public:
    Connection(boost::asio::io_context& aIOContext) : mIOContext {aIOContext}, mSocket{std::make_shared<tcp::socket>(mIOContext)}  {}

    std::string ExtractPayload(boost::asio::streambuf& aStreamBuffer)
    {
        std::istream lIstream (&aStreamBuffer);
        std::string lMessage;
        lMessage.assign((std::istreambuf_iterator<char>(lIstream)), std::istreambuf_iterator<char>());
        
        auto posStart = lMessage.find("<start>");
        posStart += 7;
        if(posStart == std::string::npos)
        {
            std::cerr << "Invalid message format\n";
            return "";
        }

        auto posEnd = lMessage.find("<end>");
        if(posEnd == std::string::npos)
        {
            std::cerr << "Invalid message format\n";
            return "";
        }
        posEnd = posEnd - posStart;

        // return lMessage.substr(posStart, posEnd);   // RVO
        return lMessage;
    }

    template<ResponseType RT>
    void Response()
    {
        std::string lResp;
        if constexpr(RT == ResponseType::OK)
            lResp = lRespOK;
        else
            lResp = lRespNOK;
            
        boost::asio::async_write(*mSocket.get(), boost::asio::buffer(lResp), [](const boost::system::error_code& aError, size_t aBytesTransferred){
            if(!aError)
            {
                std::cout << "Nr of " << aBytesTransferred << " bytes sent to client.\n";
            }
            else
            {
                std::cerr << "Error sending response to client: " << aError.message() << "\n";
            }
        }); 
    }

    void HandleConnection() 
    {
        std::cout << "Connection::HandleConnection\n";
        mSocket->async_read_some(boost::asio::buffer(mBuffer, 4), [me=shared_from_this()](const boost::system::error_code& aError, size_t aBytesTransferred){
            if(!aError)
            {
                // Merge 4 bytes into a 32-bit integer
                me->mReadBufferSize = 0;
                for (int i = 0; i < 4; ++i) 
                {
                    me->mReadBufferSize = (me->mReadBufferSize << 8) | static_cast<unsigned char>(me->mBuffer[i]);
                }
                std::cout << "Read buffer size: " << std::bitset<32>(me->mReadBufferSize) << "\n";
                std::cout << "Read buffer size: " << me->mReadBufferSize << "\n";   

                me->ReadNoBytes(me->mReadBufferSize);
            }
            else
            {
                std::cerr << "Error reading from client: " << aError.message() << "\n";
            }
        });
    }

    void ReadNoBytes(int32_t aNoBytes)
    {
        std::cout << "Connection::ReadNoBytes\n";
        mReadBuffer.resize(aNoBytes);
        mSocket->async_read_some(boost::asio::buffer(mReadBuffer), [me=shared_from_this()](const boost::system::error_code& aError, size_t aBytesTransferred){
            if(!aError)
            {
                std::cout << "Read " << aBytesTransferred << " bytes from client.\n";                
                for (int i = 0; i < aBytesTransferred; ++i) 
                {
                    std::cout << "Byte " << i << ": 0x" << std::hex << std::uppercase << static_cast<int>(static_cast<unsigned char>(me->mReadBuffer[i])) << std::endl;
                }

                me->Response<ResponseType::OK>();
            }
            else
            {
                std::cerr << "Error reading from client: " << aError.message() << "\n";
                me->Response<ResponseType::ERROR>();
            }
        });
    }

    std::shared_ptr<tcp::socket> GetSocket() { return mSocket; }


private:
    const std::string lRespOK = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
    const std::string lRespNOK = "HTTP/1.1 405 Method Not Allowed\r\nContent-Length: 0\r\n\r\n";
    boost::asio::io_context& mIOContext;
    std::shared_ptr<tcp::socket> mSocket;
    boost::asio::streambuf mStreamBuffer;
    char mBuffer[4];
    uint32_t mReadBufferSize;
    std::vector<char> mReadBuffer;
};

class Server
{
public:
    Server(int32_t aPort, int32_t aNrOfThreads=1) : mAcceptor{mIOContext, tcp::endpoint(tcp::v4(), aPort)}, mNrOfThreads{aNrOfThreads} 
    {
        AcceptConnections();
    }

    void Run()
    {
        mThreadPool.emplace_back([this](){
            mIOContext.run();   
        });

        for(auto& thread : mThreadPool)
        {
            if(thread.joinable())
            {
                thread.join();
            }
        }
    }

private:

    void AcceptConnections()
    {
        std::shared_ptr<Connection> lConnection = std::make_shared<Connection>(mIOContext);
        mAcceptor.async_accept(*(lConnection->GetSocket().get()), [this, lConnection](boost::system::error_code aError){
            if(!aError) 
            {
                // Handle the connection                
                lConnection->HandleConnection();
            }
            else
            {
                std::cerr << "Error accepting connection: " << aError.message() << "\n";
            }

            this->AcceptConnections();
        });
    }

    boost::asio::io_context mIOContext;
    tcp::acceptor mAcceptor;
    std::vector<std::thread> mThreadPool;
    const int32_t mNrOfThreads;
};


int main() {
    try {
        Server lServer{12345};
        lServer.Run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    std::cout << "Exiting...\n";
    return 0;
}