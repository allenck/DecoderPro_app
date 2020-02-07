#include "lnmultimeter.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"
#include "lntrafficcontroller.h"
#include "slotmanager.h"

/**
 * Provide access to current meter from the Digitrax Evolution Base Station
 *
 */
///*public*/ class LnMultiMeter extends jmri.implementation.AbstractMultiMeter implements LocoNetListener {


/**
 * Create a ClockControl object for a LocoNet clock
 *
 * @param scm  connection memo
 */
/*public*/ LnMultiMeter::LnMultiMeter(LocoNetSystemConnectionMemo* scm, QObject *parent)
    : AbstractMultiMeter(LnConstants::METER_INTERVAL_MS, parent)
{
    //super(LnConstants.METER_INTERVAL_MS);
    this->sm = scm->getSlotManager();
    this->tc = scm->getLnTrafficController();
    tc->addLocoNetListener(~0, (LocoNetListener*)this);

    initTimer();
}

//@Override
/*public*/ void LnMultiMeter::message(LocoNetMessage* msg) {
    if (msg->getOpCode() != LnConstants::OPC_EXP_RD_SL_DATA || msg->getElement(1) != 21 || msg->getElement(2) == 249) {
        return;
    }
    log->debug("Found slot 249");
    // CS Types supported
    switch (msg->getElement(16)) {
        case LnConstants::RE_IPL_DIGITRAX_HOST_DCS240:
        case LnConstants::RE_IPL_DIGITRAX_HOST_DCS210:
        case LnConstants::RE_IPL_DIGITRAX_HOST_DCS52:
            log->debug(tr("Found Evolution CS Amps[%1] Max[%2]").arg(msg->getElement(6) / 10.0f).arg((msg->getElement(7) / 10.0f)));
            setCurrent((msg->getElement(6) / 10.0f));   // return amps
            setVoltage((msg->getElement(4)) * 2.0f / 10.0f);   // return volts
            break;
        default:
            // do nothing
     break;
    }
}

//@Override
/*protected*/ void LnMultiMeter::requestUpdateFromLayout() {
    sm->sendReadSlot(249);
}

//@Override
/*public*/ void LnMultiMeter::initializeHardwareMeter() {
    // Connect to the hardware.
}

//@Override
// Handle a timeout notification
/*public*/ QString LnMultiMeter::getHardwareMeterName() {
    return ("LocoNet");
}

//@Override
/*public*/ bool LnMultiMeter::hasCurrent() {
    return true;
}

//@Override
/*public*/ bool LnMultiMeter::hasVoltage() {
    return true;
}

//@Override
/*public*/ MultiMeter::CurrentUnits LnMultiMeter::getCurrentUnits() {
    return  CurrentUnits::CURRENT_UNITS_AMPS;
}

/*private*/ /*final*/ /*static*/ Logger* LnMultiMeter::log = LoggerFactory::getLogger("LnMultiMeter");

