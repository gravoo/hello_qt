#pragma once
#include <QMainWindow>
#include <memory>
#include <boost/asio.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onConnectClicked();
    void onSendClicked();
private:
    std::unique_ptr<Ui::MainWindow> ui;
    boost::asio::io_service ios;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::socket socket;
    bool socket_connected;
};