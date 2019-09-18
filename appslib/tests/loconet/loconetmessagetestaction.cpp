#include "loconetmessagetestaction.h"
#include "loconetmessagetest.h"
#include "assert1.h"
#include "joptionpane.h"

LocoNetMessageTestAction::LocoNetMessageTestAction(QObject* parent) : AbstractAction(tr("LocoNetMessage Test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LocoNetMessageTestAction::actionPerformed()
{
    LocoNetMessageTest* lnmt = new LocoNetMessageTest();
    lnmt->setUp();
    try
    {
     lnmt->testCtor();
     lnmt->testArrayCtor();
     lnmt->testGetPeerXfr();
     lnmt->testConstructorNoParams();
     lnmt->testConstructorString();
     lnmt->testGetPeerXfrData();
     lnmt->testEqualsFromInt();
     lnmt->testEqualsFromBytes();
     lnmt->testEqualsFromString();
     lnmt->testEqualsSpecificCase();
     lnmt->testToString();
     lnmt->testToMonitorString();
     lnmt->testLowByte();
     lnmt->testHighByte();
     lnmt->testHighBit();
     lnmt->testInputRepAddr();
     lnmt->testSensorAddr();
     lnmt->testGetOpCodeHex();
     lnmt->testTurnoutAddr();
     lnmt->testGetElement();
     lnmt->testsetElement();
     lnmt->testHashCode();
     lnmt->testSetParity();
     lnmt->testCheckParity();;
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
    lnmt->tearDown();
}
