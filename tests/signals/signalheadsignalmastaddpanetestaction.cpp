#include "signalheadsignalmastaddpanetestaction.h"
#include "signalheadsignalmastaddpanetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

SignalHeadSignalMastAddPaneTestAction::SignalHeadSignalMastAddPaneTestAction(QObject* parent)
 : AbstractAction(tr("SignalHeadSignalMastAddPaneTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void SignalHeadSignalMastAddPaneTestAction::actionPerformed()
{
    SignalHeadSignalMastAddPaneTest* test = new SignalHeadSignalMastAddPaneTest();
    try
    {
     QStringList testList = QStringList()
       //  AbstractSignalMastAddPaneTestBase
       << "testInfoMethods"

       // SignalHeadSignalMastAddPaneTest
       << "testSetMast"
       ;

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* SignalHeadSignalMastAddPaneTestAction::log = LoggerFactory::getLogger("SignalHeadSignalMastAddPaneTestAction");
