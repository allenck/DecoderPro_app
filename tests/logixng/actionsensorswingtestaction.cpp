#include "actionsensorswingtestaction.h"
#include "actionsensorswingtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
ActionSensorSwingTestAction::ActionSensorSwingTestAction(QObject *parent)
    : AbstractAction(tr("ActionSensorSwing"), parent)
{
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void ActionSensorSwingTestAction::actionPerformed()
{
 ActionSensorSwingTest* test = new ActionSensorSwingTest();
 try
 {
  QStringList testList = QStringList()

          << "testCtor"
          << "testCreatePanel"
          << "testDialogUseExistingSensor"
             ;

       JUnitUtil::runTests(test, testList);
       }
       catch (AssertionError* ex)
       {
        JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
       }
      }
      Logger* ActionSensorSwingTestAction::log = LoggerFactory::getLogger("ActionSensorSwingTestAction");
