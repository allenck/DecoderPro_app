#include "actionsandexpressionstestaction.h"
#include "actionsandexpressionstest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
ActionsAndExpressionsTestAction::ActionsAndExpressionsTestAction(QObject *parent) :AbstractAction(tr("ActionsAndExpressions"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void ActionsAndExpressionsTestAction::actionPerformed()
{
 ActionsAndExpressionsTest* test = new ActionsAndExpressionsTest();
 try
 {
  QStringList testList = QStringList()
    << "testGetBeanType"
    ;

    JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* ex)
    {
     JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
   }
   Logger* ActionsAndExpressionsTestAction::log = LoggerFactory::getLogger("ActionAndExpressionsTestAction");
