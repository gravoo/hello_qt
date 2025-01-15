#include <iostream>
#include <boost/asio.hpp>
#include <array>
#include <iterator>

void send_something(int port, std::string message)
{
	boost::asio::io_service ios;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);

    boost::asio::ip::tcp::socket socket(ios);

	socket.connect(endpoint);

	std::array<char, 128> buf;
    std::copy(message.begin(),message.end(),buf.begin());
	boost::system::error_code error;
    std::copy(buf.begin(), buf.begin() + message.size(), std::ostream_iterator<char>(std::cout, " "));
	socket.write_some(boost::asio::buffer(buf, message.size()), error);
    buf.fill(0);
    socket.read_some(boost::asio::buffer(buf, message.size()), error);
    std::copy(buf.begin(), buf.begin() + message.size(), std::ostream_iterator<char>(std::cout, " "));
    socket.close();
}

int main()
{
    std::cout<<"HELLO FROM CLIENT\n";
    send_something(1990, "hello flowers team");
}