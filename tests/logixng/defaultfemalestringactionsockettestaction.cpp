#include "defaultfemalestringactionsockettestaction.h"
#include "defaultfemalestringactionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultFemaleStringActionSocketTestAction::DefaultFemaleStringActionSocketTestAction(QObject *parent)
 : AbstractAction(tr("StringAction"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void DefaultFemaleStringActionSocketTestAction::actionPerformed()
{
 DefaultFemaleStringActionSocketTest* test = new DefaultFemaleStringActionSocketTest();
 try
 {
  QStringList testList = QStringList()
  // in FemaleSocketTestBase
    << "testBadSocketName"
    << "testSetup"
    << "testConnectIncompatibleSocket"
    << "testConnect"
    << "testDisconnect"
    << "testSetParentForAllChildren"
    << "testValidateName"
    << "testSetName"
    << "testDisposeWithoutChild"
    << "testDisposeWithChild"
    << "testMethodsThatAreNotSupported"
    << "testCategory"
    << "testSWISystemName"

  // in DefaultFemaleAnalogActionSocketTest
//    << "testBundleClass"
    << "testGetName"
    << "testGetDescription"
    << "testSetValue"
    << "testGetConnectableClasses"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultFemaleStringActionSocketTestAction::log = LoggerFactory::getLogger("DefaultFemaleStringActionSocketTestAction");
