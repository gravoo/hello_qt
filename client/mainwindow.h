#pragma once
#include <QMainWindow>
#include <memory>
#include <boost/asio.hpp>
#include "ping_client.hpp"
#include <thread>
#include "client.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public std::enable_shared_from_this<Client>
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onConnectClicked();
    void onDisconnectClicked();
    void onSendClicked();
private:
    void do_read();
    void do_write(std::size_t length);
    std::unique_ptr<Ui::MainWindow> ui;
    std::shared_ptr<boost::asio::io_context> ios;
    std::shared_ptr<Ping> ping;
    std::shared_ptr<Client> client;
    bool socket_connected;
    std::thread ios_thread;
    QPointer<QTextBrowser> textBrowser;
};