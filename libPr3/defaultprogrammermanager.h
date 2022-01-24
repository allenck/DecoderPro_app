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
    ~DefaultProgrammerManager() {}
    DefaultProgrammerManager(const DefaultProgrammerManager&) : QObject() {}
    /*public*/ QString getUserName()override;
    /*public*/ Programmer* getGlobalProgrammer() override;
    /*public*/ virtual AddressedProgrammer* getAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ Programmer* reserveGlobalProgrammer() override;
    /*public*/ void releaseGlobalProgrammer(Programmer* p) override;
    /*public*/ AddressedProgrammer* reserveAddressedProgrammer(bool pLongAddress, int pAddress) override;
    /*public*/ void releaseAddressedProgrammer(AddressedProgrammer *p) override;
    /**
     * Default programmer does not provide Ops Mode
     * @return false if there's no chance of getting one
     */
    /*public*/ bool isAddressedModePossible() override;
    /*public*/ bool isAddressedModePossible(/*@Nonnull*/ DccLocoAddress* l) override;

    /**
     * Allow for implementations that do not support Service mode programming
     * @return false if there's no chance of getting one
     */
    /*public*/ bool isGlobalProgrammerAvailable() override;
    /*public*/ QList<QString> getDefaultModes() override;
    /*public*/ QObject* self() override {return (QObject*)this;}

    /*public*/ QString toString() override;

private:
    /*private*/ Programmer* programmer;
    QString userName;// = "<Default>";
    static Logger* log;
};
Q_DECLARE_METATYPE(DefaultProgrammerManager)
#endif // DEFAULTPROGRAMMERMANAGER_H
