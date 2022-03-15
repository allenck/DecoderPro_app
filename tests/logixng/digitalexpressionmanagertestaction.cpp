#include "digitalexpressionmanagertestaction.h"
#include "digitalexpressionmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
DigitalExpressionManagerTestAction::DigitalExpressionManagerTestAction(QObject *parent) : AbstractAction(tr("DigitalExpressionManager"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DigitalExpressionManagerTestAction::actionPerformed(JActionEvent *)
{
 DigitalExpressionManagerTest* test = new DigitalExpressionManagerTest();
 try
 {
  QStringList testList = QStringList()
   // in AbstractManagerTestBase:
   << "testManagerDataListenerAddAndRemove"
   << "testPropertyChangeListenerAddAndRemove"
   << "testVetoableChangeListenerAddAndRemove"
   << "testMakeSystemName"

   // in DigitalActionManagerTest
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
Logger* DigitalExpressionManagerTestAction::log = LoggerFactory::getLogger("DigitalExpressionManagerTestAction");
