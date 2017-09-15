#include "addnewhardwaredevicepanel.h"
#include "actionlistener.h"
#include <QGridLayout>
#include "gridbagconstraints.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include "jtextfield.h"
#include "flowlayout.h"

//AddNewHardwareDevicePanel::AddNewHardwareDevicePanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
///*public*/ class AddNewHardwareDevicePanel extends jmri.util.swing.JmriPanel {

/*public*/ AddNewHardwareDevicePanel::AddNewHardwareDevicePanel(JTextField* sysAddress, JTextField* userName, QComboBox* prefixBox, JTextField* endRange, QCheckBox* addRange, QString addButtonLabel, ActionListener* okListener, ActionListener* cancelListener, ActionListener* rangeListener, QWidget* parent) : QWidget(parent)
{
 setObjectName("AddNewHardwareDevicePanel");
 sysNameLabel = new QLabel(tr("System:"));
 sysAddressLabel = new QLabel(tr("Hardware Address:"));
 sysAddress->setValidator(new QIntValidator(1,2047));
 userNameLabel = new QLabel(tr("User Name:"));
 finishLabel = new QLabel(tr("Number to Add:"));
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout(this/*, BoxLayout.Y_AXIS*/));
 _endRange=endRange;
 _range=addRange;
//        JPanel p;
//        p = new JPanel();
//        p.setLayout(new FlowLayout());
 QGridLayout* g  = new QGridLayout();
//        p.setLayout(g = new QGridLayout());
 GridBagConstraints c;// =  GridBagConstraints();
 c.gridwidth  = 1;
 c.gridheight = 1;
 c.gridx = 0;
 c.gridy = 0;
 c.anchor = GridBagConstraints::EAST;
 g->addWidget(sysNameLabel,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
 c.gridx =0;
 c.gridy = 1;
 g->addWidget(sysAddressLabel,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
 c.gridy = 2;
 g->addWidget(userNameLabel,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
 c.gridx = 2;
 c.gridy = 1;
 c.anchor = GridBagConstraints::WEST;
 c.weightx = 1.0;
 c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
 c.gridy = 0;
 g->addWidget(prefixBox,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
 c.gridx = 3;
 g->addWidget(addRange,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
 c.gridx = 2;
 c.gridy = 1;
 g->addWidget(sysAddress,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
 c.gridx = 3;
 g->addWidget(finishLabel,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
 c.gridx = 4;
 g->addWidget(endRange,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
 c.gridx=2;
 c.gridy = 2;
 g->addWidget(userName,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
 //add(p);
 thisLayout->addLayout(g);
 QWidget* panelBottom = new QWidget();
 FlowLayout* panelBottomLayout = new FlowLayout(panelBottom);
QPushButton* ok;
 panelBottomLayout->addWidget(cancel = new QPushButton(tr("Cancel")));
 connect(cancel, SIGNAL(clicked(bool)), cancelListener, SLOT(actionPerformed()));
 thisLayout->addWidget(ok = new QPushButton(addButtonLabel),0,Qt::AlignHCenter);
//        ok.addActionListener(listener);
 connect(ok, SIGNAL(clicked()), okListener, SLOT(actionPerformed()));
//        addRange .addItemListener(
 connect(addRange, SIGNAL(clicked()), this, SLOT(rangeState()));
//        new ItemListener() {
//            /*public*/ void itemStateChanged(ItemEvent e){
//                rangeState();
//            }
//        });
 //prefixBox.addActionListener(rangeListener);
 connect(prefixBox, SIGNAL(currentIndexChanged(int)), rangeListener, SLOT(actionPerformed()));

 finishLabel->setEnabled(false);
 _endRange->setEnabled(false);
       /* System.out.println(jmri.InstanceManager.getList(jmri.jmrix.SystemConnectionMemo.class));
        java.util.List<Object> list
            = jmri.InstanceManager.getList(jmri.jmrix.SystemConnectionMemo.class);
        if (list != null) {
            for (Object memo : list) {
                System.out.println(((jmri.jmrix.SystemConnectionMemo)memo).getUserName());
                //if (menu != null) m.add(menu);
            }
        }*/
}
/*public*/ void AddNewHardwareDevicePanel::addLabels(QString labelSystemName, QString labelUserName) {
    sysAddressLabel->setText(labelSystemName);
    userNameLabel->setText(labelUserName);
}

/*private*/ void AddNewHardwareDevicePanel::rangeState()
{
 if (_range->isChecked())
 {
  finishLabel->setEnabled(true);
  _endRange->setEnabled(true);
 }
 else
 {
  finishLabel->setEnabled(false);
  _endRange->setEnabled(false);
 }
}


//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");
//    static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AddNewHardwareDevicePanel.class.getName());
//}
