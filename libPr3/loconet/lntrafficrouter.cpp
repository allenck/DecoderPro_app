#include "lntrafficrouter.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"

/**
 * Implements a LocoNetInterface by doing a scatter-gather to another, simpler
 * implementation.
 * <p>
 * This is intended for remote operation, where only one copy of each message
 * should go to/from another node. By putting an LnTrafficRouter implementation
 * at the remote node, all of the routing of messages to multiple consumers can
 * be done without traffic over the connection.
 *
 * @author Bob Jacobsen Copyright (C) 2002
 */
// /*public*/ class LnTrafficRouter extends LnTrafficController implements LocoNetListener {

/**
 * Create a default LnTrafficRouter instance without a SystemConnectionMemo.
 * Not compatible with multi connections.
 *
 * @deprecated since 4.11.6, use LnTrafficRouter(LocoNetSystemConnectionMemo) instead
 */
//@Deprecated
/*public*/ LnTrafficRouter::LnTrafficRouter(QObject *parent) : LnTrafficController(parent){
    //jmri.util.Log4JUtil.deprecationWarning(log, "LnTrafficRouter");
 log->warn(tr("%1 is deprecated, please remove references to it").arg("LnTrafficRouter::LnTrafficRouter(QObject *parent)"));
}

/**
 * Create a default instance connected to a given SystemConnectionMemo.
 *
 * @since 4.11.6
 * @param m the connected LocoNetSystemConnectionMemo
 */
/*public*/ LnTrafficRouter::LnTrafficRouter(LocoNetSystemConnectionMemo* m, QObject *parent) : LnTrafficController(parent){
    // set the memo to point here
    memo = m;
    m->setLnTrafficController(this);
}

// Methods to implement the LocoNetInterface for clients.
// These use the parent implementations of listeners, addLocoNetListener,
// removeLocoNetListener, notify

//@Override
/*public*/ bool LnTrafficRouter::status() {
    return connected;
}

/**
 * Forward a preformatted LocoNetMessage to the actual interface.
 *
 * @param m Message to send; will be updated with CRC
 */
//@Override
/*public*/ void LnTrafficRouter::sendLocoNetMessage(LocoNetMessage* m) {
    // update statistics
    transmittedMsgCount++;

    // forward message
    destination->sendLocoNetMessage(m);
}

/**
 * Receive a LocoNet message from upstream and forward it to all the local
 * clients.
 */
//@Override
/*public*/ void LnTrafficRouter::message(LocoNetMessage* m) {
    //notify(m);
}

// methods to connect/disconnect to a source of data in another
// LocoNetInterface

/**
 * Make connection to existing LocoNetInterface object for upstream
 * communication.
 *
 * @param i Interface to be connected
 */
/*public*/ void LnTrafficRouter::connect(LocoNetInterface* i) {
    destination = i;
    connected = true;
    i->addLocoNetListener(LocoNetInterface::ALL, (LocoNetListener*)this);
//    connect(i, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
}

/**
 * Break connection to upstream LocoNetInterface object. Once broken,
 * attempts to send via "message" member will fail.
 *
 * @param i previously connected interface
 */
/*public*/ void LnTrafficRouter::disconnectPort(LocoNetInterface* i) {
    if (destination != i) {
        log->warn("disconnectPort: disconnect called from non-connected LnPortController");
    }
    destination = nullptr;
    connected = false;
}

/**
 * Implement abstract method to signal if there's a backlog of information
 * waiting to be sent.
 *
 * @return true if busy, false if nothing waiting to send
 */
//@Override
/*public*/ bool LnTrafficRouter::isXmtBusy() {
    return false;
}

/*private*/ /*final*/ /*static*/ Logger* LnTrafficRouter::log = LoggerFactory::getLogger("LnTrafficRouter");
