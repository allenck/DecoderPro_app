#include "simpleturnoutctrlframe.h"
#include "jtextfield.h"
#include <QPushButton>
#include <QLabel>
#include "instancemanager.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include "gridbagconstraints.h"
#include <QGroupBox>
#include "level.h"
#include "userpreferencesmanager.h"
#include "exceptions.h"

//SimpleTurnoutCtrlFrame::SimpleTurnoutCtrlFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Frame controlling a single turnout
 * @author	Bob Jacobsen   Copyright (C) 2001
 * @version     $Revision: 17977 $
 */
// /*public*/ class SimpleTurnoutCtrlFrame extends jmri.util.JmriJFrame implements java.beans.PropertyChangeListener {

    /*private static final*/ QString SimpleTurnoutCtrlFrame::LOCKED = "Locked";
    /*private static final*/ QString SimpleTurnoutCtrlFrame::UNLOCKED = "Normal";


/*public*/ SimpleTurnoutCtrlFrame::SimpleTurnoutCtrlFrame(QWidget *parent) :
JmriJFrame(parent)
{
 //super();
 log = new Logger("SimpleTurnoutCtrlFrame");
 // GUI member declarations
 adrTextField = new JTextField(16);
 connect(adrTextField, SIGNAL(textEdited(QString)), this, SLOT(on_adrTextField_textEdited(QString)));
 connect(adrTextField, SIGNAL(editingFinished()), this, SLOT(on_adrTextField_editingFinished()));

 throwButton = new QPushButton();
 closeButton = new QPushButton();

 nowStateLabel = new QLabel();

 nowFeedbackLabel = new QLabel();

 lockButtonLabel = new QLabel();
 lockButton = new QPushButton();

 lockPushButtonLabel = new QLabel();
 lockPushButton = new QPushButton();

 turnout = NULL;
 newState = "";

 // configure items for GUI
 resize(300,400);
 adrTextField->setText("");
 adrTextField->setVisible(true);
 adrTextField->setToolTip(tr("turnout number being controlled"));
 connect(adrTextField, SIGNAL(editingFinished()), this, SLOT(on_adrTextField_editingFinished()));
 throwButton->setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText());
 throwButton->setVisible(true);
 throwButton->setToolTip(tr("Press to set turnout '")+
        ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText()+"'");
// throwButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                throwButtonActionPerformed(e);
//            }
//        });
 connect(throwButton, SIGNAL(clicked()), this, SLOT(throwButtonActionPerformed()));

 closeButton->setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText());
 closeButton->setVisible(true);
 closeButton->setToolTip("Press to set turnout '"+  ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText()+"'");
//    closeButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                closeButtonActionPerformed(e);
//            }
//        });
 connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonActionPerformed()));

 nowStateLabel->setText("<unknown>");
    nowStateLabel->setVisible(true);

    nowFeedbackLabel->setText("<unknown>");
    nowFeedbackLabel->setVisible(true);

    lockButtonLabel->setText("Cab operation: ");
    lockButtonLabel->setVisible(true);

    lockButton->setText(UNLOCKED);
    lockButton->setVisible(true);
    lockButton->setEnabled(false);
    lockButton->setToolTip ("When locked, turnout can not be changed by cabs");
//    lockButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            lockButtonActionPerformed(e);
//        }
//    });
    connect(lockButton, SIGNAL(clicked()), this, SLOT(lockButtonActionPerformed()));

    lockPushButtonLabel->setText("Pushbuttons: ");
    lockPushButtonLabel->setVisible(true);

    lockPushButton->setText(UNLOCKED);
    lockPushButton->setVisible(true);
    lockPushButton->setEnabled(false);
    lockPushButton->setToolTip ("When locked, turnout pushbuttons are disabled");
