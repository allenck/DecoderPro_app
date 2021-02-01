#include "deferringprogrammermanager.h"
#include "globalprogrammermanager.h"
#include "instancemanager.h"
#include "addressedprogrammermanager.h"

//DeferringProgrammerManager::DeferringProgrammerManager(QObject *parent) :
//  QObject(parent)
//{
//}
/* DeferringProgrammerManager.java */

/**
 * Defers GlobalProgrammer operations to the default GlobalProgrammer, and
 * AddressedProgrammer operations to the default AddressedProgrammer.
 * <p>
 * The underlying Programmer is looked up for each access to ensure that it's
 * current.
 *
 * @see jmri.ProgrammerManager
 * @author	Bob Jacobsen Copyright (C) 2014
 * @version	$Revision: 29920 $
 */
//public class DeferringProgrammerManager implements AddressedProgrammerManager, GlobalProgrammerManager {


/*public*/ DeferringProgrammerManager::DeferringProgrammerManager(QObject *parent) :
DefaultProgrammerManager(parent) // see note in .h
{
 setObjectName("DeferringProgrammerManager");
 userName = "<Default>";
 log = new Logger("DeferringProgrammerManager");
}


/**
 * Provides the human-readable representation for including
 * ProgrammerManagers directly in e.g. JComboBoxes, so it should return a
 * user-provided name for this particular one.
 */
/*public*/ QString DeferringProgrammerManager::getUserName() {
    return userName;
}

/**
 * Provides the human-readable representation for including
 * ProgrammerManagers directly in e.g. JComboBoxes, so it should return a
 * user-provided name for this particular one.
 */
/*public*/ QString DeferringProgrammerManager::toString() {
    return getUserName();
}

/*public*/ Programmer* DeferringProgrammerManager::getGlobalProgrammer() {
 GlobalProgrammerManager* gp = (DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager");
 if (gp == NULL || this == gp)
 {
     log->debug("no defaultGlobal ProgrammerManager, getGlobalProgrammer returns NULL" );
     return NULL;
 }
 Programmer* p = gp->getGlobalProgrammer();
 log->debug(tr("getGlobalProgrammer returns default service-mode programmer of type %1 from %2").arg(
     (p != NULL ? p->self()->metaObject()->className() : "(NULL)")).arg(gp->toString()));
 return p;
}

/*public*/ Programmer* DeferringProgrammerManager::reserveGlobalProgrammer() {
 GlobalProgrammerManager* gp = (DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager");
    if (gp == NULL || this == gp) {
        return NULL;
    }
    return gp->reserveGlobalProgrammer();
}

/*public*/ void DeferringProgrammerManager::releaseGlobalProgrammer(Programmer* p) {
 GlobalProgrammerManager* gp = (DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager");
    if (gp == NULL || this == gp) {
        return;
    }
    gp->releaseGlobalProgrammer(p);
}

/**
 * Allow for implementations that do not support Service mode programming
 *
 * @return false if there's no chance of getting one
 */
/*public*/ bool DeferringProgrammerManager::isGlobalProgrammerAvailable()
{
 GlobalProgrammerManager* gp = (DefaultProgrammerManager*)InstanceManager::getNullableDefault("GlobalProgrammerManager");
 if (gp == NULL || this == gp)
 {
  return false;
 }
 return ((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->isGlobalProgrammerAvailable();
}

/*public*/ AddressedProgrammer* DeferringProgrammerManager::getAddressedProgrammer(bool pLongAddress, int pAddress) {
 AddressedProgrammerManager* ap = (DefaultProgrammerManager*)InstanceManager::getNullableDefault("AddressedProgrammerManager");
    if (ap == NULL  || this == ap) {
        return NULL;
    }
    return ap->getAddressedProgrammer(pLongAddress, pAddress);
}

/*public*/ AddressedProgrammer* DeferringProgrammerManager::reserveAddressedProgrammer(bool pLongAddress, int pAddress) {
 AddressedProgrammerManager* ap = (DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager");
    if (ap == NULL || this == ap) {
        return NULL;
    }
    return ap->reserveAddressedProgrammer(pLongAddress, pAddress);
}

/*public*/ void DeferringProgrammerManager::releaseAddressedProgrammer(AddressedProgrammer* p) {
 AddressedProgrammerManager* ap = (DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager");
    if (ap == NULL || this == ap) {
        return;
    }
    ap->releaseAddressedProgrammer(p);
}

/**
 * Default programmer does not provide Ops Mode
 *
 * @return false if there's no chance of getting one
 */
/*public*/ bool DeferringProgrammerManager::isAddressedModePossible() {
 AddressedProgrammerManager* ap = (DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager");
    if (ap == NULL || this == ap) {
        return false;
    }
    return ap->isAddressedModePossible();
}

/**
 * Default programmer doesn't depend on address
 *
 * @return false if there's no chance of getting one
 */
/*public*/ bool DeferringProgrammerManager::isAddressedModePossible(LocoAddress* l) {
    return isAddressedModePossible();
}

/*public*/ QList<QString> DeferringProgrammerManager::getDefaultModes() {
 return ((DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->getDefaultModes();
}
