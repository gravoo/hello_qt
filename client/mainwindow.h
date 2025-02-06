#pragma once
#include "client.hpp"
#include "connection.hpp"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <boost/asio.hpp>
#include <memory>

namespace Ui
{
class MainWindow;
}

class MainWindow
  : public QMainWindow
  , public std::enable_shared_from_this<Client>
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
  private slots:
    void onConnectClicked();
    void onDisconnectClicked();
    void onSendClicked();

  private:
    void do_read();
    void do_write(std::size_t length);
    void display_warning(bool status, std::string s);
    std::shared_ptr<Connection> connection;
    QTabWidget* tabWidget;
    QPushButton* connectButton;
    QPushButton* sendButton;
    QRadioButton* connectionIndicator;
    QPushButton* disconnectButton;
    QLineEdit* lineEdit;
    QVBoxLayout* mainLayout;
    QHBoxLayout* connection_layout;
    QHBoxLayout* user_input_layout;
    QHBoxLayout* output_layout;
    QWidget* tab1;
    QWidget* tab2;
    QPointer<QTextBrowser> textBrowser;
};