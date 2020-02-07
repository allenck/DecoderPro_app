#ifndef DEFAULTPROGRAMMERMANAGER_H
#define DEFAULTPROGRAMMERMANAGER_H
#include "addressedprogrammermanager.h"
#include "systemconnectionmemo.h"

class DefaultProgrammerManager : public QObject, public AddressedProgrammerManager, public GlobalProgrammerManager
{
 Q_OBJECT
 Q_INTERFACES(AddressedProgrammerManager GlobalProgrammerManager)
public:
    DefaultProgrammerManager(QObject* parent = 0);
    /*public*/ DefaultProgrammerManager(Programmer* pProgrammer,QObject* parent = 0);
    /*public*/ DefaultProgrammerManager(Programmer* pProgrammer, SystemConnectionMemo* memo,QObject* parent = 0);
    /*public*/ QString getUserName();
    /*public*/ Programmer* getGlobalProgrammer();
    /*public*/ virtual AddressedProgrammer* getAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ Programmer* reserveGlobalProgrammer();
    /*public*/ void releaseGlobalProgrammer(Programmer* p);
    /*public*/ AddressedProgrammer* reserveAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ void releaseAddressedProgrammer(AddressedProgrammer *p);
    /**
     * Default programmer does not provide Ops Mode
     * @return false if there's no chance of getting one
     */
    /*public*/ bool isAddressedModePossible();
    /*public*/ bool isAddressedModePossible(/*@Nonnull*/ DccLocoAddress* l);

    /**
     * Allow for implementations that do not support Service mode programming
     * @return false if there's no chance of getting one
     */
    /*public*/ bool isGlobalProgrammerAvailable() override;
    /*public*/ QList<ProgrammingMode*> getDefaultModes() override;
    /*public*/ QObject* self() override {return (QObject*)this;}

    /*public*/ QString toString();

private:
    /*private*/ Programmer* programmer;
    QString userName;// = "<Default>";
    static Logger* log;
};

#endif // DEFAULTPROGRAMMERMANAGER_H
