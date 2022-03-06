#include "defaultfemaleanalogactionsockettestaction.h"
#include "defaultfemaleanalogactionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultFemaleAnalogActionSocketTestAction::DefaultFemaleAnalogActionSocketTestAction(QObject *parent)
    : AbstractAction(tr("AnalogAction"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DefaultFemaleAnalogActionSocketTestAction::actionPerformed()
{
 DefaultFemaleAnalogActionSocketTest* test = new DefaultFemaleAnalogActionSocketTest();
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
//    << "testCategory"

       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultFemaleAnalogActionSocketTestAction::log = LoggerFactory::getLogger("DefaultFemaleAnalogActionSocketTestAction");
