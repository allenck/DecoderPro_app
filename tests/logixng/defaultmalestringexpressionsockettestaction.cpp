#include "defaultmalestringexpressionsockettestaction.h"
#include "defaultmalestringexpressionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultMaleStringExpressionSocketTestAction::DefaultMaleStringExpressionSocketTestAction(QObject *parent)
 : AbstractAction(tr("MaleStringExpression"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DefaultMaleStringExpressionSocketTestAction::actionPerformed()
{
 DefaultMaleStringExpressionSocketTest* test = new DefaultMaleStringExpressionSocketTest();
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

    // in DefaultMaleAnalogActionSocketTest
    << "testCtor"
    <<  "testEvaluate"
    <<  "testVetoableChange"
    <<  "testCompareSystemNameSuffix"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultMaleStringExpressionSocketTestAction::log = LoggerFactory::getLogger("DefaultMaleStringExpressionSocketTestAction");
