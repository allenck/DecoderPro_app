#ifndef ADDHARDWAREDEVICEPANEL_H
#define ADDHARDWAREDEVICEPANEL_H

#include <QWidget>

class JTextField;
class QPushButton;
class QComboBox;
class ActionListener;
class QLabel;
class QCheckBox;
class QSpinBox;
class AddNewHardwareDevicePanel : public QWidget
{
    Q_OBJECT
public:
    //explicit AddHardwareDevicePanel(QWidget *parent = 0);
    /*public*/ AddNewHardwareDevicePanel(JTextField* sysAddress, JTextField* userName, QComboBox* prefixBox, QSpinBox* endRange, QCheckBox* addRange,
                QPushButton* addButton, ActionListener* cancelListener, ActionListener* rangeListener, QLabel* statusBar, QWidget* parent = nullptr);
    /*public*/ void addLabels(QString labelSystemName, QString labelUserName);

signals:

public slots:
private:
    QSpinBox* _endRange;
    QCheckBox* _range;
    QLabel* sysNameLabel;// = new JLabel("System");
    QLabel* sysAddressLabel;// = new JLabel("Hardware Address");
    QLabel* userNameLabel;// = new JLabel(rb.getString("LabelUserName"));
    QLabel* finishLabel;// = new JLabel("Number to Add");
    QPushButton* cancel;

private slots:
    /*private*/ void rangeState();

};

#endif // ADDHARDWAREDEVICEPANEL_H
