#include "matrixsignalmastaddpanetestaction.h"
#include "matrixsignalmastaddpanetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

MatrixSignalMastAddPaneTestAction::MatrixSignalMastAddPaneTestAction(QObject* parent) : AbstractAction(tr("MatrixSignalMastAddPaneTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void MatrixSignalMastAddPaneTestAction::actionPerformed()
{
    MatrixSignalMastAddPaneTest* test = new MatrixSignalMastAddPaneTest();
    try
    {
     QStringList testList = QStringList()
       //  AbstractSignalMastAddPaneTestBase
       << "testInfoMethods"

       // SignalHeadSignalMastAddPaneTest
       << "testSetMastOK"
       << "testSetMastReject"
       << "testEditAndDisableViaGui"

       ;

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* MatrixSignalMastAddPaneTestAction::log = LoggerFactory::getLogger("MatrixSignalMastAddPaneTestAction");
