#include "consisttoolframetestaction.h"
#include "consisttoolframetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
ConsistToolFrameTestAction::ConsistToolFrameTestAction(QObject *parent) : AbstractAction(tr("ConsistToolFrameTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void ConsistToolFrameTestAction::actionPerformed()
{
    ConsistToolFrameTest* smt = new ConsistToolFrameTest();
    try
    {
     QStringList testList = QStringList()
       << "testCtor"
       << "testCtorWithCSpossible"
       << "testAdd"
       << "testReverseButton"
       << "testRestoreButton"
       << "testThrottle"
       << "testDeleteNoConsistAddress"
       << "testScanEmptyRoster"
       << "testScanRosterNoConsists"
       << "testScanRosterWithConsists";

       JUnitUtil::runTests(smt, testList);

    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* ConsistToolFrameTestAction::log = LoggerFactory::getLogger("ConsistToolFrameTestAction");
