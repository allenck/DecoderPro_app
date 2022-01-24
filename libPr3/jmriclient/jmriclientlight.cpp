#include "jmriclientlight.h"
#include "loggerfactory.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclienttrafficcontroller.h"
#include "jmriclientmessage.h"
#include "jmriclientreply.h"
#include "jmriclientmessage.h"

/**
 * JMRIClient implementation of the Light interface.
 * <P>
 *
 * Description: extend jmri.AbstractLight for JMRIClient layouts
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2008
 * @author Paul Bender Copyright (C) 2010
 */
// /*public*/ class JMRIClientLight extends AbstractLight implements JMRIClientListener {


/**
 * JMRIClient lights use the light number on the remote host.
 */
/*public*/ JMRIClientLight::JMRIClientLight(int number, JMRIClientSystemConnectionMemo* memo, QObject* parent)
 : AbstractLight(memo->getSystemPrefix() + "l" + QString::number(number), parent)
{
    //super(memo.getSystemPrefix() + "l" + number);
    _number = number;
    transmitName = memo->getTransmitPrefix() + "L" + QString::number(number);
    tc = memo->getJMRIClientTrafficController();
    // At construction, register for messages
    tc->addJMRIClientListener((JMRIClientListener*)this);
    // then request status
    requestUpdateFromLayout();
}

/*public*/ int JMRIClientLight::getNumber() {
    return _number;
}

//request a status update from the layout
//@Override
/*public*/ void JMRIClientLight::requestUpdateFromLayout() {
    // create the message
    QString text = "LIGHT " + transmitName + "\n";
    // create and send the message
    tc->sendJMRIClientMessage(new JMRIClientMessage(text), (JMRIClientListener*)this);
}

// Handle a request to change state by sending a formatted packet
// to the server.
//@Override
/*public*/ /*synchronized*/ void JMRIClientLight::doNewState(int oldState, int s) {
    if (oldState == s) {
        return; //no change, just quit.
    }  // sort out states
    if ((s & Light::ON) != 0) {
        // first look for the double case, which we can't handle
        if ((s & Light::OFF) != 0) {
            // this is the disaster case!
            log->error("Cannot command both ON and OFF " + s);
            return;
        } else {
            // send a ON command
            sendMessage(true);
        }
    } else {
        // send a OFF command
        sendMessage(false);
    }

    notifyStateChange(oldState, s);

}

/*protected*/ void JMRIClientLight::sendMessage(bool on) {
    // get the message text
    QString text;
    if (on) {
        text = "LIGHT " + transmitName + " ON\n";
    } else // thrown
    {
        text = "LIGHT " + transmitName + " OFF\n";
    }

    // create and send the message itself
    tc->sendJMRIClientMessage(new JMRIClientMessage(text), (JMRIClientListener*)this);
}

// to listen for status changes from JMRIClient system
//@Override
/*public*/ /*synchronized*/ void JMRIClientLight::reply(JMRIClientReply* m) {
    QString message = m->toString();
    if (!message.contains(transmitName + " ")) {
        return; // not for us
    }
    if (m->toString().contains("OFF")) {
        notifyStateChange(mState, Light::OFF);
    } else if (m->toString().contains("ON")) {
        notifyStateChange(mState, Light::ON);
    } else {
        notifyStateChange(mState, Light::UNKNOWN);
    }
}

//@Override
/*public*/ void JMRIClientLight::message(JMRIClientMessage* m) {
}

/*private*/ /*final*/ /*static*/ Logger* JMRIClientLight::log = LoggerFactory::getLogger("JMRIClientLight");
