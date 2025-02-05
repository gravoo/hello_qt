#pragma once
#include <QPointer>
#include <QtWidgets/QTextBrowser>
#include <boost/asio.hpp>
#include <memory>
#include <string>

class Client : public std::enable_shared_from_this<Client>
{
  public:
    explicit Client(std::shared_ptr<boost::asio::io_service> io,
                    boost::asio::ip::port_type port_num,
                    QPointer<QTextBrowser> textBrowser);
    ~Client() = default;
    void connect();
    void disconnect();
    void async_receive_something();
    void send_something(std::string message);
    std::string receive_something(std::string message);

  private:
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::socket socket;
    std::shared_ptr<boost::asio::io_service> io;
    QPointer<QTextBrowser> textBrowser;
};