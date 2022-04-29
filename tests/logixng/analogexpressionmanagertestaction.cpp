#include "analogexpressionmanagertestaction.h"
#include "analogexpressionmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
AnalogExpressionManagerTestAction::AnalogExpressionManagerTestAction(QObject *parent) : AbstractAction(tr("AnalogExpression"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void AnalogExpressionManagerTestAction::actionPerformed(JActionEvent *)
{
 AnalogExpressionManagerTest* test = new AnalogExpressionManagerTest();
 try
 {
  QStringList testList = QStringList()
   // in AbstractManagerTestBase:
   << "testManagerDataListenerAddAndRemove"
   << "testPropertyChangeListenerAddAndRemove"
   << "testVetoableChangeListenerAddAndRemove"
   << "testMakeSystemName"

   // in AnalogExpressionManagerTest
   << "testRegisterExpression"
   << "testCreateFemaleSocket"
   << "testGetBeanTypeHandled"
   << "testInstance"

       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* AnalogExpressionManagerTestAction::log = LoggerFactory::getLogger("AnalogExpressionManagerTestAction");
