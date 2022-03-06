#include "defaultfemaledigitalactionsockettestaction.h"
#include "defaultfemaledigitalactionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultFemaleDigitalActionSocketTestAction::DefaultFemaleDigitalActionSocketTestAction(QObject *parent)
 : AbstractAction(tr("DigitalAction"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void DefaultFemaleDigitalActionSocketTestAction::actionPerformed()
{
 DefaultFemaleDigitalActionSocketTest* test = new DefaultFemaleDigitalActionSocketTest();
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
Logger* DefaultFemaleDigitalActionSocketTestAction::log = LoggerFactory::getLogger("DefaultFemaleDigitalActionSocketTestAction");
