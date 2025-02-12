#pragma once
#include "connection.hpp"
#include "connection_tab.h"
#include <QMainWindow>
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
    QWidget* processes_tab;
    std::unique_ptr<Connection_tab> connection_tab;
};