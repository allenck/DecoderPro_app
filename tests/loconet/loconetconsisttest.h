#ifndef LOCONETCONSISTTEST_H
#define LOCONETCONSISTTEST_H

#include "abstractconsisttestbase.h"

class LocoNetInterfaceScaffold;
class SlotManager;
class LocoNetSystemConnectionMemo;
class LnThrottleManager;

class LocoNetConsistTest : public AbstractConsistTestBase
{
    Q_OBJECT
public:
    explicit LocoNetConsistTest(QObject *parent = nullptr);
    Q_INVOKABLE/*public*/ void setUp() ;
    Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCtor2();
 /*public*/ void testGetConsistType();
 /*public*/ void testSetConsistTypeCS();
 /*public*/ void checkAddressAllowedBad();
 /*public*/ void checkAddressAllowedGoodAdvanced();
 /*public*/ void checkAddressAllowedBadAdvanced();
 /*public*/ void checkSizeLimitCS();
 /*public*/ void checkGetLocoDirectionCS();

private:
    LocoNetInterfaceScaffold* lnis;
    SlotManager* slotmanager;
    LocoNetSystemConnectionMemo* memo;
    LnThrottleManager* ltm;
    /*private*/ void ReturnSlotInfo();

};

#endif // LOCONETCONSISTTEST_H
