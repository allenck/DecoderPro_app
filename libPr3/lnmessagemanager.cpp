#include "lnmessagemanager.h"
#include "lntrafficcontroller.h"

LnMessageManager::LnMessageManager(LnTrafficController* tc, QObject *parent) :
    QObject(parent)
{
    // connect to the TrafficManager
    this->tc = tc;
    //this->tc->addLocoNetListener(~0, (LocoNetListener*)this);
    connect(this->tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
}

void LnMessageManager::sendMessage(QString text) {
        sendMessage(0, text);
    }

void LnMessageManager::sendMessage(int id, QString text) {
        LocoNetMessage* l = new LocoNetMessage(16);
        QString localText = text+"        "; // insure at least 8 characters
        l->setOpCode(LnConstants::OPC_PEER_XFER);
        l->setElement(1, 0x10);
        l->setElement(2, 0x7F);   // throttle message
        l->setElement(3, id&0x7F);
        l->setElement(4, id/128);
        l->setElement(5, 0);
        l->setElement(6, localText.at(0).toLatin1());
        l->setElement(7, localText.at(1).toLatin1());
        l->setElement(8, localText.at(2).toLatin1());
        l->setElement(9, localText.at(3).toLatin1());
        l->setElement(10, 0);
        l->setElement(11, localText.at(4).toLatin1());
        l->setElement(12, localText.at(5).toLatin1());
        l->setElement(13, localText.at(6).toLatin1());
        l->setElement(14, localText.at(7).toLatin1());
        tc->sendLocoNetMessage(l);
    }

/**
 * Free resources when no longer used
 */
void LnMessageManager::dispose(){
    tc->removeLocoNetListener(~0, (LocoNetListener*)this);
    tc = NULL;
}


/**
 * Listen for status changes from LocoNet
 * <P>
 * This doesn't do anything now. Eventually, it will handle the
 * user response.
 */
void LnMessageManager::message(LocoNetMessage* m) {
}
