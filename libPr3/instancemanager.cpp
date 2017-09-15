#include "instancemanager.h"
#include "defaultmemorymanager.h"
#include "memorymanager.h"
#include "lnsensormanager.h"
#include "defaultidtagmanager.h"
#include "rfidsensormanager.h"
#include "rfidreportermanager.h"
#include "defaultroutemanager.h"
#include "lightmanager.h"
#include "../libPr3/Signal/signalheadmanager.h"
#include "../libPr3/Signal/signalmastmanager.h"
#include "../libPr3/Signal/signalsystemmanager.h"
#include "../libPr3/Signal/signalgroupmanager.h"
#include "../libPr3/Signal/signalmastlogicmanager.h"
#include "../LayoutEditor/layoutblockmanager.h"
#include "../libPr3/Signal/defaultsignalmastmanager.h"
//#include "defaultconsistmanager.h"
#include "../libPr3/Signal/defaultsignalmastlogicmanager.h"
#include "defaultusermessagepreferences.h"
#include "catalogtreemanager.h"
#include "defaultconditionalmanager.h"
#include "../LayoutEditor/transitmanager.h"
#include "../libPr3/Signal/defaultsignalsystemmanager.h"
#include "defaultlogixmanager.h"
#include "oblockmanager.h"
#include "warrantmanager.h"
#include "entryexitpairs.h"
#include "defaultinstanceinitializer.h"
#include "warranttableaction.h"
#include "abstractsignalheadmanager.h"
#include "defaultsignalgroupmanager.h"
#include "throttlespreferences.h"
//#include "loconetsystemconnectionmemo.h"
#include "configxmlmanager.h"
#include "defaultprogrammermanager.h"
#include "lnprogrammermanager.h"
#include "tabbedpreferences.h"
#include "nmraconsistmanager.h"
#include "createbuttonmodel.h"
#include "defaultshutdownmanager.h"
#include "defaultaudiomanager.h"
#include "filehistory.h"
#include "lnpowermanager.h"
#include "metatypes.h"

QHash<QString,QObjectList*>* InstanceManager::managerLists = new QHash<QString,QObjectList*>();
//Logger InstanceManager::log;
SensorManager* InstanceManager::sensorManager=NULL;
ConfigureManager* InstanceManager::configureManager =NULL;
//SensorManager* InstanceManager::sensorManagerInstance();
//TurnoutManager* InstanceManager::turnoutManagerInstance();
InstanceManager* InstanceManager::root=NULL;
QVector<PropertyChangeListener*> InstanceManager::listeners;
//#ifdef BLOCKS_AND_SECTIONS
InstanceInitializer* InstanceManager::initializer = (InstanceInitializer*)new DefaultInstanceInitializer();
//#endif
QMutex InstanceManager::mutex;// = QMutex();
//Logger InstanceManager::log = Logger("InstanceManager");


InstanceManager::InstanceManager(QObject *parent) :
    QObject(parent)
{
 log = new Logger("InstanceManager");
 setObjectName("InstanceManager");
 root = this;
 init();
}
/**
 * Provides methods for locating various interface implementations.
 * These form the base for locating JMRI objects, including the key managers.
 *<p>
 * The structural goal is to have the jmri package not depend on the
 * lower jmri.jmrit and jmri.jmrix packages, with the implementations
 * still available at run-time through the InstanceManager.
 *<p>
 * To retrieve the default object of a specific type, do
 * {@link    InstanceManager#getDefault}
 * where the argument is e.g. "SensorManager.class".
 * In other words, you ask for the default object of a particular type.
 *<p>
 * Multiple items can be held, and are retrieved as a list with
 * {@link    InstanceManager#getList}.
 *<p>
 * If a specific item is needed, e.g. one that has been constructed via
 * a complex process during startup, it should be installed with
 * {@link     InstanceManager#store}.
 * If it's OK for the InstanceManager to create an object on first
 * request, have that object's class implement the
 * {@link     InstanceManagerAutoDefault}
 * flag interface. The InstanceManager will then construct a default
 * object via the no-argument constructor when one is first needed.
 *<p>
 * For initialization of more complex objects, see the
 * {@link InstanceInitializer} mechanism and it's default implementation
 * in {@link jmri.managers.DefaultInstanceInitializer}.
 *
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
 * @author			Bob Jacobsen Copyright (C) 2001, 2008, 2013
 * @author          Matthew Harris copyright (c) 2009
 * @version			$Revision: 22528 $
 */
