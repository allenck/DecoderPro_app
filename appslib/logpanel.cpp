#include "logpanel.h"
#include <QLabel>
#include <jtextfield.h>
#include <QPushButton>
#include <QBoxLayout>
#include "flowlayout.h"

///*LogPanel::*/LogPanel(QWidget *parent) : QWidget(parent)
//{

//}
/**
 * User interface for adding an item to the log file.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2007
  */
// /*public*/ class LogPanel extends JPanel {

Logger* LogPanel::log = new Logger("LogPanel");
/*public*/ LogPanel::LogPanel(QWidget* parent) : QWidget(parent)
{
 label = new QLabel("Message:");
 sendButton = new QPushButton("Add");
 textField = new JTextField(40);

 QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout()); //(this, BoxLayout.Y_AXIS));

    QWidget* p1 = new QWidget();
    FlowLayout* p1Layout;
    p1->setLayout(p1Layout = new FlowLayout());
    p1Layout->addWidget(label);
    p1Layout->addWidget(textField);
    thisLayout->addWidget(p1);
    thisLayout->addWidget(sendButton);

    sendButton->setToolTip("Add message to the log file");
//    sendButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            sendButtonActionPerformed(e);
//        }
//    });
    connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(sendButtonActionPerformed()));
}

/*public*/ void LogPanel::sendButtonActionPerformed(/*java.awt.event.ActionEvent e*/) {
    log->error(textField->text());
}
