#include "processes_tab.h"
#include <QLabel>
Processes_tab::Processes_tab(QWidget* parent)
  : QWidget(parent)
{
    tab_widget = new QWidget();
    tab_layout = new QVBoxLayout();

    tab_layout->addWidget(new QLabel("Nothing special here yet."));
    tab_widget->setLayout(tab_layout);
}
QWidget* Processes_tab::get_tab_widget() { return tab_widget; }