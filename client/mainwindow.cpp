#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "socket_send.hpp"
#include <QMessageBox>
#include <qdebug.h>
#include <qobject.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()),
    endpoint(boost::asio::ip::tcp::v4(), 1990), socket(ios), socket_connected(false)
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
        socket.connect(endpoint);
        socket_connected = true;
        ui->connectionIndicator->setChecked(socket_connected);
        QMessageBox::information(this, "Connected", "Connection started");
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
        if(!socket_connected)
        {
            QMessageBox::warning(this, "Warning", "Socket not connected!");
        }
        else
        {
            if(!input.isEmpty())
            {
                send_something(socket, input.toStdString());
                ui->lineEdit->clear();
                auto received = receive_something(socket, input.toStdString());
                ui->textBrowser->insertPlainText(QString(received.c_str()));
                ui->textBrowser->insertPlainText(QString("\n"));
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
    socket_connected = false;
}