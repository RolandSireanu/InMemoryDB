#include <boost/asio.hpp>
#include <sstream>
#include <ranges>
#include "format.pb.h"

using boost::asio::ip::tcp;

std::string encodeLength(const std::string& aData)
{    
    std::string lMsgLength = std::to_string(aData.size());
    const int lNrOfDigits = lMsgLength.size();
    std::string lResult {"00000000"};

    int idx = lNrOfDigits - 1;
    for(auto& e : lResult | std::views::reverse)
    {
        if(idx < 0)
        {
            break;
        }
        e = lMsgLength[idx--];
    }
    
    std::cout << "Header: " << lResult << std::endl;

    return lResult + aData;
}

int main(int argc, char* argv[])
{
    using boost::asio::ip::tcp;
    boost::asio::io_context io_context;
    
    // we need a socket and a resolver
    tcp::socket socket(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345);
    
    // now we can use connect(..)
    socket.connect(endpoint);

    // and use write(..) to send some data which is here just a string
    pkg::Payload lPayload {};
    lPayload.set_key("Hello");
    lPayload.set_value("World");
    std::string lData = lPayload.SerializeAsString();
    socket.write_some(boost::asio::buffer(encodeLength(lData)));
    // auto result = boost::asio::write(socket, boost::asio::buffer(lData));
    
    // the result represents the size of the sent data
    std::cout << "data sent: " << lData.length() << std::endl;

    // and close the connection now
    boost::system::error_code ec;
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    socket.close();

    return 0;
}