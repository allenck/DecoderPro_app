#include "virtualsignalheadtestaction.h"
#include "virtualsignalheadtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

VirtualSignalHeadTestAction::VirtualSignalHeadTestAction(QObject *parent) : AbstractAction(tr("VirtualSignalHeadTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void VirtualSignalHeadTestAction::actionPerformed()
{
    VirtualSignalHeadTest* test = new VirtualSignalHeadTest();
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
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* VirtualSignalHeadTestAction::log = LoggerFactory::getLogger("VirtualSignalHeadTestAction");
