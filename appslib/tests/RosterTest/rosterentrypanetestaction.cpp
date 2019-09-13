#include "rosterentrypanetestaction.h"
#include "rosterentrypanetest.h"
#include "assert1.h"
#include "joptionpane.h"


RosterEntryPaneTestAction::RosterEntryPaneTestAction(QString text, QObject* parent) : AbstractAction(text, parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void RosterEntryPaneTestAction::actionPerformed()
{
    RosterEntryPaneTest* ret = new RosterEntryPaneTest();
    ret->setUp();
    try
    {
        ret->testCreate();
        ret->testGuiChanged1();
        ret->testGuiChanged2();
        ret->testGuiChanged3();
        ret->testGuiChanged4();
        ret->testGuiChanged5();
        ret->testNotDuplicate();
        ret->testIsDuplicate();
        ret->testRenamedDuplicate();
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
    ret->tearDown();
}
