#include <iostream>
#include <boost/asio.hpp>
#include <array>
#include <iterator>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    std::cout<<"HELLO FROM CLIENT\n";
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
    // QApplication app(argc, argv); // Aplikacja Qt
    // QWidget window;
    // window.setWindowTitle("Simple QT client");
    // window.resize(400, 300);

    // QPushButton *button = new QPushButton("Click to send!");
    // QVBoxLayout *layout = new QVBoxLayout();
    // layout->addWidget(button);
    // window.setLayout(layout);

    // // Połączenie przycisku z akcją
    // QObject::connect(button, &QPushButton::clicked, [&]() {
    //     QMessageBox::information(&window, "Info", "Button has been clicked!");
    //     send_something(1990, "hello flowers team");
    // });

    // // Wyświetlenie głównego okna
    // window.show();
    // return app.exec();

}