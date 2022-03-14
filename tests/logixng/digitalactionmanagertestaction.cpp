#include "digitalactionmanagertestaction.h"
#include "digitalactionmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DigitalActionManagerTestAction::DigitalActionManagerTestAction(QObject *parent) : AbstractAction(tr("DigitalActionManager"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DigitalActionManagerTestAction::actionPerformed(JActionEvent *)
{
 DigitalActionManagerTest* test = new DigitalActionManagerTest();
 try
 {
  QStringList testList = QStringList()
   // in AbstractManagerTestBase:
   << "testManagerDataListenerAddAndRemove"
   << "testPropertyChangeListenerAddAndRemove"
   << "testVetoableChangeListenerAddAndRemove"
   << "testMakeSystemName"

   // in DigitalActionManagerTest
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
Logger* DigitalActionManagerTestAction::log = LoggerFactory::getLogger("DigitalActionManagerTestAction");
