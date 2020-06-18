#include "addnewhardwaredevicepanel.h"
#include "actionlistener.h"
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include "jcombobox.h"
#include <QLabel>
#include <QSpinBox>
#include "flowlayout.h"
#include "jtextfield.h"
#include <QFont>
#include "loggerfactory.h"
#include "jpanel.h"


//AddNewHardwareDevicePanel::AddNewHardwareDevicePanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
///*public*/ class AddNewHardwareDevicePanel extends jmri.util.swing.JmriPanel {

/*public*/ AddNewHardwareDevicePanel::AddNewHardwareDevicePanel(JTextField* sysAddress, JTextField* userName, JComboBox/*<String>*/* prefixBox, JTextField* endRange, QCheckBox* addRange,
            QString addButtonLabel, ActionListener* listener, ActionListener* rangeListener)
{
 setObjectName("AddNewHardwareDevicePanel");
 setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
 _endRange = endRange;
 _range = addRange;
 JPanel* p;
 p = new JPanel();
 //p.setLayout(new FlowLayout());
 GridBagLayout* pLayout;
 p->setLayout(pLayout = new GridBagLayout());
 GridBagConstraints c = GridBagConstraints();
 c.gridwidth = 1;
 c.gridheight = 1;
 c.gridx = 0;
 c.gridy = 0;
 c.anchor = GridBagConstraints::EAST;
 pLayout->addWidget(sysNameLabel, c);
 c.gridx = 0;
 c.gridy = 1;
 pLayout->addWidget(sysAddressLabel, c);
 c.gridy = 2;
 pLayout->addWidget(userNameLabel, c);
 c.gridx = 2;
 c.gridy = 1;
 c.anchor = GridBagConstraints::WEST;
 c.weightx = 1.0;
 c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
 c.gridy = 0;
 pLayout->addWidget(prefixBox, c);
 c.gridx = 3;
 pLayout->addWidget(addRange, c);
 c.gridx = 2;
 c.gridy = 1;
 pLayout->addWidget(sysAddress, c);
 c.gridx = 3;
 pLayout->addWidget(finishLabel, c);
 c.gridx = 4;
 pLayout->addWidget(endRange, c);
 c.gridx = 2;
 c.gridy = 2;
 pLayout->addWidget(userName, c);
 layout()->addWidget(p);
 QPushButton* ok;
 layout()->addWidget(ok = new QPushButton((addButtonLabel)));
 //ok.addActionListener(listener);
 connect(ok, SIGNAL(clicked(bool)), listener, SLOT(actionPerformed(/*ActionEvent**/)));
// addRange.addItemListener(
//         new ItemListener() {
//             public void itemStateChanged(ItemEvent e) {
 connect(addRange, &QCheckBox::clicked, [=]{
                 rangeState();
//             }
         });
 //prefixBox.addActionListener(rangeListener);
 connect(prefixBox, SIGNAL(currentIndexChanged(int)), rangeListener, SLOT(actionPerformed()));

 finishLabel->setEnabled(false);
 _endRange->setEnabled(false);
 /* System.out.println(jmri.InstanceManager.getList(jmri.jmrix.SystemConnectionMemo.class));
  java.util.List<jmri.jmrix.SystemConnectionMemo> list
  = jmri.InstanceManager.getList(jmri.jmrix.SystemConnectionMemo.class);
  if (list != null) {
  for (jmri.jmrix.SystemConnectionMemo memo : list) {
  System.out.println(memo.getUserName());
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
/*static*/ Logger* AddNewHardwareDevicePanel::log = LoggerFactory::getLogger("AddNewHardwareDevicePanel");
//}
