#include "defaultfemaledigitalbooleanactionsockettestaction.h"
#include "defaultfemaledigitalbooleanactionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultFemaleDigitalBooleanActionSocketTestAction::DefaultFemaleDigitalBooleanActionSocketTestAction(QObject *parent)
 : AbstractAction(tr("DigitalBooleanAction"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void DefaultFemaleDigitalBooleanActionSocketTestAction::actionPerformed()
{
 DefaultFemaleDigitalBooleanActionSocketTest* test = new DefaultFemaleDigitalBooleanActionSocketTest();
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

  // in DefaultFemaleDigitalBooleanActionSocketTest
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
Logger* DefaultFemaleDigitalBooleanActionSocketTestAction::log = LoggerFactory::getLogger("DefaultFemaleDigitalBooleanActionSocketTestAction");
