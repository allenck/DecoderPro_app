#include "testsmenu.h"
#include "RosterTest/rostertestaction.h"
#include "RosterTest/rosterentrytestaction.h"
#include "RosterTest/rosterentrypanetestaction.h"
#include "ProfileTest/profiletestaction.h"
#include "ProfileTest/profilemanagertestaction.h"
#include "loconet/slotmanagertestaction.h"
#include "loconet/loconetslottestaction.h"
#include "loconet/lnopsmodeprogrammertestaction.h"
#include "loconet/loconetmessagetestaction.h"
#include "loconet/lntrafficcontrollertestaction.h"
#include "sprog/sprogmessagetestaction.h"
#include "loconet/lnportcontrollertestaction.h"
#include "loconet/lnpacketizertestaction.h"
#include "ProfileTest/profileutilstestaction.h"
#include "loconet/lntrafficroutertestaction.h"
#include "loconet/lnpowermanagertestaction.h"
#include "loconet/lnturnouttestaction.h"
#include "loconet/lnsensortestaction.h"
#include "loconet/lnreportertestaction.h"
#include "loconet/lnsensoraddresstestaction.h"
#include "loconet/lnsensormanagertestaction.h"
#include "loconet/lndeferprogrammertestaction.h"
#include "loconet/lnturnoutmanagertestaction.h"
#include "loconet/loconetconsisttestaction.h"
#include "misc/proxyturnoutmanagertestaction.h"
#include "loconet/lnlighttestaction.h"
#include "misc/proxysensormanagertestaction.h"
#include "misc/proxyreportmanagertestaction.h"
#include "misc/proxylightmanagertestaction.h"
#include "misc/multiindexprogrammerfacadetestaction.h"
#include "misc/addressedhighcvprogranmmerfacadetestaction.h"
#include "misc/opsmodedelayedprogrammerfacadetestaction.h"
#include "misc/verifywriteprogrammerfacadetestaction.h"
#include "misc/twoindextcsprogrammerfacadetestaction.h"
#include "misc/paneprogpanetestaction.h"
#include "misc/paneprogframetestaction.h"
#include "misc/decoderfiletestaction.h"
#include "loconet/loconetmessageinterprettestaction.h"
#include "loconet/lnreportermanagertestaction.h"
#include "loconet/loconetsystemconnectionmemotestaction.h"
#include "misc/defaultmemorymanagertestaction.h"
#include "misc/lightcontroltestaction.h"
#include "NamedBeans/namedbeanusernamecomparatortestaction.h"
#include "loconet/loconetmessageexceptiontestaction.h"
#include "loconet/loconetthrottletestaction.h"
#include "misc/nmrapackettestaction.h"
#include "misc/accessoryopsmodeprogrammerfacadetestaction.h"
#include "signals/dccsignalheadtestaction.h"
#include "signals/singleturnoutsignalheadtestaction.h"
#include "signals/doubleturnoutsignalheadtestaction.h"
#include "signals/virtualsignalheadtestaction.h"
#include "signals/signalheadsignalmasttestaction.h"
#include "signals/signalheadsignalmastaddpanetestaction.h"
#include "signals/matrixsignalmasttestaction.h"
#include "signals/matrixsignalmastaddpanetestaction.h"
#include "signals/dccsignalmastaddpanetestaction.h"
#include "signals/tripleoutputsignalheadtestaction.h"
#include "signals/tripleturnoutsignalheadtestaction.h"
#include "signals/virtualsignalmastaddpanetestaction.h"
#include "signals/turnoutsignalmastaddpanetestaction.h"
#include "signals/turnoutsignalmasttestaction.h"
#include "logix/logixactiontestaction.h"
#include "warrants/warranttestaction.h"
#include "warrants/warrantpreferencespaneltestaction.h"
#include "misc/jmriuserpreferencesmanagertestaction.h"
#include "operations/optionsmenutestaction.h"
#include "positionables/signalmasticontestaction.h"
#include "misc/colorchooserpaneltestaction.h"
#include "misc/dcclocoaddresstestaction.h"
#include "misc/controllerfilterframetestaction.h"
#include "consisttoolframetestaction.h"
#include "cabsignals/defaultcabsignaltestaction.h"
#include "cabsignals/cabsignaltablemodeltestaction.h"
#include "entryexit/entryexitpairstestaction.h"
#include "entryexit/destinationpointstestaction.h"
#include "entryexit/pointdetailstestaction.h"
#include "entryexit/sourcetestaction.h"
#include "entryexit/sectiontestaction.h"
#include "layouteditor/layouteditortoolstestaction.h"
#include "layouteditor/layoutshapetestaction.h"
#include "entryexit/circuitbuildertestaction.h"
#include "loconet/controlpaneltestaction.h"
#include "loconet/lnpredefinedmeterstestaction.h"
#include "loconet/lniplimplementationtestaction.h"
#include "tables/oblocktableactiontestaction.h"
#include "loconet/lncvdevicetestaction.h"
#include "loconet/lncvmessagecontentsclasstestaction.h"
#include "loconet/lncvprogpanetestaction.h"
#include "loconet/lncvprogtablemodeltestaction.h"
#include "misc/identifydecodertestaction.h"
#include "misc/cvutiltestaction.h"
#include "misc/fileutilsupporttestaction.h"
#include "programmers/abstractprogrammertestaction.h"
#include "misc/vetoablechangesupporttestaction.h"
#include "loconet/internalturnoutmanagertestaction.h"

