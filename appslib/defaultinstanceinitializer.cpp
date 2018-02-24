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
//#include "defaultcatalogtreemanager.h"
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
#include "layoutblockmanager.h"
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

DefaultInstanceInitializer::DefaultInstanceInitializer()
{
 log = new Logger("DefaultInstanceInitializer");
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
QObject* DefaultInstanceInitializer::getDefault(QString intype) const
{
 QString type = intype;
// if(intype == "CatalogTreeManager")
//  type = "DefaultCatalogTreeManager";
#if 0
 int iType = QMetaType::type(type.toLocal8Bit());
 void* o;
 if(iType > 0)
 {
  #if QT_VERSION < 0x050000
   o = QMetaType::construct(iType);
  #else
   o = QMetaType::create(iType);
  #endif
   return (QObject*)o;
 }
 log->warn("Not able to create class "+ type);
#endif
 if (type == "AudioManager")
 {
  return DefaultAudioManager::instance();
 }
 if (type == "BlockManager")
 {
  BlockManager* bm = new BlockManager();
  InstanceManager::store(bm,type);
  return bm;
 }

 if (type == "CatalogTreeManager") {
     DefaultCatalogTreeManager* ctm = new DefaultCatalogTreeManager();
     InstanceManager::store(ctm,type);
     return ctm;
 }

 if (type == "ClockControl") {
    DefaultClockControl* cc =new DefaultClockControl();
    InstanceManager::store(cc,type);
    return cc;
 }

 if (type == "ConditionalManager") {
     DefaultConditionalManager* cm = new DefaultConditionalManager();
     InstanceManager::store(cm, type);
     return cm;
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

 if (type == "LayoutBlockManager")
 {
  LayoutBlockManager* bm = new LayoutBlockManager();
  InstanceManager::store(bm,type);
  return bm;
 }

 if (type == "LightManager")
 {
  ProxyLightManager* lm = new ProxyLightManager();
  InstanceManager::store(lm,type);
  return lm;

 }

 if (type == "LogixManager") {
     DefaultLogixManager* lm = new DefaultLogixManager();
     InstanceManager::store(lm, type);
     return lm;
 }

 if (type == "MemoryManager") {
     return new DefaultMemoryManager();
 }

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

 if (type == "ProgrammerManager")
 {
  return new DeferringProgrammerManager();
 }

 if (type == "ReporterManager")
 {
  ProxyReporterManager* rm = new ProxyReporterManager();
  InstanceManager::store(rm,type);
  return rm;
 }

 if (type == "RosterIconFactory") {
     return RosterIconFactory::instance();
 }

 if (type == "RouteManager") {
     return new DefaultRouteManager();
 }

 if (type == "SensorManager")
 {
  //return new ProxySensorManager();
  ProxySensorManager* psm = new ProxySensorManager();
  InstanceManager::store(psm, type);
  return psm;
 }

 if (type == "SectionManager")
 {
  SectionManager* sm = new SectionManager();
  InstanceManager::store(sm, type);
  return sm;
 }

 if (type == "SignalGroupManager")
 {
  // ensure signal mast manager exists first
  InstanceManager::getDefault("SignalMastManager");
  DefaultSignalGroupManager* sgm = new DefaultSignalGroupManager();
  InstanceManager::store(sgm, type);
  return sgm;
 }

 if (type == "SignalHeadManager")
 {
   AbstractSignalHeadManager* o =  new AbstractSignalHeadManager();
   InstanceManager::store(o, type);
   return o;
 }

 if (type == "SignalMastLogicManager")
 {
  DefaultSignalMastLogicManager* smlm = new DefaultSignalMastLogicManager();
  InstanceManager::store(smlm, type);
  return smlm;
 }

 if(type == "JTablePersistenceManager")
 {
  JmriJTablePersistenceManager* jtpm = new JmriJTablePersistenceManager();
  InstanceManager::store(jtpm, type);
  return jtpm;
 }

 if (type == "SignalMastManager")
 {
   // ensure signal head manager exists first
   InstanceManager::getDefault("SignalHeadManager");
   QObject* o =  new DefaultSignalMastManager();
   InstanceManager::store(o, "SignalMastManager");
   return o;
 }

 if (type == "SignalSystemManager") {
     return new DefaultSignalSystemManager();
 }

 if (type == "Timebase")
 {
  Timebase* timebase = (Timebase*)new SimpleTimebase(/*this*/);
  if (InstanceManager::getNullableDefault("ConfigureManager") != NULL)
   ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerConfig(timebase, Manager::TIMEBASE);
  return timebase;
//        return new SimpleTimebase();
 }

 if (type == "TransitManager") {
  TransitManager* tm =new TransitManager();
  InstanceManager::store(tm,type);
  return tm;

 }

 if (type == "TurnoutManager")
 {
  ProxyTurnoutManager* tm = new ProxyTurnoutManager();
  InstanceManager::store(tm, type);
 }

 if (type == "VSDecoderManager")
 {
  return (QObject*)VSDecoderManager::instance();
 }

 if(type == "ConfigureManager")
 {
  JmriConfigurationManager* cm = new JmriConfigurationManager();
  InstanceManager::store(cm,type);
  return cm;
 }

 if(type == "JmriConfigurationManager")
 {
  JmriConfigurationManager* cm = new JmriConfigurationManager();
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
 if(type == "InternalSystemConnectionMemo")
 {
  InternalSystemConnectionMemo* itcm = new InternalSystemConnectionMemo();
  InstanceManager::store(itcm,type);
  return itcm;
 }
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
// if(type == "StartupActionModelUtil")
// {
//  StartupActionModelUtil* supf = new StartupActionModelUtil();
//  InstanceManager::store(supf,type);
//  return supf;
// }
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

// if(type == "GlobalProgrammerManager")
// {
//  DefaultProgrammerManager* dpm = new DefaultProgrammerManager();
//  InstanceManager::store(dpm,type);
//  return dpm;
// }

 // this is an error!
 //throw new IllegalArgumentException("Cannot create object of type "+type);
 log->error("DefaultInstanceInitializer: Cannot create object of type " + type);
 return NULL;
}

