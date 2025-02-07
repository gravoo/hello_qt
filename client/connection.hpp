#pragma once
#include "client.hpp"
#include <memory>

class Connection
{
  public:
    Connection(QPointer<QTextBrowser> textBrowser = nullptr);
    Connection& operator=(const Connection& other);
    ~Connection();
    void connect();
    void disconnect();
    void send(std::string s);
    bool is_connected();

  private:
    std::thread ios_thread;
    std::shared_ptr<boost::asio::io_context> ios;
    std::shared_ptr<Client> client;
    QPointer<QTextBrowser> textBrowser;
    bool socket_connected{ false };
};