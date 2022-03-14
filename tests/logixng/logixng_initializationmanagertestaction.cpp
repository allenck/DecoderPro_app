#include "logixng_initializationmanagertestaction.h"
#include "logixng_initializationmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LogixNG_InitializationManagerTestAction::LogixNG_InitializationManagerTestAction(QObject *parent)
    : AbstractAction(tr("LogixNG_Initialization"),parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
void LogixNG_InitializationManagerTestAction::actionPerformed()
{
 LogixNG_InitializationManagerTest* test = new LogixNG_InitializationManagerTest();
 try
 {
  QStringList testList = QStringList()
    << "testInitialization"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LogixNG_InitializationManagerTestAction::log = LoggerFactory::getLogger("LogixNG_InitializationManagerTestAction");
