#include "wificonsist.h"
#include "nmrapacket.h"
#include "instancemanager.h"
#include "commandstation.h"
#include "loggerfactory.h"

/**
 * @author Brett Hoffman Copyright (C) 2010, 2011
 *
 */
///*public*/ class WiFiConsist extends DccConsist {

/*public*/WiFiConsist:: WiFiConsist(DccLocoAddress* address, QObject* parent) : DccConsist(address, parent) {
    //super(address);
}

//@Override
/*public*/ void WiFiConsist::add(DccLocoAddress* loco, bool dirNorm)
{
    restore(loco, dirNorm);
    sendConsistCommand(loco, dirNorm, this);
}

//@Override
/*public*/ void WiFiConsist::remove(DccLocoAddress* loco) {
    consistDir->remove(loco);
    consistList->removeOne(loco);
    consistPosition->remove(loco);
    sendConsistCommand(loco, true, NULL);
}

/**
 * Send an NMRA consisting command to add or remove a loco from a consist
 *
 * @param loco    The loco to add or remove
 * @param dirNorm true for normal, false for reverse
 * @param consist The short consist address for a loco, null to remove
 */
/*public*/ void WiFiConsist::sendConsistCommand(DccLocoAddress* loco, bool dirNorm, WiFiConsist* consist)
{
 int conAddr = 0;
 if (consist != NULL) {
     conAddr = getConsistAddress()->getNumber();
 }
 //  Use NMRA consist command to set consist address
 QByteArray packet = NmraPacket::consistControl(loco->getNumber(),
         loco->isLongAddress(),
         conAddr,
         dirNorm);
 if (packet != NULL) {
     if (log->isDebugEnabled()) {
//            log->debug(Arrays.toString(packet));
     }
     ((CommandStation*)InstanceManager::getDefault("CommandStation"))->sendPacket(packet, 1);
 }
}
/*private*/ /*final*/ /*static*/ Logger* WiFiConsist::log = LoggerFactory::getLogger("WiFiConsist");
