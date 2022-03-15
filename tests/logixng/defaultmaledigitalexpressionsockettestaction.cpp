#include "defaultmaledigitalexpressionsockettestaction.h"
#include "defaultmaledigitalexpressionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultMaleDigitalExpressionSocketTestAction::DefaultMaleDigitalExpressionSocketTestAction(QObject *parent)
 : AbstractAction(tr("digitalexpressionsocket"),parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DefaultMaleDigitalExpressionSocketTestAction::actionPerformed()
{
 DefaultMaleDigitalExpressionSocketTest* test = new DefaultMaleDigitalExpressionSocketTest();
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
Logger* DefaultMaleDigitalExpressionSocketTestAction::log = LoggerFactory::getLogger("DefaultMaleDigitalExpressionSocketTestAction");
