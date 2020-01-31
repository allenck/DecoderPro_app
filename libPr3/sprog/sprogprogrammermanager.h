#ifndef SPROGPROGRAMMERMANAGER_H
#define SPROGPROGRAMMERMANAGER_H
#include "defaultprogrammermanager.h"
#include "sprogconstants.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
class SprogSystemConnectionMemo;
 class SprogProgrammerManager : public DefaultProgrammerManager
 {
  Q_OBJECT
 public:
  /*public*/ SprogProgrammerManager(Programmer* serviceModeProgrammer, SprogSystemConnectionMemo* memo, QObject* parent = 0);
  /*public*/ SprogProgrammerManager(Programmer* serviceModeProgrammer, SprogConstants::SprogMode mode, SprogSystemConnectionMemo* memo, QObject* parent = 0);
  /*public*/ bool isAddressedModePossible();
  /*public*/ bool isGlobalProgrammerAvailable();
  /*public*/ AddressedProgrammer* getAddressedProgrammer(bool pLongAddress, int pAddress);
  /*public*/ AddressedProgrammer* reserveAddressedProgrammer(bool pLongAddress, int pAddress);
  /*public*/ QObject* self() {return (QObject*)this;}
  /*public*/ QString toString();

 private:
  /*private*/ SprogConstants::SprogMode mode;
  /*private*/ SprogSystemConnectionMemo* adapterMemo;// = null;

 };
}
#endif // SPROGPROGRAMMERMANAGER_H
