#include "connection_tab.h"

Connection_tab::Connection_tab(QWidget* parent)
  : QWidget(parent)
{
    tabWidget = new QTabWidget();
    connection_tab = new QWidget();

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
    textBrowser = new QTextBrowser();
    textBrowser->setObjectName("textBrowser");
    output_layout->addWidget(textBrowser);

    mainLayout->addLayout(connection_layout);
    mainLayout->addLayout(user_input_layout);
    mainLayout->addLayout(output_layout);
    connection_tab->setLayout(mainLayout);
    tabWidget->addTab(connection_tab, "Connection");

    connect(connectButton, &QPushButton::clicked, this, &Connection_tab::onConnectionButtonClicked);
    connect(disconnectButton, &QPushButton::clicked, this, &Connection_tab::onDisconnectionButtonClicked);
    connect(sendButton, &QPushButton::clicked, this, &Connection_tab::onSendButtonClicked);
}
QTabWidget* Connection_tab::get_main_widget() { return tabWidget; }
QTextBrowser* Connection_tab::get_text_browser() { return textBrowser; }
QLineEdit* Connection_tab::get_line_edit() { return lineEdit; }
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