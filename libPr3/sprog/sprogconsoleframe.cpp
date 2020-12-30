#include "sprogconsoleframe.h"
#include "loggerfactory.h"
#include <QGroupBox>
#include "sprogversionquery.h"
#include "jtextfield.h"
#include "flowlayout.h"
#include <QPushButton>
#include <QCheckBox>
#include "joptionpane.h"
#include "sprogreply.h"

using namespace Sprog;

/**
 * Frame for Sprog Console
 *
 * Updated Jan 2010 by Andrew Berridge - fixed errors caused by trying to send
 * some commands while slot manager is active
 *
 * Updated April 2016 by Andrew Crosland - remove the checks on slot manager
 * status, implement a timeout and look for the correct replies which may be
 * delayed by replies for slot manager.
 *
 * Refactored, I18N
 *
 * @author	Andrew Crosland Copyright (C) 2008, 2016
 */
// /*public*/ class SprogConsoleFrame extends jmri.jmrix.AbstractMonFrame implements SprogListener, SprogVersionListener {



    /*public*/ SprogConsoleFrame::SprogConsoleFrame(SprogSystemConnectionMemo* memo, QWidget* parent) : AbstractMonFrame(parent)
{
        //super();
 setObjectName("SprogConsoleFrame");
 // member declarations
 cmdLabel = new QLabel();
 currentLabel = new QLabel();
 sendButton = new QPushButton();
 saveButton = new QPushButton();
 cmdTextField = new JTextField(12);
 currentTextField = new JTextField(12);

 ztcCheckBox = new QCheckBox();
 blueCheckBox = new QCheckBox();
 unlockCheckBox = new QCheckBox();

 speedGroup = new QButtonGroup();
 speedLabel = new QLabel();
 speed14Button = new QRadioButton(tr("%1 step").arg(14)); // i18n using shared sprogBundle
 speed28Button = new QRadioButton(tr("%1 step").arg(28));
 speed128Button = new QRadioButton(tr("%1 step").arg(128));

 currentLimit = SprogConstants::DEFAULT_I;

        // members for handling the SPROG interface
 tc = NULL;
 tmpString = "";
 state = State::IDLE;
 TIMEOUT = 1000;
 timer = NULL;

 _memo = memo;
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ QString SprogConsoleFrame::title() {
    return tr("SPROG Console");
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void SprogConsoleFrame::init() {
    // connect to TrafficController
    tc = _memo->getSprogTrafficController();
    tc->addSprogListener((SprogListener*)this);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void SprogConsoleFrame::dispose() {
    tc->removeSprogListener((SprogListener*)this);
    AbstractMonFrame::dispose();
}

/**
 * {@inheritDoc}
 */
//@SuppressFBWarnings(value = "IS2_INCONSISTENT_SYNC")
// Ignore unsynchronized access to state
//@Override

/*public*/ void SprogConsoleFrame::initComponents() throw (Exception)
{
 //SprogMessage msg;
 AbstractMonFrame::initComponents();

 QVBoxLayout* contentPaneLayout = (QVBoxLayout*)getContentPane()->layout();

 // Add a nice border to super class
// TODO:       super.jScrollPane1.setBorder(BorderFactory.createTitledBorder(
//                BorderFactory.createEtchedBorder(), tr("CommandHistoryTitle")));

 // Let user press return to enter message
// entryField.addActionListener((java.awt.event.ActionEvent e) -> {
//     enterButtonActionPerformed(e);
// });
 connect(entryField, SIGNAL(editingFinished()), this,  SLOT(enterButtonActionPerformed()));
 connect(entryField, SIGNAL(leaveField()), this, SLOT(enterButtonActionPerformed()));

 /*
  * Command panel
  */
 QGroupBox* cmdPane1 = new QGroupBox();
// cmdPane1.setBorder(BorderFactory.createTitledBorder(
//         BorderFactory.createEtchedBorder(), tr("Send SPROG Command")));
 FlowLayout* cmdPane1Layout;
 cmdPane1->setLayout(cmdPane1Layout = new FlowLayout());

 cmdLabel->setText(tr("Command"));
 cmdLabel->setVisible(true);

 sendButton->setText(tr("Send"));
 sendButton->setVisible(true);
 sendButton->setToolTip(tr("Send Packet to SPROG"));

 cmdTextField->setText("");
 cmdTextField->setToolTip(tr("Enter a SPROG command and click [%1]").arg(tr("Send")));
 cmdTextField->setMaximumSize(
         QSize(cmdTextField->maximumSize().width(),
                 cmdTextField->sizeHint().height())
 );

// cmdTextField.addActionListener((java.awt.event.ActionEvent e) -> {
//     sendButtonActionPerformed(e);
// });
connect(cmdTextField, SIGNAL(editingFinished()), this, SLOT(sendButtonActionPerformed()));
connect(cmdTextField, SIGNAL(leaveField()), this, SLOT(sendButtonActionPerformed()));

// sendButton.addActionListener((java.awt.event.ActionEvent e) -> {
//     sendButtonActionPerformed(e);
// });
connect(sendButton, SIGNAL(clicked()), this, SLOT(sendButtonActionPerformed()));

 cmdPane1Layout->addWidget(cmdLabel);
 cmdPane1Layout->addWidget(cmdTextField);
 cmdPane1Layout->addWidget(sendButton);

 contentPaneLayout->addWidget(cmdPane1);

 /*
  * Speed Step Panel
  */
 QGroupBox* speedPanel = new QGroupBox();
 FlowLayout* speedPanelLayout = new FlowLayout(speedPanel);
 //speedPanel.setBorder(BorderFactory.createEtchedBorder());
 speedLabel->setText(tr("SPROG Throttle Speed Step Mode:"));
 speedPanelLayout->addWidget(speedLabel);
 speedPanelLayout->addWidget(speed14Button);
 speedPanelLayout->addWidget(speed28Button);
 speedPanelLayout->addWidget(speed128Button);
 speedGroup->addButton(speed14Button);
 speedGroup->addButton(speed28Button);
 speedGroup->addButton(speed128Button);
 speed14Button->setToolTip(tr("Set %1 speed steps for SPROG throttle").arg(14));
 speed28Button->setToolTip(tr("Set %1 speed steps for SPROG throttle").arg(28));
 speed128Button->setToolTip(tr("Set %1 speed steps for SPROG throttle").arg(128));

 /*
  * Configuration panel
  */
 QWidget* configPanel = new QWidget();
 FlowLayout* configPanelLayout = new FlowLayout(configPanel);
 // *** Which versions support current limit ???
 currentLabel->setText(tr("Current Limit (mA):"));
 currentLabel->setVisible(true);

 currentTextField->setText("");
 currentTextField->setEnabled(false);
 currentTextField->setToolTip(tr("Enter new current limit in milliAmps (less than 1000)"));
 currentTextField->setMaximumSize(
         QSize(currentTextField->maximumSize().width(),
                 currentTextField->sizeHint().height()
         )
 );

 ztcCheckBox->setText(tr("Set ZTC mode"));
 ztcCheckBox->setVisible(true);
 ztcCheckBox->setToolTip(tr("Use this when programming older ZTC decoders"));

 blueCheckBox->setText(tr("Set Blueline mode"));
 blueCheckBox->setVisible(true);
 blueCheckBox->setEnabled(false);
 blueCheckBox->setToolTip(tr("Select this option when programming Blueline decoders - programming will be slower overall"));

 unlockCheckBox->setText(tr("Unlock SPROG firmware"));
 unlockCheckBox->setVisible(true);
 unlockCheckBox->setEnabled(false);
 unlockCheckBox->setToolTip(tr("Use this ONLY if you are about to update the SPROG firmware"));

 configPanelLayout->addWidget(currentLabel);
 configPanelLayout->addWidget(currentTextField);
 configPanelLayout->addWidget(ztcCheckBox);
 configPanelLayout->addWidget(blueCheckBox);
 configPanelLayout->addWidget(unlockCheckBox);

 /*
  * Status Panel
  */
 QGroupBox* statusPanel = new QGroupBox();
// statusPanel.setBorder(BorderFactory.createTitledBorder(
//         BorderFactory.createEtchedBorder(), tr("ConfigurationTitle")));
 statusPanel->setTitle(tr("Configuration"));
 //statusPanel.setLayout(new BoxLayout(statusPanel, BoxLayout.Y_AXIS));
 QVBoxLayout* statusPanelLayout = new QVBoxLayout(statusPanel);

 saveButton->setText(tr("Apply"));
 saveButton->setVisible(true);
 saveButton->setToolTip(tr("Save SPROG configuration (in the SPROG EEPROM)"));

// saveButton.addActionListener((java.awt.event.ActionEvent e) -> {
//     saveButtonActionPerformed(e);
// });
 connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveButtonActionPerformed()));

 statusPanelLayout->addWidget(speedPanel);
 statusPanelLayout->addWidget(configPanel);
 statusPanelLayout->addWidget(saveButton);

 contentPaneLayout->addWidget(statusPanel);

 // pack for display
 pack();
 cmdPane1->setMaximumSize(statusPanel->size());
 statusPanel->setMaximumSize(statusPanel->size());
 pack();

 // Now the GUI is all setup we can get the SPROG version
 _memo->getSprogVersionQuery()->requestVersion((SprogVersionListener*)this);
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void SprogConsoleFrame::setHelp() {
    addHelpMenu("package.jmri.jmrix.sprog.console.SprogConsoleFrame", true);
}

/*public*/ void SprogConsoleFrame::sendButtonActionPerformed(JActionEvent* /*e*/) {
    SprogMessage* m = new SprogMessage(cmdTextField->text());
    // Messages sent by us will not be forwarded back so add to display manually
    nextLine("cmd: \"" + m->toString(_memo->getSprogTrafficController()->isSIIBootMode()) + "\"\n", "");
    tc->sendSprogMessage(m, (SprogListener*)this);
}

/**
 * Validate the current limit value entered by the user, depending on the
 * SPROG version.
 */
//@SuppressFBWarnings(value = "IS2_INCONSISTENT_SYNC")
// validateCurrent() is called from synchronised code
/*public*/ void SprogConsoleFrame::validateCurrent() {
    QString currentRange = "200 - 996";
    int validLimit = 996;
    if (_memo->getSprogVersion()->sprogType->_sprogType > SprogType::SPROGIIv3) {
        currentRange = "200 - 2499";
        validLimit = 2499;
    }
    try {
     bool ok;
        currentLimit = currentTextField->text().toInt(&ok);
        if(!ok) throw NumberFormatException();
    } catch (NumberFormatException e) {
        JOptionPane::showMessageDialog(NULL, tr("CurrentLimitDialogString").arg(currentRange),
                tr("SPROG Console"), JOptionPane::ERROR_MESSAGE);
        currentLimit = validLimit;
        return;
    }
    if ((currentLimit > validLimit) || (currentLimit < 200)) {
        JOptionPane::showMessageDialog(NULL, tr("Invalid Current Limit entered.\nPlease enter a value in the range %1").arg(currentRange),
                tr("SPROG Console"), JOptionPane::ERROR_MESSAGE);
        currentLimit = validLimit;
    }
}

/*synchronized*/ /*public*/ void SprogConsoleFrame::saveButtonActionPerformed(JActionEvent* e)
{
 SprogMessage* saveMsg;
 int currentLimitForHardware;
 // Send Current Limit if possible
 state = State::CURRENTSENT;
 if (isCurrentLimitPossible())
 {
  validateCurrent();
  // Value written is scaled from mA to hardware units
  currentLimitForHardware = (int) (currentLimit * (1/sv->sprogType->getCurrentMultiplier()));
  if (sv->sprogType->_sprogType < SprogType::SPROGIIv3) {
      // Hack for SPROG bug where MSbyte of value must be non-zero
      currentLimitForHardware += 256;
  }
  tmpString = QString::number(currentLimitForHardware);
  saveMsg = new SprogMessage("I " + tmpString);
 }
 else
 {
  // Else send blank message to kick things off
  saveMsg = new SprogMessage(" " + tmpString);
 }
 nextLine("cmd: \"" + saveMsg->toString(_memo->getSprogTrafficController()->isSIIBootMode()) + "\"\n", "");
 tc->sendSprogMessage(saveMsg, (SprogListener*)this);

 // Further messages will be sent from state machine
}

//@SuppressFBWarnings(value = "IS2_INCONSISTENT_SYNC")
// Called from synchronised code
/*public*/ bool SprogConsoleFrame::isCurrentLimitPossible() {
    return sv->hasCurrentLimit();
}

//@SuppressFBWarnings(value = "IS2_INCONSISTENT_SYNC")
// Called from synchronised code
/*public*/ bool SprogConsoleFrame::isBlueLineSupportPossible() {
    return sv->hasBlueLine();
}

//@SuppressFBWarnings(value = "IS2_INCONSISTENT_SYNC")
// Called from synchronised code
/*public*/ bool SprogConsoleFrame::isFirmwareUnlockPossible() {
    return sv->hasFirmwareLock();
}

//@SuppressFBWarnings(value = "IS2_INCONSISTENT_SYNC")
// Called from synchronised code
/*public*/ bool SprogConsoleFrame::isZTCModePossible() {
    return sv->hasZTCMode();
}

/**
 * Handle a SprogVersion notification.
 * <p>
 * Decode the SPROG version and populate the console gui appropriately with
 * the features applicable to the version.
 *
 * @param v The SprogVersion being handled
 */
//@Override
/*synchronized*/ /*public*/ void SprogConsoleFrame::notifyVersion(SprogVersion* v) {
    SprogMessage* msg;
    sv = v;
    // Save it for others
    _memo->setSprogVersion(v);
    if (log->isDebugEnabled()) {
        log->debug(tr("Found: %1").arg(sv->toString()));
    }
    if (sv->sprogType->isSprog() == false) {
        // Didn't recognize a SPROG so check if it is in boot mode already
        JOptionPane::showMessageDialog(NULL, tr("No SPROG prompt found"),
                tr("SPROG Console"), JOptionPane::ERROR_MESSAGE);
    } else {
        if ((sv->sprogType->_sprogType > SprogType::SPROGIIv3) &&(sv->sprogType->_sprogType < SprogType::NANO)) {
            currentTextField->setToolTip(tr("Enter new current limit in milliAmps (less than 2500)"));
        }
        // We know what we're connected to
        setTitle(title() + " - Connected to " + sv->toString());

        // Enable blueline & firmware unlock check boxes
        if (isBlueLineSupportPossible()) {
            if (log->isDebugEnabled()) {
                log->debug("Enable blueline check box");
            }
            blueCheckBox->setEnabled(true);
            if (log->isDebugEnabled()) {
                log->debug((blueCheckBox->isEnabled()?"yes":"no"));
            }
        }
        if (isFirmwareUnlockPossible()) {
            if (log->isDebugEnabled()) {
                log->debug("Enable firmware check box");
            }
            unlockCheckBox->setEnabled(true);
            if (log->isDebugEnabled()) {
                log->debug((unlockCheckBox->isEnabled()?"yes":"no"));
            }
        }

        ztcCheckBox->setEnabled(isZTCModePossible());

        // Get Current Limit if available
        if (isCurrentLimitPossible()) {
            state = State::CURRENTQUERYSENT;
            msg = new SprogMessage(1);
            msg->setOpCode('I');
            nextLine("cmd: \"" + msg->toString() + "\"\n", "");
            tc->sendSprogMessage(msg, (SprogListener*)this);
            startTimer();
        } else {
            // Set default and get the mode word
            currentLimit = (int) (SprogConstants::DEFAULT_I * sv->sprogType->getCurrentMultiplier());
            currentTextField->setText(QString::number(SprogConstants::DEFAULT_I));
            //currentField.setValue(Integer.valueOf(SprogConstants::DEFAULT_I)); // TODO use JSpinner so int
            state = State::MODEQUERYSENT;
            msg = new SprogMessage(1);
            msg->setOpCode('M');
            nextLine("cmd: \"" + msg->toString() + "\"\n", "");
            tc->sendSprogMessage(msg, (SprogListener*)this);
            startTimer();
        }
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ /*synchronized*/ void SprogConsoleFrame::notifyMessage(SprogMessage* l) { // receive a message and log it
    nextLine("cmd: \"" + l->toString(_memo->getSprogTrafficController()->isSIIBootMode()) + "\"\n", "");
}

/**
 * Handle a SprogReply in a console specific way.
 * <p>
 * Parse replies from the SPROG using a state machine to determine what we are
 * expecting in response to commands sent to the SPROG. Extract data to populate
 * various fields in the gui.
 *
 * @param l The SprogReply to be parsed
 */
//@Override
/*public*/ /*synchronized*/ void SprogConsoleFrame::notifyReply(SprogReply* l)
{ // receive a reply message and log it
 SprogMessage* msg;
 int currentLimitFromHardware;
 replyString = l->toString();
 nextLine("rep: \"" + replyString + "\"\n", "");

 // *** Check for error reply
 switch (state)
 {
  case IDLE:
   log->debug("reply in IDLE state: " + replyString);
   break;
  case CURRENTQUERYSENT:
   // Look for an "I=" reply
   log->debug("reply in CURRENTQUERYSENT state: " + replyString);
   if (replyString.contains("I="))
   {
    stopTimer();
    int valueLength = 4;
    if (sv->sprogType->_sprogType >= SprogType::SPROGIIv3)
    {
        valueLength = 6;
    }
    tmpString = replyString.mid(replyString.indexOf("=")
            + 1, replyString.indexOf("=") + valueLength);
    log->debug("Current limit string: " + tmpString);
    try
    {
     bool ok;
     currentLimitFromHardware = tmpString.toInt(&ok);
     if(!ok) throw NumberFormatException();
    }
    catch (NumberFormatException e) {
        JOptionPane::showMessageDialog(NULL, tr("Malformed Reply for current limit"), tr("SPROG Console"), JOptionPane::ERROR_MESSAGE);
        state = State::IDLE;
        return;
    }
    // Value written is scaled from hardware units to mA
    currentLimit = (int)(currentLimitFromHardware * sv->sprogType->getCurrentMultiplier());
    log->debug("Current limit scale factor: " + QString::number(sv->sprogType->getCurrentMultiplier()));
    log->debug("Current limit from hardware: " + QString::number(currentLimitFromHardware) + " scaled to: " + QString::number(currentLimit) + "mA");
    currentTextField->setText(QString::number(currentLimit));
    currentTextField->setEnabled(true);

    // Next get the mode word
    state = State::MODEQUERYSENT;
    msg = new SprogMessage(1);
    msg->setOpCode('M');
    nextLine("cmd: \"" + msg->toString() + "\"\n", "");
    tc->sendSprogMessage(msg, (SprogListener*)this);
    startTimer();
   }
   break;
  case MODEQUERYSENT:
   log->debug("reply in MODEQUERYSENT state: " + replyString);
   if (replyString.contains("M="))
   {
    stopTimer();
    tmpString = replyString.mid(replyString.indexOf("=")
            + 2, /*replyString.indexOf("=") + 6*/4);
    // Value returned is in hex
    try
    {
     bool ok;
      modeWord = tmpString.toInt(&ok,16);
     if(!ok) throw NumberFormatException();
    }
    catch (NumberFormatException e)
    {
        JOptionPane::showMessageDialog(NULL, tr("Malformed Reply for mode word"),
                tr("SPROG Console"), JOptionPane::ERROR_MESSAGE);
        state = State::IDLE;
        return;
    }
    state = State::IDLE;
    // Set Speed step radio buttons, etc., according to mode word
    if ((modeWord & SprogConstants::STEP14_BIT) != 0) {
        speed14Button->setChecked(true);
    } else if ((modeWord & SprogConstants::STEP28_BIT) != 0) {
        speed28Button->setChecked(true);
    } else {
        speed128Button->setChecked(true);
    }
    if ((modeWord & SprogConstants::ZTC_BIT) != 0) {
        ztcCheckBox->setChecked(true);
    }
    if ((modeWord & SprogConstants::BLUE_BIT) != 0) {
        blueCheckBox->setChecked(true);
    }
   }
   break;
  case CURRENTSENT:
   // Any reply will do here
   log->debug("reply in CURRENTSENT state: " + replyString);
   // Get new mode word - assume 128 steps
   modeWord = SprogConstants::STEP128_BIT;
   if (speed14Button->isChecked()) {
       modeWord = modeWord & ~SprogConstants::STEP_MASK | SprogConstants::STEP14_BIT;
   } else if (speed28Button->isChecked()) {
       modeWord = modeWord & ~SprogConstants::STEP_MASK | SprogConstants::STEP28_BIT;
   }

   // ZTC mode
   if (ztcCheckBox->isChecked() == true) {
       modeWord = modeWord | SprogConstants::ZTC_BIT;
   }

   // Blueline mode
   if (blueCheckBox->isChecked() == true) {
       modeWord = modeWord | SprogConstants::BLUE_BIT;
   }

   // firmware unlock
   if (unlockCheckBox->isChecked() == true) {
       modeWord = modeWord | SprogConstants::UNLOCK_BIT;
   }

   // Send new mode word
   state = State::MODESENT;
   msg = new SprogMessage("M " + QString::number(modeWord));
   nextLine("cmd: \"" + msg->toString(_memo->getSprogTrafficController()->isSIIBootMode()) + "\"\n", "");
   tc->sendSprogMessage(msg, (SprogListener*)this);
   break;
  case MODESENT:
   // Any reply will do here
   log->debug("reply in MODESENT state: " + replyString);
   // Write to EEPROM
   state = State::WRITESENT;
   msg = new SprogMessage(QString("W"));
   nextLine("cmd: \"" + msg->toString(_memo->getSprogTrafficController()->isSIIBootMode()) + "\"\n", "");
   tc->sendSprogMessage(msg, (SprogListener*)this);
   break;
  case WRITESENT:
   // Any reply will do here
   log->debug("reply in WRITESENT state: " + replyString);
   // All done
   state = State::IDLE;
   break;
  default:
   log->warn(tr("Unhandled state: %1").arg(state));
   break;
 }
}

/**
 * Internal routine to handle a timeout.
 */
/*synchronized*/ /*protected*/ void SprogConsoleFrame::timeout() {
    JOptionPane::showMessageDialog(NULL, tr("Timeout talking to SPROG"),
            tr("Timeout"), JOptionPane::ERROR_MESSAGE);
    state = State::IDLE;
}

/**
 * Internal routine to start timer to protect the mode-change.
 */
/*protected*/ void SprogConsoleFrame::startTimer() {
    restartTimer(TIMEOUT);
}

/**
 * Internal routine to stop timer, as all is well.
 */
/*protected*/ void SprogConsoleFrame::stopTimer() {
    if (timer != NULL) {
        timer->stop();
    }
}

/**
 * Internal routine to handle timer starts {@literal &} restarts.
 *
 * @param delay milliseconds to delay
 */
/*protected*/ void SprogConsoleFrame::restartTimer(int delay) {
    if (timer == NULL) {
        timer = new QTimer(); //delay, (java.awt.event.ActionEvent e) -> {
//            timeout();
//        });
         connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    }
    timer->stop();
//    timer.setInitialDelay(delay);
    timer->setSingleShot(true);
    timer->start(delay);
}
/*public*/ QString SprogConsoleFrame::getClassName()
{
 return "jmri.jmrix.sprog.console.SprogConsoleFrame";
}

/*private*/ /*final*/ /*static*/ Logger* SprogConsoleFrame::log = LoggerFactory::getLogger("SprogConsoleFrame");


