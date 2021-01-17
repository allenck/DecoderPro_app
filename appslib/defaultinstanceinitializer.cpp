#include "defaultinstanceinitializer.h"
#include "exceptions.h"
#include "defaultroutemanager.h"
#include "defaultidtagmanager.h"
#include "defaultmemorymanager.h"
#include "defaultclockcontrol.h"
#include "abstractsignalheadmanager.h"
#include "defaultsignalmastmanager.h"
#include "defaultsignalsystemmanager.h"
#include "transitmanager.h"
#include "simpletimebase.h"
//#include "sectionmanager.h"
#include "defaultsignalgroupmanager.h"
#include "../LayoutEditor/configxmlmanager.h"
//#include "transitmanager.h"
#include "defaultlogixmanager.h"
#include "defaultconditionalmanager.h"
#include "defaultsignalmastlogicmanager.h"
#include "rostericonfactory.h"
#include "defaultsignalgroupmanager.h"
#include "deferringprogrammermanager.h"
#include "defaultaudiomanager.h"
#include "vsdecodermanager.h"
#include "logger.h"
#include "jmriconfigurationmanager.h"
#include "defaultshutdownmanager.h"
#include "defaultcatalogtreemanager.h"
//#include "layoutblockmanager.h"
#include "warrantmanager.h"
#include "oblockmanager.h"
#include "portalmanager.h"
#include "jmrijtablepersistencemanager.h"
#include "startupactionsmanager.h"
#include "connectionconfigmanager.h"
#include "systemconsolepreferencesmanager.h"
#include "programmerconfigmanager.h"
#include "consistmanager.h"
#include "rosterconfigmanager.h"
#include "filelocationspreferences.h"
#include "guilafpreferencesmanager.h"
#include "defaultprogrammermanager.h"
#include "withrottlepreferences.h"
#include "webserverpreferences.h"
#include "managerdefaultselector.h"
#include "internalsystemconnectionmemo.h"
#include "performactionmodelfactory.h"
#include "startuppausefactory.h"
#include "createbuttonmodelfactory.h"
#include "triggerroutemodelfactory.h"
#include "performfilemodelfactory.h"
#include "scriptbuttonmodelfactory.h"
#include "startupactionmodelutil.h"
#include "restartstartupactionfactory.h"
#include "throttlespreferences.h"
#include "jsonserverpreferences.h"
#include "loconetconsistmanager.h"
#include "catalogtreemodel.h"
#include "throttleframemanager.h"
#include "jmriuserpreferencesmanager.h"
#include "panelmenu.h"
#include "turnoutoperationmanager.h"
#include "filehistory.h"
#include "entryexitpairs.h"
#include "systemconnectionmemomanager.h"
#include "listedtableframe.h"
#include "lnprogrammermanager.h"
#include "signalspeedmap.h"
#include "decoderindexfile.h"
#include "rfid/proxyidtagmanager.h"
#include "proxylightmanager.h"
#include "editormanager.h"
#include "proxymetermanager.h"
#include "ctc/ctcmanager.h"
#include "ctc/ctcexceptionbuffer.h"
#include "appsconfigurationmanager.h"

DefaultInstanceInitializer::DefaultInstanceInitializer()
{
}
/**
 * Provide the usual default implementations for
 * the InstanceManager.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * @author			Bob Jacobsen Copyright (C) 2001, 2008
 * @version			$Revision: 22528 $
 * @since           2.9.4
 */
//public class DefaultInstanceInitializer implements jmri.InstanceInitializer {

