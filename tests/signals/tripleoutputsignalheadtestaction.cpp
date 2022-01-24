#include "tripleoutputsignalheadtestaction.h"
#include "tripleoutputsignalheadtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

TripleOutputSignalHeadTestAction::TripleOutputSignalHeadTestAction(QObject *parent) : AbstractAction(tr("TripleOutputSignalHeadTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void TripleOutputSignalHeadTestAction::actionPerformed()
{
    TripleOutputSignalHeadTest* test = new TripleOutputSignalHeadTest();
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

       // TripleTurnoutSignalHeadTest
       << "testCTor";

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* TripleOutputSignalHeadTestAction::log = LoggerFactory::getLogger("TripleOutputSignalHeadTestAction");
