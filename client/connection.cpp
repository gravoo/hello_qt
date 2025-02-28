#include "connection.hpp"
#include "client.hpp"
#include <memory>

Connection::Connection(QPointer<QTextBrowser> textBrowser)
  : textBrowser(textBrowser)
{
}
Connection::~Connection() { disconnect(); }
Connection& Connection::operator=(const Connection& other)
{
    this->textBrowser = other.textBrowser;
    return *this;
}
void Connection::connect()
{
    ios = std::make_shared<boost::asio::io_context>();
    client = std::make_shared<Client>(ios, 1990, textBrowser);
    client->connect();
    client->async_receive_something();
    socket_connected = true;
    ios_thread = std::thread([this]() { ios->run(); });
}
void Connection::disconnect()
{
    socket_connected = false;
    client.reset();
    if (ios)
    {
        ios->stop();
    }
    if (ios_thread.joinable())
    {
        ios_thread.join();
    }
}

void Connection::send(std::string s) { client->send_something(s); }
bool Connection::is_connected() { return socket_connected; }
