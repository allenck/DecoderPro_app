#include "defaultfemaleanalogexpressionsockettestaction.h"
#include "defaultfemaleanalogexpressionsockettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
DefaultFemaleAnalogExpressionSocketTestAction::DefaultFemaleAnalogExpressionSocketTestAction(QObject *parent)
 : AbstractAction(tr("AnalogExpression"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DefaultFemaleAnalogExpressionSocketTestAction::actionPerformed()
{
 DefaultFemaleAnalogExpressionSocketTest* test = new DefaultFemaleAnalogExpressionSocketTest();
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

  // in DefaultFemaleAnalogExpressionSocketTest
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
Logger* DefaultFemaleAnalogExpressionSocketTestAction::log = LoggerFactory::getLogger("DefaultFemaleAnalogExpressionSocketTestAction");
