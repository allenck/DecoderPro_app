#include "circuitbuildertestaction.h"
#include "circuitbuildertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
CircuitBuilderTestAction::CircuitBuilderTestAction(QObject *parent) : AbstractAction(tr("CircuitBuilder test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void CircuitBuilderTestAction::actionPerformed()
{
 CircuitBuilderTest* test = new CircuitBuilderTest();
 try
 {
  QStringList testList = QStringList()
    << "testCtor"
    << "testEditCircuitFrame"
    << "testEditCircuitError"
    << "testEditPortals"
    << "testEditCircuitPaths"
    << "testEditPortalDirection"
    << "testEditSignalFrame"
    << "testEditPortalError"
    << "testEditPortalErrorIcon"
    << "testNoBlock";

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* CircuitBuilderTestAction::log = LoggerFactory::getLogger("CircuitBuilderTestAction");
