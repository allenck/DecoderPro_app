#include "sprogcsturnout.h"
#include "loggerfactory.h"

using namespace Sprog;

/**
 * Sprog implementation of the Turnout interface.
 * <p>
 * This object doesn't listen to the Sprog communications. This is because it
 * should be the only object that is sending messages for this turnout; more
 * than one Turnout object pointing to a single device is not allowed.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003, 2005
 * @author J.M. (Mark) Knox Copyright (C) 2005
 */
///*public*/ class SprogCSTurnout extends AbstractTurnout {


/**
 * Create SPROG Turnout object.
 * <p>
 * Sprog turnouts use the NMRA number (0-511) as their numerical
 * identification.
 *
 * @param number address for turnout
 * @param memo connection to get prefix from
 */
/*public*/ SprogCSTurnout::SprogCSTurnout(int number, SprogSystemConnectionMemo* memo, QObject* parent) : AbstractTurnout(memo->getSystemPrefix() + "T" + QString::number(number), parent) {
    //super(memo->getSystemPrefix() + "T" + number);
    _number = number;
    _memo = memo;
    commandStation = _memo->getCommandStation();
}

/*public*/ int SprogCSTurnout::getNumber() {
    return _number;
}

/**
 * Handle a request to change state by sending a formatted DCC packet.
 *
 * @param s commanded state to set
 */
//@Override
/*protected*/ void SprogCSTurnout::forwardCommandChangeToLayout(int s) {
    // sort out states
    if ((s & Turnout::CLOSED) != 0) {
        // first look for the double case, which we can't handle
        if ((s & Turnout::THROWN) != 0) {
            // this is the disaster case!
            log->error(tr("Cannot command both CLOSED and THROWN %1").arg(s));
            return;
        } else {
            // send a CLOSED command
            commandStation->forwardCommandChangeToLayout(_number, true ^ getInverted());
        }
    } else {
        // send a THROWN command
        commandStation->forwardCommandChangeToLayout(_number, false ^ getInverted());
    }
}


/*public*/ void SprogCSTurnout::setCommandStation(SprogCommandStation* command) {
    commandStation = command;
}

//@Override
/*protected*/ void SprogCSTurnout::turnoutPushbuttonLockout(bool _pushButtonLockout) {
    if (log->isDebugEnabled()) {
        log->debug(tr("Send command to %1 Pushbutton %2T%3").arg(
                (_pushButtonLockout ? "Lock" : "Unlock")).arg(
                _memo->getSystemPrefix()).arg(
                _number));
    }
}

//@Override
/*public*/ bool SprogCSTurnout::canInvert() {
    return true;
}


/*private*/ /*final*/ /*static*/ Logger* SprogCSTurnout::log = LoggerFactory::getLogger("SprogCSTurnout");
