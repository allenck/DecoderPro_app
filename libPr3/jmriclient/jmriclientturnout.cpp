#include "jmriclientturnout.h"
#include "loggerfactory.h"
#include "jmriclienttrafficcontroller.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclientreply.h"
#include "jmriclientmessage.h"
/**
 * JMRIClient implementation of the Turnout interface.
 * <P>
 *
 * Description: extend jmri.AbstractTurnout for JMRIClient layouts
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2008
 * @author Paul Bender Copyright (C) 2010
 */
// /*public*/ class JMRIClientTurnout extends AbstractTurnout implements JMRIClientListener {


/* Static arrays to hold Lenz specific feedback mode information */
/*static*/ QVector<QString> JMRIClientTurnout::modeNames = QVector<QString>();
/*static*/  QVector<int> JMRIClientTurnout::modeValues = QVector<int>();

/**
 * JMRIClient turnouts use the turnout number on the remote host.
 */
/*public*/ JMRIClientTurnout::JMRIClientTurnout(int number, JMRIClientSystemConnectionMemo* memo, QObject* paent)
 : AbstractTurnout(memo->getSystemPrefix() + "t" + QString::number(number), parent)
{
   // super(memo.getSystemPrefix() + "t" + number);
    _number = number;
    tc = memo->getJMRIClientTrafficController();
    prefix = memo->getSystemPrefix();
    transmitName = memo->getTransmitPrefix() + "T" + QString::number(number);
    /* allow monitoring mode feedback, which is the same
     as direct for this connection (this aids the
     transition from directly connected hardware to remotly
     connected hardware.)*/
    _validFeedbackTypes |= MONITORING;

    // Default feedback mode is MONITORING
    _activeFeedbackType = MONITORING;

    setModeInformation(_validFeedbackNames, _validFeedbackModes);

    // set the mode names and values based on the static values.
    _validFeedbackNames = getModeNames();
    _validFeedbackModes = getModeValues();

    // At construction, register for messages
    tc->addJMRIClientListener((JMRIClientListener*)this);
    // Then request status.
    requestUpdateFromLayout();
}

//Set the mode information for JMRIClient Turnouts.
/*synchronized*/ /*static*/ /*private*/ void JMRIClientTurnout::setModeInformation(QVector<QString> feedbackNames, QVector<int> feedbackModes) {
    // if it hasn't been done already, create static arrays to hold
    // the JMRIClient specific feedback information.
    if (modeNames.isEmpty()) {
        if (feedbackNames.length() != feedbackModes.length()) {
            log->error("int and string feedback arrays different length");
        }
        modeNames = QVector<QString>(feedbackNames.length() + 1);
        modeValues = QVector<int>(feedbackNames.length() + 1);
        for (int i = 0; i < feedbackNames.length(); i++) {
            modeNames.replace(i,feedbackNames[i]);
            modeValues.replace(i, feedbackModes[i]);
        }
        modeNames.replace(feedbackNames.length(),  "MONITORING");
        modeValues.replace(feedbackNames.length(), MONITORING);
    }
}

/*static*/ QVector<int> JMRIClientTurnout::getModeValues() {
    return modeValues;
}

/*static*/ QVector<QString> JMRIClientTurnout::getModeNames() {
    return modeNames;
}

/*public*/ int JMRIClientTurnout::getNumber() {
    return _number;
}

// Handle a request to change state by sending a formatted packet
// to the server.
//@Override
/*protected*/ void JMRIClientTurnout::forwardCommandChangeToLayout(int s) {
    // sort out states
    if ((s & Turnout::CLOSED) != 0) {
        // first look for the double case, which we can't handle
        if ((s & Turnout::THROWN) != 0) {
            // this is the disaster case!
            log->error("Cannot command both CLOSED and THROWN " + s);
            return;
        } else {
            // send a CLOSED command
            sendMessage(true ^ getInverted());
        }
    } else {
        // send a THROWN command
        sendMessage(false ^ getInverted());
    }
}

//@Override
/*public*/ bool JMRIClientTurnout::canInvert() {
    return true;
}

// request a status update from the layout.
//@Override
/*public*/ void JMRIClientTurnout::requestUpdateFromLayout() {
    // create the message
    QString text = "TURNOUT " + transmitName + "\n";
    // create and send the message itself
    tc->sendJMRIClientMessage(new JMRIClientMessage(text), (JMRIClientListener*)this);
    // This will handle ONESENSOR and TWOSENSOR feedback modes.
    AbstractTurnout::requestUpdateFromLayout();
}

//@Override
/*protected*/ void JMRIClientTurnout::turnoutPushbuttonLockout(bool _pushButtonLockout) {
    if (log->isDebugEnabled()) {
        log->debug(tr("Send command to ") + (_pushButtonLockout ? "Lock" : "Unlock") + " Pushbutton " + prefix + QString::number(_number));
    }
}

/*protected*/ void JMRIClientTurnout::sendMessage(bool closed) {
    // get the message text
    QString text;
    if (closed) {
        text = "TURNOUT " + transmitName + " CLOSED\n";
    } else // thrown
    {
        text = "TURNOUT " + transmitName + " THROWN\n";
    }

    // create and send the message itself
    tc->sendJMRIClientMessage(new JMRIClientMessage(text), (JMRIClientListener*)this);
}

// to listen for status changes from JMRIClient system
//@Override
/*public*/ void JMRIClientTurnout::reply(JMRIClientReply* m) {
    QString message = m->toString();
    if (!message.contains(transmitName + " ")) {
        return; // not for us
    }
    if (m->toString().contains("THROWN")) {
        newKnownState(!getInverted() ? Turnout::THROWN : Turnout::CLOSED);
    } else if (m->toString().contains("CLOSED")) {
        newKnownState(!getInverted() ? Turnout::CLOSED : Turnout::THROWN);
    } else {
        newKnownState(Turnout::UNKNOWN);
    }
}

//@Override
/*public*/ void JMRIClientTurnout::message(JMRIClientMessage* /*m*/) {
}

/*private*/ /*final*/ /*static*/ Logger* JMRIClientTurnout::log = LoggerFactory::getLogger("JMRIClientTurnout");