//public class InstanceManager {


/**
 * Store an object of a particular type for later
 * retrieval via {@link #getDefault} or {@link #getList}.
 * @param item The object of type T to be stored
 * @param type The class Object for the item's type.  This will be used
 *               as the key to retrieve the object later.
 */
void InstanceManager::store(QObject* item, QString type)
{
 QObjectList* l = managerLists->value(type);
 if (l==NULL)
 {
  l = new QObjectList();
  managerLists->insert(type, l);
  }
 l->append(item);
}

/**
 * Retrieve a list of all objects of type T that were
 * registered with {@link #store}.
 * @param type The class Object for the items' type.
 */
QObjectList* InstanceManager::getList(QString type)
{
 if (managerLists!=NULL)
 {
  QObjectList* objectList =  managerLists->value(type);
  if(objectList != NULL)
   return objectList;
 }
 return new QObjectList();;
}

/**
 * Deregister all objects of a particular type.
 * @param type The class Object for the items to be removed.
 */
void InstanceManager::reset(QString type)
{
 if (managerLists == NULL) return;
    //managerLists.put(type, NULL);
 managerLists->remove(type);
}

/**
 * Remove an object of a particular type
 * that had earlier been registered with {@link #store}.
 * @param item The object of type T to be deregistered
 * @param type The class Object for the item's type.
 */
void InstanceManager::deregister(QObject* item, QString type)
{
 if (managerLists == NULL) return;
 QObjectList* l = managerLists->value(type);
 if(l!=NULL)
  l->removeOne(item);
}

/**
 * Retrieve the last object of type T that was
 * registered with {@link #store}.
 * <p>
 * Someday, we may provide another way to set the default
 * but for now it's the last one stored, see the
 * {@link #setDefault} method.
 */
