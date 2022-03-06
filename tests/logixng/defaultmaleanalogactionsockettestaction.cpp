#include "defaultmaleanalogactionsockettestaction.h"
#include "defaultmaleanalogactionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
DefaultMaleAnalogActionSocketTestAction::DefaultMaleAnalogActionSocketTestAction(QObject *parent)
 : AbstractAction(tr("AnalogAction"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void DefaultMaleAnalogActionSocketTestAction::actionPerformed()
{
 DefaultMaleAnalogActionSocketTest* test = new DefaultMaleAnalogActionSocketTest();
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
    <<  "testSetValue"

       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultMaleAnalogActionSocketTestAction::log = LoggerFactory::getLogger("DefaultMaleAnalogActionSocketTestAction");
