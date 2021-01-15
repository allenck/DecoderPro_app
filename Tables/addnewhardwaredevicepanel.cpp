#include "addnewhardwaredevicepanel.h"
#include "actionlistener.h"
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include <QVBoxLayout>
#include "jcheckbox.h"
#include "jcombobox.h"
#include "jspinner.h"
#include "flowlayout.h"
#include "jtextfield.h"
#include <QFont>
#include "loggerfactory.h"
#include "jpanel.h"
#include "managercombobox.h"
#include "systemnamevalidator.h"

//AddNewHardwareDevicePanel::AddNewHardwareDevicePanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
///*public*/ class AddNewHardwareDevicePanel extends jmri.util.swing.JmriPanel {

/*public*/ AddNewHardwareDevicePanel::AddNewHardwareDevicePanel(JTextField* sysAddress, SystemNameValidator* sysAddressValidator, JTextField* userName,
                                     ManagerComboBox/*<String>*/* prefixBox,
                                     JSpinner* endRange, JCheckBox* addRange,
                                     JButton* addButton, ActionListener* cancelListener, ActionListener* rangeListener,
                                     JLabel* statusBar, QWidget* parent) : JmriPanel(parent)
{
 setObjectName("AddNewHardwareDevicePanel");
 setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
 _endRange = endRange;
 _range = addRange;
 // directly using the addButton from the table action allows to disable it from there
 // as long until a valid address is entered
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
 userName->setToolTip(tr("Use any characters. Double or padding spaces will be trimmed.")); // fixed general instructio
 layout()->addWidget(p);
 finishLabel->setEnabled(false);
 _endRange->setEnabled(false);

 // add status bar above buttons
 JPanel* panelStatus = new JPanel();
 panelStatus->setLayout(new FlowLayout());
 QFont f = statusBar->font();
 f.setPointSizeF(0.9f * sysAddressLabel->font().pointSizeF());
 statusBar->setFont(f); // a bit smaller
 statusBar->setForeground(Qt::gray);
 panelStatus->layout()->addWidget(statusBar);
 layout()->addWidget(panelStatus);

 // cancel + add buttons at bottom of window
 JPanel* panelBottom = new JPanel();
 panelBottom->setLayout(new FlowLayout());//FlowLayout.TRAILING));

 panelBottom->layout()->addWidget(cancel);
 //cancel.addActionListener(cancelListener);
 connect(cancel, &JButton::clicked, [=]{cancelListener->actionPerformed();});

 panelBottom->layout()->addWidget(addButton);

 layout()->addWidget(panelBottom);

// addRange.addItemListener((ItemEvent e) -> {
//     rangeState();
// });
 connect(addRange, &JCheckBox::clicked, [=]{rangeState();});
 //prefixBox.addActionListener(rangeListener);
 connect(prefixBox, &ManagerComboBox::currentIndexChanged, [=]{rangeListener->actionPerformed();});
 sysAddress->setInputVerifier(sysAddressValidator);
 if (prefixBox->getSelectedItem() == nullptr) {
     prefixBox->setSelectedIndex(0);
 }
 //prefixBox.addActionListener((evt) -> {
 connect(prefixBox, &ManagerComboBox::currentIndexChanged, [=]{
     Manager/*<?>*/* manager = prefixBox->getSelectedItem();
     if (manager != nullptr) {
         sysAddress->setText("");     // Reset saved text before switching managers
         sysAddressValidator->setManager(manager);
     }
 });
 //sysAddressValidator->addPropertyChangeListener("validation", (evt) -> { // NOI18N
#if 0
 connect(sysAddressValidator, &SystemNameValidator::propertyChange(PropertyChangeEvent*), [=] {
     Validation validation = sysAddressValidator.getValidation();
     Validation.Type type = validation.getType();
     addButton.setEnabled(type != Validation.Type.WARNING && type != Validation.Type.DANGER);
     setStatusBarText(validation.getMessage());
 });
#endif
 sysAddressValidator->setManager(prefixBox->getSelectedItem());
 sysAddressValidator->verify(sysAddress);
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
