#include "defaultfemalegenericexpressionsocket1_testaction.h"
#include "defaultfemalegenericexpressionsocket1_test.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultFemaleGenericExpressionSocket1_TestAction::DefaultFemaleGenericExpressionSocket1_TestAction(QObject *parent)
 : AbstractAction(tr("FemaleGenericExpression 1"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}


void DefaultFemaleGenericExpressionSocket1_TestAction::actionPerformed()
{
 DefaultFemaleGenericExpressionSocket1_Test* test = new DefaultFemaleGenericExpressionSocket1_Test();
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

  // in DefaultFemaleGenericExpressionSocket1_Test
    << "testSWISystemName"
    << "testSetParentForAllChildren"
    << "testSocketType"
    << "testGetName"
    << "testGetDescription"
    << "testConnect"
    << "testDisconnect"
    << "testConnectableClasses"
    << "testIsCompatibleSocket"
    << "testGetAndSetSocketType"
    << "testIsCompatible"
    << "testDoI18N"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultFemaleGenericExpressionSocket1_TestAction::log = LoggerFactory::getLogger("DefaultFemaleGenericExpressionSocket1_TestAction");
