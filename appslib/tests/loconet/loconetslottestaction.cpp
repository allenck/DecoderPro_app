#include "loconetslottestaction.h"
#include "loconetslottest.h"
#include "assert1.h"
#include "joptionpane.h"


LocoNetSlotTestAction::LocoNetSlotTestAction(QObject *parent) : AbstractAction(tr("LocoNet Slot test"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LocoNetSlotTestAction::actionPerformed()
{
    LocoNetSlotTest* lnst = new LocoNetSlotTest();
    try
    {
      lnst->setUp();
      lnst->testGetSlotSend();
      lnst->testCTor();
      lnst->testMessageCTor();
      lnst->testGetSlot();
      lnst->testSetSlot();
      lnst->testDecoderType();
      lnst->testSlotStatus();
      lnst->testss2();
      lnst->testConsistStatus();
      lnst->testIsForward();
      lnst->testIsF0();
      lnst->testIsF1();
      lnst->testIsF2();
      lnst->testIsF3();
      lnst->testIsF4();
      lnst->testIsF5();
      lnst->testIsF6();
      lnst->testIsF7();
      lnst->testIsF8();
      lnst->testIsF9();
      lnst->testIsF10();
      lnst->testIsF11();
      lnst->testIsF12();
      lnst->testIsF13();
      lnst->testIsF14();
      lnst->testIsF15();
      lnst->testIsF16();
      lnst->testIsF17();
      lnst->testIsF18();
      lnst->testIsF19();
      lnst->testIsF20();
      lnst->testIsF21();
      lnst->testIsF22();
      lnst->testIsF23();
      lnst->testIsF24();
      lnst->testIsF25();
      lnst->testIsF26();
      lnst->testIsF27();
      lnst->testIsF28();
      lnst->testLocoAddr();
      lnst->testSpeed();
      lnst->testDirf();
      lnst->testSnd();
      lnst->testID();
      lnst->testWriteSlot();
      lnst->testWriteThrottleID();
      lnst->testConsistingStateVsSpeedAccept();
      lnst->checkFunctionMessage();
      lnst->checkFastClockGetSetMethods();
      lnst->checkSetAndGetTrackStatus();
      lnst->checkIsF0ToF8();}
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
    lnst->tearDown();
}
