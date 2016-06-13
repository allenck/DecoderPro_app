#ifndef LNPROGRAMMERMANAGER_H
#define LNPROGRAMMERMANAGER_H
#include "defaultprogrammermanager.h"
#include "slotmanager.h"

class SlotManager;
class LnProgrammerManager : public  DefaultProgrammerManager
{
public:
    LnProgrammerManager(SlotManager* pSlotManager, LocoNetSystemConnectionMemo* memo);
    /**
     * LocoNet command station does provide Ops Mode
     * @return true
     */
    /*public*/ virtual bool isAddressedModePossible();
    /*public*/ virtual Programmer* getAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ virtual AddressedProgrammer* reserveAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ QList<ProgrammingMode*>* getDefaultModes();

private:
    SlotManager* mSlotManager;
    LocoNetSystemConnectionMemo* memo;
    static /*final*/ ProgrammingMode* LOCONETSV1MODE;//    = new ProgrammingMode("LOCONETSV1MODE", Bundle.getMessage("LOCONETSV1MODE"));
    static /*final*/ ProgrammingMode* LOCONETSV2MODE;//    = new ProgrammingMode("LOCONETSV2MODE", Bundle.getMessage("LOCONETSV2MODE"));
    static /*final*/ ProgrammingMode* LOCONETBDOPSWMODE;// = new ProgrammingMode("LOCONETBDOPSWMODE", Bundle.getMessage("LOCONETBDOPSWMODE"));
    static /*final*/ ProgrammingMode* LOCONETCSOPSWMODE;// = new ProgrammingMode("LOCONETCSOPSWMODE", Bundle.getMessage("LOCONETCSOPSWMODE"));

 friend class LnOpsModeProgrammer;
};

#endif // LNPROGRAMMERMANAGER_H
