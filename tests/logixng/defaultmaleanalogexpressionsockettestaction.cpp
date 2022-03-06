#include "defaultmaleanalogexpressionsockettestaction.h"
#include "defaultmaleanalogexpressionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultMaleAnalogExpressionSocketTestAction::DefaultMaleAnalogExpressionSocketTestAction(QObject *parent)
 : AbstractAction(tr("AnalogExpression"), parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
void DefaultMaleAnalogExpressionSocketTestAction::actionPerformed()
{
 DefaultMaleAnalogExpressionSocketTest* test = new DefaultMaleAnalogExpressionSocketTest();
 try
 {
  QStringList testList = QStringList()
    // in MaleSocketTestBase
        << "testExists"
        << "testLock"
        << "testCategory"
        << "testShortDescription"
        << "testLongDescription"
        << "testGetSystemName"
        << "testUserName"
        << "testDisplayName"
        << "testState"
        << "testComment"
        << "testProperty"
        << "testDebugConfig"

  << "testCtor"
  << "testEvaluate"
  << "testEvaluateErrors"
  << "testVetoableChange"
  << "testCompareSystemNameSuffix"
  ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultMaleAnalogExpressionSocketTestAction::log = LoggerFactory::getLogger("DefaultMaleAnalogExpressionSocketTestAction");

