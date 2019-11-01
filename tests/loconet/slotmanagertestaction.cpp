#include "slotmanagertestaction.h"
#include "slotmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"


SlotManagerTestAction::SlotManagerTestAction(QObject *parent) : AbstractAction(tr("Slot Manager Test"), parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void SlotManagerTestAction::actionPerformed()
{
    SlotManagerTest* test = new SlotManagerTest();
    try
    {
      QStringList testList = QStringList()
        << "testGetDirectDccPacketOK"
        << "testGetDirectFunctionAddressOK"
        << "testGetSlotSend"
        << "testGetSlotRcv"
        << "testReadCVPaged"
        << "testReadCVDirect"

        << "testReadCVOpsModeLong"
        << "testReadCVOpsModeShort"
        << "testWriteCVPaged"
        << "testWriteCVRegister"
        << "testWriteCVDirectStringDCS240"
        << "testLackLogic"
        << "testWriteCVDirectStringDCS240Interrupted"
        << "testWriteCVOpsLongAddr"
        << "testWriteCVOpsShortAddr"
        << "testWriteThroughFacade"
        << "testReadThroughFacade"
        << "testReadThroughFacadeFail"
        << "testGetProgrammingModes"
        << "testSendPacket";
      JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* SlotManagerTestAction::log = LoggerFactory::getLogger("SlotManagerTestAction");
