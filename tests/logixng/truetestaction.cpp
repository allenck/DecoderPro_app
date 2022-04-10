#include "truetestaction.h"
#include "truetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
TrueTestAction::TrueTestAction(QObject *parent) : AbstractAction(tr("True"), parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void TrueTestAction::actionPerformed()
{
 TrueTest* test = new TrueTest();
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

    // in AbstractDigitalExpressionTestBase
    << "testBadSystemName"
    << "testGetBeanType"
    << "testEnableAndEvaluate"
    << "testDebugConfig"

    // in TrueTest
    << "testCtor"
    << "testGetChild"
    << "testCategory"
    << "testDescription"
    << "testExpression"

  ;

  JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError* ex)
  {
   JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
 }
 Logger* TrueTestAction::log = LoggerFactory::getLogger("TrueTestAction");
