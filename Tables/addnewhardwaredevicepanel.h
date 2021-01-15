#ifndef ADDHARDWAREDEVICEPANEL_H
#define ADDHARDWAREDEVICEPANEL_H

#include <QWidget>
#include "jmripanel.h"
#include "jlabel.h"
#include "jbutton.h"

class ManagerComboBox;
class JCheckBox;
class JSpinner;
class SystemNameValidator;
class Logger;
class JTextField;
class QPushButton;
class JComboBox;
class ActionListener;
class QLabel;
class QCheckBox;
class QSpinBox;
class AddNewHardwareDevicePanel : public JmriPanel
{
    Q_OBJECT
public:
    //explicit AddHardwareDevicePanel(QWidget *parent = 0);
    AddNewHardwareDevicePanel(JTextField* sysAddress, SystemNameValidator* sysAddressValidator, JTextField* userName,
                                       ManagerComboBox/*<String>*/* prefixBox,
                                       JSpinner* endRange, JCheckBox* addRange,
                                       JButton* addButton, ActionListener* cancelListener, ActionListener* rangeListener,
                                       JLabel* statusBar, QWidget* parent= nullptr);
    /*public*/ void addLabels(QString labelSystemName, QString labelUserName);

signals:

public slots:
private:
    JSpinner* _endRange;
    JCheckBox* _range;
    JLabel* sysNameLabel = new JLabel(tr("System Connection:"));
    JLabel* sysAddressLabel = new JLabel(tr("Hardware Address:"));
    JLabel* userNameLabel = new JLabel(tr("User Name:"));
    JLabel* finishLabel = new JLabel(tr("Number to Add:"));
    JLabel* statusBar = new JLabel();
    static Logger* log;
    JButton* cancel = new JButton(tr("Close")); // when Apply has been clicked at least once, this is not Revert/Cancel


private slots:
    /*private*/ void rangeState();

};

#endif // ADDHARDWAREDEVICEPANEL_H
