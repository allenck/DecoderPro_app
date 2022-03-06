#include "defaultmaledigitalactionsockettestaction.h"
#include "defaultmaledigitalactionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultMaleDigitalActionSocketTestAction::DefaultMaleDigitalActionSocketTestAction(QObject *parent)
 : AbstractAction(tr("DigitalAction"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DefaultMaleDigitalActionSocketTestAction::actionPerformed()
{
 DefaultMaleDigitalActionSocketTest* test = new DefaultMaleDigitalActionSocketTest();
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
    << "testExecute"
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
Logger* DefaultMaleDigitalActionSocketTestAction::log = LoggerFactory::getLogger("DefaultMaleDigitalActionSocketTestAction");
