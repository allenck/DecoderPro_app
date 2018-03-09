#include "sprogturnout.h"
#include "loggerfactory.h"
#include "nmrapacket.h"

using namespace Sprog;

/**
 * Sprog implementation of the Turnout interface.
 * <P>
 * This object doesn't listen to the Sprog communications. This is because it
 * should be the only object that is sending messages for this turnout; more
 * than one Turnout object pointing to a single device is not allowed.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003, 2005
 * @author J.M. (Mark) Knox Copyright (C) 2005
 */
// /*public*/ class SprogTurnout extends AbstractTurnout {


/**
 * Create a SPROG Turnout object.
 * <p>
 * Sprog turnouts use the NMRA number (0-511) as their numerical
 * identification.
 */
/*public*/ SprogTurnout::SprogTurnout(int number, SprogSystemConnectionMemo* memo, QObject* parent) : AbstractTurnout(memo->getSystemPrefix() + "T" + QString::number(number),parent)
{
    //super(memo.getSystemPrefix() + "T" + number);

    _number = number;
    _memo = memo;
}

/*public*/ int SprogTurnout::getNumber() {
    return _number;
}

/**
 * Handle a request to change state by sending a formatted DCC packet.
 */
//@Override
/*protected*/ void SprogTurnout::forwardCommandChangeToLayout(int s) {
    // sort out states
    if ((s & Turnout::CLOSED) != 0) {
        // first look for the double case, which we can't handle
        if ((s & Turnout::THROWN) != 0) {
            // this is the disaster case!
            log->error("Cannot command both CLOSED and THROWN " + QString::number(s));
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
/*protected*/ void SprogTurnout::turnoutPushbuttonLockout(bool _pushButtonLockout) {
    if (log->isDebugEnabled()) {
        log->debug(tr("Send command to %1 Pushbutton {%2T%3").arg(
                (_pushButtonLockout ? "Lock" : "Unlock")).arg(_memo->getSystemPrefix()).arg(
                _number));
    }
}

/*protected*/ void SprogTurnout::sendMessage(bool closed) {
    // get the packet
    QByteArray bl = NmraPacket::accDecoderPkt(_number, closed);
    if (log->isDebugEnabled()) {
        log->debug("packet: "
                + QString::number(0xFF & bl[0],0,16)
                + " " +  QString::number(0xFF & bl[1], 0, 16)
                + " " + QString::number(0xFF & bl[2],0,16));
    }

    SprogMessage* m = new SprogMessage(10);
    int i = 0; // counter to make it easier to format the message
    m->setElement(i++, 'O');  // "S02 " means send it twice
    m->setElement(i++, ' ');
    // m->setElement(i++, '2'); // not required?
    QString s = QString::number(bl[0] & 0xFF,0,16).toUpper();
    if (s.length() == 1) {
        m->setElement(i++, '0');
        m->setElement(i++, s.toLocal8Bit().at(0));
    } else {
        m->setElement(i++, s.toLocal8Bit().at(0));
        m->setElement(i++, s.toLocal8Bit().at(1));
    }
    m->setElement(i++, ' ');
    s = QString::number(bl[1] & 0xFF,0,16).toUpper();
    if (s.length() == 1) {
        m->setElement(i++, '0');
        m->setElement(i++, s.toLocal8Bit().at(0));
    } else {
        m->setElement(i++, s.toLocal8Bit().at(0));
        m->setElement(i++, s.toLocal8Bit().at(1));
    }
    m->setElement(i++, ' ');
    s = QString::number(bl[2] & 0xFF,0,16).toUpper();
    if (s.length() == 1) {
        m->setElement(i++, '0');
        m->setElement(i++, s.toLocal8Bit().at(0));
    } else {
        m->setElement(i++, s.toLocal8Bit().at(0));
        m->setElement(i++, s.toLocal8Bit().at(1));
    }

    _memo->getSprogTrafficController()->sendSprogMessage(m, NULL);
}

//@Override
/*public*/ bool SprogTurnout::canInvert() {
    return true;
}

/*private*/ /*final*/ /*static*/ Logger* SprogTurnout::log = LoggerFactory::getLogger("SprogTurnout");
