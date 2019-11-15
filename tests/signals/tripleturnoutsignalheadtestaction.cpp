#include "tripleturnoutsignalheadtestaction.h"
#include "tripleturnoutsignalheadtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

TripleTurnoutSignalHeadTestAction::TripleTurnoutSignalHeadTestAction(QObject* parent) : AbstractAction(tr("TripleTurnoutSignalHeadTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void TripleTurnoutSignalHeadTestAction::actionPerformed()
{
    TripleTurnoutSignalHeadTest* test = new TripleTurnoutSignalHeadTest();
    try
    {
     QStringList testList = QStringList()
       // AbstractSignalHeadTestBase
       << "testLit"
       << "testHeld"
       << "testLitDarkIndependent"
       << "testBaseAppearanceStop"
       << "testBaseAppearanceClearYellow"
       << "testBaseAppearanceClearGreen"
       << "testBaseAppearanceRestrictingFlashRed"
       << "testBaseAppearanceRestrictingLunar"
       << "testClearStopRestrictingOverlaps"
       << "testGetBeanType"

       // DoubleTurnoutSignalHeadTest
       << "testCTor";
     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* TripleTurnoutSignalHeadTestAction::log = LoggerFactory::getLogger("TripleTurnoutSignalHeadTestAction");
