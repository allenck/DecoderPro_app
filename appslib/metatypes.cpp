#include "metatypes.h"
#include "internalturnoutmanagerxml.h"
#include "defaultmemorymanagerxml.h"
#include "controlpaneleditorxml.h"
#include "abstractsignalheadmanagerxml.h"
#include "defaultsignalmastmanagerxml.h"
#include "defaultaudiomanagerxml.h"
#include "paneleditorxml.h"
#include "entryexitpairsxml.h"
#include "rosterconfigpanexml.h"
#include "defaultconditionalmanagerxml.h"
#include "blockmanagerxml.h"
#include "oblockmanagerxml.h"
#include "oblockmanager.h"
#include "layoutblockmanagerxml.h"
#include "sectionmanagerxml.h"
#include "blockbosslogicxml.h"
#include "warrantmanagerxml.h"
#include "defaultsignalmastlogicmanagerxml.h"
#include "defaultsignalgroupmanagerxml.h"
#include "simpletimebasexml.h"
#include "layouteditorxml.h"
#include "defaultroutemanagerxml.h"
#include "defaultroutemanager.h"
#include "simpletimebasexml.h"
#include "sensoriconxml.h"
#include "turnouticonxml.h"
#include "locoiconxml.h"
//#include "signalheadiconxml.h"
#include "multisensoriconxml.h"
#include "positionablelabelxml.h"
#include "activesystemsmenu.h"
#include "tracksegmentxml.h"
#include "signalmasticonxml.h"
#include "layoutturnoutxml.h"
#include "positionablepointxml.h"
#include "levelxingxml.h"
#include "virtualsignalheadxml.h"
#include "turnoutsignalmastxml.h"
#include "systemconsoleconfigpanelxml.h"
#include "systemconsoleconfigpanel.h"
#include "createbuttonmodel.h"
#include "defaultusermessagepreferencesxml.h"
#include "../libPr3/loconet/Pr3/pr3connectionconfigxml.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfigxml.h"
#include "programmerconfigpanexml.h"
#include "filelocationpanexml.h"
#include "guilafconfigpanexml.h"
#include "managerdefaultselectorxml.h"
#include "../libPr3/loconet/Pr3/pr3connectionconfig.h"
#include "../libPr3/loconet/Locobuffer/locobufferconnectionconfig.h"
#include "../libPr3/loconet/LocobufferUsb/locobufferusbconnectionconfig.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfig.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfigxml.h"
#include "../libPr3/loconet/LnOverTcp/lnovertcpconnectionconfig.h"
#include "../libPr3/loconet/LnOverTcp/lnovertcpconnectionconfigxml.h"
#include "audiotableaction.h"
#include "lnturnoutmanagerxml.h"
#include "locostatspanel.h"
#include "slotmonpane.h"
#include "ds64panel.h"
#include "clockmonpane.h"
#include "locoidpanel.h"
#include "locomonpane.h"
#include "querycvdialog.h"
#include "loconetmsgdialog.h"
#include "cmdstnconfigpane.h"
#include "messagepanel.h"
#include "pr3selectpane.h"
#include "loaderpane.h"
#include "soundloaderpane.h"
#include "editorpane.h"
#include <QAbstractSocket>
#include "route.h"
#include "routetableaction.h"
#include "appconfigbase.h"
#include "logixtableaction.h"
#include "lroutetableaction.h"
#include "sectiontableaction.h"
#include "sensortableaction.h"
#include "sensortabletabaction.h"
#include "signalgrouptableaction.h"
#include "defaultshutdownmanager.h"
#include "connectionspreferencespanel.h"
#include "programmerconfigpane.h"
#include "performactionmodel.h"
//#include "createbuttonpanel.h"
//#include "performactionpanel.h"
#include "managerdefaultsconfigpane.h"
#include "filelocationpane.h"
#include "guilafconfigpane.h"
#include "throttlespreferencespane.h"
#include "usermessagepreferencespane.h"
#include "performfilepanel.h"
#include "rosterconfigpane.h"
#include "guilocalepreferencespanel.h"
#include "railroadnamepreferencespanel.h"
#include "profilepreferencespanel.h"
#include "signalheadtableaction.h"
#include "turnouttableaction.h"
#include "turnouttabletabaction.h"
#include "performscriptpanel.h"
#include "createrostergroupaction.h"
#include "powerpanelaction.h"
#include "dualdecodertoolaction.h"
#include "simpleturnoutctrlaction.h"
#include "throttlecreationaction.h"
#include "rostergrouptableaction.h"
#ifdef SCRIPTING_ENABLED
#include "runjythonscript.h"
#endif
#include "abstractrosteritemaction.h"
#include "fullbackupexportaction.h"
#include "fullbackupimportaction.h"
#include "recreaterosteraction.h"
#include "updatedecoderdefinitionaction.h"
#include "decoderindexcreateaction.h"
#include "panelproaction.h"
#include "rosterframeaction.h"
#include "paneprogdp3action.h"
#include "lnlightmanagerxml.h"
#include "defaultcatalogtreemanagerxml.h"
#include "lnsensormanagerxml.h"
#include "internalreportermanagerxml.h"
#include "lnreportermanagerxml.h"
#include "defaultlogixmanagerxml.h"
#include "locoiopanel.h"
#include "guilafconfigpanexml.h"
#include "lnreportermanagerxml.h"
#include "internalsensormanagerxml.h"
#include "internallightmanagerxml.h"
#include "layoutslipxml.h"
#include "layoutblockmanager.h"
#include "blocktableaction.h"
#include "importrosteritemaction.h"
#include "printrosteraction.h"
#include "tabbedpreferencesaction.h"
#include "consisttoolaction.h"
#include "simpleprogaction.h"
#include "deleterostergroupaction.h"
#include "copyrosteritemaction.h"
#include "panelproaction.h"
#include "copyrostergroupaction.h"
#include "renamerostergroupaction.h"
#include "installdecoderfileaction.h"
#include "rosterframe.h"
#include "positionableroundrectxml.h"
#include "positionablerectanglexml.h"
#include "positionablecirclexml.h"
#include "positionableellipsexml.h"
#include "memorycomboiconxml.h"
#include "memoryspinnericonxml.h"
#include "memoryinputiconxml.h"
#include "dccsignalmastxml.h"
#include "managerdefaultsconfigpanexml.h"
//#include "createbuttonpanelxml.h"
#include "performscriptpanelxml.h"
//#include "performactionpanelxml.h"
#include "performfilepanelxml.h"
#include "warrantpreferencespanel.h"
#include "jmrixconfigpanexml.h"
#include "warranttableaction.h"
#include "portalmanager.h"
#include "controlpaneleditor.h"
#include "warrantpreferences.h"
#include "vsdecodermanager.h"
#include "defaultaudiomanager.h"
#include "blockmanager.h"
#include "defaultcatalogtreemanager.h"
#include "transitmanager.h"
#include "sectionmanager.h"
#include "configuremanager.h"
#include "trainmanifesttext.h"
#include "layoutturntablexml.h"
#include "filehistory.h"
#include "lighttabletabaction.h"
#include "signalmasttableaction.h"
#include "../libPr3/Signal/signalgroupmanager.h"
#include "reportertableaction.h"
#include "memorytableaction.h"
#include "idtagtableaction.h"
#include "../libPr3/Signal/defaultsignalgroupmanager.h"
#include "../libPr3/Signal/defaultsignalsystemmanager.h"
#include "../libPr3/Signal/defaultsignalmastlogicmanager.h"
#include "../libPr3/Signal/defaultsignalmastmanager.h"
#include "signalmastlogictableaction.h"
#include "transittableaction.h"
#include "positionablepolygonxml.h"
#include "positionableshape.h"
#include "doubleturnoutsignalheadxml.h"
#include "singleturnoutsignalheadxml.h"
#include "virtualsignalmastxml.h"
#include "lememoryiconxml.h"
#include "analogclock2displayxml.h"
#include "lighticonxml.h"
#include "slipturnouticonxml.h"
#include "indicatorturnouticonxml.h"
#include "indicatortrackiconxml.h"
#include "reportericonxml.h"
#include "signalmasticon.h"
#include "signalheadiconxml.h"
#include "tripleturnoutsignalheadxml.h"
#include "quadoutputsignalheadxml.h"
#include "signalheadsignalmastxml.h"
#include "transitmanagerxml.h"
#include "rosterentry.h"
//#include "jmriconfigurationmanager.h"
#include "warrantmanager.h"
#include "jmriuserpreferencesmanager.h"
#include "jmrijtablepersistencemanager.h"
#include "startupactionsmanager.h"
#include "managerdefaultselector.h"
#include "connectionconfigmanager.h"
#include "systemconsolepreferencesmanager.h"
#include "programmerconfigmanager.h"
#include "rosterconfigmanager.h"
#include "treeframe.h"
#include "dccthrottle.h"
#include "withrottleprefspanel.h"
#include "webserverpreferencespanel.h"
#include "jsonserverpreferencespanel.h"
#include "startupactionspreferencespanel.h"
//#include "servletutil.h"
#include "Locobuffer/locobufferconnectionconfigxml.h"
#include "LocobufferUsb/locobufferusbconnectionconfigxml.h"
#include "entryexitpairs.h"
#include "paneleditor.h"
#include "performactionmodelfactory.h"
#include "createbuttonmodelfactory.h"
#include "triggerroutemodelfactory.h"
#include "scriptbuttonmodelfactory.h"
#include "performfilemodelfactory.h"
#include "webserveraction.h"
#include "restartstartupactionfactory.h"
#include "systemconnectionaction.h"
#include "restartaction.h"
#include "jsonserveraction.h"
#include "jmriabstractaction.h"
#include "loadxmlconfigaction.h"
#include "analogclockaction.h"
#include "automattableaction.h"
#include "withrottlecreationaction.h"
#include "performactionmodelxml.h"
#include "performfilemodelxml.h"
#include "createbuttonmodelxml.h"
#include "startuppausemodelxml.h"
#include "performscriptmodelxml.h"
#include "triggerroutemodelxml.h"
#include "usbviewaction.h"
#include "treeaction.h"
#include "oblocktableaction.h"
#include "listedtableaction.h"
#include "lighttableaction.h"
#include "xmlfilevalidateaction.h"
#include "startuppausemodel.h"
#include "nixieclockaction.h"
#include "lcdclockaction.h"
#include "powerbuttonaction.h"
#include "locoaddressxml.h"
#include "loconetmenustartupaction.h"
#include "blockcontentsiconxml.h"
#include "treeselectionlistener.h"
#include "sprog/sprogconnectionconfig.h"
#include "sprog/sprogcsconnectionconfig.h"
#include "sprog/sprogconnectionconfigxml.h"
#include "sprog/sprogcsconnectionconfigxml.h"
#include "throttleframemanager.h"
#include "lntcppreferencespanel.h"
#include "lntcpserveraction.h"
#include "switchboardeditorxml.h"
#include "layouttrackdrawingoptionsxml.h"
#include "internalsystemconnectionmemo.h"
#include "systemconsoleconfigpanel.h"
#include "systemconsoleconfigpanelxml.h"
#include "matrixsignalmastxml.h"
#include "signalspeedmap.h"
#include "dccsignalheadxml.h"
#include "tripleoutoutsignalheadxml.h"
#include "../libPr3/loconet/PR2/pr2connectionconfigxml.h"
#include "../libPr3/loconet/PR2/pr2connectionconfig.h"
#include "../libPr3/rfid/rfidsensormanagerxml.h"
#include "../libPr3/rfid/rfidreportermanagerxml.h"
#include "../libPr3/rfid/rfidserialconnectionconfig.h"
#include "../libPr3/rfid/rfidserialconnectionconfigxml.h"
#include "operationssetupxml.h"
#include "sensortabledatamodel.h"
#include "enginemanager.h"
#include "enginemanagerxml.h"
#include "jmriclient/jmriclientconnectionconfigxml.h"
#include "jmriclient/jmriclientconnectionconfig.h"
#include "simpleserveraction.h"
#include "jmrisrcpserveraction.h"
#include "lnmessageserveraction.h"
#include "jmriclient/jmriclientmonpane.h"
#include "jmriclient/jmriclientmonaction.h"
#include "rfid/proxyidtagmanager.h"
#include "nofeedbackturnoutoperation.h"
#include "sensorturnoutoperation.h"
#include "rawturnoutoperation.h"
#include "proxyturnoutmanagerxml.h"
#include "proxysensormanagerxml.h"
#include "../libPr3/jmriclient/jmriclientsystemconnectionmemo.h"
#include "nofeedbackturnoutoperationxml.h"
#include "rawturnoutoperationxml.h"
#include "sensorturnoutoperationxml.h"
#include "blocktableaction.h"
#include "dispatcherframe.h"
#include "optionsfile.h"
#include "leblockcontentsiconxml.h"
#include "lememoryiconxml.h"
#include "Pr4/pr4connectionconfig.h"
#include "Pr4/pr4connectionconfigxml.h"
#include "PR2/pr2connectionconfig.h"
#include "PR2/pr2connectionconfigxml.h"
#include "DCS52/dcs52connectionconfigxml.h"
#include "DCS52/dcs52connectionconfig.h"
#include "DCS240/dcs240connectionconfigxml.h"
#include "DCS240/dcs240connectionconfig.h"
#include "LocoBufferII/locobufferiiconnectionconfigxml.h"
#include "LocoBufferII/locobufferiiconnectionconfig.h"
#include "loaderpane.h"
#include "pr3selectpane.h"
#include "Pr4/pr4selectpane.h"
#include "DCS52/dcs52usbmodeselectpane.h"
#include "DCS240/dcs240usbmodeselectpane.h"
#include "guilafpreferencesmanager.h"
#include "webserverpreferences.h"
#include "layoutshapexml.h"
#include "editormanager.h"
#include "meterframemanagerxml.h"
#include "internalmetermanagerxml.h"
#include "ctc/ctcmanager.h"
#include "ctc/ctcmanagerxml.h"
#include "ctc/ctcexceptionbuffer.h"
#include "ctc/otherdata.h"
#include "se8csignalheadxml.h"
#include "turnoutoperationmanagerxml.h"
#include "lncvprogpane.h"
#include "decoderindexfile.h"

