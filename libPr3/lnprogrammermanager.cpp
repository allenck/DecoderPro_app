#include "lnprogrammermanager.h"
#include "lnopsmodeprogrammer.h"
#include "programmingmode.h"
#include "lndeferprogrammer.h"

LnProgrammerManager::LnProgrammerManager(LocoNetSystemConnectionMemo* memo)
 : DefaultProgrammerManager(new LnDeferProgrammer(memo), (SystemConnectionMemo*)memo)
{
 setObjectName("LnProgrammerManager");
 //super(new LnDeferProgrammer(memo), memo)
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

/**
 * LocoNet command station does provide Ops Mode
 * @return true
 */
/*public*/ bool LnProgrammerManager::isAddressedModePossible() {return true;}

/*public*/ AddressedProgrammer* LnProgrammerManager::getAddressedProgrammer(bool pLongAddress, int pAddress) {
    return new LnOpsModeProgrammer(memo, pAddress, pLongAddress);
}

/*public*/ AddressedProgrammer* LnProgrammerManager::reserveAddressedProgrammer(bool pLongAddress, int pAddress) {
 Q_UNUSED(pLongAddress)
 Q_UNUSED(pAddress)
    return NULL;
}

/*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETSV1MODE    = new ProgrammingMode("LOCONETSV1MODE", tr("System Variable Type 1"));
/*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETSV2MODE    = new ProgrammingMode("LOCONETSV2MODE", tr("System Variable Type 2"));
/**
 * Programming for Uhlenbrock (LocoNet) LNCV protocol.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETLNCVMODE    = new ProgrammingMode("LOCONETLNCVMODE", tr("LNCV (Uhlenbrock)"));
/*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETBDOPSWMODE = new ProgrammingMode("LOCONETBDOPSWMODE", tr("Board Op Switches"));
/*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETCSOPSWMODE = new ProgrammingMode("LOCONETCSOPSWMODE", tr("Cmd Station Op Switches"));
/**
 * Programming in Ops mode via the LocoNet cable.
 */
/*static*/ /*final*/ ProgrammingMode* LnProgrammerManager::LOCONETOPSBOARD    = new ProgrammingMode("LOCONETOPSBOARD", tr("LocoNet-Attached Board"));

/**
 * Types implemented here.
 */
// @Override
/*public*/ QList<QString> LnProgrammerManager::getDefaultModes()
{
 QList<QString> ret =  QList<QString>();
 ret.append("OPSBYTEMODE");
 ret.append("LOCONETOPSBOARD");
 ret.append("LOCONETSV2MODE");
 ret.append("LOCONETSV1MODE"); // the show in interface in order listed here
 return ret;
}

/*public*/ QString LnProgrammerManager::toString() {return "LnProgrammerManager";}
