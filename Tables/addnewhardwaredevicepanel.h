#ifndef ADDHARDWAREDEVICEPANEL_H
#define ADDHARDWAREDEVICEPANEL_H

#include <QWidget>

class QComboBox;
class ActionListener;
class QLabel;
class QCheckBox;
class JTextField;
class AddNewHardwareDevicePanel : public QWidget
{
    Q_OBJECT
public:
    //explicit AddHardwareDevicePanel(QWidget *parent = 0);
    /*public*/ AddNewHardwareDevicePanel(JTextField* sysAddress, JTextField* userName, QComboBox* prefixBox, JTextField* endRange, QCheckBox* addRange, QString addButtonLabel, ActionListener* listener, ActionListener* rangeListener,QWidget *parent = 0);
    /*public*/ void addLabels(QString labelSystemName, QString labelUserName);

signals:

public slots:
private:
    JTextField* _endRange;
    QCheckBox* _range;
    QLabel* sysNameLabel;// = new JLabel("System");
    QLabel* sysAddressLabel;// = new JLabel("Hardware Address");
    QLabel* userNameLabel;// = new JLabel(rb.getString("LabelUserName"));
    QLabel* finishLabel;// = new JLabel("Number to Add");
private slots:
    /*private*/ void rangeState();

};

#endif // ADDHARDWAREDEVICEPANEL_H
