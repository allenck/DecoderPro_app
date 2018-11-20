#include "addnewhardwaredevicepanel.h"
#include "actionlistener.h"
#include <QGridLayout>
#include "gridbagconstraints.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include "flowlayout.h"
#include "jtextfield.h"
#include <QFont>

//AddNewHardwareDevicePanel::AddNewHardwareDevicePanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
///*public*/ class AddNewHardwareDevicePanel extends jmri.util.swing.JmriPanel {

/*public*/ AddNewHardwareDevicePanel::AddNewHardwareDevicePanel(JTextField* sysAddress, JTextField* userName, QComboBox* prefixBox, QSpinBox* endRange, QCheckBox* addRange,
            QPushButton* addButton, ActionListener* cancelListener, ActionListener* rangeListener, QLabel* statusBar, QWidget *parent) : QWidget(parent)
{
 setObjectName("AddNewHardwareDevicePanel");
 sysNameLabel = new QLabel(tr("System:"));
 sysAddressLabel = new QLabel(tr("Hardware Address:"));
 sysAddress->setValidator(new QIntValidator(1,2047));
 userNameLabel = new QLabel(tr("User Name:"));
 finishLabel = new QLabel(tr("Number to Add:"));
 QVBoxLayout* thisLayout;

 if(statusBar == nullptr)
  statusBar = new QLabel("");
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

 finishLabel->setEnabled(false);
 _endRange->setEnabled(false);

 // add status bar above buttons
 QWidget* panelStatus = new QWidget();
 panelStatus->setLayout(new FlowLayout());
 //statusBar->setFont(statusBar->getFont().deriveFont(0.9f * sysAddressLabel.getFont().getSize())); // a bit smaller
 QFont f = statusBar->font();
 f.setPointSizeF(sysAddressLabel->font().pointSizeF()*.9);
 statusBar->setFont(f);
 statusBar->setStyleSheet("QLabel {color: gray}");
 panelStatus->layout()->addWidget(statusBar);
 thisLayout->addWidget(panelStatus);

 QWidget* panelBottom = new QWidget();
 FlowLayout* panelBottomLayout = new FlowLayout(panelBottom);
 panelBottomLayout->addWidget(cancel = new QPushButton(tr("Cancel")));
 connect(cancel, SIGNAL(clicked(bool)), cancelListener, SLOT(actionPerformed()));
 panelBottom->layout()->addWidget(addButton);
 thisLayout->addWidget(panelBottom);

 connect(addRange, SIGNAL(clicked()), this, SLOT(rangeState()));
//        new ItemListener() {
//            /*public*/ void itemStateChanged(ItemEvent e){
//                rangeState();
//            }
//        });
 //prefixBox.addActionListener(rangeListener);
 connect(prefixBox, SIGNAL(currentIndexChanged(int)), rangeListener, SLOT(actionPerformed()));

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