//    lockPushButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            lockPushButtonActionPerformed(e);
//        }
//    });
    connect(lockPushButton, SIGNAL(clicked()), this, SLOT(lockPushButtonActionPerformed()));

    // general GUI config
    setTitle("Turnout Control");
    getContentPane()->setLayout(new QVBoxLayout(getContentPane()/*,BoxLayout.Y_AXIS*/));
    GridBagConstraints c;// = GridBagConstraints();
    c.gridwidth  = 1;
    c.gridheight = 1;
    c.weightx = 1.0;

    // install items in GUI
    QGroupBox* tPanel = new QGroupBox();
    QGridLayout* g;
    tPanel->setLayout(g = new QGridLayout());
    //tPanel.setBorder(BorderFactory.createTitledBorder("Turnout"));
    tPanel->setTitle(tr("Turnout"));

    c.gridx = 0;
    c.gridy = 0;
    c.anchor = GridBagConstraints::EAST;
    g->addWidget(adrTextField, c.gridy, c.gridx, c.rowSpan(), c.colSpan());

    c.gridx = 0;
    c.gridy = 1;
    c.anchor = GridBagConstraints::EAST;
    g->addWidget(throwButton,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
    c.gridx = 2;
    c.anchor = GridBagConstraints::WEST;
    g->addWidget(closeButton,c.gridy, c.gridx, c.rowSpan(), c.colSpan());

    QGroupBox* sPanel = new QGroupBox();
    QGridLayout* g2;
    sPanel->setLayout(g2 = new QGridLayout());
    //sPanel.setBorder(BorderFactory.createTitledBorder("Current State"));
    sPanel->setTitle("CurrentState");

    g2->addWidget(nowStateLabel);

    QGroupBox* fPanel = new QGroupBox();
    QGridLayout* g3;
    fPanel->setLayout(g3 = new QGridLayout());
    //fPanel.setBorder(BorderFactory.createTitledBorder("Feedback Mode"));
    fPanel->setTitle("Feedback Mode");

    g3->addWidget(nowFeedbackLabel);

    QGroupBox* avPanel = new QGroupBox();
    QGridLayout* g4;
    avPanel->setLayout(g4 = new QGridLayout());
    //avPanel.setBorder(BorderFactory.createTitledBorder("Advanced Features"));
    avPanel->setTitle("Advanced Features");

    c.gridx = 0;
    c.gridy = 5;
    c.anchor = GridBagConstraints::EAST;
    g4->addWidget(lockButtonLabel,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
    c.gridx = 1;
    c.anchor = GridBagConstraints::WEST;
    g4->addWidget(lockButton,c.gridy, c.gridx, c.rowSpan(), c.colSpan());

    c.gridx = 0;
    c.gridy = 6;
    c.anchor = GridBagConstraints::EAST;
    g4->addWidget(lockPushButtonLabel,c.gridy, c.gridx, c.rowSpan(), c.colSpan());
    c.gridx = 1;
    c.anchor = GridBagConstraints::WEST;
    g4->addWidget(lockPushButton,c.gridy, c.gridx, c.rowSpan(), c.colSpan());

    getContentPane()->layout()->addWidget(tPanel);
    getContentPane()->layout()->addWidget(sPanel);
    getContentPane()->layout()->addWidget(fPanel);
    getContentPane()->layout()->addWidget(avPanel);

    // add help menu to window
    addHelpMenu("package.jmri.jmrit.simpleturnoutctrl.SimpleTurnoutCtrl", true);

    pack();
}

/*public*/ void SimpleTurnoutCtrlFrame::closeButtonActionPerformed(JActionEvent* /*e*/)
{
 // load address from switchAddrTextField
 try {
 if (turnout != NULL)
  turnout->removePropertyChangeListener((PropertyChangeListener*)this);
//     disconnect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 turnout = (AbstractTurnout*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(adrTextField->text());

 if (turnout == NULL)
 {
  log->error("Turnout " + adrTextField->text()
                    + " is not available");
 }
 else
 {
  turnout->addPropertyChangeListener((PropertyChangeListener*)this);
//  connect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  updateTurnoutStatusFields();
  if (turnout->getCommandedState() == Turnout::CLOSED)
  {
   nowStateLabel->setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText());
  }
  if (log->isDebugEnabled())
                log->debug("about to command CLOSED");
            // and set commanded state to CLOSED
            turnout->setCommandedState(Turnout::CLOSED);
        }
    } catch (IllegalArgumentException ex1) {
        invalidTurnout(adrTextField->text(), ex1);
    } catch (Exception ex2) {
        log->error("exception during closeButtonActionPerformed", ex2);
        nowStateLabel->setText("ERROR");
        nowFeedbackLabel->setText("<unknown>");
    }
}

