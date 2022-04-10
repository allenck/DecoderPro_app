#include "digitalformulatestaction.h"
#include "digitalformulatest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
DigitalFormulaTestAction::DigitalFormulaTestAction(QObject *parent) : AbstractAction(tr("DigitalFormula"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}


void DigitalFormulaTestAction::actionPerformed()
{
 DigitalFormulaTest* test = new DigitalFormulaTest();
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

    // in DigitalFormulaTest
    << "testCtor"
    << "testCtorAndSetup1"
    // more to follow...
  ;

  JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError* ex)
  {
   JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
 }
 Logger* DigitalFormulaTestAction::log = LoggerFactory::getLogger("DigitalFormulaTestAction");
