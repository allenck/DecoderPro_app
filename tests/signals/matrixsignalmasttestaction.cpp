#include "matrixsignalmasttestaction.h"
#include "matrixsignalmasttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

MatrixSignalMastTestAction::MatrixSignalMastTestAction(QObject* parent) : AbstractAction(tr("MatrixSignalMastTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void MatrixSignalMastTestAction::actionPerformed()
{
    MatrixSignalMastTest* test = new MatrixSignalMastTest();
    try
    {
     QStringList testList = QStringList()
       << "testSetup"
       << "testCtor1"
       << "testHeld"
       << "testLit"
       << "testAspects"
       << "testAspectAttributes"
       << "testAspectNotSet"
       << "testSetDelay"
       ;

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* MatrixSignalMastTestAction::log = LoggerFactory::getLogger("MatrixSignalMastTestAction");