/*public*/ void SimpleTurnoutCtrlFrame::throwButtonActionPerformed(JActionEvent* /*e*/) {
    // load address from switchAddrTextField
    try {
        if (turnout != NULL)
            turnout->removePropertyChangeListener((PropertyChangeListener*)this);
//            disconnect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

        turnout = (AbstractTurnout*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(
                adrTextField->text());

        if (turnout == NULL) {
            log->error("Turnout " + adrTextField->text()
                    + " is not available");
        } else {
            turnout->addPropertyChangeListener((PropertyChangeListener*)this);
//            connect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

            updateTurnoutStatusFields();
            if (turnout->getCommandedState() == Turnout::THROWN) {
                nowStateLabel->setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText());
            }
            if (log->isDebugEnabled())
                log->debug("about to command THROWN");
            // and set commanded state to THROWN
            turnout->setCommandedState(Turnout::THROWN);
        }
    } catch (IllegalArgumentException ex1) {
        invalidTurnout(adrTextField->text(), ex1);
    } catch (Exception ex2) {
        log->error("exception during throwButtonActionPerformed", ex2);
        nowStateLabel->setText("ERROR");
        nowFeedbackLabel->setText("<unknown>");
    }
}

/*public*/ void SimpleTurnoutCtrlFrame::lockButtonActionPerformed(JActionEvent* /*e*/) {
    // load address from switchAddrTextField
    try {
        if (turnout != NULL)
            turnout->removePropertyChangeListener((PropertyChangeListener*)this);
//            disconnect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

        turnout = (AbstractTurnout*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(
                adrTextField->text());

        if (turnout == NULL) {
            log->error("Turnout " + adrTextField->text()
                    + " is not available");
        } else {
            turnout->addPropertyChangeListener((PropertyChangeListener*)this);
//            connect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

            updateTurnoutStatusFields();

            if (lockButton->text() == LOCKED) {
                turnout->setLocked(Turnout::CABLOCKOUT, false);
            } else if (turnout->canLock(Turnout::CABLOCKOUT)) {
                turnout->setLocked(Turnout::CABLOCKOUT, true);
            }
        }
    } catch (IllegalArgumentException ex1) {
        invalidTurnout(adrTextField->text(), ex1);
    } catch (Exception ex2) {
        log->error("exception during lockButtonActionPerformed", ex2);
        nowStateLabel->setText("ERROR");
        nowFeedbackLabel->setText("<unknown>");
    }
}

/*public*/ void SimpleTurnoutCtrlFrame::lockPushButtonActionPerformed(JActionEvent* /*e*/) {
    // load address from switchAddrTextField
    try {
        if (turnout != NULL)
            turnout->removePropertyChangeListener((PropertyChangeListener*)this);
//            disconnect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

        turnout = (AbstractTurnout*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(
                adrTextField->text());

        if (turnout == NULL) {
            log->error("Turnout " + adrTextField->text()
                    + " is not available");
        } else {
            turnout->addPropertyChangeListener((PropertyChangeListener*)this);
//            connect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

            updateTurnoutStatusFields();

            if (lockPushButton->text() == LOCKED) {
                turnout->setLocked(Turnout::PUSHBUTTONLOCKOUT, false);
            } else if (turnout->canLock(Turnout::PUSHBUTTONLOCKOUT)) {
                turnout->setLocked(Turnout::PUSHBUTTONLOCKOUT, true);
            }

        }
    } catch (IllegalArgumentException ex1) {
        invalidTurnout(adrTextField->text(), ex1);
    } catch (Exception ex2) {
        log->error("exception during lockPushButtonActionPerformed", ex2);
        nowStateLabel->setText("ERROR");
        nowFeedbackLabel->setText("<unknown>");
    }
}


// update state field in GUI as state of turnout changes
/*public*/ void SimpleTurnoutCtrlFrame::propertyChange(PropertyChangeEvent* e) {
    // If the Commanded State changes, show transition state as "<inconsistent>"
    if (e->getPropertyName()==("CommandedState")){
        nowStateLabel->setText("<inconsistent>");
    }
    if (e->getPropertyName()==("KnownState")) {
        int now =  e->getNewValue().toInt();
        switch (now) {
        case Turnout::UNKNOWN:
            nowStateLabel->setText("<unknown>");
            return;
        case Turnout::CLOSED:
            nowStateLabel->setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText());
            return;
        case Turnout::THROWN:
            nowStateLabel->setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText());
            return;
        default:
            nowStateLabel->setText("<inconsistent>");
            return;
        }
    }
    if (e->getPropertyName()==("locked")) {
        if (turnout->canLock(Turnout::CABLOCKOUT)) {
            if (turnout->getLocked(Turnout::CABLOCKOUT)) {
                lockButton->setText(LOCKED);
            } else {
                lockButton->setText(UNLOCKED);
            }
            lockButton->setEnabled(true);
        } else {
            lockButton->setText(UNLOCKED);
            lockButton->setEnabled(false);
        }
        if (turnout->canLock(Turnout::PUSHBUTTONLOCKOUT)) {
            if (turnout->getLocked(Turnout::PUSHBUTTONLOCKOUT)) {
                lockPushButton->setText(LOCKED);
            } else {
                lockPushButton->setText(UNLOCKED);
            }
            lockPushButton->setEnabled(true);
        } else {
            lockPushButton->setText(UNLOCKED);
            lockPushButton->setEnabled(false);
        }
    }
    if (e->getPropertyName()==("feedbackchange")) {
        updateTurnoutStatusFields();
    }
 }