//@SuppressWarnings("unchecked")   // checked by construction
QObject* InstanceManager::getDefault(QString type)
{
 Logger* log = new Logger("InstanceManager");
 if (managerLists == NULL) return NULL;
 if(!Metatypes::done)
  new Metatypes();
 QObjectList* l = managerLists->value(type);
 if (l == NULL || l->size()<1)
 {
//        // see if need to autocreate
//        if (InstanceManagerAutoDefault.class.isAssignableFrom(type)) {
//            // yes, make sure list is present before creating object
  if (l==NULL)
  {
//      l = new ArrayList<Object>();
   l= new QObjectList();
   managerLists->insert(type, l);
  }
  int iType = QMetaType::type(type.toLocal8Bit());
  void* o;
  if(iType > 0)
  {
#if QT_VERSION < 0x050000
   o = QMetaType::construct(iType);
#else
   o = QMetaType::create(iType);
#endif
   l->append((QObject*)o);
   return (QObject*)o;
  }
  log->warn("cannot create class of type " + type);
  if(type == "NamedBeanHandleManager")
  {
   l->append(new NamedBeanHandleManager());
   return (NamedBeanHandleManager*)l->at(l->size()-1);
  }
  if(type == "BlockManager")
  {
   l->append(new BlockManager());
   return (BlockManager*)l->at(l->size()-1);
  }
  if(type == "IdTagManager")
  {
   l->append(new DefaultIdTagManager());
   return (DefaultIdTagManager*)l->at(l->size()-1);
  }
  if(type == "RfidSensorManager")
  {
   l->append(new RfidSensorManager());
   return (RfidSensorManager*)l->at(l->size()-1);
  }
  if(type == "RfidReporterManager")
  {
   l->append(new RfidReporterManager("R"));
   return (RfidReporterManager*)l->at(l->size()-1);
  }
  if(type == "RouteManager")
  {
   l->append(new DefaultRouteManager());
   return (RouteManager*)l->at(l->size()-1);
  }
  if(type == "SignalHeadManager")
  {
   l->append(new AbstractSignalHeadManager());
   return (SignalHeadManager*)l->at(l->size()-1);
  }
  if(type == "SignalMastManager")
  {
   l->append(new DefaultSignalMastManager());
   return (SignalMastManager*)l->at(l->size()-1);
  }
  if(type == "SignalSystemManager")
  {
   l->append(new DefaultSignalSystemManager());
   return (SignalSystemManager*)l->at(l->size()-1);
  }
  if(type == "ConsistManager")
  {
   l->append(new DefaultSignalSystemManager());
   return (ConsistManager*)l->at(l->size()-1);
  }
  if(type == "SignalMastLogicManager")
  {
   l->append(new DefaultSignalMastLogicManager());
   return (SignalMastLogicManager*)l->at(l->size()-1);
  }
  if(type == "LayoutBlockManager")
  {
   l->append(new LayoutBlockManager());
   return (LayoutBlockManager*)l->at(l->size()-1);
  }
  if(type == "UserPreferencesManager")
  {
//      //l->append(DefaultUserMessagePreferences::getInstance());
//         l->append(new DefaultUserMessagePreferences());
//      return (DefaultUserMessagePreferences*)l->at(l->size()-1);
   for(int i=0; i< l->count(); i++)
   {
    if(qobject_cast<DefaultUserMessagePreferences*>(l->at(i)) != NULL)   return (DefaultUserMessagePreferences*)l->at(i);
   }
   return NULL;
  }
  if(type == "OBlockManager")
  {
   l->append(new OBlockManager());
   return (OBlockManager*)l->at(l->size()-1);
  }
  if(type == "WarrantManager")
  {
   l->append(new WarrantManager());
   return (WarrantManager*)l->at(l->size()-1);
  }
  if(type == "WarrantTableAction")
  {
   l->append(new WarrantTableAction());
   return (WarrantTableAction*)l->at(l->size()-1);
  }
  if(type == "EntryExitPairs")
  {
   l->append(new EntryExitPairs());
   return (EntryExitPairs*)l->at(l->size()-1);
  }
  if(type == "SignalGroupManager")
  {
   l->append(new DefaultSignalGroupManager());
   return (DefaultSignalGroupManager*)l->at(l->size()-1);
  }
  if(type == "SectionManager")
  {
   l->append(new SectionManager());
   return (SectionManager*)l->at(l->size()-1);
  }
  if(type == "ThrottlesPreferences")
  {
   l->append(new ThrottlesPreferences());
   return (ThrottlesPreferences*)l->at(l->size()-1);
  }
//  if(type == "SystemConnectionMemo")
//  {
//   l->append(new SystemConnectionMemo(/*"I", "Internal"*/));
//   return (SystemConnectionMemo*)l->at(l->size()-1);
//  }
  if(type == "ConfigureManager")
  {
   l->append(new ConfigXmlManager());
   return (ConfigXmlManager*)l->at(l->size()-1);
  }
  if(type == "ProgrammerManager")
  {
   l->append(new DefaultProgrammerManager());
   return (DefaultProgrammerManager*)l->at(l->size()-1);
  }
  if(type == "TabbedPreferences")
  {
   l->append(new TabbedPreferences());
   return (TabbedPreferences*)l->at(l->size()-1);
  }
  if(type == "ShutDownManager")
  {
   l->append(new DefaultShutDownManager());
   return (DefaultShutDownManager*)l->at(l->size()-1);
  }
  if(type == "AudioManager")
  {
   l->append(new DefaultAudioManager());
   return (AudioManager*)l->at(l->size()-1);
  }
  if(type == "FileHistory")
  {
   l->append(new FileHistory());
   return (FileHistory*)l->at(l->size()-1);
  }
//  if(type == "PowerManager")
//  {
//   l->append(new LnPowerManager());
//   return (PowerManager*)l->at(l->size()-1);
//  }
  if(type == "CommandStation") // TODO:
      return NULL;
  log->error( QString("Manager '%1' not found!").arg(type));
//     Q_ASSERT(false);
     //throw new Exception();
//            try {
//                l.add(type.getConstructor((Class[])NULL).newInstance((Object[])NULL));
//            } catch (Exception e) {
//                log->error("Exception creating default object", e); // unexpected
//                return NULL;
//            }
//            return (T)l.get(l.size()-1);
//        } else {
            return NULL;
//        }
 }
    //return (T)l.get(l.size()-1);
 if(!l->isEmpty())
  return l->last();
 return NULL;
}
/**
 * Retrieve the last object of type T that was registered with
 * {@link #store(java.lang.Object, java.lang.Class) }.
 * <p>
 * Unless specifically set, the default is the last object stored, see the
 * {@link #setDefault(java.lang.Class, java.lang.Object) } method.
 * <p>
 * In some cases, InstanceManager can create the object the first time it's
 * requested. For more on that, see the class comment.
 * <p>
 * In most cases, system configuration assures the existence of a default
 * object, but this method also handles the case where one doesn't exist.
 * Use {@link #getDefault(java.lang.Class)} when the object is guaranteed to
 * exist.
 *
 * @param <T>  The type of the class
 * @param type The class Object for the item's type.
 * @return The default object for type.
 * @see #getOptionalDefault(java.lang.Class)
 */
