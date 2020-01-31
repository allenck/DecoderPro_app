#include "debugprogrammermanager.h"
#include "systemconnectionmemo.h"
#include "progdebugger.h"

//DebugProgrammerManager::DebugProgrammerManager(QObject *parent) :
//    DefaultProgrammerManager(parent)
//{
//}
/**
 * Provides an implementation of ProgrammerManager for the
 * debug programmer. It will consistently return the same
 * ProgDebugger instance for a given request.
 * <P>
 * It uses the DefaultProgrammerManager to handle the service
 * mode operations.
 *
 * @see             jmri.ProgrammerManager
 * @author			Bob Jacobsen Copyright (C) 2002
 * @version			$Revision: 27685 $
 */
///*public*/ class DebugProgrammerManager extends DefaultProgrammerManager {


/*public*/ DebugProgrammerManager::DebugProgrammerManager(QObject *parent) :
    DefaultProgrammerManager( new ProgDebugger, parent) {
   //super(new ProgDebugger());
    common();
}

/*public*/ DebugProgrammerManager::DebugProgrammerManager(SystemConnectionMemo* memo, QObject *parent) {
    //super(new ProgDebugger(), memo);
    common();
}

void DebugProgrammerManager::common()
{
 setObjectName("DebugProgrammerManager");
 opsProgrammers =  QHash<int,ProgDebugger*>();
 log = new Logger("DebugProgrammerManager");
}

/*public*/ AddressedProgrammer* DebugProgrammerManager::getAddressedProgrammer(bool pLongAddress, int pAddress) {
    int address = pAddress;
    if (!pLongAddress) address = -address;
    // look for an existing entry by getting something from hash table
    ProgDebugger* saw = opsProgrammers.value(address);
    if (saw!=NULL) {
        if (log->isDebugEnabled()) log->debug("return existing ops-mode programmer "
                                            +QString::number(pAddress)+" "+QString::number(pLongAddress));
        return saw;
    }
    // if not, save a new one & return it
    opsProgrammers.insert(address, saw = new ProgDebugger(pLongAddress, pAddress));
    if (log->isDebugEnabled()) log->debug("return new ops-mode programmer "
                                            +QString::number(pAddress)+" "+QString::number(pLongAddress));
    return saw;
}

/*public*/ AddressedProgrammer* DebugProgrammerManager::reserveAddressedProgrammer(bool pLongAddress, int pAddress) {
    return NULL;
}

/**
 * Debug programmer does provide Ops Mode
 * @return true
 */
/*public*/ bool DebugProgrammerManager::isAddressedModePossible() {return true;}

/*public*/ QString DebugProgrammerManager::toString() {return "DebugProgrammerManager";}
