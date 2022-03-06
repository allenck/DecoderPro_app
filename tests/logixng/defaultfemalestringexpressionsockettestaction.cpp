#include "defaultfemalestringexpressionsockettestaction.h"
#include "defaultfemalestringexpressionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultFemaleStringExpressionSocketTestAction::DefaultFemaleStringExpressionSocketTestAction(QObject *parent)
    : AbstractAction(tr("FemaleStringExpression"), parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DefaultFemaleStringExpressionSocketTestAction::actionPerformed()
{
 DefaultFemaleStringExpressionSocketTest* test = new DefaultFemaleStringExpressionSocketTest();
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
Logger* DefaultFemaleStringExpressionSocketTestAction::log = LoggerFactory::getLogger("DefaultFemaleStringExpressionSocketTestAction");
