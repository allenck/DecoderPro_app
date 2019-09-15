#include "slotmanagertestaction.h"
#include "abstractaction.h"
#include "slotmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"

SlotManagerTestAction::SlotManagerTestAction(QObject *parent) : AbstractAction(tr("Slot Manager Test"), parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void SlotManagerTestAction::actionPerformed()
{
    SlotManagerTest* smt = new SlotManagerTest();
    smt->setUp();
    try
    {
        smt->testGetDirectDccPacketOK();
        smt->testGetDirectFunctionAddressOK();
        smt->testGetSlotSend();
        smt->testGetSlotRcv();
        smt->testReadCVPaged();
        smt->testReadCVDirect();
        smt->testReadCVOpsModeLong();
        smt->testReadCVOpsModeShort();
        smt->testWriteCVPaged();
        smt->testWriteCVRegister();
        smt->testWriteCVDirectStringDCS240();
        smt->testLackLogic();

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    smt->tearDown();
}
