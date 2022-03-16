#include "digitalbooleanonchangetestaction.h"
#include "digitalbooleanonchangetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DigitalBooleanOnChangeTestAction::DigitalBooleanOnChangeTestAction(QObject *parent)
 : AbstractAction(tr("DigitalBooleanOnChange"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DigitalBooleanOnChangeTestAction::actionPerformed()
{
 DigitalBooleanOnChangeTest* test = new DigitalBooleanOnChangeTest();
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

  // in AbstractDigitalBooleanActionTestBase
    << "testBadSystemName"
    << "testGetBeanType"
    // in DigitalBooleanOnChangeTest
    << "testCtor"
    << "testCtorAndSetup1"
    << "testCtorAndSetup2"
    << "testCtorAndSetup3"
    << "testGetChild"
    << "testCategory"
    << "testGetShortDescription"
    << "testGetLongDescription"
    << "testTrigger"
    << "testExecute"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DigitalBooleanOnChangeTestAction::log = LoggerFactory::getLogger("DigitalBooleanOnChangeTestAction");
