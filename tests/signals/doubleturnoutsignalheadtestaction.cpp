#include "doubleturnoutsignalheadtestaction.h"
#include "doubleturnoutsignalheadtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DoubleTurnoutSignalHeadTestAction::DoubleTurnoutSignalHeadTestAction(QObject* parent)
: AbstractAction(tr("DoubleTurnoutSignalHeadTest"), parent){
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
void DoubleTurnoutSignalHeadTestAction::actionPerformed()
{
    DoubleTurnoutSignalHeadTest* test = new DoubleTurnoutSignalHeadTest();
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
       << "testSetAppearance"
       << "testNotify"
       << "testReadOutput"
       << "testFlashingIgnoresTurnoutFeedback";


     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* DoubleTurnoutSignalHeadTestAction::log = LoggerFactory::getLogger("DoubleTurnoutSignalHeadTestAction");
