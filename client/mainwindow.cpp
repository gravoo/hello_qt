#include "mainwindow.h"
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
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    connection_tab = new QWidget();
    processes_tab = new QWidget();

    mainLayout = new QVBoxLayout();
    connection_layout = new QHBoxLayout();
    connectButton = new QPushButton("Connect");
    connectButton->setObjectName("connectButton");

    disconnectButton = new QPushButton("Disconnect");
    disconnectButton->setObjectName("disconnectButton");

    connectionIndicator = new QRadioButton("Connected");
    connectionIndicator->setObjectName("connectionIndicator");

    connectionIndicator->setEnabled(false);
    connectionIndicator->setCheckable(true);

    connection_layout->addWidget(connectButton);
    connection_layout->addWidget(disconnectButton);
    connection_layout->addWidget(connectionIndicator);

    user_input_layout = new QHBoxLayout();
    lineEdit = new QLineEdit("");
    lineEdit->setObjectName("lineEdit");
    lineEdit->setPlaceholderText("Enter what you want send to server here...");
    sendButton = new QPushButton("Send");
    sendButton->setObjectName("sendButton");
    sendButton->setDisabled(true);

    user_input_layout->addWidget(lineEdit);
    user_input_layout->addWidget(sendButton);

    output_layout = new QHBoxLayout();
    textBrowser = QPointer<QTextBrowser>(new QTextBrowser());
    textBrowser->setObjectName("textBrowser");
    output_layout->addWidget(textBrowser);

    mainLayout->addLayout(connection_layout);
    mainLayout->addLayout(user_input_layout);
    mainLayout->addLayout(output_layout);
    connection_tab->setLayout(mainLayout);

    QVBoxLayout* layout2 = new QVBoxLayout();
    layout2->addWidget(new QLabel("Nothing special here yet."));
    processes_tab->setLayout(layout2);

    tabWidget->addTab(connection_tab, "Connection");
    tabWidget->addTab(processes_tab, "Processes");

    setWindowTitle("Client");
    resize(400, 300);

    sendButton->setDisabled(true);
    disconnectButton->setDisabled(true);
    lineEdit->setDisabled(true);

    connect(connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(disconnectButton, &QPushButton::clicked, this, &MainWindow::onDisconnectClicked);
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);

    connection = std::make_shared<Connection>(textBrowser);
}

void MainWindow::onConnectClicked()
{
    if (!connection->is_connected())
    {
        try
        {
            connection->connect();
            connectionIndicator->setChecked(true);
            sendButton->setEnabled(true);
            disconnectButton->setEnabled(true);
            connectButton->setDisabled(true);
            lineEdit->setEnabled(true);
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
    connectionIndicator->setChecked(false);
    sendButton->setDisabled(true);
    disconnectButton->setDisabled(true);
    connectButton->setEnabled(true);
    lineEdit->setDisabled(true);
}

void MainWindow::onSendClicked()
{
    QString input = lineEdit->text();
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
                lineEdit->clear();
            }
        }
    }
    catch (const boost::system::system_error& e)
    {
        QMessageBox::information(this, "Error", "Connection failed: " + QString(e.what()));
    }
}

MainWindow::~MainWindow() {}