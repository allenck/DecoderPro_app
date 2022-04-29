#include "analogexpressionmemorytestaction.h"
#include "analogexpressionmemorytest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
AnalogExpressionMemoryTestAction::AnalogExpressionMemoryTestAction(QObject *parent) : AbstractAction(tr("AnalogExpressionMemory"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void AnalogExpressionMemoryTestAction::actionPerformed()
{
 AnalogExpressionMemoryTest* test = new AnalogExpressionMemoryTest();
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

    // in AbstractAnalogExpressionTestBase
    << "testBadSystemName"
    << "testGetBeanType"
    << "testState"
    << "testEnableAndEvaluate"
    << "testDebugConfig"


    // in AnalogExpressionMemoryTest
    << "testCtor"
    << "testEvaluate"
    << "testEvaluateAndAction"
    << "testMemory"
    << "testRegisterListeners"
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
 Logger* AnalogExpressionMemoryTestAction::log = LoggerFactory::getLogger("AnalogExpressionMemoryTestAction");

