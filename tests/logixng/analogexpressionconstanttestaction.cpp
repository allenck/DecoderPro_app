#include "analogexpressionconstanttestaction.h"
#include "analogexpressionconstanttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
AnalogExpressionConstantTestAction::AnalogExpressionConstantTestAction(QObject* parent) : AbstractAction(tr("AnalogExpressionConstant"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void AnalogExpressionConstantTestAction::actionPerformed()
{
 AnalogExpressionConstantTest* test = new AnalogExpressionConstantTest();
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


    // in AnalogExpressionConstantTest
    << "testCtor"
    << "testSetValueWithListenersRegistered"
    << "testEvaluate"
    << "testEvaluateAndAction"
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
 Logger* AnalogExpressionConstantTestAction::log = LoggerFactory::getLogger("AnalogExpressionConstantTestAction");

