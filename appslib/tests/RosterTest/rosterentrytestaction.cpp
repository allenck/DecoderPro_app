#include "rosterentrytestaction.h"
#include "rosterentrytest.h"

RosterEntryTestAction::RosterEntryTestAction(QString text, QObject* parent) : AbstractAction(text, parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void RosterEntryTestAction::actionPerformed()
{
    RosterEntryTest* ret = new RosterEntryTest();
    ret->testCreate();
}
