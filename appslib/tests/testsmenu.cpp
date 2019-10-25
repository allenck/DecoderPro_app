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
#include "tests/ProfileTest/profileutilstestaction.h"
#include "tests/loconet/lntrafficroutertestaction.h"
#include "tests/loconet/lnpowermanagertestaction.h"
#include "tests/loconet/lnturnouttestaction.h"
#include "tests/loconet/lnsensortestaction.h"
#include "tests/loconet/lnreportertestaction.h"
#include "tests/loconet/lnsensoraddresstestaction.h"
#include "tests/loconet/lnsensormanagertestaction.h"
#include "tests/loconet/lndeferprogrammertestaction.h"
#include "tests/loconet/lnturnoutmanagertestaction.h"
#include "tests/misc/proxyturnoutmanagertestaction.h"
#include "tests/loconet/lnlighttestaction.h"
#include "tests/misc/proxysensormanagertestaction.h"
#include "tests/misc/proxyreportmanagertestaction.h"
#include "tests/misc/proxylightmanagertestaction.h"
#include "tests/misc/multiindexprogrammerfacadetestaction.h"
#include "tests/misc/addressedhighcvprogranmmerfacadetestaction.h"
#include "tests/misc/opsmodedelayedprogrammerfacadetestaction.h"
#include "tests/misc/verifywriteprogrammerfacadetestaction.h"
#include "tests/misc/twoindextcsprogrammerfacadetestaction.h"
#include "tests/misc/paneprogpanetestaction.h"
#include "tests/misc/paneprogframetestaction.h"
#include "tests/misc/decoderfiletestaction.h"
#include "tests/loconet/loconetmessageinterprettestaction.h"
#include "tests/loconet/lnreportermanagertestaction.h"
#include "tests/loconet/loconetsystemconnectionmemotestaction.h"

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
    profileTestMenu->addAction(new ProfileUtilsTestAction(this));

    QMenu* loconetTestMenu = new QMenu(tr("LocoNet Tests ..."));
    addMenu(loconetTestMenu);
    loconetTestMenu->addAction(new SlotManagerTestAction(this));
    loconetTestMenu->addAction(new LocoNetSlotTestAction(this));
    loconetTestMenu->addAction(new LoconetSystemConnectionMemoTestAction(this));
    QMenu* loconetProgrammersMenu = new QMenu(tr("Programmers ..."));
    loconetTestMenu->addMenu(loconetProgrammersMenu);
    loconetProgrammersMenu->addAction(new LnOpsModeProgrammerTestAction(this));
    loconetProgrammersMenu->addAction(new LnDeferProgrammerTestAction(this));
    loconetTestMenu->addAction(new LocoNetMessageTestAction(this));
    loconetTestMenu->addAction(new LnTrafficControllerTestAction(this));
    loconetTestMenu->addAction(new LnPortControllerTestAction(this));
    loconetTestMenu->addAction(new LnPacketizerTestAction(this));
    loconetTestMenu->addAction(new LnPowerManagerTestAction(this));
    QMenu* loconetLightMenu = new QMenu(tr("Lights ..."));
    loconetTestMenu->addMenu(loconetLightMenu);
    loconetLightMenu->addAction(new LnLightTestAction(this));
    QMenu* loconetSensorsMenu = new QMenu(tr("Sensors ..."));
    loconetTestMenu->addMenu(loconetSensorsMenu);
    loconetSensorsMenu->addAction(new LnSensorTestAction(this));
    QMenu* loconetReporterMenu = new QMenu(tr("Reporters"));
    loconetTestMenu->addMenu(loconetReporterMenu);
    loconetReporterMenu->addAction(new LnReporterTestAction(this));
    loconetReporterMenu->addAction(new LnReporterManagerTestAction(this));
    loconetSensorsMenu->addAction(new LnSensorAddressTestAction(this));
    loconetSensorsMenu->addAction(new LnSensorManagerTestAction(this));
    QMenu* loconetTurnoutsMenu = new QMenu(tr("Turnouts ..."));
    loconetTestMenu->addMenu(loconetTurnoutsMenu);
    loconetTurnoutsMenu->addAction(new LnTurnoutTestAction(this));
    loconetTurnoutsMenu->addAction(new LnTurnoutManagerTestAction(this));
    loconetTestMenu->addAction(new LocoNetMessageInterpretTestAction(this));

    QMenu* sprogTestMenu = new QMenu(tr("Sprog"));
    addMenu(sprogTestMenu);
    sprogTestMenu->addAction(new SprogMessageTestAction(this));
    QMenu* proxyMenu = new QMenu(tr("Proxy Managers ..."));
    addMenu(proxyMenu);
    proxyMenu->addAction(new ProxyTurnoutManagerTestAction(this));
    proxyMenu->addAction(new ProxySensorManagerTestAction(this));
    proxyMenu->addAction(new ProxyReporterManagerTestAction(this));
    proxyMenu->addAction(new ProxyLightManagerTestAction(this));
    QMenu* facadeMenu = new QMenu(tr("Programmer facades ..."));
    addMenu(facadeMenu);
    facadeMenu->addAction(new AddressedHighCvProgranmmerFacadeTestAction(this));
    facadeMenu->addAction(new MultiIndexProgrammerFacadeTestAction(this));
    facadeMenu->addAction(new OpsModeDelayedProgrammerFacadeTestAction(this));
    facadeMenu->addAction(new TwoIndexTcsProgrammerFacadeTestAction(this));
    facadeMenu->addAction(new VerifyWriteProgrammerFacadeTestAction(this));
    QMenu* paneleMenu = new QMenu(tr("Panels ..."));
    addMenu(paneleMenu);
    paneleMenu->addAction(new PaneProgFrameTestAction(this));
    paneleMenu->addAction(new PaneProgPaneTestAction(this));
    paneleMenu->addAction(new DecoderFileTestAction(this));

}
