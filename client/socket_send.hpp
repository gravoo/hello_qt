#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <array>
#include <iterator>

void send_something(boost::asio::ip::tcp::socket &socket, std::string message)
{
	boost::system::error_code error;
	socket.write_some(boost::asio::buffer(message.c_str(), message.size()), error);
}
std::string receive_something(boost::asio::ip::tcp::socket &socket, std::string message)
{
	std::array<char, 128> buf;
	boost::system::error_code error;
    socket.read_some(boost::asio::buffer(buf, message.size()), error);
    return std::string(buf.begin(), buf.begin() + message.size());
}