//@CheckForNull
//static /*public*/ <T> T getNullableDefault(@Nonnull Class<T> type) {
/*static*/ /*public*/ QObject* InstanceManager::getNullableDefault(QString type)
{
 Logger* log = new Logger("(nstanceManager");
    //log.trace("getOptionalDefault of type {}", type.getName());
    //ArrayList<T> l = (ArrayList<T>) getList(type);
 QObjectList* l = getList(type);
 if (l->isEmpty())
 {
  // see if can autocreate
  log->debug(tr("    attempt auto-create of %1").arg(type/*.getName()*/));
#if 0
        if (InstanceManagerAutoDefault.class.isAssignableFrom(type)) {
            try {
                l.add(type.getConstructor((Class[]) null).newInstance((Object[]) null));
                log.debug("      auto-created default of {}", type.getName());
            } catch (NoSuchMethodException | InstantiationException | IllegalAccessException | InvocationTargetException e) {
                log.error("Exception creating auto-default object", e); // unexpected
                return null;
            }
            return l.get(l.size() - 1);
        }
#endif
        // see if initializer can handle
        log->debug(tr("    attempt initializer create of %1").arg( type/*.getName()*/));
        //@SuppressWarnings("unchecked")
        QObject* obj = initializer->getDefault(type);
        if (obj != NULL) {
            log->debug(tr("      initializer created default of %1").arg(type/*.getName()*/));
            l->append(obj);
            return l->at(l->size() - 1);
        }

        // don't have, can't make
        return NULL;
    }
    return l->at(l->size() - 1);
}

/**
 * Set an object of type T as the default for that type.
 *<p>
 * Also registers (stores) the object if not already present.
 *<p>
 * Now, we do that moving the item to the back of the list;
 * see the {@link #getDefault} method
 */
void InstanceManager::setDefault(QString type, QObject* val)
{
    QObjectList* l = getList(type);
    if (l == NULL || (l->size()<1) ) {
        store(val, type);
        l = getList(type);
    }
    int i = l->indexOf(val);
    l->removeAt(i);
    l->append(val);
}

/**
 * Dump generic content of InstanceManager
 * by type.
 */
QString InstanceManager::contentsToString()
{
    QString retval;
    QHashIterator<QString,QObjectList*> i(*managerLists);
//    for (Class<?> c : managerLists.keySet()) {
    while(i.hasNext())
    {
     i.next();
#if 1
     QString  c = i.key();
     retval.append("List of");
     retval.append(c);
     retval.append(" with ");
     //retval.append(Integer.toString(getList(c).size()));
     retval.append(QString("%1").arg(getList(c)->size()));
     retval.append(" objects\n");
     QList<QObject*>* list = getList(c);
     foreach (QObject* o , *list)
     {
      retval.append("    ");
//      retval.append(o->objectName());
      if(o != NULL)
       retval.append(o->metaObject()->className());
      retval.append("\n");
     }
#endif
    }
    return retval;
}

PowerManager* InstanceManager::powerManagerInstance()
{
 return (PowerManager*)getDefault("PowerManager");
}

void InstanceManager::setPowerManager(PowerManager* p)
{
    //store(p, p->metaObject()->className());
    store(p,"PowerManager");
}

ProgrammerManager* InstanceManager::programmerManagerInstance()
{
 return (ProgrammerManager*)getDefault("ProgrammerManager");
}

void InstanceManager::setProgrammerManager(ProgrammerManager* p) {
    if(p->isAddressedModePossible() )
        store(p, "AddressedProgrammerManager");
    if(p->isGlobalProgrammerAvailable() )
        store(p, "GlobalProgrammerManager");

//  Now that we have a programmer manager, install the default
//  Consist manager if Ops mode is possible, and there isn't a
//  consist manager already.
 //if(programmerManagerInstance()->isAddressedModePossible()
 if(p->isAddressedModePossible()
    && consistManagerInstance() == NULL)
 {
    setConsistManager(new DccConsistManager());
 }
 instance()->notifyPropertyChangeListener("programmermanager", QVariant(), QVariant());
}
SensorManager* InstanceManager::sensorManagerInstance()
{
 return instance()->sensorManager;
}
TurnoutManager* InstanceManager::turnoutManagerInstance()
{
 return instance()->turnoutManager;
}

