#pragma once
#include <QMainWindow>
#include <memory>
#include <boost/asio.hpp>
#include "ping_client.hpp"
#include <thread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onConnectClicked();
    void onSendClicked();
private:
    void do_read();
    void do_write(std::size_t length);
    std::unique_ptr<Ui::MainWindow> ui;
    std::shared_ptr<boost::asio::io_service> ios;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::socket socket;
    std::shared_ptr<Ping> ping;
    bool socket_connected;
    std::thread ios_thread;
};