bool Metatypes::done = false;

Metatypes::Metatypes(QObject *parent) :
    QObject(parent)
{
 if(done) return;
 qRegisterMetaType<CreateButtonModel>("CreateButtonModel");
 qRegisterMetaType<DefaultUserMessagePreferencesXml>("DefaultUserMessagePreferencesXml");
 qRegisterMetaType<Pr3ConnectionConfigXml>("ConnectionConfigXml");
 qRegisterMetaType<ProgrammerConfigPaneXml>("ProgrammerConfigPaneXml");
 qRegisterMetaType<FileLocationPaneXml>("FileLocationPaneXml");
 qRegisterMetaType<GuiLafConfigPaneXml>("GuiLafConfigPanelXml");
 qRegisterMetaType<ManagerDefaultSelectorXml>("ManagerDefaultSelectorXml");
 qRegisterMetaType<Pr3ConnectionConfig>("Pr3ConnectionConfig");
 qRegisterMetaType<LocobufferConnectionConfig>("LocobufferConnectionConfig");
 qRegisterMetaType<LocobufferUsbConnectionConfig>("LocobufferUsbConnectionConfig");
 qRegisterMetaType<LocobufferUsbConnectionConfigXml>("LocobufferUsbConnectionConfigXml");
 qRegisterMetaType<HexFileConnectionConfig>("HexFileConnectionConfig");
 qRegisterMetaType<HexFileConnectionConfigXml>("HexFileConnectionConfigXml");
 qRegisterMetaType<LnOverTcpConnectionConfig>("LnOverTcpConnectionConfig");
 qRegisterMetaType<LnOverTcpConnectionConfigXml>("LnOverTcpConnectionConfigXml");
 qRegisterMetaType<AudioTableAction>("AudioTableAction");
 qRegisterMetaType<BlockTableAction>("BlockTableAction");
// qRegisterMetaType<LightTableAction>("LightTableAction");
// qRegisterMetaType<MemoryTableAction>("MemoryTableAction");
// qRegisterMetaType<SignalMastTableAction>("SignalMastTableAction");
// qRegisterMetaType<TransitTableAction>("TransitTableAction");
 qRegisterMetaType<LnTurnoutManagerXml>("LnTurnoutManagerXml");
 qRegisterMetaType<InternalTurnoutManagerXml>("InternalTurnoutManagerXml");
 qRegisterMetaType<DefaultMemoryManagerXml>("DefaultMemoryManagerXml");
 qRegisterMetaType<ControlPanelEditorXml>("ControlPanelEditorXml");
 qRegisterMetaType<AbstractSignalHeadManagerXml>("AbstractSignalHeadManagerXml");
 qRegisterMetaType<DefaultSignalMastManagerXml>("DefaultSignalMastManagerXml");
 qRegisterMetaType<DefaultAudioManagerXml>("DefaultAudioManagerXml");
 qRegisterMetaType<PanelEditorXml>("PanelEditorXml");
 qRegisterMetaType<EntryExitPairsXml>("EntryExitPairsXml");
 qRegisterMetaType<RosterConfigPaneXml>("RosterConfigPaneXml");
 qRegisterMetaType<DefaultConditionalManagerXml>("DefaultConditionalManagerXml");
 qRegisterMetaType<BlockManagerXml>("BlockManagerXml");
 qRegisterMetaType<OBlockManagerXml>("OBlockManagerXml");
 qRegisterMetaType<LayoutBlockManagerXml>("LayoutBlockManagerXml");
 qRegisterMetaType<SectionManagerXml>("SectionManagerXml");
 qRegisterMetaType<BlockBossLogicXml>("BlockBossLogicXml");
 qRegisterMetaType<WarrantManagerXml>("WarrantManagerXml");
 qRegisterMetaType<DefaultSignalMastLogicManagerXml>("DefaultSignalMastLogicManagerXml");
 qRegisterMetaType<DefaultSignalGroupManagerXml>("DefaultSignalGroupManagerXml");
 qRegisterMetaType<LayoutEditorXml>("LayoutEditorXml");
 qRegisterMetaType<DefaultRouteManagerXml>("DefaultRouteManagerXml");
 qRegisterMetaType<SimpleTimebaseXml>("SimpleTimebaseXml");
 qRegisterMetaType<SensorIconXml>("SensorIconXml");
 qRegisterMetaType<LocoIconXml>("LocoIconXml");
 qRegisterMetaType<SignalHeadIconXml>("SignalHeadIconXml");
 qRegisterMetaType<MultiSensorIconXml>("MultiSensorIconXml");
 qRegisterMetaType<PositionableLabelXml>("PositionableLabelXml");
 qRegisterMetaType<TrackSegmentXml>("TrackSegmentXml");
 qRegisterMetaType<SignalMastIconXml>("SignalMastIconXml");
 qRegisterMetaType<LayoutTurnoutXml>("LayoutTurnoutXml");
 qRegisterMetaType<PositionablePointXml>("PositionablePointXml");
 qRegisterMetaType<LevelXingXml>("LevelXingXml");
 qRegisterMetaType<VirtualSignalHeadXml>("VirtualSignalHeadXml");
 qRegisterMetaType<TurnoutSignalMastXml>("TurnoutSignalMastXml");
 qRegisterMetaType<SystemConsoleConfigPanelXml>("SystemConsoleConfigPanelXml");
 qRegisterMetaType<SystemConsoleConfigPanel>("SystemConsoleConfigPanel");
 qRegisterMetaType<JFrame>("JFrame");
 qRegisterMetaType<LocoStatsPanel>("LocoStatsPanel");
 qRegisterMetaType<SlotMonPane>("SlotMonPane");
 qRegisterMetaType<DS64Panel>("DS64Panel");
 qRegisterMetaType<ClockMonPane>("ClockMonPane");
 qRegisterMetaType<LocoIdPanel>("LocoIdPanel");
 qRegisterMetaType<LocoMonPane>("LocoMonPane");
 qRegisterMetaType<QueryCvDialog>("QueryCvDialog");
 qRegisterMetaType<LocoNetMsgDialog>("LocoNetMsgDialog");
 qRegisterMetaType<CmdStnConfigPane>("CmdStnConfigPane");
 qRegisterMetaType<MessagePanel>("MessagePanel");
 qRegisterMetaType<Pr3SelectPane>("Pr3SelectPane");
 qRegisterMetaType<LoaderPane>("LoaderPane");
 qRegisterMetaType<SoundLoaderPane>("SoundLoaderPane");
 qRegisterMetaType<EditorPane>("EditorPane");
#if QT_VERSION < 0x50000
 qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
 qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
#endif
 qRegisterMetaType<RouteTableAction>("RouteTableAction");
 qRegisterMetaType<AppConfigBase>("AppConfigBase");
 qRegisterMetaType<LogixTableAction>("LogixTableAction");
 qRegisterMetaType<LRouteTableAction>("LRouteTableAction");
 qRegisterMetaType<SectionTableAction>("SectionTableAction");
 qRegisterMetaType<SensorTableAction>("SensorTableAction");
 qRegisterMetaType<SensorTableTabAction>("SensorTableTabAction");
 qRegisterMetaType<SignalGroupTableAction>("SignalGroupTableAction");
 qRegisterMetaType<DefaultShutDownManager>("DefaultShutDownManager");
 qRegisterMetaType<ConnectionsPreferencesPanel>("ConnectionsPreferencesPanel");
 qRegisterMetaType<ProgrammerConfigPane>("ProgrammerConfigPane");
 //qRegisterMetaType<CreateButtonPanel>("CreateButtonPanel");
 //qRegisterMetaType<PerformActionPanel>("PerformActionPanel");
 qRegisterMetaType<PerformActionModel>("PerformActionModel");
 qRegisterMetaType<ManagerDefaultsConfigPane>("ManagerDefaultsConfigPane");
 qRegisterMetaType<FileLocationPane>("FileLocationPane");
 qRegisterMetaType<GuiLafConfigPane>("GuiLafConfigPane");
 qRegisterMetaType<ThrottlesPreferencesPane>("ThrottlesPreferencesPane");
 qRegisterMetaType<UserMessagePreferencesPane>("UserMessagePreferencesPane");
 qRegisterMetaType<PerformFilePanel>("PerformFilePanel");
 qRegisterMetaType<RosterConfigPane>("RosterConfigPane");
 qRegisterMetaType<GuiLocalePreferencesPanel>("GuiLocalePreferencesPanel");
 qRegisterMetaType<RailroadNamePreferencesPanel>("RailroadNamePreferencesPanel");
 qRegisterMetaType<ProfilePreferencesPanel>("ProfilePreferencesPanel");
 qRegisterMetaType<SignalHeadTableAction>("SignalHeadTableAction");
 qRegisterMetaType<TurnoutTableAction>("TurnoutTableAction");
 qRegisterMetaType<TurnoutTableTabAction>("TurnoutTableTabAction");
 qRegisterMetaType<PerformScriptPanel>("PerformScriptPanel");
 qRegisterMetaType<CreateRosterGroupAction>("CreateRosterGroupAction");
 qRegisterMetaType<PowerPanelAction>("PowerPanelAction");
 qRegisterMetaType<DualDecoderToolAction>("DualDecoderToolAction");
 qRegisterMetaType<SimpleTurnoutCtrlAction>("SimpleTurnoutCtrlAction");
 qRegisterMetaType<ThrottleCreationAction>("ThrottleCreationAction");
 qRegisterMetaType<RosterGroupTableAction>("RosterGroupTableAction");
#ifdef SCRIPTING_ENABLED
 qRegisterMetaType<RunJythonScript>("RunJythonScript");
#endif
 qRegisterMetaType<AbstractRosterItemAction>("AbstractRosterItemAction");
 qRegisterMetaType<FullBackupExportAction>("FullBackupExportAction");
 qRegisterMetaType<FullBackupImportAction>("FullBackupImportAction");
 qRegisterMetaType<DecoderIndexCreateAction>("DecoderIndexCreateAction");
 qRegisterMetaType<UpdateDecoderDefinitionAction>("UpdateDecoderDefinitionAction");
 qRegisterMetaType<RecreateRosterAction>("RecreateRosterAction");
 qRegisterMetaType<PanelProAction>("PanelProAction");
 qRegisterMetaType<RosterFrameAction>("RosterFrameAction");
 qRegisterMetaType<PaneProgDp3Action>("PaneProgDp3Action");
 qRegisterMetaType<LnLightManagerXml>("LnLightManagerXml");
 qRegisterMetaType<LnSensorManagerXml>("LnSensorManagerXml");
 qRegisterMetaType<InternalReporterManagerXml>("InternalReporterManagerXml");
 qRegisterMetaType<InternalReporterManagerXml>("InternalReporterManagerXml");
 qRegisterMetaType<DefaultLogixManagerXml>("DefaultLogixManagerXml");
 qRegisterMetaType<LocoIOPanel>("LocoIOPanel");
 qRegisterMetaType<GuiLafConfigPaneXml>("GuiLafConfigPaneXml");
 qRegisterMetaType<LnReporterManagerXml>("LnReporterManagerXml");
 qRegisterMetaType<InternalSensorManagerXml>("InternalSensorManagerXml");
 qRegisterMetaType<InternalLightManagerXml>("InternalLightManagerXml");
 qRegisterMetaType<LayoutSlipXml>("LayoutSlipXml");
 qRegisterMetaType<LayoutBlockManager>("LayoutBlockManager");
 qRegisterMetaType<RfidSensorManagerXml>("RfidSensorManagerXml");
 qRegisterMetaType<BlockTableAction>("BlockTableAction");
 qRegisterMetaType<ImportRosterItemAction>("ImportRosterItemAction");
 qRegisterMetaType<PrintRosterAction>("PrintRosterAction");
 qRegisterMetaType<TabbedPreferencesAction>("TabbedPreferencesAction");
 qRegisterMetaType<ConsistToolAction>("ConsistToolAction");
 qRegisterMetaType<SimpleProgAction>("SimpleProgAction");
 qRegisterMetaType<DeleteRosterGroupAction>("DeleteRosterGroupAction");
 qRegisterMetaType<CopyRosterItemAction>("CopyRosterItemAction");
 qRegisterMetaType<PanelProAction>("PanelProAction");
 qRegisterMetaType<CopyRosterGroupAction>("CopyRosterGroupAction");
 qRegisterMetaType<RenameRosterGroupAction>("RenameRosterGroupAction");
 qRegisterMetaType<InstallDecoderFileAction>("InstallDecoderFileAction");
 qRegisterMetaType<InstallDecoderURLAction>("InstallDecoderURLAction");
 qRegisterMetaType<RosterFrame>("RosterFrame");
 qRegisterMetaType<PositionableCircleXml>("PositionableCircleXml");
 qRegisterMetaType<PositionableEllipseXml>("PositionableEllipseXml");
 qRegisterMetaType<PositionableRectangleXml>("PositionableRectangleXml");
 qRegisterMetaType<PositionableRoundRectXml>("PositionableRoundRectXml");
 qRegisterMetaType<MemorySpinnerIconXml>("MemorySpinnerIconXml");
 qRegisterMetaType<MemoryComboIconXml>("MemoryComboIconXml");
 qRegisterMetaType<MemoryInputIconXml>("MemoryInputIconXml");
 qRegisterMetaType<DccSignalMastXml>("DccSignalMastXml");
 qRegisterMetaType<ManagerDefaultsConfigPaneXml>("ManagerDefaultsConfigPaneXml");
 //qRegisterMetaType<CreateButtonPanelXml>("CreateButtonPanelXml");
 qRegisterMetaType<PerformScriptPanelXml>("PerformScriptPanelXml");
 //qRegisterMetaType<PerformActionPanelXml>("PerformActionPanelXml");
 qRegisterMetaType<PerformFilePanelXml>("PerformFilePanelXml");
 qRegisterMetaType<WarrantPreferencesPanel>("WarrantPreferencesPanel");
 qRegisterMetaType<JmrixConfigPaneXml>("JmrixConfigPaneXml");
 qRegisterMetaType<WarrantTableAction>("WarrantTableAction");
 qRegisterMetaType<PortalManager>("PortalManager");
 qRegisterMetaType<ControlPanelEditor>("");
 qRegisterMetaType<WarrantPreferences>("WarrantPreferences");
 qRegisterMetaType<VSDecoderManager>("VSDecoderManager");
 qRegisterMetaType<DefaultAudioManager>("DefaultAudioManager");
 qRegisterMetaType<BlockManager>("BlockManager");
 qRegisterMetaType<DefaultCatalogTreeManager>("DefaultCatalogTreeManager");
 qRegisterMetaType<TransitManager>("TransitManager");
 qRegisterMetaType<SectionManager>("SectionManager");
 //qRegisterMetaType<CatalogTreeManager>("CatalogTreeManager");
 //qRegisterMetaType<SystemConnectionMemo>("SystemConnectionMemo");
 //qRegisterMetaType<ConfigureManager>("ConfigureManager");
 qRegisterMetaType<Operations::TrainManifestText>("TrainManifestText");
 qRegisterMetaType<LayoutTurntableXml>("LayoutTurntableXml");
 qRegisterMetaType<FileHistory>("FileHistory");
 qRegisterMetaType<JmriUserPreferencesManager>("JmriUserPreferencesManager");
 //qRegisterMetaType<ListedTableFrame>("ListedTableFrame");
 qRegisterMetaType<LightTableTabAction>("LightTableTabAction");
 qRegisterMetaType<SignalMastTableAction>("SignalMastTableAction");
 //qRegisterMetaType<SignalGroupManager>("SignalGroupManager");
 qRegisterMetaType<ReporterTableAction>("ReporterTableAction");
 qRegisterMetaType<MemoryTableAction>("MemoryTableAction");
 qRegisterMetaType<IdTagTableAction>("IdTagTableAction");
 qRegisterMetaType<DefaultSignalGroupManager>("DefaultSignalGroupManager");
 qRegisterMetaType<DefaultSignalSystemManager>("DefaultSignalSystemManager");
 qRegisterMetaType<DefaultSignalMastLogicManager>("DefaultSignalMastLogicManager");
 //qRegisterMetaType<DefaultRouteManager>("DefaultRouteManager");
 qRegisterMetaType<DefaultSignalMastManager>("DefaultSignalMastManager");
 qRegisterMetaType<SignalMastLogicTableAction>("SignalMastLogicTableAction");
 qRegisterMetaType<TransitTableAction>("TransitTableAction");
 qRegisterMetaType<PositionablePolygonXml>("PositionablePolygonXml");
 qRegisterMetaType<PositionableShapeXml>("PositionableShapeXml");
 qRegisterMetaType<DoubleTurnoutSignalHeadXml>("DoubleTurnoutSignalHeadXml");
 qRegisterMetaType<SingleTurnoutSignalHeadXml>("SingleTurnoutSignalHeadXml");
 qRegisterMetaType<VirtualSignalMastXml>("VirtualSignalMastXml");
 qRegisterMetaType<LEMemoryIconXml>("MemoryIconXml");
 qRegisterMetaType<AnalogClock2DisplayXml>("AnalogClock2DisplayXml");
 qRegisterMetaType<LightIconXml>("LightIconXml");
 qRegisterMetaType<TurnoutIconXml>("TurnoutIconXml");
 qRegisterMetaType<SlipTurnoutIconXml>("SlipTurnoutIconXml");
 qRegisterMetaType<IndicatorTurnoutIconXml>("IndicatorTurnoutIconXml");
 qRegisterMetaType<IndicatorTrackIconXml>("IndicatorTrackIconXml");
 qRegisterMetaType<ReporterIconXml>("ReporterIconXml");
 qRegisterMetaType<SignalMastIcon>("SignalMastIcon");
 qRegisterMetaType<TripleTurnoutSignalHeadXml>("TripleTurnoutSignalHeadXml");
 qRegisterMetaType<QuadOutputSignalHeadXml>("QuadOutputSignalHeadXml");
 qRegisterMetaType<SignalHeadSignalMastXml>("SignalHeadSignalMastXml");
 qRegisterMetaType<TransitManagerXml>("TransitManagerXml");
 qRegisterMetaType<RosterEntry>("RosterEntry");
 //qRegisterMetaType<JmriConfigurationManager>("JmriConfigurationManager");
 qRegisterMetaType<WarrantManager>("WarrantManager");
 qRegisterMetaType<OBlockManager>("OBlockManager");
 //qRegisterMetaType<JmriUserPreferencesManager>("JmriUserPreferencesManager");
 qRegisterMetaType<JmriJTablePersistenceManager>("JmriJTablePersistenceManager");
 qRegisterMetaType<StartupActionsManager>("StartupActionsManager");
 qRegisterMetaType<ManagerDefaultSelector>("ManagerDefaultSelector");
 qRegisterMetaType<ConnectionConfigManager>("ConnectionConfigManager");
 qRegisterMetaType<SystemConsolePreferencesManager>("SystemConsolePreferencesManager");
 qRegisterMetaType<ProgrammerConfigManager>("ProgrammerConfigManager");
 qRegisterMetaType<RosterConfigManager>("RosterConfigManager");
 qRegisterMetaType<TreeFrame>("TreeFrame");
 qRegisterMetaType<DccThrottle>("DccThrottle");
 qRegisterMetaType<WiThrottlePrefsPanel>("WiThrottlePrefsPanel");
 qRegisterMetaType<WebServerPreferencesPanel>("WebServerPreferencesPanel");
 qRegisterMetaType<JsonServerPreferencesPanel>("JsonServerPreferencesPanel");
 qRegisterMetaType<StartupActionsPreferencesPanel>("StartupActionsPreferencesPanel");
 qRegisterMetaType<EntryExitPairs>("EntryExitPairs");
 qRegisterMetaType<EntryExitPairsXml>("EntryExitPairsXml");
 qRegisterMetaType<PanelEditor>("PanelEditor");
 qRegisterMetaType<LayoutEditor>("LayoutEditor");
 qRegisterMetaType<PerformActionModelFactory>("PerformActionModelFactory");
 qRegisterMetaType<CreateButtonModelFactory>("CreateButtonModelFactory");
 qRegisterMetaType<TriggerRouteModelFactory>("TriggerRouteModelFactory");
 qRegisterMetaType<ScriptButtonModelFactory>("ScriptButtonModelFactory");
 qRegisterMetaType<PerformFileModelFactory>("PerformFileModelFactory");
 qRegisterMetaType<WebServerAction>("WebServerAction");
 qRegisterMetaType<RestartStartupActionFactory>("RestartStartupActionFactory");
 qRegisterMetaType<SystemConnectionAction>("SystemConnectionAction");
 qRegisterMetaType<RestartAction>("RestartAction");
 qRegisterMetaType<JsonServerAction>("JsonServerAction");
 qRegisterMetaType<JmriAbstractAction>("JmriAbstractAction");
 qRegisterMetaType<LoadXmlConfigAction>("LoadXmlConfigAction");
 qRegisterMetaType<AnalogClockAction>("AnalogClockAction");
 qRegisterMetaType<AutomatTableAction>("AutomatTableAction");
 qRegisterMetaType<WiThrottleCreationAction>("WiThrottleCreationAction");
 qRegisterMetaType<PerformActionModelXml>("PerformActionModelXml");
 qRegisterMetaType<PerformFileModelXml>("PerformFileModelXml");
 qRegisterMetaType<CreateButtonModelXml>("CreateButtonModelXml");
 qRegisterMetaType<StartupPauseModelXml>("StartupPauseModelXml");
 qRegisterMetaType<PerformScriptModelXml>("PerformScriptModelXml");
 qRegisterMetaType<TriggerRouteModelXml>("TriggerRouteModelXml");
 qRegisterMetaType<UsbViewAction>("UsbViewAction");
 qRegisterMetaType<TreeAction>("TreeAction");
 qRegisterMetaType<ListedTableAction>("ListedTableAction");
 qRegisterMetaType<OBlockTableAction>("OBlockTableAction");
 qRegisterMetaType<LightTableAction>("LightTableAction");
 qRegisterMetaType<XmlFileValidateAction>("XmlFileValidateAction");
 qRegisterMetaType<StartupPauseModel>("StartupPauseModel");
 qRegisterMetaType<NixieClockAction>("NixieClockAction");
 qRegisterMetaType<LcdClockAction>("LcdClockAction");
 qRegisterMetaType<PowerButtonAction>("PowerButtonAction");
 qRegisterMetaType<LocoAddressXml>("LocoAddressXml");
 qRegisterMetaType<LocoNetMenuStartupAction>("LocoNetMenuStartupAction");
 qRegisterMetaType<BlockContentsIconXml>("BlockContentsIconXml");
 qRegisterMetaType<TreeSelectionListener>("TreeSelectionListener");
 qRegisterMetaType<Sprog::SprogConnectionConfig>("SprogConnectionConfig");
 qRegisterMetaType<Sprog::SprogCSConnectionConfig>("SprogCSConnectionConfig");
 qRegisterMetaType<Sprog::SprogConnectionConfigXml>("SprogConnectionConfigXml");
 qRegisterMetaType<Sprog::SprogCSConnectionConfigXml>("SprogCSConnectionConfigXml");
 qRegisterMetaType<LnTcpPreferencesPanel>("LnTcpPreferencesPanel");
 qRegisterMetaType<LnTcpServerAction>("LnTcpServerAction");
 qRegisterMetaType<SwitchboardEditorXml>("SwitchboardEditorXml");
 qRegisterMetaType<LayoutTrackDrawingOptionsXml>("LayoutTrackDrawingOptionsXml");
 qRegisterMetaType<InternalSystemConnectionMemo>("InternalSystemConnectionMemo");
 qRegisterMetaType<SystemConsoleConfigPanel>("SystemConsoleConfigPanel");
 qRegisterMetaType<SystemConsoleConfigPanelXml>("SystemConsoleConfigPanelXml");
 qRegisterMetaType<MatrixSignalMastXml>("MatrixSignalMastXml");
 qRegisterMetaType<SignalSpeedMap>("SignalSpeedMap");
 qRegisterMetaType<DccSignalHeadXml>("DccSignalHeadXml");
 qRegisterMetaType<TripleOutputSignalHeadXml>("TripleOutputSignalHeadXml");
 qRegisterMetaType<Pr2ConnectionConfigXml>("Pr2ConnectionConfigXml");
 qRegisterMetaType<Pr2ConnectionConfig>("Pr2ConnectionConfig");
 qRegisterMetaType<RfidReporterManagerXml>("RfidReporterManagerXml");
 qRegisterMetaType<RfidSensorManagerXml>("RfidSensorManagerXml");
 qRegisterMetaType<RfidSerialConnectionConfig>("RfidSerialConnectionConfig");
 qRegisterMetaType<RfidSerialConnectionConfigXml>("RfidSerialConnectionConfigXml");
 qRegisterMetaType<Operations::OperationsSetupXml>("OperationsSetupXml");
 qRegisterMetaType<SensorTableDataModel>("SensorTableDataModel");
 qRegisterMetaType<SensorTableAction>("SensorTableAction");
 qRegisterMetaType<Operations::EngineManager>("EngineManager");
 qRegisterMetaType<Operations::EngineManagerXml>("EngineManagerXml");
 qRegisterMetaType<JMRIClientConnectionConfigXml>("JMRIClientConnectionConfigXml");
 qRegisterMetaType<JMRIClientConnectionConfig>("JMRIClientConnectionConfig");
 qRegisterMetaType<SimpleServerAction>("SimpleServerAction");
 qRegisterMetaType<JmriSRCPServerAction>("JmriSRCPServerAction");
 qRegisterMetaType<LnMessageServerAction>("LnMessageServerAction");
 qRegisterMetaType<JMRIClientMonAction>("JMRIClientMonAction");
 qRegisterMetaType<JMRIClientMonPane>("JMRIClientMonPane");
 qRegisterMetaType<ProxyIdTagManager>("ProxyIdTagManager");
 qRegisterMetaType<RawTurnoutOperation>("RawTurnoutOperation");
 qRegisterMetaType<NoFeedbackTurnoutOperation>("NoFeedbackTurnoutOperation");
 qRegisterMetaType<SensorTurnoutOperation>("SensorTurnoutOperation");
 qRegisterMetaType<ProxyTurnoutManagerXml>("ProxyTurnoutManagerXml");
 qRegisterMetaType<ProxySensorManagerXml>("ProxySensorManagerXml");
 qRegisterMetaType<NamedBeanHandleManager>("NamedBeanHandleManager");
 qRegisterMetaType<JMRIClientSystemConnectionMemo>("JMRIClientSystemConnectionMemo");
 qRegisterMetaType<NoFeedbackTurnoutOperationXml>("NoFeedbackTurnoutOperationXml");
 qRegisterMetaType<RawTurnoutOperationXml>("RawTurnoutOperationXml");
 qRegisterMetaType<SensorTurnoutOperationXml>("SensorTurnoutOperationXml");
 qRegisterMetaType<DispatcherFrame>("DispatcherFrame");
 qRegisterMetaType<OptionsFile>("OptionsFile");
 qRegisterMetaType<LEBlockContentsIconXml>("LEBlockContentsIconXml");
 qRegisterMetaType<LEMemoryIconXml>("LEMemoryIconXml");
 qRegisterMetaType<Pr4ConnectionConfig>("Pr4ConnectionConfig");
 qRegisterMetaType<Pr4ConnectionConfigXml>("Pr4ConnectionConfigXml");
 qRegisterMetaType<Pr2ConnectionConfig>("Pr2ConnectionConfig");
 qRegisterMetaType<Pr2ConnectionConfigXml>("Pr2ConnectionConfigXml");
 qRegisterMetaType<DCS52ConnectionConfigXml>("DCS52ConnectionConfigXml");
 qRegisterMetaType<DCS52ConnectionConfig>("DCS52ConnectionConfig");
 qRegisterMetaType<DCS240ConnectionConfigXml>("DCS240ConnectionConfigXml");
 qRegisterMetaType<DCS240ConnectionConfig>("DCS240ConnectionConfig");
 qRegisterMetaType<LocoBufferIIConnectionConfigXml>("LocoBufferIIConnectionConfigXml");
 qRegisterMetaType<LocoBufferIIConnectionConfig>("LocoBufferIIConnectionConfig");
 qRegisterMetaType<LoaderPane>("LoaderPane");
 qRegisterMetaType<Dcs52UsbModeSelectPane>("Dcs52UsbModeSelectPane");
 qRegisterMetaType<Pr4SelectPane>("Pr4SelectPane");
 qRegisterMetaType<Pr3SelectPane>("Pr3SelectPane");
 qRegisterMetaType<Dcs240UsbModeSelectPane>("Dcs240UsbModeSelectPane");
 qRegisterMetaType<GuiLafPreferencesManager>("GuiLafPreferencesManager");
 qRegisterMetaType<WebServerPreferences>("WebServerPreferences");
 qRegisterMetaType<LayoutShapeXml>("LayoutShapeXml");
 qRegisterMetaType<EditorManager>("EditorManager");
 qRegisterMetaType<MeterFrameManagerXml>("MeterFrameManagerXml");
 qRegisterMetaType<InternalMeterManagerXml>("InternalMeterManagerXml");
 qRegisterMetaType<CtcManager>("CtcManager");
 qRegisterMetaType<CtcManagerXml>("CtcManagerXml");
 qRegisterMetaType<CTCExceptionBuffer>("CTCExceptionBuffer");
 qRegisterMetaType<OtherData>("OtherData");
 qRegisterMetaType<SE8cSignalHeadXml>("SE8cSignalHeadXml");
 qRegisterMetaType<TurnoutOperationManagerXml>("TurnoutOperationManagerXml");
 qRegisterMetaType<LncvProgPane>("LncvProgPane");
 qRegisterMetaType<DecoderIndexFile>("DecoderIndexFile");

 Metatypes::done = true;
}