LightManager* InstanceManager::lightManagerInstance()  { return instance()->lightManager; }

ConfigureManager* InstanceManager::configureManagerInstance()  { return (ConfigureManager* ) getDefault("ConfigureManager"); }

ThrottleManager* InstanceManager::throttleManagerInstance()  {
    return (ThrottleManager*)getDefault(/*ThrottleManager.class*/  "ThrottleManager");
}
#if 1
SignalHeadManager* InstanceManager::signalHeadManagerInstance()  {
    if (instance()->signalHeadManager != NULL) return instance()->signalHeadManager;
    // As a convenience, we create a default object if none was provided explicitly.
    // This must be replaced when we start registering specific implementations
    //instance()->signalHeadManager = (SignalHeadManager*)initializer->getDefault(/*SignalHeadManager.class)*/"SignalHeadManager");
    instance()->signalHeadManager = (SignalHeadManager*)new  AbstractSignalHeadManager();
    return instance()->signalHeadManager;
}
#endif
#if 1
SignalMastManager* InstanceManager::signalMastManagerInstance()
{
 SignalMastManager* m = (SignalMastManager*)getDefault("SignalMastManager");
 if (m == NULL)
 {
  m = (SignalMastManager*)initializer->getDefault("SignalMastManager");
  setSignalMastManager(m);
 }
 return m;
}
void InstanceManager::setSignalMastManager(SignalMastManager* p)
{
    store(p, "SignalMastManager");
}
#endif
#if 1
SignalSystemManager* InstanceManager::signalSystemManagerInstance()
{
 SignalSystemManager* m = (SignalSystemManager*)getDefault("SignalSystemManager");
 if (m == NULL)
 {
  m = (SignalSystemManager*)initializer->getDefault("SignalSystemManager");
  setSignalSystemManager(m);
 }
 return m;
}

void InstanceManager::setSignalSystemManager(SignalSystemManager* p) {
    store(p, "SignalSystemManager");
}

SignalGroupManager* InstanceManager::signalGroupManagerInstance()  {
 SignalGroupManager* m = (SignalGroupManager*)getDefault("DefaultSignalGroupManager");
 if (m == NULL) {
     m = (SignalGroupManager*)initializer->getDefault("SignalGroupManager");
     setSignalGroupManager(m);
 }
 return m;
}

void InstanceManager::setSignalGroupManager(SignalGroupManager* p) {
    store(p, "SignalGroupManager");
}
#endif
BlockManager* InstanceManager::blockManagerInstance()
{
 BlockManager* o = (BlockManager*)getDefault("BlockManager");
 if (o != NULL) return o;
 o = (BlockManager*)initializer->getDefault("BlockManager");
 store(o, "BlockManager");
 return o;
}
#if 0
////    /**
////     * @deprecated Since 3.3.1, use @{link #getDefault} directly.
////     */
////    @Deprecated
////    static public jmri.jmrit.logix.OBlockManager oBlockManagerInstance()  {
////        return getDefault(jmri.jmrit.logix.OBlockManager.class);
////    }

#endif

SectionManager* InstanceManager::sectionManagerInstance()
{
 if (instance()->sectionManager != NULL)
  return instance()->sectionManager;
    instance()->sectionManager = (SectionManager*)((DefaultInstanceInitializer*)initializer)->getDefault("SectionManager");
    return instance()->sectionManager;
}

TransitManager* InstanceManager::transitManagerInstance()  {
    if (instance()->transitManager != NULL) return instance()->transitManager;
    instance()->transitManager = (TransitManager*)((DefaultInstanceInitializer*)initializer)->getDefault("TransitManager");
    return instance()->transitManager;
}

 SignalMastLogicManager* InstanceManager::signalMastLogicManagerInstance()  {
     SignalMastLogicManager* r = (SignalMastLogicManager*)getDefault("SignalMastLogicManager");
    if (r != NULL) return r;
    r = (SignalMastLogicManager*)initializer->getDefault("SignalMastLogicManager");
    store(r, "SignalMastLogicManager");
    return r;
}

RouteManager* InstanceManager::routeManagerInstance()
{
    RouteManager* r = (RouteManager*)getDefault("RouteManager");
    if (r != NULL) return r;
    r = (RouteManager*)initializer->getDefault("RouteManager");
    store(r, "RouteManager");
    return r;
}

