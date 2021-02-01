#ifndef DEFERRINGPROGRAMMERMANAGER_H
#define DEFERRINGPROGRAMMERMANAGER_H

#include "defaultprogrammermanager.h"
#include "addressedprogrammermanager.h"
class Logger;
class ProgrammingMode;
class LocoAddress;
class AddressedProgrammer;
class Programmer;
// Note: we are subclassing DefaultProgrammerManager even though all of it's methods are overridden because
// we want to be able to cast a GlobalProgrammerManager or AddressedProgrammer manager to a valid QObject
// derived pointer.
class DeferringProgrammerManager : public DefaultProgrammerManager//QObject, public AddressedProgrammerManager, public GlobalProgrammerManager
{
 Q_OBJECT
 Q_INTERFACES(AddressedProgrammerManager GlobalProgrammerManager)
public:
 explicit DeferringProgrammerManager(QObject *parent = 0);
 /*public*/ QString getUserName();
 /*public*/ QString toString();
 /*public*/ Programmer* getGlobalProgrammer();
 /*public*/ Programmer* reserveGlobalProgrammer();
 /*public*/ void releaseGlobalProgrammer(Programmer* p) ;
 /*public*/ bool isGlobalProgrammerAvailable();
 /*public*/ AddressedProgrammer* getAddressedProgrammer(bool pLongAddress, int pAddress);
 /*public*/ AddressedProgrammer* reserveAddressedProgrammer(bool pLongAddress, int pAddress) ;
 /*public*/ void releaseAddressedProgrammer(AddressedProgrammer* p) ;
 /*public*/ bool isAddressedModePossible();
 /*public*/ bool isAddressedModePossible(LocoAddress* l);
 /*public*/ QList<QString> getDefaultModes();

signals:

public slots:

private:
 QString userName;// = "<Default>";
 Logger* log;

};

#endif // DEFERRINGPROGRAMMERMANAGER_H
