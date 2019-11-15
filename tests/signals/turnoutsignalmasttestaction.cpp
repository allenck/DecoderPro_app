#include "turnoutsignalmasttestaction.h"
#include "turnoutsignalmasttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

TurnoutSignalMastTestAction::TurnoutSignalMastTestAction(QObject* parent) : AbstractAction(tr("TurnoutSignalMastTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void TurnoutSignalMastTestAction::actionPerformed()
{
    TurnoutSignalMastTest* test = new TurnoutSignalMastTest();
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
       << "testCTor"
       << "testSetAspect"
       << "testSetAspectResetOthers"
       << "testUnLitNoTurnout"
       << "testUnLitWithTurnout";

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* TurnoutSignalMastTestAction::log = LoggerFactory::getLogger("TurnoutSignalMastTestAction");