////    /**
////     * @deprecated Since 3.3.1, use @{link #getDefault} directly.
////     */
////    @Deprecated
////    static public jmri.jmrit.display.layoutEditor.LayoutBlockManager layoutBlockManagerInstance()  {
////        return getDefault(jmri.jmrit.display.layoutEditor.LayoutBlockManager.class);
////    }

//#ifdef LAYOUTS
 /*static*/ /*public*/ LayoutBlockManager* InstanceManager::layoutBlockManagerInstance()
 {
  return (LayoutBlockManager*)getDefault("LayoutBlockManager");
 }

//#endif

ConditionalManager* InstanceManager::conditionalManagerInstance()  {
    if (instance()->conditionalManager != NULL) return instance()->conditionalManager;
    //instance()->conditionalManager = (ConditionalManager*)initializer->getDefault("ConditionalManager");
    instance()->conditionalManager = (ConditionalManager*)new DefaultConditionalManager();
    return instance()->conditionalManager;
}

LogixManager* InstanceManager::logixManagerInstance()
{
 if (instance()->logixManager != NULL) return instance()->logixManager;
 //instance()->logixManager = (LogixManager*)initializer->getDefault("LogixManager");
 instance()->logixManager = (LogixManager*)new DefaultLogixManager();
 return instance()->logixManager;
}

/**
 * Will eventually be deprecated, use @{link #getDefault} directly.
 */
ShutDownManager* InstanceManager::shutDownManagerInstance()  {
    return (ShutDownManager*)getDefault("ShutDownManager");
}

TabbedPreferences* InstanceManager::tabbedPreferencesInstance()
{
 return (TabbedPreferences*)getDefault("TabbedPreferences");
}

Timebase* InstanceManager::timebaseInstance()
{

 if (instance()->timebase != NULL) return instance()->timebase;
 //instance()->timebase = dynamic_cast<Timebase*>(initializer->getDefault("Timebase"));
 instance()->timebase = (Timebase*)((DefaultInstanceInitializer*)initializer)->getDefault("Timebase");
    return instance()->timebase;
}

ClockControl* InstanceManager::clockControlInstance()
{
 if (instance()->clockControl != NULL)
  return (ClockControl*)instance()->clockControl;
 instance()->clockControl = (ClockControl*)((DefaultInstanceInitializer*)initializer)->getDefault("ClockControl");
  return (ClockControl*)instance()->clockControl;
}
void InstanceManager::addClockControl(ClockControl* cc) {
    instance()->clockControl = cc;
}

ConsistManager* InstanceManager::consistManagerInstance() { return (ConsistManager*) getDefault("ConsistManager");
}
CommandStation* InstanceManager::commandStationInstance()  {
    return (CommandStation*)getDefault("CommandStation");
}

ReporterManager* InstanceManager::reporterManagerInstance()  { return instance()->reporterManager; }

CatalogTreeManager* InstanceManager::catalogTreeManagerInstance()
{
 if (instance()->catalogTreeManager == NULL) instance()->catalogTreeManager = (CatalogTreeManager*)((DefaultInstanceInitializer*)initializer)->getDefault("CatalogTreeManager");
  return instance()->catalogTreeManager;
}

MemoryManager* InstanceManager::memoryManagerInstance()
{
 if (instance()->memoryManager == NULL)
  //instance()->memoryManager = (MemoryManager*)initializer->getDefault("MemoryManager");
     instance()->memoryManager = (MemoryManager*)new DefaultMemoryManager();
 return (MemoryManager*)instance()->memoryManager;
}

AudioManager* InstanceManager::audioManagerInstance()
{
// if (instance()->audioManager == NULL)
//  instance()->audioManager = DefaultAudioManager::instance();
// return instance()->audioManager;
 return (AudioManager*)getDefault("AudioManager");

}
#if 0
RosterIconFactory* InstanceManager::rosterIconFactoryInstance()  {
    if (instance()->rosterIconFactory == NULL) instance()->rosterIconFactory = RosterIconFactory::instance();
    return instance()->rosterIconFactory;
}
#endif
//VSDecoderManager InstanceManager::vsdecoderManagerInstance() {
//if (instance()->vsdecoderManager == NULL) instance()->vsdecoderManager = VSDecoderManager.instance();
//return instance()->vsdecoderManager;
//}

InstanceManager* InstanceManager::instance()
{
 if (root==NULL)
 {
  setRootInstance();
 }
 return root;
}

void InstanceManager::setRootInstance()
{
 if(root!=NULL)
  return;
 root = new InstanceManager();
}

