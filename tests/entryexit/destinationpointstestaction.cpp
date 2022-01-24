#include "destinationpointstestaction.h"
#include "destinationpointstest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DestinationPointsTestAction::DestinationPointsTestAction(QObject* parent) : AbstractAction(tr("DestinationPointsTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void DestinationPointsTestAction::actionPerformed()
{
 DestinationPointsTest* test = new DestinationPointsTest();
 try
 {
  QStringList testList = QStringList()
    << "testCTor"
    << "testSetRoute"
    << "testEnabled"
    <<  "testState"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DestinationPointsTestAction::log = LoggerFactory::getLogger("DestinationPointsTestAction");
