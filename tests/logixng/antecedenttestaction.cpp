#include "antecedenttestaction.h"
#include "antecedenttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
AntecedentTestAction::AntecedentTestAction(QObject *parent) : AbstractAction(tr("Antecedent"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void AntecedentTestAction::actionPerformed()
{
 AntecedentTest* test = new AntecedentTest();
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

    // in AntecedentTest
    << "testCtor"
    << "testCtorAndSetup1"
    << "testCtorAndSetup2"
    << "testCtorAndSetup3"
    << "testSetChildCount"
    << "testGetChild"
    << "testCategory"
    << "testConnected_getExpressionSystemName"
    << "testDescription"
    << "testValidate"
    << "testCalculate"

  ;

  JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError* ex)
  {
   JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
 }
 Logger* AntecedentTestAction::log = LoggerFactory::getLogger("AntecedentTestAction");
