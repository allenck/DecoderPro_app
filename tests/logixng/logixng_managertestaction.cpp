#include "logixng_managertestaction.h"
#include "logixng_managertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LogixNG_ManagerTestAction::LogixNG_ManagerTestAction(QObject *parent)
 : AbstractAction(tr("LogixNG_Manager"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void LogixNG_ManagerTestAction::actionPerformed()
{
 LogixNG_ManagerTest* test = new LogixNG_ManagerTest();
 try
 {
  QStringList testList = QStringList()

    << "testValidSystemNameFormat"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LogixNG_ManagerTestAction::log = LoggerFactory::getLogger("LogixNG_ManagerTestAction");
