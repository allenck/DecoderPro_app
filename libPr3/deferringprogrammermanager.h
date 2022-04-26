#ifndef DEFERRINGPROGRAMMERMANAGER_H
#define DEFERRINGPROGRAMMERMANAGER_H

#include "defaultprogrammermanager.h"
#include "addressedprogrammermanager.h"
#include "abstractinstanceinitializer.h"

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
 /*public*/ void releaseAddressedProgrammer(AddressedProgrammer* p)override ;
 /*public*/ bool isAddressedModePossible()override;
 /*public*/ bool isAddressedModePossible(DccLocoAddress* l)override;
 /*public*/ QList<QString> getDefaultModes()override;
  //@ServiceProvider(service=InstanceInitializer.class)
  /*public*/ /*static*/ /*final*/ class Initializer : public AbstractInstanceInitializer {

      //@Override
      /*public*/ /*<T>*/ QObject* getDefault(/*Class<T>*/QString type)const override {
          if (type == "AddressedProgrammerManager") {
              return new DeferringProgrammerManager();
          }
          if (type == "GlobalProgrammerManager") {
              return new DeferringProgrammerManager();
          }
          return AbstractInstanceInitializer::getDefault(type);
      }

      //@Override
      /*public*/ QSet</*Class<?>*/QString>* getInitalizes() {
          QSet</*Class<?>*/QString>* set = AbstractInstanceInitializer::getInitalizes();
          set->insert("AddressedProgrammerManager");
          set->insert("GlobalProgrammerManager");
          return set;
      }

  };

signals:

public slots:

private:
 QString userName;// = "<Default>";
 static Logger* log;

};

#endif // DEFERRINGPROGRAMMERMANAGER_H
