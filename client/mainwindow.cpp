#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QtWidgets/QTextBrowser>
#include <memory>
#include <qdebug.h>
#include <qobject.h>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Enter what you want send to server here...");
    ui->sendButton->setDisabled(true);
    ui->disconnectButton->setDisabled(true);
    ui->lineEdit->setDisabled(true);
    textBrowser = QPointer<QTextBrowser>(ui->textBrowser);
    connection = std::make_shared<Connection>(textBrowser);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &MainWindow::onDisconnectClicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);
}

void MainWindow::onConnectClicked()
{
    if (!connection->is_connected())
    {
        try
        {
            connection->connect();
            ui->connectionIndicator->setChecked(true);
            ui->sendButton->setEnabled(true);
            ui->disconnectButton->setEnabled(true);
            ui->connectButton->setDisabled(true);
            ui->lineEdit->setEnabled(true);
            QMessageBox::information(this, "Info", "Server connected!");
        }
        catch (const boost::system::system_error& e)
        {
            connection->disconnect();
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
    QMessageBox::information(this, "Info", "Server disconnected!");
    connection->disconnect();
    ui->connectionIndicator->setChecked(false);
    ui->sendButton->setDisabled(true);
    ui->disconnectButton->setDisabled(true);
    ui->connectButton->setEnabled(true);
    ui->lineEdit->setDisabled(true);
}

void MainWindow::onSendClicked()
{
    QString input = ui->lineEdit->text();
    try
    {
        if (!connection->is_connected())
        {
            QMessageBox::warning(this, "Warning", "Socket not connected!");
        }
        else
        {
            if (!input.isEmpty())
            {
                connection->send(input.toStdString());
                ui->lineEdit->clear();
            }
        }
    }
    catch (const boost::system::system_error& e)
    {
        QMessageBox::information(this, "Error", "Connection failed: " + QString(e.what()));
    }
}

MainWindow::~MainWindow() {}