#include "defaultfemaledigitalexpressionsockettestaction.h"
#include "defaultfemaledigitalexpressionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultFemaleDigitalExpressionSocketTestAction::DefaultFemaleDigitalExpressionSocketTestAction(QObject *parent)
 : AbstractAction(tr("DigitalExpression"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void DefaultFemaleDigitalExpressionSocketTestAction::actionPerformed()
{
 DefaultFemaleDigitalExpressionSocketTest* test = new DefaultFemaleDigitalExpressionSocketTest();
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
Logger* DefaultFemaleDigitalExpressionSocketTestAction::log = LoggerFactory::getLogger("DefaultFemaleDigitalExpressionSocketTestAction");
