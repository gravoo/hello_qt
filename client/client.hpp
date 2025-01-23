#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <QPointer>
#include <QtWidgets/QTextBrowser>
class Client : public std::enable_shared_from_this<Client>
{
public:
    explicit Client(
        std::shared_ptr<boost::asio::io_service> io,
        boost::asio::ip::port_type port_num,
        QPointer<QTextBrowser> textBrowser):
    io(io),
    socket(*io),
    endpoint(boost::asio::ip::tcp::v4(), 1990),
    textBrowser(textBrowser)
    {}
    ~Client() = default;

void connect()
{
    socket.connect(endpoint);
}


void disconnect()
{
    socket.cancel();
    socket.close();
}

void async_receive_something()
{
    auto self(shared_from_this());
	std::array<char, 128> buf;
    socket.async_read_some(boost::asio::buffer(buf),
        [this, self, &buf](boost::system::error_code ec, std::size_t length)
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
                QMetaObject::invokeMethod(textBrowser, [this, str]() {
                    textBrowser->append(QString(str.c_str()));
                }, Qt::QueuedConnection);
            }
            async_receive_something();
        });
}

void send_something(std::string message)
{
	boost::system::error_code ec;
	socket.write_some(boost::asio::buffer(message.c_str(), message.size()), ec);
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
    }
}

std::string receive_something(std::string message)
{
	std::array<char, 128> buf;
	boost::system::error_code ec;
    socket.read_some(boost::asio::buffer(buf, message.size()), ec);
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
        return std::string();
    }
    return std::string(buf.begin(), buf.begin() + message.size());
}

private:
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::socket socket;
    std::shared_ptr<boost::asio::io_service> io;
    QPointer<QTextBrowser> textBrowser;
};