#ifdef HAVE_LOGIXNG
#include "logixng/symboltabletestaction.h"
#include "logixng/logixng_initializationmanagertestaction.h"
#include "logixng/defaultlogixngmanagertestaction.h"
#include "logixng/conditionalngtestaction.h"
#include "logixng/defaultmaleanalogexpressionsockettestaction.h"
#include "logixng/defaultmaleanalogactionsockettestaction.h"
#include "logixng/defaultmaledigitalactionsockettestaction.h"
#include "logixng/defaultmalestringactionsockettestaction.h"
#include "logixng/defaultfemaleanalogactionsockettestaction.h"
#include "logixng/defaultfemaleanalogexpressionsockettestaction.h"
#include "logixng/defaultfemaledigitalactionsockettestaction.h"
#include "logixng/defaultfemalestringexpressionsockettestaction.h"
#include "logixng/defaultfemaledigitalexpressionsockettestaction.h"
#include "logixng/defaultfemaledigitalbooleanactionsockettestaction.h"
#include "logixng/defaultfemalestringactionsockettestaction.h"
#include "logixng/logixng_managertestaction.h"
#include "logixng/digitalactionmanagertestaction.h"
#include "logixng/digitalexpressionmanagertestaction.h"
#include "logixng/defaultmaledigitalexpressionsockettestaction.h"
#include "logixng/digitalbooleanactionmanagertestaction.h"
#include "logixng/digitalbooleanonchangetestaction.h"
#include "logixng/logixngtestaction.h"
#include "logixng/digitalexpressionstestaction.h"
#include "logixng/recursivedescentparsertestaction.h"
#include "logixng/tokenizertestaction.h"
#include "logixng/tableforeachtestaction.h"
#include "logixng/defaultfemalegenericexpressionsocket1_testaction.h"
#include "logixng/defaultfemalegenericexpressionsocket2_testaction.h"
#include "logixng/defaultmalestringexpressionsockettestaction.h"
#include "logixng/defaultmaledigitalbooleanactionsockettestaction.h"
#include "logixng/analogformulatestaction.h"
#include "logixng/analogactionmemorytestaction.h"
#include "logixng/stringformulatestaction.h"
#include "logixng/actionsensortestaction.h"
#include "logixng/digitalformulatestaction.h"
#include "logixng/truetestaction.h"
#include "logixng/andtestaction.h"
#include "logixng/actionmemorytestaction.h"
#include "logixng/storeandloadtestaction.h"
#include "logixng/stringmanytestaction.h"
#include "logixng/analogactionmanagertestaction.h"
#include "logixng/antecedenttestaction.h"
#include "logixng/analogexpressionmanagertestaction.h"
#include "logixng/analogexpressionmemorytestaction.h"
#include "logixng/analogexpressionconstanttestaction.h"
#include "logixng/swingconfiguratorinterfacetestactionaction.h"
#include "logixng/actionsensorswingtestaction.h"
#include "logixng/actionsandexpressionstestaction.h"
#endif

