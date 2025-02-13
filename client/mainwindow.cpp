#include "mainwindow.h"
#include "processes_tab.h"
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QtWidgets/QTextBrowser>
#include <memory>
#include <qdebug.h>
#include <qobject.h>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
    main_tab_widget = new QTabWidget();
    connection_tab = std::make_unique<Connection_tab>(main_tab_widget);
    processes_tab = std::make_unique<Processes_tab>(main_tab_widget);

    main_tab_widget->addTab(connection_tab->get_tab_widget(), "Connection");
    main_tab_widget->addTab(processes_tab->get_tab_widget(), "Processes");

    setCentralWidget(main_tab_widget);
    setWindowTitle("Client");
    resize(400, 300);
    connection_tab->disable_communication_ui();

    connect(connection_tab.get(), &Connection_tab::connectionButtonClicked, this, &MainWindow::onConnectClicked);
    connect(connection_tab.get(), &Connection_tab::disconnectionButtonClicked, this, &MainWindow::onDisconnectClicked);
    connect(connection_tab.get(), &Connection_tab::sendButtonClicked, this, &MainWindow::onSendClicked);
}

void MainWindow::onConnectClicked()
{
    if (!connection.is_connected())
    {
        try
        {
            connection = Connection(QPointer<QTextBrowser>(connection_tab->get_text_browser()));
            connection.connect();
            connection_tab->enable_communication_ui();
            QMessageBox::information(this, "Info", "Server connected!");
        }
        catch (const boost::system::system_error& e)
        {
            connection.disconnect();
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
    connection_tab->disable_communication_ui();
    connection.disconnect();
}

void MainWindow::onSendClicked()
{
    QString input = connection_tab->get_line_edit()->text();
    try
    {
        if (!connection.is_connected())
        {
            QMessageBox::warning(this, "Warning", "Socket not connected!");
        }
        else
        {
            if (!input.isEmpty())
            {
                connection.send(input.toStdString());
                connection_tab->get_line_edit()->clear();
            }
        }
    }
    catch (const boost::system::system_error& e)
    {
        QMessageBox::information(this, "Error", "Connection failed: " + QString(e.what()));
    }
}

MainWindow::~MainWindow() {}