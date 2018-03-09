#include "sprogprogrammermanager.h"

using namespace Sprog;
/**
 * Extend DefaultProgrammerManager to provide programmers for SPROG systems.
 *
 * @see jmri.managers.DefaultProgrammerManager
 * @author	Andrew crosland Copyright (C) 2001
  */
// /*public*/ class SprogProgrammerManager extends DefaultProgrammerManager {

///*private*/ Programmer localProgrammer;

/*public*/ SprogProgrammerManager::SprogProgrammerManager(Programmer* serviceModeProgrammer, SprogSystemConnectionMemo* memo, QObject* parent)
: DefaultProgrammerManager(serviceModeProgrammer, memo, parent)
{
    //super(serviceModeProgrammer, memo);
    adapterMemo = NULL;
    //localProgrammer = serviceModeProgrammer;
    this->mode = SprogConstants::SprogMode::SERVICE;
    adapterMemo = memo;
}

/*public*/ SprogProgrammerManager::SprogProgrammerManager(Programmer* serviceModeProgrammer, SprogConstants::SprogMode mode, SprogSystemConnectionMemo* memo, QObject* parent) : DefaultProgrammerManager(serviceModeProgrammer, memo, parent)
{
    //super(serviceModeProgrammer, memo);
    adapterMemo = NULL;
    //localProgrammer = serviceModeProgrammer;
    this->mode = mode;
    adapterMemo = memo;
}

/**
 * Classic SPROG is service mode only. SPROG Command Station is Ops mode only.
 *
 * @return true for SPROG Command Station
 */
 //@Override
/*public*/ bool SprogProgrammerManager::isAddressedModePossible() {
    if (mode == SprogConstants::SprogMode::OPS) {
        return true;
    } else {
        return false;
    }
}

 //@Override
/*public*/ bool SprogProgrammerManager::isGlobalProgrammerAvailable() {
    if (mode == SprogConstants::SprogMode::SERVICE) {
        return true;
    } else {
        return false;
    }
}

 //@Override
/*public*/ AddressedProgrammer* SprogProgrammerManager::getAddressedProgrammer(bool pLongAddress, int pAddress) {
#if 0
    return new SprogOpsModeProgrammer(pAddress, pLongAddress, adapterMemo);
#endif
}

 //@Override
/*public*/ AddressedProgrammer* SprogProgrammerManager::reserveAddressedProgrammer(bool /*pLongAddress*/, int /*pAddress*/) {
    return NULL;
}

