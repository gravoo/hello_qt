#pragma once
#include "client.hpp"
#include <memory>

class Connection
{
  public:
    Connection(QPointer<QTextBrowser> textBrowser = nullptr)
      : textBrowser(textBrowser)
    {
    }
    Connection& operator=(const Connection& other)
    {
        this->textBrowser = other.textBrowser;
        return *this;
    }
    ~Connection() { disconnect(); };
    void connect()
    {
        ios = std::make_shared<boost::asio::io_context>();
        client = std::make_shared<Client>(ios, 1990, textBrowser);
        client->connect();
        client->async_receive_something();
        socket_connected = true;
        ios_thread = std::thread([this]() { ios->run(); });
    }
    void disconnect()
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
    void send(std::string s) { client->send_something(s); }
    bool is_connected() { return socket_connected; }

  private:
    std::thread ios_thread;
    std::shared_ptr<boost::asio::io_context> ios;
    std::shared_ptr<Client> client;
    QPointer<QTextBrowser> textBrowser;
    bool socket_connected{ false };
};