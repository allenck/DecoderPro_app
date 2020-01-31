#ifndef DEFERRINGPROGRAMMERMANAGER_H
#define DEFERRINGPROGRAMMERMANAGER_H

#include <QObject>
#include "addressedprogrammermanager.h"
class Logger;
class ProgrammingMode;
class locoAddress;
class AddressedProgrammer;
class Programmer;
class DeferringProgrammerManager : public QObject, public AddressedProgrammerManager, public GlobalProgrammerManager
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
 /*public*/ bool isAddressedModePossible(locoAddress* l);
 /*public*/ QList<ProgrammingMode*> getDefaultModes();

signals:

public slots:

private:
 QString userName;// = "<Default>";
 Logger* log;

};

#endif // DEFERRINGPROGRAMMERMANAGER_H
