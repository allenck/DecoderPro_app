#include "conditionalngtestaction.h"
#include "conditionalngtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

ConditionalNGTestAction::ConditionalNGTestAction(QObject *parent) : AbstractAction(tr("ConditionalNGTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void ConditionalNGTestAction::actionPerformed()
{
 ConditionalNGTest* test = new ConditionalNGTest();
 try
 {
  QStringList testList = QStringList()
   << "testGetBeanType"
   << "testGetParent"
   << "testGetRoot"
   << "testGetLogixNG"
   << "testState"
   << "testConnectDisconnect"
   << "testSetSocketName"
   << "testShortDescription"
   << "testLongDescription"
   << "testGetChild"
   << "testGetChildCount"
   << "testGetCategory"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* ConditionalNGTestAction::log = LoggerFactory::getLogger("ConditionalNGTestAction");
