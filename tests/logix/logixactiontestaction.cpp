#include "logixactiontestaction.h"
#include "logixactiontest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LogixActionTestAction::LogixActionTestAction(QObject* parent) : AbstractAction(tr("LogixActionTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
void LogixActionTestAction::actionPerformed()
{
 LogixActionTest* test = new LogixActionTest();
 try
 {
  QStringList testList = QStringList()
    << "testLogixAction"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LogixActionTestAction::log = LoggerFactory::getLogger("LogixActionTestAction");
