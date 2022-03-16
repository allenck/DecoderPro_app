#include "digitalbooleanactionmanagertestaction.h"
#include "digitalbooleanactionmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DigitalBooleanActionManagerTestAction::DigitalBooleanActionManagerTestAction(QObject *parent)
 : AbstractAction(tr("Boolean Action"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DigitalBooleanActionManagerTestAction::actionPerformed(JActionEvent *)
{
 DigitalBooleanActionManagerTest* test = new DigitalBooleanActionManagerTest();
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
Logger* DigitalBooleanActionManagerTestAction::log = LoggerFactory::getLogger("DigitalBooleanActionManagerTestAction");