//    public InstanceManager() {
//        init();
//    }

    // This is a separate, protected member so it
    // can be overridden in unit tests
    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",justification="Only used during system initialization")
void InstanceManager::init()
{
 sensorManager = NULL;
 configureManager = NULL;
 timebase = NULL;
 sectionManager = NULL;
 transitManager = NULL;
 turnoutManager = NULL;
 lightManager = NULL;
 catalogTreeManager = NULL;
 audioManager = NULL;
 memoryManager = NULL;
     //rosterIconFactory = NULL;
 clockControl = NULL;
 signalHeadManager = NULL;
 conditionalManager = NULL;
 reporterManager = NULL;
 shutdownManager = NULL;
 logixManager = NULL;
 tabbedPreferencesManager = NULL;
#if 0
 qRegisterMetaType<CreateButtonModel>("CreateButtonModel");
 qRegisterMetaType<DefaultShutDownManager>("DefaultShutDownManager");
#endif
 //    vsdecoderManager = NULL;
//#ifdef BLOCKS_AND_SECTIONS
 initializer = new DefaultInstanceInitializer();
//#endif
 managerLists = new  QHash<QString,QObjectList*>();
 sensorManager = (SensorManager*)new ProxySensorManager();
 turnoutManager = (TurnoutManager*)new ProxyTurnoutManager(this);

 lightManager = (LightManager*)new ProxyLightManager();
 reporterManager = (ReporterManager*)new ProxyReporterManager();
 log->setDebugEnabled(true);
}

void InstanceManager::setSensorManager(SensorManager* p)
{
 instance()->addSensorManager(p);
    //sensorManager =p;
}
void InstanceManager::addSensorManager(SensorManager* p)
{
 //SensorManager* sensorManager = instance()->sensorManager;
// if(qobject_cast<LnSensorManager*>(sensorManager)!=NULL)
//  return;
 //if(qobject_cast<AbstractProxyManager*>(sensorManager)!= NULL)
    ((AbstractProxyManager*)instance()->sensorManager)->addManager(p);
}

void InstanceManager::setTurnoutManager(TurnoutManager* p) {
    instance()->addTurnoutManager(p);
}
void InstanceManager::addTurnoutManager(TurnoutManager* p) {
    ((AbstractProxyManager*)instance()->turnoutManager)->addManager(p);
}

void InstanceManager::setLightManager(LightManager* p) {
    instance()->addLightManager(p);
}

void InstanceManager::addLightManager(LightManager* p) {
    ((AbstractProxyManager*)instance()->lightManager)->addManager(p);
}


void InstanceManager::setConfigureManager(ConfigureManager* p)
{
 instance()->addConfigureManager(p);
}
void InstanceManager::addConfigureManager(ConfigureManager* p)
{
 if (p!=configureManager && configureManager!=NULL && log->isDebugEnabled()) log->debug(QString("ConfigureManager instance is being replaced: %1").arg("?"));
 if (p!=configureManager && configureManager==NULL && log->isDebugEnabled()) log->debug(QString("ConfigureManager instance is being installed: %1").arg("?"));
 configureManager = p;
}

void InstanceManager::setThrottleManager(ThrottleManager* p)
{
    store(p, "ThrottleManager");
    instance()->notifyPropertyChangeListener("throttlemanager", QVariant(), QVariant());
}

void InstanceManager::setSignalHeadManager(SignalHeadManager* p) {
    instance()->addSignalHeadManager(p);
}

void InstanceManager::addSignalHeadManager(SignalHeadManager* p) {
    if (p!=signalHeadManager && signalHeadManager!=NULL && log->isDebugEnabled()) log->debug(QString("SignalHeadManager instance is being replaced: %1").arg(p->getSystemPrefix()));
    if (p!=signalHeadManager && signalHeadManager==NULL && log->isDebugEnabled()) log->debug(QString("SignalHeadManager instance is being installed: %1").arg(p->getSystemPrefix()));
    signalHeadManager = p;
}

//    /**
//     * @deprecated 2.9.5
//     */
//    @Deprecated
//    static public void setRouteManager(RouteManager p) {
//        store(p, RouteManager.class);
//    }

