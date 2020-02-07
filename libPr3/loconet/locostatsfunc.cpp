#include "locostatsfunc.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"
#include "lntrafficcontroller.h"
#include "loconetinterfacestatslistener.h"
#include <QVector>
#include "loconetinterfacestatslistener.h"
#include "rawstatus.h"
#include "LocoBufferII/locobufferiistatus.h"
#include "PR2/pr2status.h"
#include "pr3ms100modestatus.h"

/**
 * Implements functionality to query the LocoNet interface device for status.
 *
 * @author Bob Milhaupt Copyright (C) 2017
 */
// /*public*/ class LocoStatsFunc implements LocoNetListener {

/*public*/ LocoStatsFunc::LocoStatsFunc(LocoNetSystemConnectionMemo* memo, QObject *parent) : QObject(parent) {
    this->memo = memo;
    updatePending = false;
    need2ndUpdate = false;
    ifaceStatus = nullptr;
    if (memo != nullptr) {
        this->memo->getLnTrafficController()->addLocoNetListener(0, this);
    }
}

/**
 * Request LocoNet interface Status
 */
/*public*/ void LocoStatsFunc::sendLocoNetInterfaceStatusQueryMessage() {
    updatePending = true;
    need2ndUpdate = false;  // assume that we do not need a second query

    log->debug("Sent a LocoNet interface status query");
    sendQuery();
}

/*private*/ void LocoStatsFunc::sendQuery() {
    if (memo == nullptr) {
        return;
    }
    LocoNetMessage* l = new LocoNetMessage(QVector<int>() << 0x81 << 0x7f);
    memo->getLnTrafficController()->sendLocoNetMessage(l);
}

/**
 * LocoNet message handler.
 *
 * @param msg  incoming LocoNet message to be interpreted
 */
//@Override
/*public*/ void LocoStatsFunc::message(LocoNetMessage* msg)
{
    if ((msg->getOpCode() == LnConstants::OPC_PEER_XFER)
            && (msg->getElement(1) == 0x10)
            && (msg->getElement(2) == 0x50)
            && (msg->getElement(3) == 0x50)
            && (msg->getElement(4) == 0x01)
            && ((msg->getElement(5) & 0xF0) == 0x0)
            && ((msg->getElement(10) & 0xF0) == 0x0)
            && updatePending) {
        // LocoBuffer II form
        QVector<int> data = msg->getPeerXfrData();
        ifaceStatus = new LocoBufferIIStatus(
                data[0]*256+data[4],
                (data[5] << 16) + (data[6] << 8) + data[7],
                (data[1] << 16) + (data[2] << 8) + data[3]
        );
        updatePending = false;
        updateListeners();
        log->debug("Got a LocoNet interface status reply: LocoBufferII");

    } else
     if ((msg->getOpCode() == LnConstants::OPC_PEER_XFER)
            && (msg->getElement(1) == 0x10)
            && (msg->getElement(2) == 0x22)
            && (msg->getElement(3) == 0x22)
            && (msg->getElement(4) == 0x01)
            && ((msg->getElement(5) & 0x70) == 0x0)
            && ((msg->getElement(10) & 0x70) == 0x0)
            && updatePending) {  // Digitrax form, check PR2/PR3 or MS100/PR3 mode

        if ((msg->getElement(8) & 0x20) == 0) {
            // PR2 format
            QVector<int> data = msg->getPeerXfrData();
            ifaceStatus = new PR2Status(
                    data[1] * 256 + data[0],
                    data[2],
                    data[3],
                    data[4],
                    data[5]
            );
            log->debug("Got a LocoNet interface status reply: PR2 mode");
            if (updatePending) {
                if (need2ndUpdate == false) {
                    need2ndUpdate = true;
                    sendQuery();   // get info for MS100 mode, too
                } else {
                    need2ndUpdate = false;
                    updatePending = false;
                }
            }

        } else {
            // MS100 format
            QVector<int> data = msg->getPeerXfrData();
            ifaceStatus = new PR3MS100ModeStatus(
                    data[1] * 256 + data[0],
                    data[5] * 256 + data[4],
                    data[2]
            );
            log->debug("Got a LocoNet interface status reply: PR3 MS100 mode");
            if (updatePending) {
                if (need2ndUpdate == false) {
                    need2ndUpdate = true;
                    sendQuery();   // get info for PR2 mode, too
                } else {
                    need2ndUpdate = false;
                    updatePending = false;
                }
            }
        }
        updateListeners();

    } else
      if ((msg->getOpCode() == LnConstants::OPC_PEER_XFER) &&
            (msg->getElement(1) == 0x10) &&
            updatePending) {
        // Raw mode format
        // Accept only the first OPC_PEER_XFER of length 0x10 after a request.
        // This assumes that the interface device will be the first response
        // after the request, and that the reply will be a "typical" OPC_PEER_XFER
        // message, and not one of the "alternate" forms with different overall
        // length..
        QVector<int> data = msg->getPeerXfrData();
        ifaceStatus = new RawStatus(data[0], data[1], data[2], data[3],
                data[4], data[5], data[6], data[7]
        );

        updatePending = false;
        updateListeners();
        log->debug("Got a LocoNet interface status reply: Raw mode");
    }
}
/*private*/ void LocoStatsFunc::updateListeners() {
    //listeners.stream().forEach((l) ->
    foreach(LocoNetInterfaceStatsListener* l, listeners)
    {
        l->notifyChangedInterfaceStatus(ifaceStatus);
    }//);
}



/**
 * Get the latest interface status
 *
 * @return the latest interface status; will be null if status has
 *          not been pulled.
 */
/*public*/ QObject* LocoStatsFunc::getInterfaceStatus() {
    return ifaceStatus;
}

/**
 * Free resources when no longer used
 */
/*public*/ void LocoStatsFunc::dispose() {
    listeners.clear();
    //listeners = nullptr;
}

// The methods to implement adding and removing listeners

/**
 * Add a listener to the list of listeners which will be notified upon receipt
 * a LocoNet message containing interface statistics.
 *
 * @param l  LocoNetInterfaceStatsListener to be added
 */
/*public*/ /*synchronized*/ void LocoStatsFunc::addLocoNetInterfaceStatsListener(/*@Nonnull*/ LocoNetInterfaceStatsListener* l) {
    //java.util.Objects.requireNonNull(l);
    // add only if not already registered
    if (!listeners.contains(l)) {
        listeners.append(l);
    }
}

/**
 * Remove a listener (if present) from the list of listeners which will be
 * notified upon receipt LocoNet message containing interface statistics.
 *
 * @param l  LocoNetInterfaceStatsListener to be removed
 */
/*public*/ /*synchronized*/ void LocoStatsFunc::removeLocoNetInterfaceStatsListener(/*@Nonnull*/ LocoNetInterfaceStatsListener* l) {
    //java.util.Objects.requireNonNull(l);
    if (listeners.contains(l)) {
        listeners.removeOne(l);
    }
}

/*private*/ /*final*/ /*static*/ Logger* LocoStatsFunc::log = LoggerFactory::getLogger("LocoStatsFunc");
