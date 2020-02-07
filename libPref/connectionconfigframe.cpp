#include "connectionconfigframe.h"
#include "jmrixconfigpane.h"
#include <QBoxLayout>

ConnectionConfigFrame::ConnectionConfigFrame(QWidget *parent) :
    JmriJFrame(parent)
{
 QWidget* centralWidget = new QWidget;
 setWindowTitle(tr("Configure Connection"));
 QVBoxLayout* layout = new QVBoxLayout;
 centralWidget->setLayout(layout);
 setCentralWidget(centralWidget);
 //JmrixConfigPane* pane = JmrixConfigPane::instance(0);
 //layout->addWidget(pane);
}
