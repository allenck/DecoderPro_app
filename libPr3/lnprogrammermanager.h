#ifndef LNPROGRAMMERMANAGER_H
#define LNPROGRAMMERMANAGER_H
#include "defaultprogrammermanager.h"
#include "slotmanager.h"

class SlotManager;
class LnProgrammerManager : public  DefaultProgrammerManager
{
 Q_OBJECT
public:
    LnProgrammerManager() {}
    LnProgrammerManager( LocoNetSystemConnectionMemo* memo);
    ~LnProgrammerManager() {}
    LnProgrammerManager(const LnProgrammerManager&) : DefaultProgrammerManager() {}
    /**
     * LocoNet command station does provide Ops Mode
     * @return true
     */
    /*public*/ bool isAddressedModePossible() override;
    /*public*/ AddressedProgrammer* getAddressedProgrammer(bool pLongAddress, int pAddress) override;
    /*public*/ AddressedProgrammer* reserveAddressedProgrammer(bool pLongAddress, int pAddress) override;
    /*public*/ QList<QString> getDefaultModes() override;
    /*public*/ QString toString() override;
    /*public*/ QObject* self() override {return (QObject*)this;}


private:
    LocoNetSystemConnectionMemo* memo;
    static /*final*/ ProgrammingMode* LOCONETSV1MODE;//    = new ProgrammingMode("LOCONETSV1MODE", Bundle.getMessage("LOCONETSV1MODE"));
    static /*final*/ ProgrammingMode* LOCONETSV2MODE;//    = new ProgrammingMode("LOCONETSV2MODE", Bundle.getMessage("LOCONETSV2MODE"));
    /**
     * Programming for Uhlenbrock (LocoNet) LNCV protocol.
     */
    /*public*/ static /*final*/ ProgrammingMode* LOCONETLNCVMODE;//    = new ProgrammingMode("LOCONETLNCVMODE", Bundle.getMessage("LOCONETLNCVMODE"));
    static /*final*/ ProgrammingMode* LOCONETBDOPSWMODE;// = new ProgrammingMode("LOCONETBDOPSWMODE", Bundle.getMessage("LOCONETBDOPSWMODE"));
    static /*final*/ ProgrammingMode* LOCONETCSOPSWMODE;// = new ProgrammingMode("LOCONETCSOPSWMODE", Bundle.getMessage("LOCONETCSOPSWMODE"));
    static /*final*/ ProgrammingMode* LOCONETOPSBOARD;//    = new ProgrammingMode("LOCONETOPSBOARD", Bundle.getMessage("LOCONETOPSBOARD"));

 friend class LnOpsModeProgrammer;
 friend class LnOpsModeProgrammerTest;
 friend class LncvDevicesManager;
};
Q_DECLARE_METATYPE(LnProgrammerManager)
#endif // LNPROGRAMMERMANAGER_H
