#pragma once
#include "client.hpp"
#include <memory>

class Connection
{
  public:
    Connection(QPointer<QTextBrowser> textBrowser)
      : textBrowser(textBrowser)
    {
    }
    void connect()
    {
        ios = std::make_shared<boost::asio::io_context>();
        client = std::make_shared<Client>(ios, 1990, textBrowser);
        client->connect();
        socket_connected = true;
        client->async_receive_something();
        ios_thread = std::thread([this]() { ios->run(); });
    }
    void disconnect()
    {
        socket_connected = false;
        client.reset();
        ios->stop();
        if (ios_thread.joinable())
        {
            ios_thread.join();
        }
    }
    void send(std::string s) { client->send_something(s); }
    bool is_connected() { return socket_connected; }

  private:
    std::thread ios_thread;
    std::shared_ptr<boost::asio::io_context> ios;
    std::shared_ptr<Client> client;
    QPointer<QTextBrowser> textBrowser;
    bool socket_connected{ false };
};