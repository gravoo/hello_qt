#pragma once
#include "client.hpp"
#include "connection.hpp"
#include <QMainWindow>
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
    std::unique_ptr<Ui::MainWindow> ui;
    std::shared_ptr<boost::asio::io_context> ios;
    QPointer<QTextBrowser> textBrowser;
};