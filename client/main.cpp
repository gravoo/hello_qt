#include <iostream>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    std::cout<<"HELLO FROM CLIENT\n";
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}