#ifndef ADDNEWDEVICEPANEL_H
#define ADDNEWDEVICEPANEL_H

#include "jmripanel.h"
#include "jtextfield.h"
#include <QLabel>
#include <QPushButton>

class AddNewDevicePanel : public JmriPanel
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
  void sysName_textEdited(QString txt);

private:
 QPushButton* ok;
 QPushButton* cancel;
 JTextField* sysName;
 QLabel* sysNameLabel;// = new JLabel(Bundle.getMessage("LabelSystemName"));
 QLabel* userNameLabel;// = new JLabel(Bundle.getMessage("LabelUserName"));
 void reset();

};

#endif // ADDNEWDEVICEPANEL_H
