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

class MainWindow : public QMainWindow
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
    Connection connection;
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
    QWidget* connection_tab;
    QWidget* processes_tab;
    QTextBrowser* textBrowser;
};