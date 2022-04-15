#include "stringmanytestaction.h"
#include "stringmanytest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

StringManyTestAction::StringManyTestAction(QObject *parent) : AbstractAction(tr("StringMany"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void StringManyTestAction::actionPerformed()
{
 StringManyTest* test = new StringManyTest();
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
  // << "testSetParentForAllChildren_WithConnectedChildren"
  // << "testSetParentForAllChildren_WithoutConnectedChildren"
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

  // in AbstractStringActionTestBase
      << "testBadSystemName"
      << "testGetBeanType"
      << "testState"

  // in StringManyTest
    << "testCtor"
    << "testCtorAndSetup1"
    << "testCtorAndSetup2"
    << "testCtorAndSetup3"
    << "testGetChild"
    << "testCategory"
    << "testConnected_getExpressionSystemName"
    << "testDescription"

       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* StringManyTestAction::log = LoggerFactory::getLogger("StringManyTestAction");
