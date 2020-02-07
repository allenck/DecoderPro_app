#ifndef LNPROGRAMMERMANAGER_H
#define LNPROGRAMMERMANAGER_H
#include "defaultprogrammermanager.h"
#include "slotmanager.h"

class SlotManager;
class LnProgrammerManager : public  DefaultProgrammerManager
{
 Q_OBJECT
public:
    LnProgrammerManager( LocoNetSystemConnectionMemo* memo);
    ~LnProgrammerManager()
    {

    }
    LnProgrammerManager(const LnProgrammerManager&) : DefaultProgrammerManager() {}
    /**
     * LocoNet command station does provide Ops Mode
     * @return true
     */
    /*public*/ virtual bool isAddressedModePossible();
    /*public*/ virtual AddressedProgrammer* getAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ virtual AddressedProgrammer* reserveAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ QList<ProgrammingMode*> getDefaultModes();
    /*public*/ QString toString();
    /*public*/ QObject* self() override{return (QObject*)this;}


private:
    LocoNetSystemConnectionMemo* memo;
    static /*final*/ ProgrammingMode* LOCONETSV1MODE;//    = new ProgrammingMode("LOCONETSV1MODE", Bundle.getMessage("LOCONETSV1MODE"));
    static /*final*/ ProgrammingMode* LOCONETSV2MODE;//    = new ProgrammingMode("LOCONETSV2MODE", Bundle.getMessage("LOCONETSV2MODE"));
    static /*final*/ ProgrammingMode* LOCONETBDOPSWMODE;// = new ProgrammingMode("LOCONETBDOPSWMODE", Bundle.getMessage("LOCONETBDOPSWMODE"));
    static /*final*/ ProgrammingMode* LOCONETCSOPSWMODE;// = new ProgrammingMode("LOCONETCSOPSWMODE", Bundle.getMessage("LOCONETCSOPSWMODE"));
    static /*final*/ ProgrammingMode* LOCONETOPSBOARD;//    = new ProgrammingMode("LOCONETOPSBOARD", Bundle.getMessage("LOCONETOPSBOARD"));

 friend class LnOpsModeProgrammer;
 friend class LnOpsModeProgrammerTest;
};

#endif // LNPROGRAMMERMANAGER_H
