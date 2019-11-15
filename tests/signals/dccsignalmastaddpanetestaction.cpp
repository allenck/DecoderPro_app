#include "dccsignalmastaddpanetestaction.h"
#include "dccsignalmastaddpanetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DccSignalMastAddPaneTestAction::DccSignalMastAddPaneTestAction(QObject *parent) : AbstractAction(tr("DccSignalMastAddPaneTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void DccSignalMastAddPaneTestAction::actionPerformed()
{
    DccSignalMastAddPaneTest* test = new DccSignalMastAddPaneTest();
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
Logger* DccSignalMastAddPaneTestAction::log = LoggerFactory::getLogger("DccSignalMastAddPaneTestAction");