//    /**
//     * @deprecated Since 3.3.1, use @{link #store} directly.
//     */
//    @Deprecated
/*static*/ /*public*/ void InstanceManager::setLayoutBlockManager(LayoutBlockManager* p) {
store(p, "LayoutBlockManager");
}
#if 1
void InstanceManager::setConditionalManager(ConditionalManager* p) {
    instance()->addConditionalManager(p);
}
/*protected*/ void InstanceManager::addConditionalManager(ConditionalManager* p) {
    if (p!=conditionalManager && conditionalManager!=NULL && log->isDebugEnabled()) log->debug(QString("ConditionalManager instance is being replaced%1: ").arg(p->getSystemPrefix()));
    if (p!=conditionalManager && conditionalManager==NULL && log->isDebugEnabled()) log->debug(QString("ConditionalManager instance is being installed: %1").arg(p->getSystemPrefix()));
    conditionalManager = p;
}
#endif
void InstanceManager::setLogixManager(LogixManager* p) {
    instance()->addLogixManager(p);
}
/*protected*/ void InstanceManager::addLogixManager(LogixManager* p)
{
 if (p!=logixManager && logixManager!=NULL && log->isDebugEnabled()) log->debug("LogixManager instance is being replaced: "+p->objectName());
 if (p!=logixManager && logixManager==NULL && log->isDebugEnabled()) log->debug("LogixManager instance is being installed: "+p->objectName());
 logixManager = p;
}
#if 1
/**
 * @deprecated Since 3.7.4, use @{link #store} directly.
 */
//@Deprecated
void InstanceManager::setShutDownManager(ShutDownManager* p) {
    store(p, "ShutDownManager");
    setDefault("ShutDownManager", p);
}
void InstanceManager::addShutdownManager(ShutDownManager* p) {
    if (p!=shutdownManager && shutdownManager!=NULL && log->isDebugEnabled()) log->debug(QString("ShutDownManager instance is being replaced: %1").arg(p->objectName()));
    if (p!=shutdownManager && shutdownManager==NULL && log->isDebugEnabled()) log->debug(QString("ShutDownManager instance is being installed: %1").arg(p->objectName()));
    shutdownManager = p;
}
#endif
void InstanceManager::setTabbedPreferences(TabbedPreferences* p) {
    instance()->addTabbedPreferences(p);
}
void InstanceManager::addTabbedPreferences(TabbedPreferences* p) {
    tabbedPreferencesManager = p;
}


void InstanceManager::setConsistManager(ConsistManager* p) {
    store(p, "ConsistManager");
    instance()->notifyPropertyChangeListener("consistmanager", QVariant(), QVariant());
}

//
// This updates the consist manager, which must be
// either built into instances of calling code or a
// new service, before this can be deprecated.
//
/*static*/ /*public*/ void InstanceManager::setCommandStation(CommandStation* p)
{
 store(p, "CommandStation");

 // since there is a command station available, use
 // the NMRA consist manager instead of the generic consist
 // manager.
 if (consistManagerInstance() == NULL ||
            (consistManagerInstance()->metaObject()->className())=="DccConsistManager")
 {
  setConsistManager(new NmraConsistManager());
 }
}

void InstanceManager::setReporterManager(ReporterManager* p) {
    instance()->addReporterManager(p);
}
void InstanceManager::addReporterManager(ReporterManager* p) {
    ((AbstractProxyManager*)instance()->reporterManager)->addManager(p);
}

void InstanceManager::removePropertyChangeListener(PropertyChangeListener* l)
{
    QMutexLocker locker(&mutex);
    if (listeners.contains(l))
    {
     int i = listeners.indexOf(l);
     listeners.remove(i);
    }
}
/*public*/ /*static*/ /*synchronized*/ void InstanceManager::addPropertyChangeListener(PropertyChangeListener* l) {
 //QMutex mutex;
    QMutexLocker locker(&mutex);
    // add only if not already registered
    if (!listeners.contains(l)) {
        listeners.append(l);
    }
}

/**
 * Trigger the notification of all PropertyChangeListeners
 */
//@SuppressWarnings("unchecked")
void InstanceManager::notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue)
{
 // make a copy of the listener vector to synchronized not needed for transmit
 QVector<PropertyChangeListener*>* v = new QVector<PropertyChangeListener*>(listeners);
//    synchronized(this)
//        {
//            v = (Vector<PropertyChangeListener>) listeners.clone();
//        }
 // forward to all listeners
 int cnt = v->size();
 for (int i=0; i < cnt; i++)
 {
  PropertyChangeListener* client = v->at(i);
  client->propertyChange(new PropertyChangeEvent(this, property, oldValue, newValue));
 }
 emit propertyChange(new PropertyChangeEvent(this, property, oldValue, newValue));
}


////    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(InstanceManager.class.getName());
//}