//public <T> Object getDefault(Class<T> type) {
QObject* DefaultInstanceInitializer::getDefault(QString type) const
{
 InternalSystemConnectionMemo* memo= nullptr;
 if(type =="AudioManager" ||
         type == "ConditionalManager" ||
         type ==  "LogixManager" ||
         type == "MemoryManager" ||
         type == "RouteManager" || type == "DefaultRouteManager" ||
         type == "SignalGroupManager" ||
         type == "SignalHeadManager" ||
         type == "SignalMastLogicManager" ||
         type == "SignalMastManager" ||
         type == "SignalSystemManager")
  memo = (InternalSystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo");
    // In order for getDefault() to create a new object, the manager also
    // needs to be added to the method getInitalizes() below.
 if (type == "AudioManager")
 {
  DefaultAudioManager* dam =  new DefaultAudioManager(memo);
  InstanceManager::store(dam,type);
  return dam;
 }

 if (type == "ClockControl") {
    DefaultClockControl* cc =new DefaultClockControl();
    InstanceManager::store(cc,type);
    return cc;
 }

 if (type == "BlockManager")
 {
  BlockManager* bm = new BlockManager();
  InstanceManager::store(bm,type);
  return bm;
 }

 if (type == "ConditionalManager") {
     DefaultConditionalManager* cm = new DefaultConditionalManager(memo);
     InstanceManager::store(cm, type);
     return cm;
 }

 if (type == "LightManager")
 {
  ProxyLightManager* lm = new ProxyLightManager();
  InstanceManager::store(lm,type);
  return lm;
 }

 if (type == "LogixManager") {
     DefaultLogixManager* lm = new DefaultLogixManager(memo);
     InstanceManager::store(lm, type);
     return lm;
 }

 if (type == "MemoryManager") {
    DefaultMemoryManager* mm = new DefaultMemoryManager(memo);
    InstanceManager::store(mm,type);
    return mm;
 }

 if (type == "MeterManager") {
  ProxyMeterManager* mm = new ProxyMeterManager();
  InstanceManager::store(mm,type);
  return mm;
 }
// if (type == RailComManager.class) {
//             return new DefaultRailComManager();
//         }

 if (type == "ReporterManager")
 {
  ProxyReporterManager* rm = new ProxyReporterManager();
  InstanceManager::store(rm,type);
  return rm;
 }

 if (type == "RouteManager") {
  return new DefaultRouteManager(memo);
 }

 if (type == "SensorManager")
 {
  //return new ProxySensorManager();
  ProxySensorManager* psm = new ProxySensorManager();
  InstanceManager::store(psm, type);
  return psm;
 }

 if (type == "SignalGroupManager")
 {
  // ensure signal mast manager exists first
  InstanceManager::getDefault("SignalMastManager");
  DefaultSignalGroupManager* sgm = new DefaultSignalGroupManager(memo);
  InstanceManager::store(sgm, type);
  return sgm;
 }

 if (type == "SignalHeadManager")
 {
   AbstractSignalHeadManager* o =  new AbstractSignalHeadManager(memo);
//   InstanceManager::store(o, type);
   return o;
 }

 if (type == "SignalMastLogicManager")
 {
  DefaultSignalMastLogicManager* smlm = new DefaultSignalMastLogicManager(memo);
  InstanceManager::store(smlm, type);
  return smlm;
 }

 if (type == "EditorManager")
 {
  EditorManager* em = new EditorManager();
  InstanceManager::store(em, type);
  return em;
 }

 if (type == "SignalMastManager")
 {
   // ensure signal head manager exists first
   InstanceManager::getDefault("SignalHeadManager");
   QObject* o =  new DefaultSignalMastManager(memo);
   InstanceManager::store(o, "SignalMastManager");
   return o;
 }

 if (type == "SignalSystemManager") {
     return new DefaultSignalSystemManager(memo);
 }
 if (type == "DecoderIndexFile") {
     return new DecoderIndexFile();
 }

 if (type == "Timebase")
 {
  Timebase* timebase = static_cast<Timebase*>(new SimpleTimebase(/*this*/));
  if (InstanceManager::getNullableDefault("ConfigureManager") != nullptr)
   static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->registerConfig(timebase, Manager::TIMEBASE);
  return timebase;
//        return new SimpleTimebase();
 }

 if (type == "TurnoutManager")
 {
  ProxyTurnoutManager* tm = new ProxyTurnoutManager();
  InstanceManager::store(tm, type);
  return tm;
 }

 if (type == "VSDecoderManager")
 {
  return VSDecoderManager::instance();
 }

 //return super.getDefault(type);

 //***************************** added by ACK ***************
 if (type == "CatalogTreeManager") {
     DefaultCatalogTreeManager* ctm = new DefaultCatalogTreeManager();
     InstanceManager::store(ctm,type);
     return ctm;
 }



 if(type == "JmriJTablePersistenceManager")
 {
  JmriJTablePersistenceManager* jjtpm = new JmriJTablePersistenceManager();
  InstanceManager::store (jjtpm, type);
  InstanceManager::store(jjtpm, "JTablePersistenceManager");
  return jjtpm;
 }

 if (type == "IdTagManager")
 {
  DefaultIdTagManager* tm =new DefaultIdTagManager();
  InstanceManager::store(tm, type);
  return tm;
 }

 if (type == "DefaultIdTagManager")
 {
  DefaultIdTagManager* tm =new DefaultIdTagManager();
  InstanceManager::store(tm, type);
  return tm;
 }

// if (type == "LayoutBlockManager")
// {
//  LayoutBlockManager* bm = new LayoutBlockManager();
//  InstanceManager::store(bm,type);
//  return bm;
// }

 if (type == "OBlockManager")
 {
  OBlockManager* bm = new OBlockManager();
  InstanceManager::store(bm,type);
  return bm;
 }

 if (type == "PortalManager")
 {
  PortalManager* pm = new PortalManager();
  InstanceManager::store(pm,type);
  return pm;
 }
#if 0
 if (type == "ProgrammerManager")
 {
  DeferringProgrammerManager* dpm = new DeferringProgrammerManager();
  InstanceManager::store(dpm,type);
  return dpm;
 }

 if (type == "AddressedProgrammerManager")
 {
  LnProgrammerManager* lnpm = new lnProgrammerManager();
  InstanceManager::store(lnpm,type);
  return lnpm;
 }
#endif

 if (type == "RosterIconFactory") {
     return RosterIconFactory::instance();
 }


 if (type == "PanelMenu") {
  PanelMenu* pm =  new PanelMenu();
  InstanceManager::store(pm, type);
  return pm; }


 if (type == "SectionManager")
 {
  SectionManager* sm = new SectionManager();
  InstanceManager::store(sm, type);
  return sm;
 }

 if(type == "JTablePersistenceManager")
 {
  JmriJTablePersistenceManager* jtpm = new JmriJTablePersistenceManager();
  InstanceManager::store(jtpm, type);
  return jtpm;
 }



 if (type == "TransitManager") {
  TransitManager* tm =new TransitManager();
  InstanceManager::store(tm,type);
  return tm;

 }
 if (type == "EntryExitPairs") {
  EntryExitPairs* eep =new EntryExitPairs();
  InstanceManager::store(eep,type);
  return eep;

 }

 if (type == "SystemConnectionMemoManager") {
  SystemConnectionMemoManager* scmm =new SystemConnectionMemoManager();
  InstanceManager::store(scmm,type);
  return scmm;

 }

// if(type == "ConfigureManager")
// {
//  ConfigXmlManager* cm = new ConfigXmlManager();
//  InstanceManager::store(cm,type);
//  return cm;
// }

 if(type == "ConfigureManager")
 {
  ConfigureManager* cm = new AppsConfigurationManager();
  InstanceManager::store(cm,type);
  return cm;
 }

 if(type == "ShutDownManager")
  return new DefaultShutDownManager();

 if(type == "WarrantManager")
 {
  WarrantManager* wm = new WarrantManager();
  InstanceManager::store(wm,type);
  return wm;
 }

 if(type == "StartupActionModelUtil")
 {
  StartupActionModelUtil* samu = new StartupActionModelUtil();
  InstanceManager::store(samu,type);
  return samu;
 }

 if(type == "StartupActionsManager")
 {
  StartupActionsManager* sam = new StartupActionsManager();
  InstanceManager::store(sam,type);
  return sam;
 }

 if(type == "ConnectionConfigManager")
 {
  ConnectionConfigManager* ccm = new ConnectionConfigManager();
  InstanceManager::store(ccm,type);
  return ccm;
 }

 if(type == "SystemConsolePreferencesManager")
 {
  SystemConsolePreferencesManager* scpm = new SystemConsolePreferencesManager();
  InstanceManager::store(scpm,type);
  return scpm;
 }
 if(type == "ProgrammerConfigManager")
 {
  ProgrammerConfigManager* pcm = new ProgrammerConfigManager();
  InstanceManager::store(pcm,type);
  return pcm;
 }

 if(type == "RosterConfigManager")
 {
  RosterConfigManager* rcm = new RosterConfigManager();
  InstanceManager::store(rcm,type);
  return rcm;
 }

 if(type == "FileLocationsPreferences")
 {
  FileLocationsPreferences* flp = new FileLocationsPreferences();
  InstanceManager::store(flp,type);
  return flp;
 }
 if(type == "FileHistory")
 {
  FileHistory* fh = new FileHistory();
  InstanceManager::store(fh,type);
  return fh;
 }

 if(type == "GuiLafPreferencesManager")
 {
  GuiLafPreferencesManager* glpm = new GuiLafPreferencesManager();
  InstanceManager::store(glpm,type);
  return glpm;
 }

 if(type == "WiThrottlePreferences")
 {
  WiThrottlePreferences* wtp = new WiThrottlePreferences();
  InstanceManager::store(wtp,type);
  return wtp;
 }
 if(type == "ThrottlesPreferences")
 {
  ThrottlesPreferences* wtp = new ThrottlesPreferences();
  InstanceManager::store(wtp,type);
  return wtp;
 }

 if(type == "WebServerPreferences")
 {
  WebServerPreferences* wtp = new WebServerPreferences();
  InstanceManager::store(wtp,type);
  return wtp;
 }

// if(type == "InternalSystemConnectionMemo") // is optional getNullableDefault will store it
// {
//  InternalSystemConnectionMemo* itcm = new InternalSystemConnectionMemo();
//  InstanceManager::store(itcm,type);
//  InstanceManager::store(itcm, "SystemConnectionMemo");
//  return itcm;
// }

 if(type == "ManagerDefaultSelector")
 {
  ManagerDefaultSelector* mds = new ManagerDefaultSelector();
  InstanceManager::store(mds,type);
  return mds;
 }
 if(type == "PerformActionModelFactory")
 {
  PerformActionModelFactory* pamf = new PerformActionModelFactory();
  InstanceManager::store(pamf,type);
  return pamf;
 }
 if(type == "StartupPauseFactory")
 {
  StartupPauseFactory* supf = new StartupPauseFactory();
  InstanceManager::store(supf,type);
  return supf;
 }
 if(type == "CreateButtonModelFactory")
 {
  CreateButtonModelFactory* supf = new CreateButtonModelFactory();
  InstanceManager::store(supf,type);
  return supf;
 }
 if(type == "TriggerRouteModelFactory")
 {
  TriggerRouteModelFactory* supf = new TriggerRouteModelFactory();
  InstanceManager::store(supf,type);
  return supf;
 }
 if(type == "ScriptButtonModelFactory")
 {
  ScriptButtonModelFactory* supf = new ScriptButtonModelFactory();
  InstanceManager::store(supf,type);
  return supf;
 }

 if(type == "PerformFileModelFactory")
 {
  PerformFileModelFactory* supf = new PerformFileModelFactory();
  InstanceManager::store(supf,type);
  return supf;
 }

 if(type == "RestartStartupActionFactory")
 {
  RestartStartupActionFactory* rsaf = new RestartStartupActionFactory();
  InstanceManager::store(rsaf,type);
  return rsaf;
 }

 if(type == "JsonServerPreferences")
 {
  JsonServerPreferences* jsp = new JsonServerPreferences();
  InstanceManager::store(jsp,type);
  return jsp;
 }

 if (type == "CatalogTreeModel") {
     CatalogTreeModel* ctm = new CatalogTreeModel();
     InstanceManager::store(ctm, type);
     return ctm;
 }

 if (type == "ThrottleFrameManager") {
     ThrottleFrameManager* tfm = new ThrottleFrameManager();
     InstanceManager::store(tfm, type);
     return tfm;
 }

 if (type == "UserPreferencesManager") {
     JmriUserPreferencesManager* jupm = new JmriUserPreferencesManager();
     InstanceManager::store(jupm, type);
     jupm->initialize();  // called instead of Java InstanceManagerAutoInitialize
     return jupm;
 }

 if(type == "TurnoutOperationManager")
 {
  TurnoutOperationManager* tom = new TurnoutOperationManager();
  InstanceManager::store(tom,type);
  return tom;
 }

 if(type == "ProxyIdTagManager")
 {
  ProxyIdTagManager* pitm = new ProxyIdTagManager();
  InstanceManager::store(pitm,type);
  return pitm;
 }

// if(type == "ConsistManager")
// {
//  LocoNetConsistManager* lncm = new LocoNetConsistManager();
//  InstanceManager::store(lncm,type);
//  return pitm;
// }
 if (type == "CtcManager")
 {
  CtcManager* m = new CtcManager();
  InstanceManager::store(m, type);
  return m;
 }

 if (type == "CTCExceptionBuffer")
 {
  CTCExceptionBuffer* m = new CTCExceptionBuffer();
  InstanceManager::store(m, type);
  return m;
 }

 if (type == "DefaultRouteManager")
 {
  DefaultRouteManager* m = new DefaultRouteManager(memo);
  return m;
 }

 // this is an error!
 //throw new IllegalArgumentException("Cannot create object of type "+type);
 log->warn("DefaultInstanceInitializer: Cannot create object of type " + type);
 return nullptr;
}

/*static*/ Logger* DefaultInstanceInitializer::log = LoggerFactory::getLogger("DefaultInstanceInitializer");
