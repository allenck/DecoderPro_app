#include "actionsensortestaction.h"
#include "actionsensortest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
ActionSensorTestAction::ActionSensorTestAction(QObject *parent)
 : AbstractAction(tr("ActionSensor"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void ActionSensorTestAction::actionPerformed()
{
 ActionSensorTest* test = new ActionSensorTest();
 try
 {
  QStringList testList = QStringList()
    // in AbstractBaseTestBase
    << "testGetConditionalNG"
    << "testGetLogixNG"
    << "testMaleSocketGetConditionalNG"
    << "testMaleSocketGetLogixNG"
    << "testMaleSocketGetRoot"
    << "testGetParent"
    << "testFemaleSocketSystemName"
  //  << "testSetParentForAllChildren_WithConnectedChildren"
  //  << "testSetParentForAllChildren_WithoutConnectedChildren"
    << "testGetPrintTree"
    << "testMaleSocketGetPrintTree"
    << "testGetPrintTreeWithStandardLocale"
    << "testMaleSocketGetPrintTreeWithStandardLocale"
    << "testGetPrintTreeFromRoot"
    << "testGetDeepCopy"
    << "testIsActive"
    << "testMaleSocketIsActive"
    << "testConstants"
    << "testNames"
    << "testParent"
    << "testIsEnabled"
    << "testDispose"
    << "testRunOnGUIDelayed"
    << "testChildAndChildCount"
    << "testBeanType"
    << "testDescribeState"
    << "testAddAndRemoveSocket"

    // in AbstractDigitalActionTestBase
    << "testBadSystemName"
    << "testGetBeanType"

    // in ActionSensorMemoryTest
    << "testSensorState"
    << "testCtor"
    << "testGetChild"
    << "testSetSensor"
    << "testAction"
    << "testIndirectAddressing"
    << "testIndirectStateAddressing"
    << "testVetoableChange"
    << "testCategory"
    << "testShortDescription"
    << "testLongDescription"
    << "testChild"

  ;

  JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError* ex)
  {
   JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
 }
 Logger* ActionSensorTestAction::log = LoggerFactory::getLogger("ActionSensorTestAction");
