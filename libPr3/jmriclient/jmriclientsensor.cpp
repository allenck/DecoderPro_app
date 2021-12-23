#include "jmriclientsensor.h"
#include "loggerfactory.h"
#include "jmriclienttrafficcontroller.h"
#include "jmriclientreply.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclientmessage.h"
#include "jmriclientlistener.h"

/**
 * JMRIClient implementation of the Sensor interface.
 * <P>
 *
 * Description: extend jmri.AbstractSensor for JMRIClient layouts
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2008
 * @author Paul Bender Copyright (C) 2010
 */
///*public*/ class JMRIClientSensor extends AbstractSensor implements JMRIClientListener {


/**
 * JMRIClient sensors use the sensor number on the remote host.
 */
/*public*/ JMRIClientSensor::JMRIClientSensor(int number, JMRIClientSystemConnectionMemo* memo, QObject *parent)
 : AbstractSensor(memo->getSystemPrefix() + "S" + number)
{
    //super(memo.getSystemPrefix() + "S" + number);
    _number = number;
    transmitName = memo->getTransmitPrefix() + "S" + QString::number(number);
    tc = memo->getJMRIClientTrafficController();
    // At construction, register for messages
    tc->addJMRIClientListener((JMRIClientListener*)this);
    // Then request status.
    requestUpdateFromLayout();
}

/*public*/ int JMRIClientSensor::getNumber() {
    return _number;
}

// Handle a request to change state by sending a formatted packet
// to the server.
//@Override
/*public*/ void JMRIClientSensor::setKnownState(int s) /*throw (JmriException)*/ {
    // sort out states
    if ((s & Sensor::ACTIVE) != 0) {
        // first look for the double case, which we can't handle
        if ((s & Sensor::INACTIVE) != 0) {
            // this is the disaster case!
            log->error("Cannot command both ACTIVE and INACTIVE " + s);
            return;
        } else {
            // send an ACTIVE command
            sendMessage(true ^ getInverted());
        }
    } else {
        // send a INACTIVE command
        sendMessage(false ^ getInverted());
    }
    if (_knownState != s) {
        int oldState = _knownState;
        _knownState = s;
        firePropertyChange("KnownState", (oldState), (_knownState));
    }
}

//@Override
/*public*/ void JMRIClientSensor::requestUpdateFromLayout()const {
    // get the message text
    QString text = "SENSOR " + transmitName + "\n";

    // create and send the message itself
    tc->sendJMRIClientMessage(new JMRIClientMessage(text), (JMRIClientListener*)this);
}

/*protected*/ void JMRIClientSensor::sendMessage(bool active) {
    // get the message text
    QString text;
    if (active) {
        text = "SENSOR " + transmitName + " ACTIVE\n";
    } else // thrown
    {
        text = "SENSOR " + transmitName + " INACTIVE\n";
    }

    // create and send the message itself
    tc->sendJMRIClientMessage(new JMRIClientMessage(text), (JMRIClientListener*)this);
}

// to listen for status changes from JMRIClient system
//@Override
/*public*/ void JMRIClientSensor::reply(JMRIClientReply* m) {
    QString message = m->toString();
    log->debug("Message Received: " + m->toString());
    if (!message.contains(transmitName + " ")) {
        return; // not for us
    }
    if (m->toString().contains("INACTIVE")) {
        setOwnState(!getInverted() ? Sensor::INACTIVE : Sensor::ACTIVE);
    } else if (m->toString().contains("ACTIVE")) {
        setOwnState(!getInverted() ? Sensor::ACTIVE : Sensor::INACTIVE);
    } else {
        setOwnState(Sensor::UNKNOWN);
    }
}

//@Override
/*public*/ void JMRIClientSensor::message(JMRIClientMessage* /*m*/) {
}

/*private*/ /*final*/ /*static*/ Logger* JMRIClientSensor::log = LoggerFactory::getLogger("JMRIClientSensor");

