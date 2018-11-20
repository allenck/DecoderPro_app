#include "addnewdevicepanel.h"
#include "jtextfield.h"
#include <QGridLayout>
#include "gridbagconstraints.h"
#include <QPushButton>
#include <QLabel>
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
 sysNameLabel = new QLabel(tr("System Name:"));
 userNameLabel = new QLabel(tr("User Name:"));

 sysName = sys;
 setLayout(new QVBoxLayout(this));
 QWidget* p;
 p = new QWidget();
 //p.setLayout(new FlowLayout());
 QGridLayout* g;
 p->setLayout(g = new QGridLayout());
 GridBagConstraints* c = new GridBagConstraints();
 c->gridwidth  = 1;
 c->gridheight = 1;
 c->gridx = 0;
 c->gridy = 0;
 c->anchor = GridBagConstraints::EAST;
 g->addWidget(sysNameLabel,c->gridy, c->gridx, 1,1);
 c->gridy = 1;
 g->addWidget(userNameLabel,c->gridy, c->gridx, 1,1);
 c->gridx = 1;
 c->gridy = 0;
 c->anchor = GridBagConstraints::WEST;
 c->weightx = 1.0;
 c->fill = GridBagConstraints::HORIZONTAL;  // text field will expand
 g->addWidget(sysName,c->gridy, c->gridx, 1,1);
 c->gridy = 1;
 g->addWidget(userName,c->gridy, c->gridx, 1,1);
 layout()->addWidget(p);
 layout()->addWidget(ok = new QPushButton((addButtonLabel)));
 QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(ok->sizePolicy().hasHeightForWidth());
 ok->setSizePolicy(sizePolicy);
// ok.addActionListener(listener);
 connect(ok, SIGNAL(clicked()), listener, SLOT(actionPerformed()));
 QPushButton* cancel = new QPushButton(tr("Cancel"));
 cancel->setSizePolicy(sizePolicy);
 layout()->addWidget(cancel);
 connect(cancel, SIGNAL(clicked()), cancelListener, SLOT(actionPerformed()));
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


