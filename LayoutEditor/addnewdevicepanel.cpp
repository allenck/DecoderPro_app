#include "addnewdevicepanel.h"
#include "jtextfield.h"
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include "jbutton.h"
#include "jlabel.h"
#include "actionlistener.h"

//AddNewDevicePanel::AddNewDevicePanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * JPanel to create a new JMRI devices
 * HiJacked to serve other beantable tables.
 *
 * @author	Bob Jacobsen    Copyright (C) 2009
 * @author  Pete Cressman    Copyright (C) 2010
 * @version     $Revision: 17977 $
 */

///*public*/ class AddNewDevicePanel extends jmri.util.swing.JmriPanel {

/*public*/ AddNewDevicePanel::AddNewDevicePanel(JTextField* sys, JTextField* userName,QString addButtonLabel, ActionListener* listener, ActionListener* cancelListener, QWidget *parent) : JmriPanel(parent)
{
 sysName = sys;
 setLayout(new QVBoxLayout(/*this*/));
 JPanel* p;
 p = new JPanel();
 //p.setLayout(new FlowLayout());
 GridBagLayout* g;
 p->setLayout(g = new GridBagLayout());
 GridBagConstraints c =  GridBagConstraints();
 c.gridwidth  = 1;
 c.gridheight = 1;
 c.gridx = 0;
 c.gridy = 0;
 c.anchor = GridBagConstraints::EAST;
 g->addWidget(sysNameLabel,c);
 c.gridy = 1;
 g->addWidget(userNameLabel,c);
 c.gridx = 1;
 c.gridy = 0;
 c.anchor = GridBagConstraints::WEST;
 c.weightx = 1.0;
 c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
 g->addWidget(sysName,c);
 c.gridy = 1;
 g->addWidget(userName,c);
 layout()->addWidget(p);
 ((QVBoxLayout*)layout())->addWidget(ok = new QPushButton((addButtonLabel)),0);
// ok.addActionListener(listener);
 connect(ok, SIGNAL(clicked()), listener->self(), SLOT(actionPerformed()));
 QPushButton* cancel = new QPushButton(tr("Cancel"));
 ((QVBoxLayout*)layout())->addWidget(cancel, 0);
 connect(cancel, SIGNAL(clicked()), cancelListener->self(), SLOT(actionPerformed()));
// ok.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            reset();
//        }
// });
 connect(ok,SIGNAL(clicked()), this, SLOT(reset()));
 reset();
// sysName.addKeyListener(new KeyAdapter() {
//        /*public*/ void keyReleased(KeyEvent a){
//            if (sysName.getText().length() > 0) {
//                ok.setEnabled(true);
//                ok.setToolTipText(null);
//            }
//        }
//    });
 connect(sysName, SIGNAL(textEdited(QString)), this, SLOT(sysName_textEdited(QString)));
}
void AddNewDevicePanel::sysName_textEdited(QString txt)
{
 if (txt.length() > 0)
 {
  ok->setEnabled(true);
  ok->setToolTip("");
 }
}

void AddNewDevicePanel::reset() {
    ok->setEnabled(false);
    ok->setToolTip(tr("This button will be active after you type text into the text box"));
}
/**
 * Activate the OK button without user key activity.
 */
/*public*/ void AddNewDevicePanel::setOK() {
    ok->setEnabled(true);
    ok->setToolTip("");
}

/**
 * Lock the System Name JTextField.
 */
/*public*/ void AddNewDevicePanel::setSystemNameFieldIneditable() {
    sysName->setEnabled(false);
//    sysName.setBorder(null);
//    sysName->setDisabledTextColor(QColor(Qt::black));
}

/*public*/ void AddNewDevicePanel::addLabels(QString labelSystemName, QString labelUserName) {
        sysNameLabel->setText(labelSystemName);
        userNameLabel->setText(labelUserName);
}