TestsMenu::TestsMenu(QWidget *parent) : QMenu(parent)
{
    setTitle(tr("Tests"));
    QMenu* cabSignalMenu = new QMenu(tr("Cab Signals"));
    addMenu(cabSignalMenu);
    cabSignalMenu->addAction(new DefaultCabSignalTestAction(this));
    cabSignalMenu->addAction(new CabSignalTableModelTestAction(this));

    QMenu* entryExitMenu = new QMenu(tr("EntryExit"));
    addMenu(entryExitMenu);
    entryExitMenu->addAction(new CircuitBuilderTestAction(this));
    entryExitMenu->addAction(new DestinationPointsTestAction(this));
    entryExitMenu->addAction(new EntryExitPairsTestAction(this));
    entryExitMenu->addAction(new PointDetailsTestAction(this));
    entryExitMenu->addAction(new SectionTestAction(this));
    entryExitMenu->addAction(new SourceTestAction(this));

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
    profileTestMenu->addAction(new IdentifyDecoderTestAction(this));

    QMenu* loconetTestMenu = new QMenu(tr("LocoNet Tests ..."));
    addMenu(loconetTestMenu);
    loconetTestMenu->addAction(new SlotManagerTestAction(this));
    loconetTestMenu->addAction(new LocoNetSlotTestAction(this));
    loconetTestMenu->addAction(new LoconetSystemConnectionMemoTestAction(this));
    loconetTestMenu->addAction(new DefaultMemoryManagerTestAction(this));
    loconetTestMenu->addAction(new LocoNetMessageExceptionTestAction(this));
    loconetTestMenu->addAction(new LnPredefinedMetersTestAction(this));
    loconetTestMenu->addAction(new LnIplImplementationTestAction(this));

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
    loconetLightMenu->addAction(new LightControlTestAction(this));

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
    loconetTestMenu->addAction(new LocoNetConsistTestAction(this));
    loconetTestMenu->addAction(new InternalTurnoutManagerTestAction(this));

    QMenu* lncvMenu = new QMenu("Lncv");
    loconetTestMenu->addMenu(lncvMenu);
    lncvMenu->addAction(new LncvDeviceTestAction(this));
    lncvMenu->addAction(new LncvMessageContentsClassTestAction(this));
    lncvMenu->addAction(new LncvProgPaneTestAction(this));
    lncvMenu->addAction(new LncvProgTableModelTestAction(this));

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
    facadeMenu->addAction(new AccessoryOpsModeProgrammerFacadeTestAction(this));
    facadeMenu->addAction(new AddressedHighCvProgranmmerFacadeTestAction(this));
    facadeMenu->addAction(new MultiIndexProgrammerFacadeTestAction(this));
    facadeMenu->addAction(new OpsModeDelayedProgrammerFacadeTestAction(this));
    facadeMenu->addAction(new TwoIndexTcsProgrammerFacadeTestAction(this));
    facadeMenu->addAction(new VerifyWriteProgrammerFacadeTestAction(this));

    QMenu* progMenu = new QMenu(tr("Programmer tests ..."));
    addMenu(progMenu);
    progMenu->addAction(new AbstractProgrammerTestAction(this));

    QMenu* panelsMenu = new QMenu(tr("Panels ..."));
    addMenu(panelsMenu);
    panelsMenu->addAction(new PaneProgFrameTestAction(this));
    panelsMenu->addAction(new PaneProgPaneTestAction(this));
    panelsMenu->addAction(new DecoderFileTestAction(this));

    QMenu* namedBeansMenu = new QMenu(tr("NamedBeans ..."));
    addMenu(namedBeansMenu);
    namedBeansMenu->addAction(new NamedBeanUserNameComparatorTestAction(this));

    QMenu* loconetThrottleMenu = new QMenu(tr("Throttle test"));
    loconetTestMenu->addMenu(loconetThrottleMenu);
    loconetThrottleMenu->addAction(new LocoNetThrottleTestAction(this));
    loconetThrottleMenu->addAction(new NmraPacketTestAction(this));
    loconetThrottleMenu->addAction(new ControlPanelTestAction(this));

    QMenu* signalMenu = new QMenu(tr("Signals ..."));
    addMenu(signalMenu);
    signalMenu->addAction(new DccSignalHeadTestAction(this));
    signalMenu->addAction(new DccSignalMastAddPaneTestAction(this));
    signalMenu->addAction(new DoubleTurnoutSignalHeadTestAction(this));
    signalMenu->addAction(new MatrixSignalMastTestAction(this));
    signalMenu->addAction(new MatrixSignalMastAddPaneTestAction(this));
    signalMenu->addAction(new SingleTurnoutSignalHeadTestAction(this));
    signalMenu->addAction(new SignalHeadSignalMastTestAction(this));
    signalMenu->addAction(new SignalHeadSignalMastAddPaneTestAction(this));
    signalMenu->addAction(new TripleOutputSignalHeadTestAction(this));
    signalMenu->addAction(new TripleTurnoutSignalHeadTestAction(this));
    signalMenu->addAction(new TurnoutSignalMastTestAction(this));
    signalMenu->addAction(new TurnoutSignalMastAddPaneTestAction(this));
    signalMenu->addAction(new VirtualSignalHeadTestAction(this));

    QMenu* logixMenu = new QMenu("Logix");
    addMenu(logixMenu);
    logixMenu->addAction(new LogixActionTestAction(this));

    QMenu* operationsMenu = new QMenu(tr("Operations"));
    addMenu(operationsMenu);
    operationsMenu->addAction(new OptionsMenuTestAction(this));

    QMenu* warrantMenu = new QMenu("Warrants");
    addMenu(warrantMenu);
    warrantMenu->addAction(new WarrantTestAction(this));
    warrantMenu->addAction(new WarrantPreferencesPanelTestAction(this));
    warrantMenu->addAction(new JmriUserPreferencesManagerTestAction(this));

    QMenu* positionablesMenu = new QMenu(tr("Positionables ..."));
    addMenu(positionablesMenu);
    positionablesMenu->addAction(new SignalMastIconTestAction(this));

    QMenu* miscMenu = new QMenu("misc");
    addMenu(miscMenu);
    miscMenu->addAction(new ColorChooserPanelTestAction(this));
    miscMenu->addAction(new DccLocoAddressTestAction(this));
    miscMenu->addAction(new ControllerFilterFrameTestAction(this));
    miscMenu->addAction(new ConsistToolFrameTestAction(this));
    miscMenu->addAction(new OBlockTableActionTestAction(this));
    miscMenu->addAction(new CvUtilTestAction(this));
    miscMenu->addAction(new FileUtilSupportTestAction(this));
    miscMenu->addAction(new VetoableChangeSupportTestAction(this));

    QMenu* layoutEditorMenu = new QMenu("LayoutEditor");
    addMenu(layoutEditorMenu);
    layoutEditorMenu->addAction(new LayoutEditorToolsTestAction(this));
    layoutEditorMenu->addAction(new LayoutShapeTestAction(this));
#ifdef HAVE_LOGIXNG
    QMenu* logixNGMenu = new QMenu("LogixNG");
    addMenu(logixNGMenu);
    QMenu* logixNGFemaleSocketMenu = new QMenu("Female Sockets");
    logixNGMenu->addMenu(logixNGFemaleSocketMenu);
    QMenu* logixNGMaleSocketMenu = new QMenu("Male Sockets");
    logixNGMenu->addMenu(logixNGMaleSocketMenu);
    QMenu* logixNGManagerMenu = new QMenu("Managers");
    logixNGMenu->addMenu(logixNGManagerMenu);
    QMenu* logixNGMiscMenu = new QMenu("Misc");
    logixNGMenu->addMenu(logixNGMiscMenu);
    QMenu* logixNGTypesMenu = new QMenu("Actions/Expressions");
    logixNGMenu->addMenu(logixNGTypesMenu);


    logixNGMiscMenu->addAction(new ConditionalNGTestAction(this));
    logixNGMenu->addAction(new LogixNGTestAction(this));
    logixNGMenu->addAction(new DigitalExpressionsTestAction(this));
    logixNGMiscMenu->addAction(new RecursiveDescentParserTestAction(this));
    logixNGMiscMenu->addAction(new StoreAndLoadTestAction(this));
    logixNGMiscMenu->addAction(new TokenizerTestAction(this));
    logixNGMiscMenu->addAction(new SwingConfiguratorInterfaceTestActionAction(this));
    logixNGMiscMenu->addAction(new ActionSensorSwingTestAction(this));
    logixNGMiscMenu->addAction(new ActionsAndExpressionsTestAction(this));

    logixNGTypesMenu->addAction(new ActionMemoryTestAction(this));
    logixNGTypesMenu->addAction(new ActionSensorTestAction(this));
    logixNGTypesMenu->addAction(new AnalogActionMemoryTestAction(this));
    logixNGTypesMenu->addAction(new AnalogExpressionConstantTestAction(this));
    logixNGTypesMenu->addAction(new AnalogExpressionMemoryTestAction(this));
    logixNGTypesMenu->addAction(new AnalogFormulaTestAction(this));
    logixNGTypesMenu->addAction(new AntecedentTestAction(this));
    logixNGTypesMenu->addAction(new AndTestAction(this));
    logixNGTypesMenu->addAction(new DigitalBooleanOnChangeTestAction(this));
    logixNGTypesMenu->addAction(new DigitalFormulaTestAction(this));
    logixNGTypesMenu->addAction(new StringFormulaTestAction(this));
    logixNGTypesMenu->addAction(new StringManyTestAction(this));
    logixNGTypesMenu->addAction(new TableForEachTestAction());
    logixNGTypesMenu->addAction(new TrueTestAction(this));

    logixNGManagerMenu->addAction(new AnalogActionManagerTestAction(this));
    logixNGManagerMenu->addAction(new AnalogExpressionManagerTestAction(this));
    logixNGManagerMenu->addAction(new DefaultLogixNGManagerTestAction(this));
    logixNGManagerMenu->addAction(new DigitalActionManagerTestAction(this));
    logixNGManagerMenu->addAction(new DigitalExpressionManagerTestAction(this));
    logixNGManagerMenu->addAction(new DigitalBooleanActionManagerTestAction(this));
    logixNGManagerMenu->addAction(new LogixNG_InitializationManagerTestAction(this));
    logixNGManagerMenu->addAction(new LogixNG_ManagerTestAction(this));

    logixNGFemaleSocketMenu->addAction(new DefaultFemaleAnalogActionSocketTestAction(this));
    logixNGFemaleSocketMenu->addAction(new DefaultFemaleAnalogExpressionSocketTestAction(this));
    logixNGFemaleSocketMenu->addAction(new DefaultFemaleDigitalActionSocketTestAction(this));
    logixNGFemaleSocketMenu->addAction(new DefaultFemaleDigitalExpressionSocketTestAction(this));
    logixNGFemaleSocketMenu->addAction(new DefaultFemaleDigitalBooleanActionSocketTestAction(this));
    logixNGFemaleSocketMenu->addAction(new DefaultFemaleStringActionSocketTestAction(this));
    logixNGFemaleSocketMenu->addAction(new DefaultFemaleStringExpressionSocketTestAction(this));
    logixNGFemaleSocketMenu->addAction(new DefaultFemaleGenericExpressionSocket1_TestAction(this));
    logixNGFemaleSocketMenu->addAction(new DefaultFemaleGenericExpressionSocket2_TestAction(this));

    logixNGMaleSocketMenu->addAction(new DefaultMaleAnalogActionSocketTestAction(this));
    logixNGMaleSocketMenu->addAction(new DefaultMaleAnalogExpressionSocketTestAction(this));
    logixNGMaleSocketMenu->addAction(new DefaultMaleDigitalActionSocketTestAction(this));
    logixNGMaleSocketMenu->addAction(new DefaultMaleDigitalExpressionSocketTestAction(this));
    logixNGMaleSocketMenu->addAction(new DefaultMaleDigitalBooleanActionSocketTestAction(this));
    logixNGMaleSocketMenu->addAction(new DefaultMaleStringActionSocketTestAction(this));
    logixNGMaleSocketMenu->addAction(new DefaultMaleStringExpressionSocketTestAction(this));

    logixNGMenu->addAction(new SymbolTableTestAction(this));

#endif
}
