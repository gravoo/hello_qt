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

class Processes_tab : public QWidget
{
    Q_OBJECT

  public:
    explicit Processes_tab(QWidget* parent = nullptr);
    QWidget* get_tab_widget();
  signals:

  private slots:

  private:
    QVBoxLayout* tab_layout;
    QWidget* tab_widget;
};