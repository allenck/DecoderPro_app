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
#include "layoutblockmanagerxml.h"
#include "sectionmanagerxml.h"
#include "blockbosslogicxml.h"
#include "warrantmanagerxml.h"
#include "defaultsignalmastlogicmanagerxml.h"
#include "defaultsignalgroupmanagerxml.h"
#include "simpletimebasexml.h"
#include "layouteditorxml.h"
#include "defaultroutemanagerxml.h"
#include "simpletimebasexml.h"
#include "sensoriconxml.h"
#include "turnouticonxml.h"
#include "locoiconxml.h"
#include "signalheadiconxml.h"
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
#include "../libPr3/loconet/Pr3/connectionconfigxml.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfigxml.h"
#include "programmerconfigpanexml.h"
#include "filelocationpanexml.h"
#include "guilafconfigpanexml.h"
#include "managerdefaultselectorxml.h"
#include "../libPr3/loconet/Pr3/pr3connectionconfig.h"
#include "../libPr3/loconet/Locobuffer/locobufferconnectionconfig.h"
#include "../libPr3/loconet/LocobufferUsb/locobufferusbconnectionconfig.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfig.h"
#include "../libPr3/loconet/LnOverTcp/lnovertcpconnectionconfig.h"
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
#include "signalgrouptableaction.h"
#include "defaultshutdownmanager.h"
#include "connectionspreferencespanel.h"
#include "programmerconfigpane.h"
#include "performactionmodel.h"
#include "createbuttonpanel.h"
#include "performactionpanel.h"
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
#include "rfidsensormanagerxml.h"
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
#include "createbuttonpanelxml.h"
#include "performscriptpanelxml.h"
#include "performactionpanelxml.h"
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
#include "defaultusermessagepreferences.h"

bool Metatypes::done = false;

Metatypes::Metatypes(QObject *parent) :
    QObject(parent)
{
 qRegisterMetaType<CreateButtonModel>("CreateButtonModel");
 qRegisterMetaType<DefaultUserMessagePreferencesXml>("DefaultUserMessagePreferencesXml");
 qRegisterMetaType<ConnectionConfigXml>("ConnectionConfigXml");
 qRegisterMetaType<HexFileConnectionConfigXml>("HexFileConnectionConfigXml");
 qRegisterMetaType<ProgrammerConfigPaneXml>("ProgrammerConfigPaneXml");
 qRegisterMetaType<FileLocationPaneXml>("FileLocationPaneXml");
 qRegisterMetaType<GuiLafConfigPaneXml>("GuiLafConfigPanelXml");
 qRegisterMetaType<ManagerDefaultSelectorXml>("ManagerDefaultSelectorXml");
 qRegisterMetaType<Pr3ConnectionConfig>("Pr3ConnectionConfig");
 qRegisterMetaType<LocobufferConnectionConfig>("LocobufferConnectionConfig");
 qRegisterMetaType<LocobufferUsbConnectionConfig>("LocobufferUsbConnectionConfig");
 qRegisterMetaType<HexFileConnectionConfig>("HexFileConnectionConfig");
 qRegisterMetaType<HexFileConnectionConfigXml>("HexFileConnectionConfigXml");
 qRegisterMetaType<LnOverTcpConnectionConfig>("LnOverTcpConnectionConfig");
 qRegisterMetaType<LnOverTcpConnectionConfigXml>("LnOverTcpConnectionConfigXml");
 qRegisterMetaType<AudioTableAction>("AudioTableAction");
// qRegisterMetaType<BlockTableAction>("BlockTableAction");
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
 qRegisterMetaType<SignalGroupTableAction>("SignalGroupTableAction");
 qRegisterMetaType<DefaultShutDownManager>("DefaultShutDownManager");
 qRegisterMetaType<ConnectionsPreferencesPanel>("ConnectionsPreferencesPanel");
 qRegisterMetaType<ProgrammerConfigPane>("ProgrammerConfigPane");
 qRegisterMetaType<CreateButtonPanel>("CreateButtonPanel");
 qRegisterMetaType<PerformActionPanel>("PerformActionPanel");
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
 qRegisterMetaType<DefaultCatalogTreeManagerXml>("DefaultCatalogTreeManagerXml");
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
 qRegisterMetaType<CreateButtonPanelXml>("CreateButtonPanelXml");
 qRegisterMetaType<PerformScriptPanelXml>("PerformScriptPanelXml");
 qRegisterMetaType<PerformActionPanelXml>("PerformActionPanelXml");
 qRegisterMetaType<PerformFilePanelXml>("PerformFilePanelXml");
 qRegisterMetaType<WarrantPreferencesPanel>("WarrantPreferencesPanel");
 qRegisterMetaType<JmrixConfigPaneXml>("JmrixConfigPaneXml");
 qRegisterMetaType<WarrantTableAction>("WarrantTableAction");
 qRegisterMetaType<PortalManager>("PortalManager");
 qRegisterMetaType<ControlPanelEditor>("ControlPanelEditor");
 qRegisterMetaType<WarrantPreferences>("WarrantPreferences");
 qRegisterMetaType<VSDecoderManager>("VSDecoderManager");
 qRegisterMetaType<DefaultAudioManager>("DefaultAudioManager");
 qRegisterMetaType<BlockManager>("BlockManager");
 qRegisterMetaType<DefaultCatalogTreeManager>("DefaultCatalogTreeManager");
 qRegisterMetaType<TransitManager>("TransitManager");
 qRegisterMetaType<SectionManager>("SectionManager");
 qRegisterMetaType<CatalogTreeManager>("CatalogTreeManager");
 qRegisterMetaType<SystemConnectionMemo>("SystemConnectionMemo");
 //qRegisterMetaType<ConfigureManager>("ConfigureManager");
 qRegisterMetaType<Operations::TrainManifestText>("TrainManifestText");
 qRegisterMetaType<LayoutTurntableXml>("LayoutTurntableXml");
 qRegisterMetaType<FileHistory>("FileHistory");
 qRegisterMetaType<DefaultUserMessagePreferences>("DefaultUserMessagePreferences");

 Metatypes::done = true;
}

QObject* Class::forName(QString adapterName)
{
 QObject* adapter = NULL;
 QString aName = adapterName.mid(adapterName.lastIndexOf(".") +1);
 int typeId = QMetaType::type(aName.toLocal8Bit());
 if(typeId > 0)
 {
#if QT_VERSION < 0x050000
  adapter = (QObject*)QMetaType::construct(typeId);
#else
  adapter = (QObject*)QMetaType::create(typeId);
#endif
 }
 return adapter;
}
