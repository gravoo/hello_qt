#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "socket_send.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [&]() {
        send_something(1990, "simple string");
    });
}

MainWindow::~MainWindow() {
    delete ui;
}