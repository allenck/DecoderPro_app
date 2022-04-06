#include "analogactionmemorytestaction.h"
#include "analogactionmemorytest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
AnalogActionMemoryTestAction::AnalogActionMemoryTestAction(QObject *parent) : AbstractAction(tr("AnalogActionMemory"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void AnalogActionMemoryTestAction::actionPerformed()
{
 AnalogActionMemoryTest* test = new AnalogActionMemoryTest();
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

    // in TableForEachTest
    << "testCtor"
  //  << "testCtorAndSetup2"
  //  << "testCtorAndSetup3"""
    << "testGetChild"
    << "testCategory"
    << "testDescription"
    << "testExecute"
    << "testIsActive"
    << "testMaleSocketIsActive"
  ;

  JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError* ex)
  {
   JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
 }
 Logger* AnalogActionMemoryTestAction::log = LoggerFactory::getLogger("AnalogActionMemoryTestAction");
