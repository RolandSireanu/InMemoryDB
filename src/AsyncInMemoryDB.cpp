#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <ranges>
#include <iomanip>
#include <concepts>
#include <bitset>
#include <optional>
#include <variant>
#include "format.pb.h"

using boost::asio::ip::tcp;

class InMemoryDB
{
public:
    std::variant<bool, std::string> SetRequest(const std::string& aKey, const std::string& aValue)
    {        
        try
        {
            mDB[aKey] = aValue;
            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error setting key-value pair in DB: " << e.what() << "\n";
            return std::string(e.what());
        }        
    }

    std::optional<std::string> GetRequest(const std::string& aKey)
    {
        std::cout << "Searching for key :" << aKey << "\n";
        if(mDB.contains(aKey) == false)
        {
            std::cout << "Key not found in DB return nullopt\n";
            return std::nullopt;
        }
        std::cout << "Key found in DB return " << mDB[aKey] << "\n";
        return mDB[aKey];
    }

private:
    std::unordered_map<std::string, std::string> mDB;
};

InMemoryDB gInMemoryDB;

class Connection : public std::enable_shared_from_this<Connection>
{
    enum class ResponseType
    {
        OK,
        ERROR,
        MESSAGE
    };

public:
    Connection(boost::asio::io_context& aIOContext) : mIOContext {aIOContext}, mSocket{std::make_shared<tcp::socket>(mIOContext)}  {}

    template<ResponseType RT>
    void Response(const std::string& aMessage = {"Operation completed."})
    {
        std::string lResp {};
        if constexpr(RT == ResponseType::OK)
            lResp = "[OK] : ";
        else if constexpr (RT == ResponseType::ERROR)
            lResp = "[NOK] : ";
        
        lResp += aMessage;
            
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

    void ReadMsgLength() 
    {
        std::cout << "Connection::ReadMsgLength " << std::this_thread::get_id() <<"\n";
        mSocket->async_read_some(boost::asio::buffer(mHeaderBuffer, mMsgHeaderLength), [me=shared_from_this()](const boost::system::error_code& aError, size_t aBytesTransferred){
            if(aError)
            {
                std::cerr << "Error reading from client: " << aError.message() << "\n";
                me->Response<ResponseType::ERROR>("Error reading from client" + aError.message());
            }
            else if(aBytesTransferred != me->mMsgHeaderLength)
            {
                std::cerr << "Invalid message: " << me->mMsgHeaderLength << " bytes expected, but only " << aBytesTransferred << " bytes received.\n";
                me->Response<ResponseType::ERROR>("Wrong number of bytes received");
            }
            else
            {
                uint32_t const lMsgLength = me->ConvertTo<uint32_t>(std::string(me->mHeaderBuffer));
                me->ReadNoBytes(lMsgLength);
            }
        });
    }

    void ReadNoBytes(uint32_t aMsgLength)
    {
        std::cout << "Connection::ReadNoBytes" << std::this_thread::get_id() <<"\n";

        mReadBuffer.resize(aMsgLength);
        mSocket->async_read_some(boost::asio::buffer(mReadBuffer), [aMsgLength, me=shared_from_this()](const boost::system::error_code& aError, size_t aBytesTransferred){
            if(aError)
            {
                std::cerr << "Error reading from client: " << aError.message() << "\n";
                me->Response<ResponseType::ERROR>("Error reading from client" + aError.message());
            }
            else if(aBytesTransferred != (aMsgLength))
            {
                std::cerr << "Invalid message: " << (aMsgLength) << " bytes expected, but " << aBytesTransferred << " bytes received.\n";
                me->Response<ResponseType::ERROR>("Wrong number of bytes received");
            }
            else
            {
                pkg::Payload lPayload {};
                std::string lMessage (me->mReadBuffer.begin(), me->mReadBuffer.end());
                lPayload.ParseFromString(lMessage);

                std::string const lKey = lPayload.key();
                std::string const lValue = lPayload.value();
                std::cout << "Key : " << lKey << " , " << " Value : " << lValue << "\n";
                if(lValue.empty())
                {
                    std::optional<std::string> lTempValue = gInMemoryDB.GetRequest(lKey);
                    if(lTempValue.has_value() == false)
                    {
                        me->Response<ResponseType::ERROR>("Key not found in DB.");
                    }
                    else
                    {
                        me->Response<ResponseType::MESSAGE>(lTempValue.value());
                    }                    
                }
                else
                {
                    auto result = gInMemoryDB.SetRequest(lKey, lValue);
                    if(std::holds_alternative<std::string>(result))
                    {
                        std::string tempString = "Error setting key-value pair in DB." + std::get<std::string>(result);
                        me->Response<ResponseType::ERROR>(tempString);
                    }
                    else
                    {
                        me->Response<ResponseType::OK>();
                    }                        
                }
            }
        });
    }

    std::shared_ptr<tcp::socket> GetSocket() 
    { 
        return mSocket; 
    }


private:
    template<typename T>
    T ConvertTo(const std::string& argInputString)
    {
        T temp{};
        std::stringstream lStringStream(argInputString);
        lStringStream >> temp;
        return temp;
    }

    boost::asio::io_context& mIOContext;
    std::shared_ptr<tcp::socket> mSocket;
    boost::asio::streambuf mStreamHeaderBuffer;
    static constexpr int mMsgHeaderLength {8};
    char mHeaderBuffer[mMsgHeaderLength];
    std::vector<char> mReadBuffer;
};

class Server
{
public:
    Server(int32_t aPort, int32_t aNrOfThreads=1) : mAcceptor{mIOContext, tcp::endpoint(tcp::v4(), aPort)} 
    {
        AcceptConnections();
    }

    void Run(const int32_t aNrOfThreads=1)
    {   
        for(int i = 0; i < aNrOfThreads; ++i)
        {
            mThreadPool.emplace_back([this](){
                mIOContext.run();   
            });
        }

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
                lConnection->ReadMsgLength();                
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
};


int main() {
    std::cout << "Main thread id " << std::this_thread::get_id() << "\n";
    try {
        Server lServer{12345};
        const uint32_t lMaxNrOfThreads {std::thread::hardware_concurrency()};
        lServer.Run(lMaxNrOfThreads);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    std::cout << "Exiting...\n";
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}