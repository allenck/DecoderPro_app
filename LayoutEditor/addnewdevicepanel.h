#ifndef ADDNEWDEVICEPANEL_H
#define ADDNEWDEVICEPANEL_H

#include "jmripanel.h"
#include "liblayouteditor_global.h"

class QLabel;
class JTextField;
class QPushButton;
class ActionListener;
class LIBLAYOUTEDITORSHARED_EXPORT AddNewDevicePanel : public JmriPanel
{
    Q_OBJECT
public:
    //explicit AddDevicePanel(QWidget *parent = 0);
    /*public*/ AddNewDevicePanel(JTextField* sys, JTextField* userName,QString addButtonLabel, ActionListener* listener, ActionListener* cancelListener, QWidget *parent = 0);
    /*public*/ void addLabels(QString labelSystemName, QString labelUserName);

signals:

public slots:
    void reset();
    void sysName_textEdited(QString);
private:
    QPushButton* ok;
    JTextField* sysName;
    QLabel* sysNameLabel;// = new QLabel(tr("System Name:"));
    QLabel* userNameLabel;// = new QLabel(tr("User Name:"));

//        static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");
//        static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AddNewDevicePanel.class.getName());
};

#endif // ADDNEWDEVICEPANEL_H
