#include "analogformulatestaction.h"
#include "analogformulatest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

AnalogFormulaTestAction::AnalogFormulaTestAction(QObject *parent) : AbstractAction(tr("AnalogFormula"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void AnalogFormulaTestAction::actionPerformed()
{
 AnalogFormulaTest* test = new AnalogFormulaTest();
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


    // in AnalogFormulaTest
    << "testCtor"
    << "testCtorAndSetup1"
    << "testCtorAndSetup2"
    << "testCtorAndSetup3"
    << "testSetChildCount"
    << "testFormula"
    << "testGetChild"
    << "testCategory"
    << "testConnected_getExpressionSystemName"
    << "testDescription"
    << "testEvaluateEmptyFormula"
    ;
  JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError* ex)
  {
   JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
 }
 Logger* AnalogFormulaTestAction::log = LoggerFactory::getLogger("AnalogFormulaTestAction");
