#include "paneprogpanetestaction.h"
#include "paneprogpanetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
PaneProgPaneTestAction::PaneProgPaneTestAction(QObject* parent)
 : AbstractAction(tr("PaneProgPane test"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void PaneProgPaneTestAction::actionPerformed()
{
 PaneProgPaneTest* test = new PaneProgPaneTest();
 try
 {
  QStringList testList = QStringList()
    << "testColumn"
    << "testVariables"
    << "testVarListFill"
    << "testPaneRead"
    << "testPaneWrite"
    << "testPaneReadOpCount"
    ;
  JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError ex)
  {
    JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
}
Logger* PaneProgPaneTestAction::log = LoggerFactory::getLogger("PaneProgPaneTestAction");
