#include "logixngtestaction.h"
#include "logixngtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
LogixNGTestAction::LogixNGTestAction(QObject *parent) : AbstractAction(tr("LogixNG"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void LogixNGTestAction::actionPerformed()
{
 LogixNGTest* test = new LogixNGTest();
 try
 {
  QStringList testList = QStringList()
    << "testSetParent"
    << "testGetParent"
    << "testState"
    << "testShortDescription"
    << "testLongDescription"
    << "testGetChild"
    << "testGetChildCount"
    << "testGetCategory"
    << "testSwapConditionalNG"
    << "testGetConditionalNG"
    //     << "testAddConditionalNG"
    << "testGetConditionalNGByUserName"
    << "testDeleteConditionalNG"
    << "testActivateLogixNG"
    << "testGetConditionalNG_WithoutParameters"
    << "testGetLogixNG"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LogixNGTestAction::log = LoggerFactory::getLogger("LogixNGTestAction");
