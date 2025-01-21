#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "socket_send.hpp"
#include <QMessageBox>
#include <memory>
#include <qdebug.h>
#include <qobject.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()), ios(std::make_shared<boost::asio::io_service>()),
    endpoint(boost::asio::ip::tcp::v4(), 1990),
    socket(*ios), socket_connected(false)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Enter what you want send to server here...");
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);
}

void MainWindow::onConnectClicked()
{
    if(!socket_connected)
    {
        try
        {
            ios = std::make_shared<boost::asio::io_service>();
            socket = boost::asio::ip::tcp::socket(*ios);
            socket.connect(endpoint);
            ping = std::make_shared<Ping>(ios.get());
            ping->ping_start();
            async_receive_something(socket,
                [this](std::string text) { ui->textBrowser->insertPlainText(QString(text.c_str()) + QString("\n"));});
            ios_thread = std::thread([this](){ios->run(); std::cout<<"END!";});
            socket_connected = true;
            ui->connectionIndicator->setChecked(socket_connected);
            ui->textBrowser->insertPlainText("Server connected!\n");
        }
        catch(const boost::system::system_error& e)
        {
            QMessageBox::warning(this, "Warning", "Can't connect to server!");
            qDebug() << "Error code:" << e.what();
        }
    }
    else
    {
        QMessageBox::information(this, "Connected", "Already connected!");
    }
}

void MainWindow::onSendClicked()
{
    QString input = ui->lineEdit->text();
    try
    {
        if(ping->is_timer_expired())
        {
            QMessageBox::warning(this, "Warning", "Server connection lost!\n Try reconnecting!");
            socket_connected = false;
            ui->connectionIndicator->setChecked(socket_connected);
            socket.close();
            ios->stop();
            ios_thread.join();
        }
        else if(!socket_connected)
        {
            QMessageBox::warning(this, "Warning", "Socket not connected!");
        }
        else
        {
            if(!input.isEmpty())
            {
                send_something(socket, input.toStdString());
                ui->lineEdit->clear();
            }
        }
    }
    catch (const boost::system::system_error& e)
    {
        QMessageBox::information(this, "Error", "Connection failed: " + QString(e.what()));
    }
}

MainWindow::~MainWindow()
{
    socket.close();
    ios->stop();
    if(ios_thread.joinable())
    {
        ios_thread.join();
    }
    socket_connected = false;
}