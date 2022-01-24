#include "rosterentrypanetestaction.h"
#include "rosterentrypanetest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"

RosterEntryPaneTestAction::RosterEntryPaneTestAction(QString text, QObject* parent) : AbstractAction(text, parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void RosterEntryPaneTestAction::actionPerformed()
{
    RosterEntryPaneTest* ret = new RosterEntryPaneTest();
    try
    {
        QStringList testList = QStringList()
             << "testCreate"
             << "testGuiChanged1"
             << "testGuiChanged2"
             << "testGuiChanged3"
             << "testGuiChanged4"
             << "testGuiChanged5"
             << "testNotDuplicate"
             << "testIsDuplicate"
             << "testRenamedDuplicate";
        JUnitUtil::runTests(ret, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* RosterEntryPaneTestAction::log = LoggerFactory::getLogger("RosterEntryPaneTestAction");
