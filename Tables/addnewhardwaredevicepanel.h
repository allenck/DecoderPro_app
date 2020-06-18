#ifndef ADDHARDWAREDEVICEPANEL_H
#define ADDHARDWAREDEVICEPANEL_H

#include <QWidget>
#include <QLabel>

class Logger;
class JTextField;
class QPushButton;
class JComboBox;
class ActionListener;
class QLabel;
class QCheckBox;
class QSpinBox;
class AddNewHardwareDevicePanel : public QWidget
{
    Q_OBJECT
public:
    //explicit AddHardwareDevicePanel(QWidget *parent = 0);
 /*public*/ AddNewHardwareDevicePanel(JTextField* sysAddress, JTextField* userName, JComboBox/*<String>*/* prefixBox,
                                      JTextField* endRange, QCheckBox* addRange,
                                      QString addButtonLabel, ActionListener* listener, ActionListener* rangeListener);
    /*public*/ void addLabels(QString labelSystemName, QString labelUserName);

signals:

public slots:
private:
    JTextField* _endRange;
    QCheckBox* _range;
    QLabel* sysNameLabel = new QLabel(tr("System Name:"));
    QLabel* sysAddressLabel = new QLabel(tr("Hardware Address:"));
    QLabel* userNameLabel = new QLabel(tr("User Name:"));
    QLabel* finishLabel = new QLabel(tr("Number to Add:"));
    static Logger* log;

private slots:
    /*private*/ void rangeState();

};

#endif // ADDHARDWAREDEVICEPANEL_H
