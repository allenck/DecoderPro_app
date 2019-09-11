#include "rostertestaction.h"
#include "rostertest.h"
#include "../assert.h"
#include "joptionpane.h"

RosterTestAction::RosterTestAction( QObject* parent) : AbstractAction(tr("Roster Test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
RosterTestAction::RosterTestAction(QString text, QObject* parent) : AbstractAction(text, parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


void RosterTestAction::actionPerformed()
{
    RosterTest* rt = new RosterTest();
    try
    {
        rt->testDirty();
        rt->testAdd();
        rt->testDontAddNullEntriesLater();
        rt->testDontAddNullEntriesFirst();
        rt->testAddrSearch();
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
