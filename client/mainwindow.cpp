#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "client.hpp"
#include "socket_send.hpp"
#include <QMessageBox>
#include <memory>
#include <qdebug.h>
#include <qobject.h>
#include <QDebug>
#include <QtWidgets/QTextBrowser>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()), socket_connected(false)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Enter what you want send to server here...");
    ui->sendButton->setDisabled(true);
    ui->disconnectButton->setDisabled(true);
    textBrowser = QPointer<QTextBrowser>(ui->textBrowser);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &MainWindow::onDisconnectClicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);
}

void MainWindow::onConnectClicked()
{
    if(!socket_connected)
    {
        try
        {
            ios = std::make_shared<boost::asio::io_context>();
            client = std::make_shared<Client>(ios, 1990, textBrowser);
            client->connect();
            client->async_receive_something();

            ios_thread = std::thread([this](){ios->run(); std::cout<<"END\n";});
            socket_connected = true;
            ui->connectionIndicator->setChecked(socket_connected);
            ui->sendButton->setEnabled(true);
            ui->disconnectButton->setEnabled(true);
            ui->connectButton->setDisabled(true);
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

void MainWindow::onDisconnectClicked()
{
    // QMessageBox::information(this, "Info", "Server disconnected!");
    socket_connected = false;

    ui->connectionIndicator->setChecked(socket_connected);
    client->disconnect();
    ios->stop();
    if(ios_thread.joinable())
    {
        ios_thread.join();
    }

    // ui->lineEdit->text().clear();
    ui->sendButton->setDisabled(true);
    ui->disconnectButton->setDisabled(true);
    ui->connectButton->setEnabled(true);
    ui->textBrowser->insertPlainText("Server disconnected!\n");
    std::cout<<"Server disconnected!\n";
}

void MainWindow::onSendClicked()
{
    QString input = ui->lineEdit->text();
    try
    {
        // if(ping->is_timer_expired())
        // {
        //     QMessageBox::warning(this, "Warning", "Server connection lost!\n Try reconnecting!");
        //     socket_connected = false;
        //     ui->connectionIndicator->setChecked(socket_connected);
        //     ios->stop();
        //     if(ios_thread.joinable())
        //     {
        //         ios_thread.join();
        //     }
        //     ui->sendButton->setDisabled(true);
        // }
        // else
        if(!socket_connected)
        {
            QMessageBox::warning(this, "Warning", "Socket not connected!");
        }
        else
        {
            if(!input.isEmpty())
            {
                client->send_something(input.toStdString());
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
    ios->stop();
    if(ios_thread.joinable())
    {
        ios_thread.join();
    }
    socket_connected = false;
}