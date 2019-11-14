#include "singleturnoutsignalheadtestaction.h"
#include "singleturnoutsignalheadtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

SingleTurnoutSignalHeadTestAction::SingleTurnoutSignalHeadTestAction(QObject* parent)
 : AbstractAction(tr("SingleTurnoutSignalHeadTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void SingleTurnoutSignalHeadTestAction::actionPerformed()
{
    SingleTurnoutSignalHeadTest* test = new SingleTurnoutSignalHeadTest();
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

          // SingleTurnoutSignalHeadTest
       << "testNoDarkValidTypes"
       << "testDarkValidTypes1"
       << "testDarkValidTypes2";

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* SingleTurnoutSignalHeadTestAction::log = LoggerFactory::getLogger("SingleTurnoutSignalHeadTestAction");
