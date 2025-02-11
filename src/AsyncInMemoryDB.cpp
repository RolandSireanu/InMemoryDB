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

using boost::asio::ip::tcp;

// class InMemoryDB
// {
//     template<typename ...Args>
//     auto ProcessRequest(Args&& ...args)
//     {
//         static_assert(sizeof...(args) > 0, "At least one argument is required.");
//         static_assert(sizeof...(args) < 3, "Maximum number of arguments is 2.");
//         static_assert((std::convertible_to<Args, std::string> && ...), "All arguments must be convertible to std::string.");

//         if constexpr (sizeof...(args) == 2)
//         {
//             const auto& [lKey, lValue] = std::forward_as_tuple(args...);
//             mInMemoryDB[lKey] = lValue;
//         }
//         else if constexpr(sizeof...(args) == 1)
//         {
//             const std::string& lKey = std::get<0>(std::forward_as_tuple(args...));
//             return mInMemoryDB[lKey];
//         }
//     }

//     const std::string& ProcessRequest(const std::string& aKey)
//     {
//         return mInMemoryDB[aKey];
//     }

// private:
//     std::unordered_map<std::string, std::string> mInMemoryDB;
// };

template<typename T>
void printMap(const T& arg)
{
    std::cout << " ======" << "================= \n";
    for(const auto& [k,v] : arg)
    {
        std::cout << k << " : " << v << "\n";
    }
    std::cout << "\n";
    std::cout << " ======================= \n";
}



class InMemoryDB
{
public:
    std::variant<bool, std::string> SetRequest(const std::string& aKey, const std::string& aValue)
    {        
        try
        {
            mDB[aKey] = aValue;
            printMap(mDB);
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
        printMap(mDB);

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
        std::cout << "Connection::ReadMsgLength\n";
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
                uint32_t const lKeyLength = me->ConvertTo<int32_t>(std::string(me->mHeaderBuffer, me->mKeyHeaderLength));
                uint32_t const lValueLength = me->ConvertTo<int32_t>(std::string(&me->mHeaderBuffer[me->mKeyHeaderLength], + me->mValueheaderLength));
                
                std::cout << "lKeyLength: " << lKeyLength << "\n";
                std::cout << "lValueLength: " << lValueLength << "\n";

                me->ReadNoBytes(lKeyLength, lValueLength);
            }
        });
    }

    void ReadNoBytes(int32_t const aNBKey, int32_t const aNBValue)
    {
        std::cout << "Connection::ReadNoBytes\n";
        mReadBuffer.resize(aNBKey + aNBValue);
        mSocket->async_read_some(boost::asio::buffer(mReadBuffer), [aNBKey, aNBValue, me=shared_from_this()](const boost::system::error_code& aError, size_t aBytesTransferred){
            if(aError)
            {
                std::cerr << "Error reading from client: " << aError.message() << "\n";
                me->Response<ResponseType::ERROR>("Error reading from client" + aError.message());
            }
            else if(aBytesTransferred != (aNBKey + aNBValue))
            {
                std::cerr << "Invalid message: " << (aNBKey + aNBValue) << " bytes expected, but " << aBytesTransferred << " bytes received.\n";
                me->Response<ResponseType::ERROR>("Wrong number of bytes received");
            }
            else
            {
                std::string const lKey{me->mReadBuffer.begin(), me->mReadBuffer.begin() + aNBKey};
                std::string const lValue{me->mReadBuffer.begin() + aNBKey, me->mReadBuffer.end()};
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

    std::shared_ptr<tcp::socket> GetSocket() { return mSocket; }


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
    static constexpr int mKeyHeaderLength {4};
    static constexpr int mValueheaderLength {4};
    static constexpr int mMsgHeaderLength {mKeyHeaderLength + mValueheaderLength};
    char mHeaderBuffer[mMsgHeaderLength];
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