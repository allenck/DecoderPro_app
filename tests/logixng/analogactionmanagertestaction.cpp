#include "analogactionmanagertestaction.h"
#include "analogactionmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
AnalogActionManagerTestAction::AnalogActionManagerTestAction(QObject *parent) : AbstractAction(tr("AnalogActionManager"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void AnalogActionManagerTestAction::actionPerformed(JActionEvent *)
{
 AnalogActionManagerTest* test = new AnalogActionManagerTest();
 try
 {
  QStringList testList = QStringList()
   // in AbstractManagerTestBase:
   << "testManagerDataListenerAddAndRemove"
   << "testPropertyChangeListenerAddAndRemove"
   << "testVetoableChangeListenerAddAndRemove"
   << "testMakeSystemName"

   // in AnalogActionManagerTest
   << "testRegisterAction"
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
Logger* AnalogActionManagerTestAction::log = LoggerFactory::getLogger("AnalogActionManagerTestAction");
