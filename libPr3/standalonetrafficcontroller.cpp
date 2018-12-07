#include "standalonetrafficcontroller.h"
#include "loggerfactory.h"
#include "rfid/rfidsystemconnectionmemo.h"
#include "abstractmrmessage.h"
#include "rfid/rfidmessage.h"
#include "standalonemessage.h"
#include "rfid/rfidprotocol.h"
#include "standalonereply.h"
#include "timeunit.cpp"

#include <QMetaObject>
#include <QNetworkRequest>
#include <QTableView>

/**
 * Converts Stream-based I/O to/from messages. The "SerialInterface" side
 * sends/receives message objects.
 * <P>
 * The connection to a SerialPortController is via a pair of *Streams, which
 * then carry sequences of characters for transmission. Note that this
 * processing is handled in an independent thread.
 * <P>
 * This maintains a list of nodes, but doesn't currently do anything with it.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003, 2005, 2006, 2008
 * @author Matthew Harris Copyright (c) 2011
 * @since 2.11.4
 */
///*public*/ class StandaloneTrafficController extends RfidTrafficController {

//@Override
/*public*/ void StandaloneTrafficController::sendInitString() {
    QString init = adapterMemo->getProtocol()->initString();
    if (init.length() > 0) {
        sendRfidMessage(new StandaloneMessage(init, 0), nullptr);
    }
}

/*public*/ StandaloneTrafficController::StandaloneTrafficController(RfidSystemConnectionMemo* memo, QObject* parent) : RfidTrafficController(parent)
{
    //super();
    adapterMemo = memo;
    logDebug = log->isDebugEnabled();

    // not polled at all, so allow unexpected messages, and
    // use poll delay just to spread out startup
    setAllowUnexpectedReply(true);
    mWaitBeforePoll = 1000;  // can take a long time to send

}

//@Override
/*protected*/ void StandaloneTrafficController::forwardToPort(AbstractMRMessage* m, AbstractMRListener* reply) {
    if (logDebug) {
        log->debug("forward " + m->toString());
    }
    sendInterlock = ((RfidMessage*) m)->getInterlocked();
    RfidTrafficController::forwardToPort(m, reply);
}

//@Override
/*public*/ RfidMessage* StandaloneTrafficController::getRfidMessage(int length) {
    return new StandaloneMessage(length);
}

//@Override
/*protected*/ AbstractMRReply* StandaloneTrafficController::newReply() {
    StandaloneReply* reply = new StandaloneReply(adapterMemo->getTrafficController());
    return reply;
}

//@Override
/*public*/ QString StandaloneTrafficController::getRange() {
    return "1";
}

//@Override
/*protected*/ bool StandaloneTrafficController::endOfMessage(AbstractMRReply* msg) {
    return adapterMemo->getProtocol()->endOfMessage(msg);
}


/*private*/ /*static*/ /*final*/ Logger* StandaloneTrafficController::log = LoggerFactory::getLogger("StandaloneTrafficController");
