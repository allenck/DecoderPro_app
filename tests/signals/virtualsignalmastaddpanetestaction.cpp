#include "virtualsignalmastaddpanetestaction.h"
#include "virtualsignalmastaddpanetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

VirtualSignalMastAddPaneTestAction::VirtualSignalMastAddPaneTestAction(QObject* parent) : AbstractAction(tr("VirtualSignalMastAddPaneTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void VirtualSignalMastAddPaneTestAction::actionPerformed()
{
    VirtualSignalMastAddPaneTest* test = new VirtualSignalMastAddPaneTest();
    try
    {
     QStringList testList = QStringList()
       //  AbstractSignalMastAddPaneTestBase
       << "testInfoMethods"

       // SignalHeadSignalMastAddPaneTest
       << "testSetMast"
       << "testCreateMast"
       << "testCreateAndDisableViaGui"
       << "testEditAndDisableViaGui"
       ;

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError er)
    {
     JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* VirtualSignalMastAddPaneTestAction::log = LoggerFactory::getLogger("VirtualSignalMastAddPaneTestAction");
