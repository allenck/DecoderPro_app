#include "addnewdevicepanel.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include "actionlistener.h"
/**
 * JPanel to create a new JMRI devices HiJacked to serve other beantable tables.
 *
 * @author Bob Jacobsen Copyright (C) 2009
 * @author Pete Cressman Copyright (C) 2010
 */
///*public*/ class AddNewDevicePanel extends jmri.util.swing.JmriPanel {

/*public*/ AddNewDevicePanel::AddNewDevicePanel(JTextField* sys, JTextField* userName,
        QString addButtonLabel, ActionListener* okListener, ActionListener* cancelListener, QWidget *parent)
 : QWidget(parent)
{
 sysNameLabel = new QLabel(tr("System Name"));
 userNameLabel = new QLabel(tr("User Name"));

    sysName = sys;
    QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout(this)); //, BoxLayout.Y_AXIS));
    QWidget* p;
    p = new QWidget();
    GridBagLayout* pLayout;
    //p->setLayout(pLayout=new FlowLayout());
    p->setLayout(pLayout = new GridBagLayout());
    GridBagConstraints c =  GridBagConstraints();
    c.gridwidth = 1;
    c.gridheight = 1;
    c.gridx = 0;
    c.gridy = 0;
    c.anchor = GridBagConstraints::EAST;
    pLayout->addWidget(sysNameLabel, c);
    c.gridy = 1;
    pLayout->addWidget(userNameLabel, c);
    c.gridx = 1;
    c.gridy = 0;
    c.anchor = GridBagConstraints::WEST;
    c.weightx = 1.0;
    c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
    pLayout->addWidget(sysName, c);
    c.gridy = 1;
    pLayout->addWidget(userName, c);
    thisLayout->addWidget(p);

    // button(s) at bottom of window
    QWidget* panelBottom = new QWidget();
    FlowLayout* panelBottomLayout;
    panelBottom->setLayout(panelBottomLayout = new FlowLayout());//FlowLayout.TRAILING));
    // only add a Cancel button when the the OKbutton string is OK (so don't show on Picker Panels)
    if (addButtonLabel == ("OK")) {
        panelBottomLayout->addWidget(cancel = new QPushButton(tr("Cancel")));
        connect(cancel, &QPushButton::clicked, [=] { cancelListener->actionPerformed();});
    }

    panelBottomLayout->addWidget(ok = new QPushButton(addButtonLabel));
//    ok->addActionListener(okListener);
    connect(ok, SIGNAL(clicked(bool)), okListener->self(), SLOT(actionPerformed()));
//    ok.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent a) {
//            reset();
//        }
//    });

    thisLayout->addWidget(panelBottom);

    reset();
#if 0
    sysName.addKeyListener(new KeyAdapter() {
        @Override
        /*public*/ void keyReleased(KeyEvent a) {
            if (sysName.getText().length() > 0) {
                setOK();
            }
        }
    });
#endif
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
   // sysName.setBorder(null);
//    sysName.setDisabledTextColor(Color.black);
}

/*public*/ void AddNewDevicePanel::addLabels(QString labelSystemName, QString labelUserName) {
    sysNameLabel->setText(labelSystemName);
    userNameLabel->setText(labelUserName);
}


