#include "defaultmalestringactionsockettestaction.h"
#include "defaultmalestringactionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultMaleStringActionSocketTestAction::DefaultMaleStringActionSocketTestAction(QObject *parent)
 : AbstractAction(tr("StringAction"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void DefaultMaleStringActionSocketTestAction::actionPerformed()
{
 DefaultMaleStringActionSocketTest* test = new DefaultMaleStringActionSocketTest();
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

  ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultMaleStringActionSocketTestAction::log = LoggerFactory::getLogger("DefaultMaleStringActionSocketTestAction");
