#ifndef DEFERRINGPROGRAMMERMANAGER_H
#define DEFERRINGPROGRAMMERMANAGER_H

#include "programmermanager.h"

class Logger;
class ProgrammingMode;
class LocoAddress;
class AddressedProgrammer;
class Programmer;
class DeferringProgrammerManager : public ProgrammerManager
{
 Q_OBJECT
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
 /*public*/ QList<ProgrammingMode*> getDefaultModes();

signals:

public slots:

private:
 QString userName;// = "<Default>";
 Logger* log;

};

#endif // DEFERRINGPROGRAMMERMANAGER_H
