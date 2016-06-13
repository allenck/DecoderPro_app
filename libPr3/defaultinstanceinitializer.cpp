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
//#include "defaultaudiomanager.h"
#include "vsdecodermanager.h"
#include "logger.h"

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
 if(intype == "CatalogTreeManager")
  type = "DefaultCatalogTreeManager";
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

// if (type == "AudioManager")
// {
//  return DefaultAudioManager::instance();
// }
// if (type == "BlockManager")
// {
//  return new BlockManager();
// }

// if (type == "CatalogTreeManager") {
//     return new DefaultCatalogTreeManager();
// }

 if (type == "ClockControl") {
     return new DefaultClockControl();
 }

 if (type == "ConditionalManager") {
     return new DefaultConditionalManager();
 }

 if (type == "IdTagManager") {
     return new DefaultIdTagManager();
 }

 if (type == "LightManager")
 {
  return new ProxyLightManager();
 }

 if (type == "LogixManager") {
     return new DefaultLogixManager();
 }

 if (type == "MemoryManager") {
     return new DefaultMemoryManager();
 }

 if (type == "ProgrammerManager")
 {
  return new DeferringProgrammerManager();
 }

 if (type == "ReporterManager")
 {
  return new ProxyReporterManager();
 }

 if (type == "RosterIconFactory") {
     return RosterIconFactory::instance();
 }

 if (type == "RouteManager") {
     return new DefaultRouteManager();
 }

 if (type == "SensorManager")
 {
  return new ProxySensorManager();
 }

// if (type == "SectionManager") {
//     return new SectionManager();
// }

 if (type == "SignalGroupManager") {
     // ensure signal mast manager exists first
     InstanceManager::signalMastManagerInstance();
     return new DefaultSignalGroupManager();
 }

 if (type == "SignalHeadManager") {
        return new AbstractSignalHeadManager();
 }

 if (type == "SignalMastLogicManager")
 {
  return new DefaultSignalMastLogicManager();
 }

 if (type == "SignalMastManager") {
        // ensure signal head manager exists first
        InstanceManager::signalHeadManagerInstance();
        return new DefaultSignalMastManager();
 }

 if (type == "SignalSystemManager") {
     return new DefaultSignalSystemManager();
 }

 if (type == "Timebase")
 {
  Timebase* timebase = (Timebase*)new SimpleTimebase(/*this*/);
  if (InstanceManager::configureManagerInstance() != NULL)
   ((ConfigXmlManager*)InstanceManager::configureManagerInstance())->registerConfig(timebase, Manager::TIMEBASE);
  return timebase;
//        return new SimpleTimebase();
 }

// if (type == "TransitManager") {
//     return new TransitManager();
// }

 if (type == "TurnoutManager")
 {
  return new ProxyTurnoutManager();
 }

 if (type == "VSDecoderManager")
 {
  return (QObject*)VSDecoderManager::instance();
 }

 // this is an error!
 throw new IllegalArgumentException("Cannot create object of type "+type);
 return NULL;
}

