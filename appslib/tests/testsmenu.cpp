#include "testsmenu.h"
#include "tests/RosterTest/rostertestaction.h"
#include "tests/RosterTest/rosterentrytestaction.h"
#include "tests/RosterTest/rosterentrypanetestaction.h"
#include "tests/ProfileTest/profiletestaction.h"
#include "tests/ProfileTest/profilemanagertestaction.h"
#include "tests/loconet/slotmanagertestaction.h"
#include "tests/loconet/loconetslottestaction.h"
#include "tests/loconet/lnopsmodeprogrammertestaction.h"
#include "tests/loconet/loconetmessagetestaction.h"
#include "tests/loconet/lntrafficcontrollertestaction.h"
#include "tests/sprog/sprogmessagetestaction.h"
#include "tests/loconet/lnportcontrollertestaction.h"
#include "tests/loconet/lnpacketizertestaction.h"

TestsMenu::TestsMenu(QWidget *parent) : QMenu(parent)
{
    setTitle(tr("Tests"));
    QMenu* rosterTestMenu = new QMenu(tr("Roster Tests"));
    addMenu(rosterTestMenu);
    rosterTestMenu->addAction(new RosterTestAction("Roster Test", this));
    rosterTestMenu->addAction(new RosterEntryTestAction("Roster Entry Test", this));
    rosterTestMenu->addAction(new RosterEntryPaneTestAction("Roster Entry Pane Test", this));

    QMenu* profileTestMenu = new QMenu(tr("Profile Tests"));
    addMenu(profileTestMenu);
    profileTestMenu->addAction(new ProfileTestAction(this));
    profileTestMenu->addAction(new ProfileManagerTestAction(this));

    QMenu* loconetTestMenu = new QMenu(tr("loconet Tests"));
    addMenu(loconetTestMenu);
    loconetTestMenu->addAction(new SlotManagerTestAction(this));
    loconetTestMenu->addAction(new LocoNetSlotTestAction(this));
    loconetTestMenu->addAction(new LnOpsModeProgrammerTestAction(this));
    loconetTestMenu->addAction(new LocoNetMessageTestAction(this));
    loconetTestMenu->addAction(new LnTrafficControllerTestAction(this));
    loconetTestMenu->addAction(new LnPortControllerTestAction(this));
    loconetTestMenu->addAction(new LnPacketizerTestAction(this));

    QMenu* sprogTestMenu = new QMenu(tr("Sprog"));
    addMenu(sprogTestMenu);
    sprogTestMenu->addAction(new SprogMessageTestAction(this));
}
