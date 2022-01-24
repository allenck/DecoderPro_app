#include "internalconsistmanager.h"
#include "consist.h"
#include "exceptions.h"
#include "instancemanager.h"
#include "dcclocoaddress.h"
#include "nmraconsist.h"
#include "dccconsist.h"

/**
 * Default Consist Manager which uses the NmraConsist class for
 * the consists it builds.
 *
 * @author Paul Bender Copyright (C) 2003
 * @author Randall Wood Copyright (C) 2013
 */
///*public*/ class InternalConsistManager extends AbstractConsistManager {

/*public*/ InternalConsistManager::InternalConsistManager(QObject* parent) : AbstractConsistManager(parent)
{
    //super();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool InternalConsistManager::isCommandStationConsistPossible(){
   return false;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool InternalConsistManager::csConsistNeedsSeparateAddress(){
  return false;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ DccConsist* InternalConsistManager::addConsist(LocoAddress* address) {
    //if (! (address instanceof DccLocoAddress))
    if(qobject_cast<DccLocoAddress*>(address)== NULL)
    {
        throw new IllegalArgumentException("address is not a DccLocoAddress object");
    }
    if (consistTable->contains((DccLocoAddress*)address)) {
        return (consistTable->value((DccLocoAddress*)address));
    }
    DccConsist* consist = nullptr;
    if (InstanceManager::getNullableDefault("CommandStation") != nullptr ) {
       consist = new NmraConsist((DccLocoAddress*) address);
    }
    else if (InstanceManager::getNullableDefault("AddressedProgrammerManager") != nullptr){
       consist = new DccConsist((DccLocoAddress*) address);
    }
    if (consist != nullptr) {
       consistTable->insert((DccLocoAddress*)address, consist);
    }
    return (consist);
}


