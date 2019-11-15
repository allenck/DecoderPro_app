#include "turnoutsignalmastaddpanetestaction.h"
#include "turnoutsignalmastaddpanetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

TurnoutSignalMastAddPaneTestAction::TurnoutSignalMastAddPaneTestAction(QObject* parent)
 : AbstractAction(tr("TurnoutSignalMastAddPaneTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void TurnoutSignalMastAddPaneTestAction::actionPerformed()
{
    TurnoutSignalMastAddPaneTest* test = new TurnoutSignalMastAddPaneTest();
    try
    {
     QStringList testList = QStringList()
       // AbstractSignalMastAddPaneTestBase
       << "testInfoMethods"


       // DoubleTurnoutSignalHeadTest
       << "testSetMast";

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* TurnoutSignalMastAddPaneTestAction::log = LoggerFactory::getLogger("TurnoutSignalMastAddPaneTestAction");
