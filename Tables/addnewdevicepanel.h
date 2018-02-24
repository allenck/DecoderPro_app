#ifndef ADDNEWDEVICEPANEL_H
#define ADDNEWDEVICEPANEL_H

#include <QWidget>
#include "jtextfield.h"
#include <QLabel>
#include <QPushButton>

class AddNewDevicePanel : public QWidget
{
 Q_OBJECT
public:
 explicit AddNewDevicePanel(JTextField* sys, JTextField* userName,
                            QString addButtonLabel, ActionListener* okListener, ActionListener* cancelListener, QWidget *parent = nullptr);
 /*public*/ void setOK();
 /*public*/ void setSystemNameFieldIneditable();
 /*public*/ void addLabels(QString labelSystemName, QString labelUserName);

signals:

public slots:

private:
 QPushButton* ok;
 QPushButton* cancel;
 JTextField* sysName;
 QLabel* sysNameLabel;// = new JLabel(Bundle.getMessage("LabelSystemName"));
 QLabel* userNameLabel;// = new JLabel(Bundle.getMessage("LabelUserName"));
 void reset();

};

#endif // ADDNEWDEVICEPANEL_H
