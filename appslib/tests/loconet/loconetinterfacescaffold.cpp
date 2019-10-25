#include "loconetinterfacescaffold.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"
#include "loconetmessage.h"

/**
 * Test scaffold implementation of LocoNetInterface.
 * Use an object of this type as a LnTrafficController in tests.
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2006
 */
// /*public*/ class LocoNetInterfaceScaffold extends LnTrafficController {

/*public*/ LocoNetInterfaceScaffold::LocoNetInterfaceScaffold() : LnTrafficController(){
    /**
     * Record LocoNet messages sent, provide access for making sure they are OK.
     */
     outbound = QVector<LocoNetMessage*>();  // /*public*/ OK here, so long as this is a test class
}

/*public*/ LocoNetInterfaceScaffold::LocoNetInterfaceScaffold(LocoNetSystemConnectionMemo* adaptermemo)
    : LnTrafficController(adaptermemo)
{
    //super(adaptermemo);
    /**
     * Record LocoNet messages sent, provide access for making sure they are OK.
     */
    outbound = QVector<LocoNetMessage*>();  // /*public*/ OK here, so long as this is a test class

}

// override some LnTrafficController methods for test purposes
//@Override
/*public*/ bool LocoNetInterfaceScaffold::status() {
    return true;
}


//@Override
/*public*/ void LocoNetInterfaceScaffold::sendLocoNetMessage(LocoNetMessage* m) {
    log->debug(tr("sendLocoNetMessage [%1]").arg(m->toString()));
    // save a copy
    outbound.append(m);
    // we don't return an echo so that the processing before the echo can be
    // separately tested
}

//@Override
/*public*/ bool LocoNetInterfaceScaffold::isXmtBusy() {
    return false;
}

// test control member functions

/**
 * Forward a message that came from unit under test.
 */
void LocoNetInterfaceScaffold::forwardMessage(int i) {
    sendTestMessage(outbound.at(i));
}

/**
 * Forward a message to the listeners, e.g. test receipt
 */
/*public*/ void LocoNetInterfaceScaffold::sendTestMessage(LocoNetMessage* m) {
    // forward a test message to LocoNetListeners
    log->debug(tr("sendTestMessage    [%1]").arg(m->toString()));
// TODO    notify(m);
    // set the error correcting code byte(s) before transmittal
    m->setParity();
    LocoNetMessage* msgcopy = new LocoNetMessage(*m);
    emit sendMessage(msgcopy);
    return;
}

/**
 * Check number of listeners, used for testing dispose().
 */
/*public*/ int LocoNetInterfaceScaffold::numListeners() {
    return listeners.size();
}

/**
 * Get listeners, used for testing dispose().
 */
/*public*/ QVector<LocoNetListener*> LocoNetInterfaceScaffold::getListeners() {
    return listeners;
}

/*private*/ /*final*/ /*static*/ Logger* LocoNetInterfaceScaffold::log = LoggerFactory::getLogger("LocoNetInterfaceScaffold");
