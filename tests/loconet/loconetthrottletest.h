#ifndef LOCONETTHROTTLETEST_H
#define LOCONETTHROTTLETEST_H
#include "abstractthrottletest.h"
#include "loconetslot.h"

class LocoNetInterfaceScaffold;
class SlotManager;
class LocoNetThrottleTest : public AbstractThrottleTest
{
    Q_OBJECT
public:
    LocoNetThrottleTest();
    Q_INVOKABLE /*public*/ void setUp() throw (Exception);
    Q_INVOKABLE /*public*/ void tearDown() throw (Exception);

public slots:

    /*public*/ void testCTor();
    /*public*/ void testSpeedSetting();
    /*public*/ void testGetIsForward() override;
    /*public*/ void testGetSpeedStepMode() override;
    /*public*/ void testGetSpeedIncrement();
    /*public*/ void testGetSpeed_float();
    /*public*/ void testSetF0();
    /*public*/ void testSetF1();
    /*public*/ void testSetF2();
    /*public*/ void testSetF3();
    /*public*/ void testSetF4();
    /*public*/ void testSetF5();
    /*public*/ void testSetF6();
    /*public*/ void testSetF7();
    /*public*/ void testSetF8();
    /*public*/ void testSetF9();
    /*public*/ void testSetF10();
    /*public*/ void testSetF11();
    /*public*/ void testSetF12();
    /*public*/ void testSetF13();
    /*public*/ void testSetF14();
    /*public*/ void testSetF15();
    /*public*/ void testSetF16();
    /*public*/ void testSetF17();
    /*public*/ void testSetF18();
    /*public*/ void testSetF19();
    /*public*/ void testSetF20();
    /*public*/ void testSetF21();
    /*public*/ void testSetF22();
    /*public*/ void testSetF23();
    /*public*/ void testSetF24();
    /*public*/ void testSetF25();
    /*public*/ void testSetF26();
    /*public*/ void testSetF27();
    /*public*/ void testSetF28();
    /*public*/ void testSendFunctionGroup1();
    /*public*/ void testSendFunctionGroup2();
    /*public*/ void testSendFunctionGroup3();
    /*public*/ void testSendFunctionGroup4();
    /*public*/ void testSendFunctionGroup5();
    /*public*/ void testGetF2Momentary();

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
    /*public*/ int consistStatus() override {
        return LnConstants::CONSIST_NO;
    }

    //@Override
    /*public*/ int speed() override{
        return 0;
    }
};
class LocoNetSlotO2 : public LocoNetSlot
{
    Q_OBJECT
public:
    LocoNetSlotO2(int slotNum, QObject* parent = nullptr) : LocoNetSlot(slotNum, parent) {}
    //@Override
    /*public*/ int consistStatus() override {
        return LnConstants::CONSIST_TOP;
    }

    //@Override
    /*public*/ int speed() override{
        return 0;
    }
};
class LocoNetSlotO3 : public LocoNetSlot
{
    Q_OBJECT
public:
    LocoNetSlotO3(int slotNum, QObject* parent = nullptr) : LocoNetSlot(slotNum, parent) {}
    //@Override
    /*public*/ int consistStatus() override {
        return LnConstants::CONSIST_MID;
    }

    //@Override
    /*public*/ int speed() override{
        return 0;
    }
};
class LocoNetSlotO4 : public LocoNetSlot
{
    Q_OBJECT
public:
    LocoNetSlotO4(int slotNum, QObject* parent = nullptr) : LocoNetSlot(slotNum, parent) {}
    //@Override
    /*public*/ int consistStatus() override{
        return LnConstants::CONSIST_SUB;
    }

    //@Override
    /*public*/ int speed() override{
        return 0;
    }
};

#endif // LOCONETTHROTTLETEST_H
