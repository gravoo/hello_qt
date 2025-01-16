#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "socket_send.hpp"
#include <QMessageBox>
#include <qdebug.h>
#include <qobject.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Enter what you want send to server here...");
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);
}
void MainWindow::onSendClicked()
{
    QString input = ui->lineEdit->text();
    try
    {
        if(!input.isEmpty())
        {
            auto received = send_something(1990, input.toStdString());
            ui->textBrowser->insertPlainText(QString(received.c_str()));
            ui->textBrowser->insertPlainText(QString("\n"));
            ui->lineEdit->clear();
        }
    }
    catch (const boost::system::system_error& e)
    {
        QMessageBox::information(this, "Error", "Connection failed: " + QString(e.what()));
    }
}
MainWindow::~MainWindow() = default;