#pragma once
#include <functional>
#include <iostream>
#include <boost/asio.hpp>
#include <array>
#include <iterator>
#include <vector>

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

void async_receive_something(boost::asio::ip::tcp::socket &socket, const std::function<void(std::string)>& qt_insert)
{
	std::array<char, 128> buf;
    socket.async_read_some(boost::asio::buffer(buf),
        [&, qt_insert](boost::system::error_code ec, std::size_t length)
        {
            if (ec)
            {
                if (ec == boost::asio::error::would_block)
                {
                    std::cout << "No data available on socket." << std::endl;
                }
                else if (ec == boost::asio::error::eof)
                {
                    std::cout << "Connection closed by peer." << std::endl;
                }
                else
                {
                    std::cerr << "Error during async receive: " << ec.message() << std::endl;
                }
                return;
            }

            if (length > 0) {
                auto str = std::string(buf.data(), length);
                std::cout << "Received data: "<< str << std::endl;
                qt_insert(str);
            }
            async_receive_something(socket, qt_insert);
        });
}