#ifndef LOCONETTHROTTLETEST_H
#define LOCONETTHROTTLETEST_H
#include "abstractthrottletest.h"
#include "loconetslot.h"

class LocoNetInterfaceScaffold;
class SlotManager;
class LocoNetThrottleTest : public AbstractThrottleTest
{
public:
    LocoNetThrottleTest();
    /*public*/ void testCTor();
    /*public*/ void testSpeedSetting();
    /*public*/ void testGetIsForward();

    /*public*/ void setUp() throw (Exception);
    /*public*/ void tearDown();
private:
    /*private*/ LocoNetInterfaceScaffold* lnis;
    /*private*/ SlotManager* slotmanager;
    /*private*/ LocoNetSystemConnectionMemo* memo = nullptr;

};
class LocoNetSlotO1 : public LocoNetSlot
{
    Q_OBJECT
public:
    //@Override
    LocoNetSlotO1(int slotNum, QObject* parent = nullptr) : LocoNetSlot(slotNum, parent) {}
    /*public*/ int consistStatus() {
        return LnConstants::CONSIST_NO;
    }

    //@Override
    /*public*/ int speed() {
        return 0;
    }
};
class LocoNetSlotO2 : public LocoNetSlot
{
    Q_OBJECT
public:
    LocoNetSlotO2(int slotNum, QObject* parent = nullptr) : LocoNetSlot(slotNum, parent) {}
    //@Override
    /*public*/ int consistStatus() {
        return LnConstants::CONSIST_TOP;
    }

    //@Override
    /*public*/ int speed() {
        return 0;
    }
};
class LocoNetSlotO3 : public LocoNetSlot
{
    Q_OBJECT
public:
    LocoNetSlotO3(int slotNum, QObject* parent = nullptr) : LocoNetSlot(slotNum, parent) {}
    //@Override
    /*public*/ int consistStatus() {
        return LnConstants::CONSIST_MID;
    }

    //@Override
    /*public*/ int speed() {
        return 0;
    }
};
class LocoNetSlotO4 : public LocoNetSlot
{
    Q_OBJECT
public:
    LocoNetSlotO4(int slotNum, QObject* parent = nullptr) : LocoNetSlot(slotNum, parent) {}
    //@Override
    /*public*/ int consistStatus() {
        return LnConstants::CONSIST_SUB;
    }

    //@Override
    /*public*/ int speed() {
        return 0;
    }
};

#endif // LOCONETTHROTTLETEST_H
