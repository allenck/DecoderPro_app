#include "wificonsistmanager.h"
#include "loggerfactory.h"
#include "consist.h"
#include <QVector>
#include "wificonsist.h"
#include "controllerinterface.h"

/**
 * @author Brett Hoffman Copyright (C) 2010, 2011
 *
 */
///*public*/ class WiFiConsistManager extends AbstractConsistManager {


/*public*/ WiFiConsistManager::WiFiConsistManager()  : AbstractConsistManager()
{
    //super();
 log = LoggerFactory::getLogger("WiFiConsistManager");
    listeners= NULL;
    log->debug("New WiFiConsistManager");
    isValid = true;
}

/*public*/ DccLocoAddress* WiFiConsistManager::stringToDcc(QString s) {
    int num = s.mid(1).toInt();
    bool isLong = (s.at(0) == 'L');
    return (new DccLocoAddress(num, isLong));
}

/**
 * Check to see if an address will try to broadcast (0) a programming
 * message.
 *
 * @param addr The address to check
 * @return true if address is no good, otherwise false
 */
/*public*/ bool WiFiConsistManager::checkForBroadcastAddress(DccLocoAddress* addr) {
    if (addr->getNumber() < 1) {
        log->warn("Trying to use broadcast address!");
        return true;
    }
    return false;
}

//@Override
/*public*/ DccConsist* WiFiConsistManager::addConsist(DccLocoAddress* address) {
    WiFiConsist* consist;
    consist = new WiFiConsist(address);
    consistTable->insert(address, consist);
    return consist;
}

//@Override
/*public*/ bool WiFiConsistManager::isCommandStationConsistPossible() {
    return false;
}

//@Override
/*public*/ bool WiFiConsistManager::csConsistNeedsSeparateAddress() {
    return false;
}

/**
 * Add a listener to handle: listener.sendPacketToDevice(message);
 *
 */
/*public*/ void WiFiConsistManager::addControllerListener(ControllerInterface* listener)
{
#if 0
    if (listeners == NULL) {
        listeners = new QVector<ControllerInterface*>(1);
    }
    if (!listeners->contains(listener)) {
        listeners->append(listener);
    }
#else
 connect(this, SIGNAL(), listener, SLOT(sendPacketToDevice(QString)));
#endif

}

/*public*/ void WiFiConsistManager::removeControllerListener(ControllerInterface* listener)
{
#if 0
    if (listeners == NULL) {
        return;
    }
    if (listeners->contains(listener)) {
        listeners->removeOne(listener);
    }
#else
 disconnect(this, SIGNAL(), listener, SLOT(sendPacketToDevice(QString)));

#endif
}

/*private*/ /*final*/ /*static*/ Logger* WiFiConsistManager::log = LoggerFactory::getLogger("WiFiConsistManager");
