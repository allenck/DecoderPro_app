#include "rfidtrafficcontroller.h"
#include "loggerfactory.h"
#include "abstractmrmessage.h"
#include "rfidmessage.h"

RfidTrafficController::RfidTrafficController(QObject *parent) :
    AbstractMRTrafficController(parent)
{
    logDebug = log->isDebugEnabled();
    mSensorManager = NULL;
    // not polled at all, so allow unexpected messages, and
    // use poll delay just to spread out startup
    setAllowUnexpectedReply(true);
    mWaitBeforePoll = 1000;  // can take a long time to send

}
/**
 * Converts Stream-based I/O to/from messages.  The "RfidInterface"
 * side sends/receives message objects.
 * <P>
 * The connection to
 * a SerialPortController is via a pair of *Streams, which then carry sequences
 * of characters for transmission.     Note that this processing is
 * handled in an independent thread.
 * <P>
 * This maintains a list of nodes, but doesn't currently do anything
 * with it.
 * <p>
 * This implementation is complete and can be instantiated, but
 * is not functional.  It will be created e.g. when a default
 * object is needed for configuring nodes, etc, during the initial
 * configuration.  A subclass must be instantiated to actually
 * communicate with an adapter.
 *
 * @author      Bob Jacobsen  Copyright (C) 2001, 2003, 2005, 2006, 2008
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @since       2.11.4
 */
///*public*/ class RfidTrafficController extends AbstractMRTrafficController implements RfidInterface {
// Note: Origonal JMRI class extended AbstractMRTrafficController but we are receiving Rfid messages here via the ftdilib.

///*public*/ RfidTrafficController() {
//    super();
//    logDebug = log->isDebugEnabled();

//    // not polled at all, so allow unexpected messages, and
//    // use poll delay just to spread out startup
//    setAllowUnexpectedReply(true);
//    mWaitBeforePoll = 1000;  // can take a long time to send

//}


/*public*/ void RfidTrafficController::setAdapterMemo(RfidSystemConnectionMemo* memo) {
    adapterMemo = memo;
}

/*public*/ RfidSystemConnectionMemo* RfidTrafficController::getAdapterMemo() {
       return adapterMemo;
   }

/**
 * Get a message of a specific length for filling in.
 * <p>
 * This is a default, NULL implementation, which must be overridden
 * in an adapter-specific subclass.
 */
///*public*/ RfidMessage getRfidMessage(int length) {return NULL;}



// The methods to implement the RfidInterface

/*public*/ /*synchronized*/ void RfidTrafficController::addRfidListener(RfidListener* l) {
    this->addListener(l);
}

/*public*/ /*synchronized*/ void RfidTrafficController::removeRfidListener(RfidListener* l) {
    this->removeListener(l);
}

/**
 * Forward a RfidMessage to all registered RfidInterface listeners.
 */
/*protected*/ void RfidTrafficController::forwardMessage(AbstractMRListener* client, AbstractMRMessage*  m) {
    ((RfidListener*)client)->message((RfidMessage*)m);
}

/**
 * Forward a reply to all registered RfidInterface listeners.
 */
/*protected*/ void RfidTrafficController::forwardReply(AbstractMRListener* client, AbstractMRReply* r) {
    ((RfidListener*)client)->reply((RfidReply*)r);
}

/*public*/ void RfidTrafficController::setSensorManager(RfidSensorManager* m) { mSensorManager = m; }
/*public*/ RfidSensorManager* RfidTrafficController::getSensorManager() { return mSensorManager; }

/*public*/ void RfidTrafficController::setReporterManager(RfidReporterManager* m) { mReporterManager = m; }
/*public*/ RfidReporterManager* RfidTrafficController::getReporterManager() { return mReporterManager; }


/**
 * Eventually, do initialization if needed
 */
/*protected*/ AbstractMRMessage* RfidTrafficController::pollMessage() {
    return nullptr;
}

/*protected*/ AbstractMRListener* RfidTrafficController::pollReplyHandler() {
    return nullptr;
}

/**
 * Forward a preformatted message to the actual interface.
 */
/*public*/ void RfidTrafficController::sendRfidMessage(RfidMessage* m, RfidListener* reply) {
    sendMessage(m, reply);
}

//@Override
/*protected*/ void RfidTrafficController::forwardToPort(AbstractMRMessage* m, AbstractMRListener* reply) {
    if (logDebug) log->debug("forward "+m->toString());
    sendInterlock = ((RfidMessage*)m)->getInterlocked();
    AbstractMRTrafficController::forwardToPort(m, reply);
}

/*protected*/ AbstractMRMessage* RfidTrafficController::enterProgMode() {
    return nullptr;
}
/*protected*/ AbstractMRMessage* RfidTrafficController::enterNormalMode() {
    return nullptr;
}

/**
 * <p>
 * This is a default, NULL implementation, which must be overridden
 * in an adapter-specific subclass.
 */
/*protected*/ bool RfidTrafficController::endOfMessage(AbstractMRReply* msg) { return true; }

/**
 * <p>
 * This is a default, NULL implementation, which must be overridden
 * in an adapter-specific subclass.
 */
/*protected*/ AbstractMRReply* RfidTrafficController::newReply() { return nullptr; }

/*public*/ QString RfidTrafficController::getRange() { return ""; }

/*private*/ /*static*/ /*final*/ Logger* RfidTrafficController::log = LoggerFactory::getLogger("RfidTrafficController");
//}