/*private*/ void SimpleTurnoutCtrlFrame::updateTurnoutStatusFields()
{
    nowFeedbackLabel->setText (turnout->getFeedbackModeName());
    if (turnout->canLock(Turnout::CABLOCKOUT)) {
        if (turnout->getLocked(Turnout::CABLOCKOUT)){
            lockButton->setText(LOCKED);
        }else{
            lockButton->setText(UNLOCKED);
        }
        lockButton->setEnabled(true);
    } else {
        lockButton->setText(UNLOCKED);
        lockButton->setEnabled(false);
    }
    if (turnout->canLock(Turnout::PUSHBUTTONLOCKOUT)) {
        if (turnout->getLocked(Turnout::PUSHBUTTONLOCKOUT)){
            lockPushButton->setText(LOCKED);
        }else{
            lockPushButton->setText(UNLOCKED);
        }
        lockPushButton->setEnabled(true);
    } else {
        lockPushButton->setText(UNLOCKED);
        lockPushButton->setEnabled(false);
    }
    int knownState = turnout->getKnownState();
    switch (knownState) {
    case Turnout::UNKNOWN:
        nowStateLabel->setText("<unknown>");
        return;
    case Turnout::CLOSED:
        nowStateLabel->setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText());
        return;
    case Turnout::THROWN:
        nowStateLabel->setText(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText());
        return;
    default:
        nowStateLabel->setText("<inconsistent>");
        return;
    }
  }

void SimpleTurnoutCtrlFrame::invalidTurnout(QString name, Exception ex) {
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->showInfoMessage("Error",
    "Unable to convert \"" + name + "\" to a valid hardware address", ex.getMessage(), "", true, false);
}


//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SimpleTurnoutCtrlFrame.class.getName());

void SimpleTurnoutCtrlFrame::on_adrTextField_editingFinished()
{
 nowStateLabel->setText("<unknown>");
 nowFeedbackLabel->setText("<unknown>");
 lockButtonLabel->setText("Cab operation: ");
 lockButton->setText(UNLOCKED);
 turnout = (AbstractTurnout*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(adrTextField->text());

 if (turnout == NULL)
 {
  log->error("Turnout " + adrTextField->text()
             + " is not available");
 }
 else
  updateTurnoutStatusFields();
}
void SimpleTurnoutCtrlFrame::on_adrTextField_textEdited(QString text)
{
 QCompleter* completer = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getCompleter(text);
 if(completer!= NULL)
  adrTextField->setCompleter(completer);
}

/*public*/ QString SimpleTurnoutCtrlFrame::getClassName()
{
 return "jmri.jmrit.simpleturnoutctrl.SimpleTurnoutCtrlFrame";
}
