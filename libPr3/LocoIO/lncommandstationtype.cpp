#include "lncommandstationtype.h"
#include "lnthrottlemanager.h"
#include "slotmanager.h"

//LnCommandStationType::LnCommandStationType(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Enum to carry command-station specific information
 * for LocoNet implementations.
 *<p>
 * Because you can't inherit and extend enums, this
 * will accumulate information from subtypes.  We
 * use reflection to deal with that.
 *<p>
 * This is (slowly) centralizing all of the command-station-specific
 * dependencies for startup.  It does _not_ handle the connection-specific
 * dependencies for e.g. the connections via networks and Uhlenbrock serial/USB; those are
 * still done via port adapters, special packetizers et al.
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
 * @author			Bob Jacobsen Copyright (C) 2014
 * @version			$Revision: 28126 $
 */

//@net.jcip.annotations.Immutable
#if 0
/*public*/ enum LnCommandStationType {
    //  enum value                 name                         canRead progEndOp   ThrottleManager      SlotManager
    COMMAND_STATION_DCS100      ("DCS100 (Chief)",              true,   false,  "LnThrottleManager",    "SlotManager");
    COMMAND_STATION_DCS200      ("DCS200",                      true,   false,  "LnThrottleManager",    "SlotManager");
    COMMAND_STATION_DCS050      ("DCS50 (Zephyr)",              true,   false,  "LnThrottleManager",    "SlotManager");
    COMMAND_STATION_DCS051      ("DCS51 (Zephyr Xtra)",         true,   false,  "LnThrottleManager",    "SlotManager");
    COMMAND_STATION_DB150       ("DB150 (Empire Builder)",      false,  true,   "LnThrottleManager",    "SlotManager");
    COMMAND_STATION_LBPS        ("LocoBuffer (PS)",             true,   false,  "LnThrottleManager",    "SlotManager");
    COMMAND_STATION_MM          ("Mix-Master",                  false,  true,   "LnThrottleManager",    "SlotManager");
    COMMAND_STATION_IBX_TYPE_1  ("Intellibox-I",                true,   true,   "Ib1ThrottleManager",   "SlotManager"), // NOI18N
    COMMAND_STATION_IBX_TYPE_2  ("Intellibox-II",               true,   true,   "Ib2ThrottleManager",   "UhlenbrockSlotManager"), // NOI18N

    COMMAND_STATION_PR3_ALONE   ("PR3 standalone programmer",   true,   false,  "LnThrottleManager",    "SlotManager");
    COMMAND_STATION_STANDALONE  ("Stand-alone LocoNet",         false,  false,  "LnThrottleManager",    "SlotManager");  // NOI18N
#endif
    // Note that the convention is that the first word (space-separated token) of the name is the
    // name of a configuration file for loconet.cmdstnconfig
QList<LnCommandStationType*> LnCommandStationType::values = QList<LnCommandStationType*>();

LnCommandStationType::LnCommandStationType(QString name, bool canRead, bool progEndOp, bool supportsIdle, bool supportsMultimeter, QString throttleClassName, QString slotManagerClassName, LnCommandStationTypes type, QObject *parent) : QObject(parent)
{
 this->name = name;
 this->canRead = canRead;
 this->progEndOp = progEndOp;
  this->supportsIdle = supportsIdle;
  this->supportsMultiMeter = supportsMultimeter;
 this->throttleClassName = throttleClassName;
 this->slotManagerClassName = slotManagerClassName;
 this->type = type;
 log = new Logger("LnCommandStationType");
}



/*public*/ QString LnCommandStationType::getName() { return name; }

/**
 * Can this command station read back from decoders?
 */
/*public*/ bool LnCommandStationType::getCanRead() { return canRead; }

/*public*/ QString LnCommandStationType::toString() {return name; }

/**
 * Does a programming operation turn track power off?
 */
/*public*/ bool LnCommandStationType::getProgPowersOff() { return progEndOp; }

/*static*/ /*public*/ LnCommandStationType* LnCommandStationType::getByName(QString name)
{
 if(values.isEmpty())
 {
  values.append(new LnCommandStationType("DCS100 (Chief)",              true,   false,  true,  false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS100));
  values.append(new LnCommandStationType("DCS200",                      true,   false,  true,  false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS200));
  values.append(new LnCommandStationType("DCS50 (Zephyr)",              true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS050));
  values.append(new LnCommandStationType("DCS51 (Zephyr Xtra)",         true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS051));
  values.append(new LnCommandStationType("DB150 (Empire Builder)",      false,  true,   true,  false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DB150));
  values.append(new LnCommandStationType("LocoBuffer (PS)",             true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_LBPS));
  values.append(new LnCommandStationType("Mix-Master",                  false,  true,   false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_MM));
  values.append(new LnCommandStationType("Intellibox-I",                true,   true,   false, false, "Ib1ThrottleManager",   "SlotManager", COMMAND_STATION_IBX_TYPE_1)), // NOI18N
  values.append(new LnCommandStationType("Intellibox-II",               true,   true,   false, false, "Ib2ThrottleManager",   "UhlenbrockSlotManager", COMMAND_STATION_IBX_TYPE_2)); // NOI18N
  values.append(new LnCommandStationType("PR2 standalone programmer",   true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_PR2_ALONE)); // NOI18N
  values.append(new LnCommandStationType("PR3 standalone programmer",   true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_PR3_ALONE));
  values.append(new LnCommandStationType("Stand-alone LocoNet",         false,  false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_STANDALONE));  // NOI18N
  values.append(new LnCommandStationType("DCS240 (Advanced Command Station)", true, false, true, true,"LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS240)); // NOI18N
  values.append(new LnCommandStationType("DCS210 (Evolution Command Station)", true, false, true, true,"LnThrottleManager",   "SlotManager", COMMAND_STATION_DCS210)); // NOI18N
 }

 foreach (LnCommandStationType* p, values)
 {
  if (p->name==(name)) return p;
 }
 throw IllegalArgumentException("argument value ["+name+"] not valid");
}

/*static*/ /*public*/ LnCommandStationType* LnCommandStationType::getByType(LnCommandStationTypes type)
{
 if(values.isEmpty())
 {
   values.append(new LnCommandStationType("DCS100 (Chief)",              true,   false,  true,  false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS100));
   values.append(new LnCommandStationType("DCS200",                      true,   false,  true,  false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS200));
   values.append(new LnCommandStationType("DCS50 (Zephyr)",              true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS050));
   values.append(new LnCommandStationType("DCS51 (Zephyr Xtra)",         true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS051));
   values.append(new LnCommandStationType("DB150 (Empire Builder)",      false,  true,   true,  false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_DB150));
   values.append(new LnCommandStationType("LocoBuffer (PS)",             true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_LBPS));
   values.append(new LnCommandStationType("Mix-Master",                  false,  true,   false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_MM));
   values.append(new LnCommandStationType("Intellibox-I",                true,   true,   false, false, "Ib1ThrottleManager",   "SlotManager", COMMAND_STATION_IBX_TYPE_1)), // NOI18N
   values.append(new LnCommandStationType("Intellibox-II",               true,   true,   false, false, "Ib2ThrottleManager",   "UhlenbrockSlotManager", COMMAND_STATION_IBX_TYPE_2)); // NOI18N
   values.append(new LnCommandStationType("PR2 standalone programmer",   true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_PR2_ALONE)); // NOI18N
   values.append(new LnCommandStationType("PR3 standalone programmer",   true,   false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_PR3_ALONE));
   values.append(new LnCommandStationType("Stand-alone LocoNet",         false,  false,  false, false, "LnThrottleManager",    "SlotManager", COMMAND_STATION_STANDALONE));  // NOI18N
   values.append(new LnCommandStationType("DCS240 (Advanced Command Station)", true, false, true, true,"LnThrottleManager",    "SlotManager", COMMAND_STATION_DCS240)); // NOI18N
   values.append(new LnCommandStationType("DCS210 (Evolution Command Station)", true, false, true, true,"LnThrottleManager",   "SlotManager", COMMAND_STATION_DCS210)); // NOI18N
 }
 foreach (LnCommandStationType* p, values)
 {
  if (p->type==(type)) return p;
 }
 throw IllegalArgumentException("argument value ["+QString::number((int)type)+"] not valid");
}
/**
 * Get a new ThrottleManager of the right type for this command station.
 */
 /*public*/ ThrottleManager* LnCommandStationType::getThrottleManager(LocoNetSystemConnectionMemo* memo)
{
//    try {
//        // uses reflection
//        String className = "jmri.jmrix.loconet."+throttleClassName;
//        log->debug("attempting to create {}", className);
//        Class<?> c = Class.forName(className);
//        java.lang.reflect.Constructor<?>[] allConstructors = c.getDeclaredConstructors();
//        for (java.lang.reflect.Constructor ctor : allConstructors) {
//            Class<?>[] pType  = ctor.getParameterTypes();
//            if (pType.length == 1 && pType[0].equals(LocoNetSystemConnectionMemo.class)) {
//                // this is the right ctor
//                return (ThrottleManager)ctor.newInstance(memo);
//            }
//        }

 if(throttleClassName == "LnThrottleManager")
 {
  return new LnThrottleManager(memo);
 }
 log->error(QString("Did not find a throttle ctor for %1").arg( name));
//    } catch (ClassNotFoundException e1) {
//        log->error("Could not find class for throttle manager from type {} in enum element {}", throttleClassName, name);
//    } catch (InstantiationException e2) {
//        log->error("Could not create throttle manager object from type {} in enum element {}", throttleClassName, name, e2);
//    } catch (IllegalAccessException e3) {
//        log->error("Access error creating throttle manager object from type {} in enum element {}", throttleClassName, name, e3);
//    } catch (java.lang.reflect.InvocationTargetException e4) {
//        log->error("Invocation error while creating throttle manager object from type {} in enum element {}", throttleClassName, name, e4);
//    }
  return NULL;
 }

/**
 * Get a new SlotManager of the right type for this command station.
 */
 /*public*/ SlotManager* LnCommandStationType::getSlotManager(LnTrafficController* tc)
{
//    try {
//        // uses reflection
//        String className = "jmri.jmrix.loconet."+slotManagerClassName;
//        log->debug("attempting to create {}", className);
//        Class<?> c = Class.forName(className);
//        java.lang.reflect.Constructor<?>[] allConstructors = c.getDeclaredConstructors();
//        for (java.lang.reflect.Constructor ctor : allConstructors) {
//            Class<?>[] pType  = ctor.getParameterTypes();
//            if (pType.length == 1 && pType[0].equals(LnTrafficController.class)) {
//                // this is the right ctor
//                return (SlotManager)ctor.newInstance(tc);
//            }
//        }
  if(slotManagerClassName == "SlotManager")
   return new SlotManager(tc);
  log->error(QString("Did not find a slotmanager ctor for %1").arg(name));
//    } catch (ClassNotFoundException e1) {
//        log->error("Could not find class for slotmanager from type {} in enum element {}", slotManagerClassName, name);
//    } catch (InstantiationException e2) {
//        log->error("Could not create slotmanager object from type {} in enum element {}", slotManagerClassName, name, e2);
//    } catch (IllegalAccessException e3) {
//        log->error("Access error creating slotmanager object from type {} in enum element {}", slotManagerClassName, name, e3);
//    } catch (java.lang.reflect.InvocationTargetException e4) {
//        log->error("Invocation error while creating slotmanager object from type {} in enum element {}", slotManagerClassName, name, e4);
//    }
  return NULL;
 }
QStringList LnCommandStationType::commandStationNames()
{
  QStringList list;
  foreach(LnCommandStationType* t, values)
  {
   list.append(t->name);
  }
  return list;
 }
 /**
 * Returns command station's support for OPC_IDLE
 *
 * @return true if OPC_IDLE forces broadcast of "stop", else false
 */
/*public*/ bool LnCommandStationType::getImplementsIdle() {
    return supportsIdle;
}

/**
 * Returns whether CS supports a multimedia
 * @return true is MultiMedia support
 */
/*public*/ bool LnCommandStationType::getSupportsMultimeter() {
    return supportsMultiMeter;
}
