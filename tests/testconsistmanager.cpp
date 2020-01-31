#include "testconsistmanager.h"
#include "exceptions.h"

/**
 * Consist Manager used for consist tool tests.
 *
 * @author Paul Bender Copyright (C) 2015
 */
// /*public*/ class TestConsistManager extends jmri.implementation.AbstractConsistManager {


/*public*/ TestConsistManager::TestConsistManager(QObject *parent) : AbstractConsistManager(parent) {
    //super();
 addCalls = 0;
 removeCalls = 0;
 setObjectName("TestConsistManager");
}

/**
 * Add a new Consist with the given address to the consistTable/consistList
 */
//@Override
/*protected*/ DccConsist* TestConsistManager::addConsist(DccLocoAddress *address){
    if (! (qobject_cast< DccLocoAddress*>(address))) {
        throw  IllegalArgumentException("address is not a DccLocoAddress object");
    }
    if (consistTable->contains((DccLocoAddress*)address)) {
        return consistTable->value((DccLocoAddress*)address);
    }
    DccConsistO1* consist = new DccConsistO1((DccLocoAddress*) address,nullptr, this);
//    {
//       //@Override
//       /*protected*/ void addToAdvancedConsist(DccLocoAddress LocoAddress, bool directionNormal){
//            addCalls +=1;
//}
//       //@Override
//       /*protected*/ void removeFromAdvancedConsist(DccLocoAddress LocoAddress){
//             removeCalls += 1;
//}
//       //@Override
//       /*public*/ void dispose(){
//       }
//    };
    consistTable->insert((DccLocoAddress*)address, consist);
    return consist;
}

/**
 * Does this implementation support a command station consist?
 */
//@Override
/*public*/ bool TestConsistManager::isCommandStationConsistPossible(){
    return false;
}

/**
 * Does a CS consist require a separate consist address? (or is the lead
 * loco to be used for the consist address)
 */
//@Override
/*public*/ bool TestConsistManager::csConsistNeedsSeperateAddress(){
    return false;
}

//@Override
/*public*/ void TestConsistManager::requestUpdateFromLayout() {
}

