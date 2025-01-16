#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "socket_send.hpp"
#include <QMessageBox>
#include <qobject.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, [&]() {
        try
        {
            send_something(1990, "simple string");
        }
        catch (const boost::system::system_error& e)
        {
            QMessageBox::information(this, "Error", "Connection failed: " + QString(e.what()));
        }
    });
}
MainWindow::~MainWindow() = default;