#include "defaultmaledigitalbooleanactionsockettestaction.h"
#include "defaultmaledigitalbooleanactionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultMaleDigitalBooleanActionSocketTestAction::DefaultMaleDigitalBooleanActionSocketTestAction(QObject *parent)
 : AbstractAction(tr("DigitalBooleanAction"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void DefaultMaleDigitalBooleanActionSocketTestAction::actionPerformed()
{
 DefaultMaleDigitalBooleanActionSocketTest* test = new DefaultMaleDigitalBooleanActionSocketTest();
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
Logger* DefaultMaleDigitalBooleanActionSocketTestAction::log = LoggerFactory::getLogger("DefaultMaleDigitalBooleanActionSocketTestAction");
