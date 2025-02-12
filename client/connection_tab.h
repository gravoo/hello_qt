#pragma once
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QWidget>
#include <qwidget.h>

class Connection_tab : public QWidget
{
    Q_OBJECT

  public:
    explicit Connection_tab(QWidget* parent = nullptr);
    QTabWidget* get_main_widget();
    void disable_communication_ui();
    void enable_communication_ui();
    QTextBrowser* get_text_browser();
    QLineEdit* get_line_edit();
  signals:
    void connectionButtonClicked();
    void disconnectionButtonClicked();
    void sendButtonClicked();

  private slots:
    void onConnectionButtonClicked();
    void onDisconnectionButtonClicked();
    void onSendButtonClicked();

  private:
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