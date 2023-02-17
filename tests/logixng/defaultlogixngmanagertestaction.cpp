#include "defaultlogixngmanagertestaction.h"
#include "defaultlogixngmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultLogixNGManagerTestAction::DefaultLogixNGManagerTestAction(QObject *parent)
 : AbstractAction(tr("DefaultLogixNG"), parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DefaultLogixNGManagerTestAction::actionPerformed()
{
 DefaultLogixNGManagerTest* test = new DefaultLogixNGManagerTest();
 try
 {
  QStringList testList = QStringList()
    << "testManager"
    << "testValidSystemNameFormat"
    << "testCreateNewLogixNG"
    << "testSetupInitialConditionalNGTree"
    << "testDeleteLogixNG"
    << "testDeleteConditionalNG"
    << "testDeleteModule"
    << "testDeleteAction"
    << "testDeleteTable"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultLogixNGManagerTestAction::log = LoggerFactory::getLogger("DefaultLogixNGManagerTestAction");
