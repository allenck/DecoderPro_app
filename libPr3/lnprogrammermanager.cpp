#include "lnprogrammermanager.h"
#include "lnopsmodeprogrammer.h"
#include "programmingmode.h"

LnProgrammerManager::LnProgrammerManager(SlotManager* pSlotManager, LocoNetSystemConnectionMemo* memo):
    DefaultProgrammerManager(pSlotManager, memo)
{
 setObjectName("LnProgrammerManager");
 //super(pSlotManager, memo);
 mSlotManager = pSlotManager;
 this->memo = memo;
}
/**
 * Extend DefaultProgrammerManager to provide ops mode programmers on LocoNet
 *
 * @see         jmri.ProgrammerManager
 * @author	Bob Jacobsen Copyright (C) 2002
 * @version	$Revision: 18841 $
 */
//public class LnProgrammerManager  extends DefaultProgrammerManager {

    //private Programmer mProgrammer;

//    public LnProgrammerManager(SlotManager pSlotManager, LocoNetSystemConnectionMemo memo) {
//        super(pSlotManager, memo);
//        mSlotManager = pSlotManager;
//    }


/**
 * LocoNet command station does provide Ops Mode
 * @return true
 */
/*public*/ bool LnProgrammerManager::isAddressedModePossible() {return true;}

/*public*/ AddressedProgrammer* LnProgrammerManager::getAddressedProgrammer(bool pLongAddress, int pAddress) {
    return new LnOpsModeProgrammer(mSlotManager, memo, pAddress, pLongAddress);
}

/*public*/ AddressedProgrammer* LnProgrammerManager::reserveAddressedProgrammer(bool pLongAddress, int pAddress) {
 Q_UNUSED(pLongAddress)
 Q_UNUSED(pAddress)
    return NULL;
}

/*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETSV1MODE    = new ProgrammingMode("LOCONETSV1MODE", tr("System Variable Type 1"));
    /*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETSV2MODE    = new ProgrammingMode("LOCONETSV2MODE", tr("System Variable Type 2"));
    /*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETBDOPSWMODE = new ProgrammingMode("LOCONETBDOPSWMODE", tr("Board Op Switches"));
    /*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETCSOPSWMODE = new ProgrammingMode("LOCONETCSOPSWMODE", tr("Cmd Station Op Switches"));

/**
 * Types implemented here.
 */
// @Override
/*public*/ QList<ProgrammingMode*> LnProgrammerManager::getDefaultModes()
{
 QList<ProgrammingMode*> ret =  QList<ProgrammingMode*>();
 ret.append(ProgrammingMode::OPSBYTEMODE);
 ret.append(LOCONETSV2MODE);
 ret.append(LOCONETSV1MODE); // the show in interface in order listed here
 return ret;
}
