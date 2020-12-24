#include "oblocktableactiontestaction.h"
#include "oblocktableactiontest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

OBlockTableActionTestAction::OBlockTableActionTestAction(QWidget* parent) : AbstractAction(tr("OBlockTableAction Test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void OBlockTableActionTestAction::actionPerformed()
{
    OBlockTableActionTest* test = new OBlockTableActionTest();
    try
    {
     QStringList testList = QStringList()
     << "testCreate"
     << "testGetClassDescription"
     << "testIncludeAddButton"
     << "testInvoke"
     << "testInvokeTabbed"
     << "testAddOBlock"
     << "testRenameOBlock"
     << "testAddPortal"
     << "testAddSignal";

       JUnitUtil::runTests(test, testList);

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* OBlockTableActionTestAction::log = LoggerFactory::getLogger("OBlockTableActionTestAction");
