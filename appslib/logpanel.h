#ifndef LOGPANEL_H
#define LOGPANEL_H

#include <QWidget>

class Logger;
class QLabel;
class JTextField;
class QPushButton;
class LogPanel : public QWidget
{
 Q_OBJECT
public:
 explicit LogPanel(QWidget *parent = 0);

signals:

public slots:
 /*public*/ void sendButtonActionPerformed(/*java.awt.event.ActionEvent e*/);

private:
 // member declarations
 QLabel* label;// = new QLabel("Message:");
 QPushButton* sendButton;// = new QPushButton("Add");
 JTextField* textField;// = new JTextField(40);
 static Logger* log;
};

#endif // LOGPANEL_H
