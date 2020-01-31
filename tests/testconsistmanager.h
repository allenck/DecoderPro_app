#ifndef TESTCONSISTMANAGER_H
#define TESTCONSISTMANAGER_H
#include "abstractconsistmanager.h"
#include "dccconsist.h"

class TestConsistManager : public AbstractConsistManager
{
 Q_OBJECT
public:
 TestConsistManager(QObject* parent = nullptr);
 // package /*protected*/ integers for tests to use
 int addCalls; // records the number of times addToAdvancedConsist is called
 int removeCalls; // records the  number of times removeFromAdancedConsist is called.
 /*public*/ bool isCommandStationConsistPossible();
 /*public*/ bool csConsistNeedsSeperateAddress();
 /*public*/ void requestUpdateFromLayout();

private:
protected:
 /*protected*/ DccConsist *addConsist(DccLocoAddress* address) override;

};

class DccConsistO1 : public DccConsist
{
 Q_OBJECT
 TestConsistManager* tcm;
public:
 DccConsistO1(DccLocoAddress* address, AddressedProgrammerManager* apm, TestConsistManager* tcm)
  : DccConsist(address, apm)
 {
  this->tcm = tcm;
 }
 //@Override
 /*public*/ void dispose(){}

protected:
 //@Override
 /*protected*/ void addToAdvancedConsist(DccLocoAddress* locoAddress, bool directionNormal){
      tcm->addCalls +=1;
 }
 //@Override
 /*protected*/ void removeFromAdvancedConsist(DccLocoAddress locoAddress){
       tcm->removeCalls += 1;
 }
};

#endif // TESTCONSISTMANAGER_H
