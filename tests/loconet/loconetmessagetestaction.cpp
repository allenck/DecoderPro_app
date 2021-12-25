#include "loconetmessagetestaction.h"
#include "loconetmessagetest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"

LocoNetMessageTestAction::LocoNetMessageTestAction(QObject* parent) : AbstractAction(tr("LocoNetMessage Test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LocoNetMessageTestAction::actionPerformed()
{
    LocoNetMessageTest* test = new LocoNetMessageTest();
    try
    {
     QStringList testList = QStringList()
     << "testCtor"
     << "testArrayCtor"
     << "testGetPeerXfr"
     << "testConstructorNoParams"
     << "testConstructorString"
     << "testGetPeerXfrData"
     << "testEqualsFromInt"
     << "testEqualsFromBytes"
     << "testEqualsFromString"
     << "testEqualsSpecificCase"
     << "testToString"
     << "testToMonitorString"
     << "testLowByte"
     << "testHighByte"
     << "testHighBit"
     << "testInputRepAddr"
     << "testSensorAddr"
     << "testGetOpCodeHex"
     << "testTurnoutAddr"
     << "testGetElement"
     << "testsetElement"
     << "testHashCode"
     << "testSetParity"
     << "testCheckParity";
//     foreach(QString testName, testList)
//     {
//      log->info(tr("begin '%1'").arg(testName));
//      QMetaObject::invokeMethod(test, testName.toLocal8Bit(), Qt::DirectConnection);
//      log->info(tr("end '%1'").arg(testName));
//     }
     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
}
Logger* LocoNetMessageTestAction::log = LoggerFactory::getLogger("LocoNetMessageTestAction");
