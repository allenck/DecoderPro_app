#ifndef ADDNEWBEANPANEL_H
#define ADDNEWBEANPANEL_H
#include "jmripanel.h"
#include "jcheckbox.h"
#include "jspinner.h"
#include "jbutton.h"

class QLabel;
class ActionListener;
class QCheckBox;
class JLabel;
class JTextField;
class AddNewBeanPanel : public JmriPanel
{
 Q_OBJECT
public:
 //explicit AddNewBeanPanel(QWidget *parent = 0);
 /*public*/ AddNewBeanPanel(JTextField* sys, JTextField* userName, JSpinner* endRange, JCheckBox* addRange, JCheckBox* autoSystem,
         QString addButtonLabel, ActionListener* listener, ActionListener* cancelListner, JLabel* statusBar, QWidget *parent = 0);

signals:

public slots:
private:
 JTextField* sysName;
 QLabel* sysNameLabel;// = new JLabel(rb.getString("LabelSystemName"));
 QLabel* userNameLabel;// = new JLabel(rb.getString("LabelUserName"));

 JSpinner* _endRange;
 QCheckBox* _range;
 QCheckBox* _autoSys;
 QLabel* finishLabel;// = new JLabel(rb.getString("LabelNumberToAdd"));
private slots:
 /*private*/ void autoSystemName();
 /*private*/ void rangeState();

protected:
 JButton* ok;

 friend class BlockTableAction;
 friend class MemoryTableAction;
};

#endif // ADDNEWBEANPANEL_H
