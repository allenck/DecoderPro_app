#include "storeandloadtestaction.h"
#include "storeandloadtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

StoreAndLoadTestAction::StoreAndLoadTestAction(QObject *parent) : AbstractAction(tr("Store and Load"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void StoreAndLoadTestAction::actionPerformed()
{
 StoreAndLoadTest* test = new StoreAndLoadTest();
 try
 {
  QStringList testList = QStringList()
   << "testLogixNGs"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* StoreAndLoadTestAction::log = LoggerFactory::getLogger("StoreAndLoadTestAction");
