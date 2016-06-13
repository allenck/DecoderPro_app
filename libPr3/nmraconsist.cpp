#include "nmraconsist.h"
#include "nmrapacket.h"
#include "instancemanager.h"

//NmraConsist::NmraConsist(QObject *parent) :
//    DccConsist(parent)
//{
//}
/**
 * This is the Default DCC consist manager installed on systems which support
 * the command station interface. It uses the NMRA consist creation packet
 * instead of Operations Mode programming to build a consist, but otherwise is
 * derived from the DccConsist code.
 *
 * @author Paul Bender Copyright (C) 2011
 * @version $Revision 1.0 $
 */
// /*public*/ class NmraConsist extends DccConsist implements Consist {

// Initialize a consist for the specific address.
/*public*/ NmraConsist::NmraConsist(int address, QObject *parent)
    :    DccConsist(address, parent)
{
    //uper(address);
    log = new Logger("NmraConsist");
    log->debug("Nmra Consist created for address: "+ QString::number(address));
}

/*public*/ NmraConsist::NmraConsist(DccLocoAddress* address, QObject *parent)
    :    DccConsist(address, parent)
{
    //super(address);
    log = new Logger("NmraConsist");
    log->debug("Nmra Consist created for address: "+ QString::number(address->number));
}

/*
 *  Add a Locomotive to an Advanced Consist
 *  @param address is the Locomotive address to add to the locomotive
 *  @param directionNormal is True if the locomotive is traveling
 *        the same direction as the consist, or false otherwise.
 */
//@Override
/*protected*/ void NmraConsist::addToAdvancedConsist(DccLocoAddress* locoAddress, bool directionNormal) {
    if (log->isDebugEnabled()) {
        log->debug(QString("Add Locomotive %1to advanced consist %2 With Direction Normal %3.").arg(
                       locoAddress->toString()).arg(
                       consistAddress->toString()).arg(
                   (directionNormal?"true":"false")));
    }
    // create the message and fill it,
    QByteArray contents = NmraPacket::consistControl(locoAddress->getNumber(),
            locoAddress->isLongAddress(),
            consistAddress->getNumber(),
            directionNormal);
    InstanceManager::commandStationInstance()->sendPacket(contents, 4);
    notifyConsistListeners(locoAddress, ConsistListener::OPERATION_SUCCESS);

}

/*
 *  Remove a Locomotive from an Advanced Consist
 *  @param address is the Locomotive address to add to the locomotive
 */
//@Override
/*protected*/ void NmraConsist::removeFromAdvancedConsist(DccLocoAddress* locoAddress) {
    if (log->isDebugEnabled()) {
        log->debug(QString("Remove Locomotive %1 from advanced consist %2.").arg(
                       locoAddress->getNumber()).arg(
                consistAddress->getNumber()));
    }
    // create the message and fill it,
    QByteArray contents = NmraPacket::consistControl(locoAddress->getNumber(),
            locoAddress->isLongAddress(),
            0, //set to 0 to remove
            true);//always normal direction
    InstanceManager::commandStationInstance()->sendPacket(contents, 4);
    notifyConsistListeners(locoAddress, ConsistListener::OPERATION_SUCCESS);
}
