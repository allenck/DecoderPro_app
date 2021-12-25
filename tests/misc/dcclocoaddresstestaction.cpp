#include "dcclocoaddresstestaction.h"
#include "dcclocoaddresstest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"

DccLocoAddressTestAction::DccLocoAddressTestAction( QObject* parent) : AbstractAction(tr("DccLocoAddressTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void DccLocoAddressTestAction::actionPerformed()
{
    DccLocoAddressTest* pt = new DccLocoAddressTest();
    try
    {
        QStringList testList = QStringList()
        << "testValue1"
        << "testValue2"
        << "testValue3"
        << "testCopy1"
        << "testEquals1"
        << "testEquals2"
        << "testEquals3"
        << "testEquals4"
        << "testHash0"
        << "testHash1"
        << "testHash2"
        << "testHash3"
        << "testHash4"
        << "testHash5"
        << "testHash6";
        JUnitUtil::runTests(pt, testList);
    }
    catch (AssertionError* ex)
    {
        JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* DccLocoAddressTestAction::log = LoggerFactory::getLogger("DccLocoAddressTestAction");
