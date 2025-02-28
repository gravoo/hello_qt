#include "connection_tab.h"
#include <qwidget.h>

Connection_tab::Connection_tab(QWidget* parent)
  : QWidget(parent)
{
    tab_widget = new QWidget();
    tab_layout = new QVBoxLayout();
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
    textBrowser = new QTextBrowser();
    textBrowser->setObjectName("textBrowser");
    output_layout->addWidget(textBrowser);

    tab_layout->addLayout(connection_layout);
    tab_layout->addLayout(user_input_layout);
    tab_layout->addLayout(output_layout);
    tab_widget->setLayout(tab_layout);

    connect(connectButton, &QPushButton::clicked, this, &Connection_tab::onConnectionButtonClicked);
    connect(disconnectButton, &QPushButton::clicked, this, &Connection_tab::onDisconnectionButtonClicked);
    connect(sendButton, &QPushButton::clicked, this, &Connection_tab::onSendButtonClicked);
}
QTextBrowser* Connection_tab::get_text_browser() { return textBrowser; }
QLineEdit* Connection_tab::get_line_edit() { return lineEdit; }
QWidget* Connection_tab::get_tab_widget() { return tab_widget; }
void Connection_tab::disable_communication_ui()
{
    sendButton->setDisabled(true);
    disconnectButton->setDisabled(true);
    lineEdit->setDisabled(true);
    connectionIndicator->setChecked(false);
    connectButton->setEnabled(true);
}
void Connection_tab::enable_communication_ui()
{
    connectionIndicator->setChecked(true);
    sendButton->setEnabled(true);
    disconnectButton->setEnabled(true);
    connectButton->setDisabled(true);
    lineEdit->setEnabled(true);
}
void Connection_tab::onConnectionButtonClicked() { emit connectionButtonClicked(); }
void Connection_tab::onDisconnectionButtonClicked() { emit disconnectionButtonClicked(); }
void Connection_tab::onSendButtonClicked() { emit sendButtonClicked(); }