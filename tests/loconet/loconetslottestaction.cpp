#include "loconetslottestaction.h"
#include "loconetslottest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"

LocoNetSlotTestAction::LocoNetSlotTestAction(QObject *parent) : AbstractAction(tr("LocoNet Slot test"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LocoNetSlotTestAction::actionPerformed()
{
    LocoNetSlotTest* test = new LocoNetSlotTest();
    try
    {
     QStringList testList = QStringList()
      << "testGetSlotSend"
      << "testCTor"
      << "testMessageCTor"
      << "testGetSlot"
      << "testSetSlot"
      << "testDecoderType"
      << "testSlotStatus"
      << "testss2"
      << "testConsistStatus"
      << "testIsForward"
      << "testIsF0"
      << "testIsF1"
      << "testIsF2"
      << "testIsF3"
      << "testIsF4"
      << "testIsF5"
      << "testIsF6"
      << "testIsF7"
      << "testIsF8"
      << "testIsF9"
      << "testIsF10"
      << "testIsF11"
      << "testIsF12"
      << "testIsF13"
      << "testIsF14"
      << "testIsF15"
      << "testIsF16"
      << "testIsF17"
      << "testIsF18"
      << "testIsF19"
      << "testIsF20"
      << "testIsF21"
      << "testIsF22"
      << "testIsF23"
      << "testIsF24"
      << "testIsF25"
      << "testIsF26"
      << "testIsF27"
      << "testIsF28"
      << "testLocoAddr"
      << "testSpeed"
      << "testDirf"
      << "testSnd"
      << "testID"
      << "testWriteSlot"
      << "testWriteThrottleID"
      << "testConsistingStateVsSpeedAccept"
      << "checkFunctionMessage"
//      << "checkFastClockGetSetMethods"
      << "checkSetAndGetTrackStatus"
      << "checkIsF0ToF8";
//        foreach(QString testName, testList)
//        {
//         log->info(tr("begin '%1'").arg(testName));
//         QMetaObject::invokeMethod(test, testName.toLocal8Bit(), Qt::DirectConnection);
//         log->info(tr("end '%1'").arg(testName));
//        }
     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
    catch(Exception* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
}

Logger* LocoNetSlotTestAction::log = LoggerFactory::getLogger("LocoNetSlotTestAction");
