#ifndef LOCONETSLOTTEST_H
#define LOCONETSLOTTEST_H

#include <QObject>
#include "exceptions.h"
#include "slotlistener.h"

class LocoNetInterfaceScaffold;
class LocoNetSlotTest : public QObject
{
    Q_OBJECT
public:
    explicit LocoNetSlotTest(QObject *parent = nullptr);
    /*public*/ void testGetSlotSend();
    /*public*/ void testCTor();
    /*public*/ void testMessageCTor() throw (LocoNetException);
    /*public*/ void testGetSlot();
    /*public*/ void testSetSlot() throw (LocoNetException);
    /*public*/ void testDecoderType() throw (LocoNetException);
    /*public*/ void testSlotStatus() throw (LocoNetException);
    /*public*/ void testss2() throw (LocoNetException);
    /*public*/ void testConsistStatus() throw (LocoNetException);
    /*public*/ void testIsForward() throw (LocoNetException);
    /*public*/ void testIsF0() throw (LocoNetException);
    /*public*/ void testIsF1() throw (LocoNetException);
    /*public*/ void testIsF2() throw (LocoNetException);
    /*public*/ void testIsF3() throw (LocoNetException);
    /*public*/ void testIsF4() throw (LocoNetException);
    /*public*/ void testIsF5() throw (LocoNetException);
    /*public*/ void testIsF6() throw (LocoNetException);
    /*public*/ void testIsF7() throw (LocoNetException);
    /*public*/ void testIsF8() throw (LocoNetException);
    /*public*/ void testIsF9() throw (LocoNetException);
    /*public*/ void testIsF10() throw (LocoNetException);
    /*public*/ void testIsF11() throw (LocoNetException);
    /*public*/ void testIsF12() throw (LocoNetException);
    /*public*/ void testIsF13() throw (LocoNetException);
    /*public*/ void testIsF14() throw (LocoNetException);
    /*public*/ void testIsF15() throw (LocoNetException);
    /*public*/ void testIsF16() throw (LocoNetException);
    /*public*/ void testIsF17() throw (LocoNetException);
    /*public*/ void testIsF18() throw (LocoNetException);
    /*public*/ void testIsF19() throw (LocoNetException);
    /*public*/ void testIsF20() throw (LocoNetException);
    /*public*/ void testIsF21() throw (LocoNetException);
    /*public*/ void testIsF22() throw (LocoNetException);
    /*public*/ void testIsF23() throw (LocoNetException);
    /*public*/ void testIsF24() throw (LocoNetException);
    /*public*/ void testIsF25() throw (LocoNetException);
    /*public*/ void testIsF26() throw (LocoNetException);
    /*public*/ void testIsF27() throw (LocoNetException);
    /*public*/ void testIsF28() throw (LocoNetException);
    /*public*/ void testLocoAddr() throw (LocoNetException) ;
    /*public*/ void testSpeed() throw (LocoNetException);
    /*public*/ void testDirf() throw (LocoNetException);
    /*public*/ void testSnd() throw (LocoNetException);
    /*public*/ void testID() throw (LocoNetException);
    /*public*/ void testWriteSlot() throw (LocoNetException);
    /*public*/ void testWriteThrottleID() throw (LocoNetException);
    /*public*/ void testConsistingStateVsSpeedAccept() throw (LocoNetException);
    /*public*/ void checkFunctionMessage();
    /*public*/ void checkFastClockGetSetMethods();
    /*public*/ void checkSetAndGetTrackStatus();
    /*public*/ void checkIsF0ToF8();
    /*public*/ void setUp();
    /*public*/ void tearDown();


signals:

public slots:
  private:
    LocoNetInterfaceScaffold* lnis;
};
class SlotListenerO2 : public SlotListener
{
    Q_OBJECT
    LocoNetSlotTest* smt;
public:
    SlotListenerO2(LocoNetSlotTest* smt) {this->smt = smt;}
    //@Override
    /*public*/ void notifyChangedSlot(LocoNetSlot* l) {
    }
};

#endif // LOCONETSLOTTEST_H
