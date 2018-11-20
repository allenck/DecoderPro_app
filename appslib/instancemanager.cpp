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
#include "jmriuserpreferencesmanager.h"
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
#include <QGlobalStatic>
#include <QStringList>
#include "loggerfactory.h"
#include "class.h"
#include <QVariant>
#include "vptr.h"
#include "stringutils.h"
#include "printwriter.h"
// classes derived from InstanceInitializer
#include "abstractinstanceinitializer.h"
#include "jsonserverpreferences.h"
#include "defaultcatalogtreemanager.h"
#include "imageindexeditor.h"
#include "decoderindexfile.h"
#include "panelmenu.h"
#include "trackertableaction.h"
#include "enginemodels.h"
#include "namefile.h"
#include "withrottlepreferences.h"
//#include "server.h"
//#include "serverframe.h"
#include "defaultidtagmanager.h"
#include "defaultinstanceinitializer.h"
#include "deferringprogrammermanager.h"
#include "jmriuserpreferencesmanager.h"
//#include "webserverpreferencesinstanceinitializer.h"


class ManagerLists : public QHash<QString,QObjectList*>
{

};
// /*static*/ InstanceInitializer* InstanceManager::initializer = (InstanceInitializer*)new DefaultInstanceInitializer();
Q_GLOBAL_STATIC(DefaultInstanceInitializer, initializer)
//Q_GLOBAL_STATIC(ManagerLists, managerLists)
//Logger InstanceManager::log;
//SensorManager* InstanceManager::sensorManager=nullptr;
//ConfigureManager* InstanceManager::configureManager =nullptr;
//SensorManager* InstanceManager::sensorManagerInstance();
//TurnoutManager* InstanceManager::turnoutManagerInstance();
InstanceManager* InstanceManager::root=nullptr;
QVector<PropertyChangeListener*> InstanceManager::listeners;
QMutex InstanceManager::mutex;// = QMutex();
//Logger InstanceManager::log = Logger("InstanceManager");

/* *************************************************************************** */

/**
 * Default constructor for the InstanceManager.
 */
InstanceManager::InstanceManager(QObject *parent) :
    QObject(parent)
{
 setObjectName("InstanceManager");
 managerLists = QHash<QString,QObjectList>();
 initializers = QMap</*Class<?>*/QString, QObject*>();
#if 0
 // Load all classes that are derived from InstanceInitializer java class
 initializers.insert("AbstractInstanceInializer", new AbstractInstanceInitializer());
 initializers.insert("JsonServerPreferences", new JsonServerPreferences());
 initializers.insert("DefaultCatalogTreeManager", new DefaultCatalogTreeManager());
 initializers.insert("ImageIndexEditor", new ImageIndexEditor());
 initializers.insert("DecoderIndexFile", new DecoderIndexFile());
 initializers.insert("PanelMenu", new PanelMenu());
 initializers.insert("TrackerTableAction", new TrackerTableAction());
 initializers.insert("EngineModels", new Operations::EngineModels());
 initializers.insert("WiThrottlePreferences", new WiThrottlePreferences());
// initializers.insert("Server", new Server());
// initializers.insert("ServerFrame", new ServerFrame());
 initializers.insert("DefaultIdTagManager", new DefaultIdTagManager());
 initializers.insert("DefaultInstanceInitializer", new DefaultInstanceInitializer());
 initializers.insert("DeferringProgrammerManager", new DeferringProgrammerManager());
 initializers.insert("JmriUserPreferencesManager", new JmriUserPreferencesManager());
// initializers.insert("WebServerPreferencesInstanceInitializer", new WebServerPreferencesInstanceInitializer());
#endif
 pcs = new PropertyChangeSupport(this);
 initState = QMap</*Class<?>*/QString, StateHolder*>();
 //root = this;
 //init();
}
#if 1 // TODO:
/**
 * Get a list of all registered objects of type T.
 *
 * @param <T>  type of the class
 * @param type class Object for type T
 * @return a list of registered T instances with the manager or an empty
 *         list
 */
//@SuppressWarnings("unchecked") // the cast here is protected by the structure of the managerLists
//@Nonnull
//template<class T>
/*public*/ /*<T>*/ QObjectList InstanceManager::getInstances(/*@Nonnull Class<T>*/ QString type) {
    if(log->isTraceEnabled())
     log->trace(tr("Get list of type %1").arg(type/*.getName()*/));
    /*synchronized (type)*/ {
        if (managerLists.value(type) == QObjectList()) {
            managerLists.insert(type, QObjectList());
            pcs->fireIndexedPropertyChange(getListPropertyName(type), 0, QVariant(), QVariant());
        }
        return  managerLists.value(type);
    }
}
#endif
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
 * Store an object of a particular type for later retrieval via
 * {@link #getDefault} or {@link #getList}.
 *
 * @param <T>  The type of the class
 * @param item The object of type T to be stored
 * @param type The class Object for the item's type. This will be used as
 *             the key to retrieve the object later.
 */
//template<class T>
/*static*/ /*public*/  void InstanceManager::store(/*@Nonnull*/ QObject* item, /*@Nonnull Class<T> */ QString type) {
    log->debug(tr("Store item of type %1").arg(type));
    if (item == nullptr) {
     QString msg = tr("Should not store null value of type %1").arg(type);
     log->error(msg);
        NullPointerException npe =  NullPointerException(msg);
        throw npe;
    }
    QObjectList l = getList(type);
    l.append(item);
    getDefault()->managerLists.insert(type, l);
    getDefault()->pcs->fireIndexedPropertyChange(getListPropertyName(type), l.indexOf(item), QVariant(), VPtr<QObject>::asQVariant(item));
}

//void InstanceManager::storeBefore( int index, QObject* item, QString type)
//{
// //QHash<QString,QObjectList*>* mgrLists = managerLists;
// //Q_UNUSED(mgrLists);
// log->debug(tr("Store item of type %1").arg(type));
// if (item == nullptr) {
//     NullPointerException npe =  NullPointerException();
//     log->error(tr("Should not store null value of type %1").arg(type));
//     throw npe;
// }
// QObjectList* l =  InstanceManager::instance()->managerLists.value(type);
// if (l==nullptr)
// {
//   l = new QObjectList();
//   InstanceManager::instance()->managerLists.insert(type, l);
// }
// l->insert(index, item);
//}

/**
 * Retrieve a list of all objects of type T that were
 * registered with {@link #store}.
 * @param type The class Object for the items' type.
 */
//template<class T>
/*static*/ QObjectList InstanceManager::getList(QString type)
{
 return getDefault()->getInstances(type);
}

/**
 * Deregister all objects of a particular type.
 * @param type The class Object for the items to be removed.
 */
void InstanceManager::reset(QString type)
{
 getDefault()->clear(type);
}

/**
 * Remove an object of a particular type
 * that had earlier been registered with {@link #store}.
 * @param item The object of type T to be deregistered
 * @param type The class Object for the item's type.
 */
void InstanceManager::deregister(QObject* item, QString type)
{
 if (InstanceManager::instance()->managerLists.isEmpty()) return;
 QObjectList l =InstanceManager::instance()-> managerLists.value(type);
 if(!l.isEmpty())
  l.removeOne(item);
}

/**
 * Remove an object of a particular type that had earlier been registered
 * with {@link #store}. If item was previously registered, this will remove
 * item and fire an indexed property change event for the property matching
 * the output of {@link #getListPropertyName(java.lang.Class)} for type.
 *
 * @param <T>  The type of the class
 * @param item The object of type T to be deregistered
 * @param type The class Object for the item's type
 */
/*public*/ /*<T>*/ void InstanceManager::remove(/*@Nonnull T*/QObject* item, /*@Nonnull Class<T>*/QString type) {
    log->debug(tr("Remove item type %!").arg(type));
   QObjectList l = getList(type);
    int index = l.indexOf(item);
    if (index != -1) { // -1 means items was not in list, and therefor, not registered
        l.removeOne(item);
//        if (item instanceof Disposable) {
//            dispose((Disposable) item);
//        }
    }
    // if removing last item, re-initialize later
    if (l.isEmpty()) {
        setInitializationState(type, InitializationState::NOTSET);
    }
    if (index != -1) { // -1 means items was not in list, and therefor, not registered
        // fire property change last
        pcs->fireIndexedPropertyChange(getListPropertyName(type), index, VPtr<QObject>::asQVariant(item), QVariant());
    }
}
/**
 * Retrieve the last object of type T that was
 * registered with {@link #store}.
 * <p>
 * Someday, we may provide another way to set the default
 * but for now it's the last one stored, see the
 * {@link #setDefault} method.
 */
/*static*/ /*public*/ QObject* InstanceManager::getDefault(/*@Nonnull Class<T>*/ QString type) {
//    log->trace(tr("getDefault of type %1").arg(type));
//    return Objects.requireNonNull(InstanceManager.getNullableDefault(type),
//            "Required nonnull default for " + type.getName() + " does not exist.");
    QObject* o = InstanceManager::getNullableDefault(type);
    if(o == nullptr)
     Logger::error( "Required nonnull default for " + type + " does not exist.");
    else
    {
     if(o->objectName() == "")
      o->setObjectName(o->metaObject()->className());
    }
  return o;
}
#if 0
template<class T>
/*static*/ /*public*/ T InstanceManager::getDefault(T type) {
//    log->trace(tr("getDefault of type %1").arg(type));
//    return Objects.requireNonNull(InstanceManager.getNullableDefault(type),
//            "Required nonnull default for " + type.getName() + " does not exist.");
    QObject* o = InstanceManager::getNullableDefault(type);
    if(o == NULL)
     Logger::error( "Required nonnull default for " + QString(type) + " does not exist.");
    else
     o->setObjectName(type);
  return o;
}
#endif
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
 return getDefault()->getInstance(type);
}

//@CheckForNull
/*public*/ QObject* InstanceManager::getInstance(/*@Nonnull Class<T>*/QString type)
{
 if( log->isTraceEnabled())
  log->trace(tr("getOptionalDefault of type %1").arg(type/*.getName()*/));
 QObjectList l = getList(type);
 if (l.isEmpty())
 {
  // example of tracing where something is being initialized
  // log.error("jmri.implementation.SignalSpeedMap init", new Exception());
  if (traceFileActive)
  {
      traceFilePrint("Start initialization: " + type/*.toString()*/);
      traceFileIndent++;
  }

  // check whether already working on this type
  InitializationState working = getInitializationState(type);
  Exception except = getInitializationException(type);
  setInitializationState(type, InitializationState::STARTED);
  if (working == InitializationState::STARTED)
  {
   log->error(tr("Proceeding to initialize %1 while already in initialization").arg(type),  Exception("Thread \"" + QThread::currentThread()->objectName() + "\""));
   log->error(tr("    Prior initialization:"), except);
   if (traceFileActive) {
       traceFilePrint("*** Already in process ***");
   }
  }
  else if (working == InitializationState::DONE)
  {
   log->error(tr("Proceeding to initialize %1 but initialization is marked as complete").arg(type),  Exception("Thread \"" + QThread::currentThread()->objectName() + "\""));
  }

  // see if can autocreate
  log->debug(tr("    attempt auto-create of %1").arg(type/*.getName()*/));
        //if (InstanceManagerAutoDefault.class.isAssignableFrom(type))
  QObject* obj1;
  try
  {
   obj1 = (QObject*)Class::forName(type);
  }
  catch (ClassNotFoundException ex)
  {
   obj1 = nullptr;
  }
  if(obj1 != nullptr )
  {
   QVariant property= obj1->property("InstanceManagerAutoDefault");
   if(property != QVariant())
   {
   try
   {
    property = obj1->property("InstanceManagerAutoInitialize");
    if(property != QVariant())
    {
     int methodIndex = obj1->metaObject()->indexOfMethod(QMetaObject::normalizedSignature("initialize()"));
     if(methodIndex >= 0)
     {
      //QMetaMethod  method = obj1->metaObject()->method(methodIndex);
      QMetaObject::invokeMethod(obj1, QMetaObject::normalizedSignature("initialize()"), Qt::DirectConnection);
     }
     else throw NoSuchMethodException(tr("no method initialize found for type %1").arg(type));
     log->debug(tr("      auto-created default of %1").arg(type/*.getName()*/));
    }
    l.append((QObject*)obj1);
     store(obj1, type);
     return l.value(l.size() - 1);

 //      try {
           //l.add(type.getConstructor((Class[]) null).newInstance((Object[]) null));
   }
 //      } catch (NoSuchMethodException | InstantiationException | IllegalAccessException | InvocationTargetException e) {
 //          log.error("Exception creating auto-default object", e); // unexpected
 //          return null;
 //      }
    catch (NoSuchMethodException e)
    {
     log->error("Exception creating auto-default object", e); // unexpected
     return nullptr;
    }
   }
  }
  // see if initializer can handle
  log->debug(tr("    attempt initializer create of %1").arg( type/*.getName()*/));
  //@SuppressWarnings("unchecked")
//  if(initializers.contains(type))
//  {
   //QObject* obj = initializers.value(type);//->getDefault(type);//initializer->getDefault(type);
   QObject* obj = initializer->getDefault(type);
   if (obj != nullptr)
   {
    log->debug(tr("      initializer created default of %1").arg(type/*.getName()*/));
    l.append(obj);
    store(obj,type);
    //return l->at(l->size() - 1);
    return obj;
   }
//  }
  // don't have, can't make
  return nullptr;
 }
 return l.at(l.size() - 1);
}

/**
 * Retrieve the last object of type T that was registered with
 * {@link #store(java.lang.Object, java.lang.Class)} wrapped in an
 * {@link java.util.Optional}.
 * <p>
 * Unless specifically set, the default is the last object stored, see the
 * {@link #setDefault(java.lang.Class, java.lang.Object)} method.
 * <p>
 * In some cases, InstanceManager can create the object the first time it's
 * requested. For more on that, see the class comment.
 * <p>
 * In most cases, system configuration assures the existence of a default
 * object, but this method also handles the case where one doesn't exist.
 * Use {@link #getDefault(java.lang.Class)} when the object is guaranteed to
 * exist.
 *
 * @param <T>  the type of the default class
 * @param type the class Object for the default type
 * @return the default wrapped in an Optional or an empty Optional if the
 *         default is null
 * @see #getNullableDefault(java.lang.Class)
 */
//@Nonnull
/*static*/ /*public*/ QObject* InstanceManager::getOptionalDefault(QString type) {
    //return Optional.ofNullable(InstanceManager.getNullableDefault(type));
 return InstanceManager::getNullableDefault(type);
}
/**
 * Set an object of type T as the default for that type.
 *<p>
 * Also registers (stores) the object if not already present.
 *<p>
 * Now, we do that moving the item to the back of the list;
 * see the {@link #getDefault} method
 */
QObject* InstanceManager::setDefault(QString type, QObject* val)
{
    QObjectList l = getList(type);
    if (!l.isEmpty() ) {
        store(val, type);
        l = getList(type);
    }
    int i = l.indexOf(val);
    l.removeAt(i);
    l.append(val);
    return val;
}

/**
 * Check if a default has been set for the given type.
 *
 * @param <T>  The type of the class
 * @param type The class type
 * @return true if an item is available as a default for the given type;
 *         false otherwise
 */
/*static*/ /*public*/  bool InstanceManager::containsDefault(/*@Nonnull*/ QString type) {
    QObjectList l = getList(type);
    return !l.isEmpty();
}

/**
 * Dump generic content of InstanceManager
 * by type.
 */
/*static*/ QString InstanceManager::contentsToString()
{
 QString retval;
 //getDefault()->managerLists.keys().stream().forEachOrdered((c) ->
 foreach(QString c, getDefault()->managerLists.keys())
 {
  retval.append("List of ");
  retval.append(c);
  retval.append(" with ");
  retval.append(QString::number(getList(c).size()));
  retval.append(" objects\n");
  //getList(c).stream().forEachOrdered((o) ->
  foreach (QObject* o, getList(c))
  {
   try
   {
      retval.append("    ");
      retval.append(o->metaObject()->className());
      retval.append("\n");
   }
   catch (std::exception)
   {
    retval.append("    ");
    retval.append("????????");
    retval.append("\n");
   }
  }//);
  } //);
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

SensorManager* InstanceManager::sensorManagerInstance()
{
 return (SensorManager*)getDefault("SensorManager");
}

TurnoutManager* InstanceManager::turnoutManagerInstance()
{
 return (TurnoutManager*)getDefault("TurnoutManager");
}

ThrottleManager* InstanceManager::throttleManagerInstance()  {
    return (ThrottleManager*)getDefault(/*ThrottleManager.class*/  "ThrottleManager");
}

/**
 * Will eventually be deprecated, use @{link #getDefault} directly.
 *
 * @return the default signal head manager. May not be the only instance.
 * @deprecated 4.5.1
 */
//@Deprecated
SignalHeadManager* InstanceManager::signalHeadManagerInstance()
{
//    if (instance()->signalHeadManager != NULL) return instance()->signalHeadManager;
//    // As a convenience, we create a default object if none was provided explicitly.
//    // This must be replaced when we start registering specific implementations
//    //instance()->signalHeadManager = (SignalHeadManager*)initializer->getDefault(/*SignalHeadManager.class)*/"SignalHeadManager");
//    instance()->signalHeadManager = (SignalHeadManager*)new  AbstractSignalHeadManager();
//    return instance()->signalHeadManager;
 return (SignalHeadManager*)getDefault("SignalHeadManager");
}

/**
 * Will eventually be deprecated, use @{link #getDefault} directly.
 *
 * @return the default signal mast manager. May not be the only instance.
 * @deprecated 4.5.1
 */
//@Deprecated
SignalMastManager* InstanceManager::signalMastManagerInstance()
{
 SignalMastManager* m = (SignalMastManager*)getDefault("SignalMastManager");
// if (m == nullptr)
// {
//  m = (SignalMastManager*)initializer->getDefault("SignalMastManager");
//  setSignalMastManager(m);
// }
 return m;
}
void InstanceManager::setSignalMastManager(SignalMastManager* p)
{
    store(p, "SignalMastManager");
}

SignalSystemManager* InstanceManager::signalSystemManagerInstance()
{
 SignalSystemManager* m = (SignalSystemManager*)getDefault("SignalSystemManager");
 if (m == nullptr)
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
 if (m == nullptr) {
     m = (SignalGroupManager*)initializer->getDefault("SignalGroupManager");
     setSignalGroupManager(m);
 }
 return m;
}

void InstanceManager::setSignalGroupManager(SignalGroupManager* p) {
    store(p, "SignalGroupManager");
}

BlockManager* InstanceManager::blockManagerInstance()
{
 BlockManager* o = (BlockManager*)getDefault("BlockManager");
 if (o != nullptr) return o;
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
 return (SectionManager*)getDefault("SectionManager");
}

#if 0
TransitManager* InstanceManager::transitManagerInstance()  {
    if (instance()->transitManager != nullptr) return instance()->transitManager;
    instance()->transitManager = (TransitManager*)((DefaultInstanceInitializer*)initializer)->getDefault("TransitManager");
    return instance()->transitManager;
}
#endif
 SignalMastLogicManager* InstanceManager::signalMastLogicManagerInstance()  {
     SignalMastLogicManager* r = (SignalMastLogicManager*)getDefault("SignalMastLogicManager");
    if (r != nullptr) return r;
    r = (SignalMastLogicManager*)initializer->getDefault("SignalMastLogicManager");
    store(r, "SignalMastLogicManager");
    return r;
}

RouteManager* InstanceManager::routeManagerInstance()
{
    RouteManager* r = (RouteManager*)getDefault("RouteManager");
    if (r != nullptr) return r;
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
#if 0
 /*static*/ /*public*/ LayoutBlockManager* InstanceManager::layoutBlockManagerInstance()
 {
  return (LayoutBlockManager*)getDefault("LayoutBlockManager");
 }

ConditionalManager* InstanceManager::conditionalManagerInstance()  {
    if (instance()->conditionalManager != nullptr) return instance()->conditionalManager;
    //instance()->conditionalManager = (ConditionalManager*)initializer->getDefault("ConditionalManager");
    instance()->conditionalManager = (ConditionalManager*)new DefaultConditionalManager();
    return instance()->conditionalManager;
}

LogixManager* InstanceManager::logixManagerInstance()
{
 if (instance()->logixManager != nullptr) return instance()->logixManager;
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

 if (instance()->timebase != nullptr) return instance()->timebase;
 //instance()->timebase = dynamic_cast<Timebase*>(initializer->getDefault("Timebase"));
 instance()->timebase = (Timebase*)((DefaultInstanceInitializer*)initializer)->getDefault("Timebase");
    return instance()->timebase;
}

ClockControl* InstanceManager::clockControlInstance()
{
 if (instance()->clockControl != nullptr)
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
#endif
ReporterManager* InstanceManager::reporterManagerInstance()  { return (ReporterManager*) getDefault("ReporterManager"); }
#if 0
CatalogTreeManager* InstanceManager::catalogTreeManagerInstance()
{
 if (instance()->catalogTreeManager == nullptr) instance()->catalogTreeManager = (CatalogTreeManager*)((DefaultInstanceInitializer*)initializer)->getDefault("CatalogTreeManager");
  return instance()->catalogTreeManager;
}
#endif
/* ****************************************************************************
 *                   Primary Accessors - Left (for now)
 *
 *          These are so extensively used that we're leaving for later
 *                      Please don't create any more of these
 * ****************************************************************************/
/**
 * May eventually be deprecated, use @{link #getDefault} directly.
 *
 * @return the default light manager. May not be the only instance.
 */
LightManager* InstanceManager::lightManagerInstance()  { return (LightManager*) getDefault("LightManager");}


/**
 * May eventually be deprecated, use @{link #getDefault} directly.
 *
 * @return the default memory manager. May not be the only instance.
 */
MemoryManager* InstanceManager::memoryManagerInstance()
{
 return static_cast<MemoryManager*>(getDefault("MemoryManager"));
}
#if 0
AudioManager* InstanceManager::audioManagerInstance()
{
// if (instance()->audioManager == nullptr)
//  instance()->audioManager = DefaultAudioManager::instance();
// return instance()->audioManager;
 return (AudioManager*)getDefault("AudioManager");

}

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
 if (root==nullptr)
 {
  setRootInstance();
 }
 return root;
}

void InstanceManager::setRootInstance()
{
 if(root!=nullptr)
  return;
 root = new InstanceManager();
}

//    public InstanceManager() {
//        init();
//    }
#if 0
    // This is a separate, protected member so it
    // can be overridden in unit tests
    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",justification="Only used during system initialization")
void InstanceManager::init()
{
 log = new Logger("InstanceManager");
 //sensorManager = NULL;
 //configureManager = nullptr;
 //timebase = nullptr;
 //sectionManager = nullptr;
 //transitManager = nullptr;
 //turnoutManager = nullptr;
 //lightManager = nullptr;
 //catalogTreeManager = nullptr;
 //audioManager = nullptr;
 //memoryManager = nullptr;
     //rosterIconFactory = NULL;
 //clockControl = nullptr;
 //signalHeadManager = nullptr;
 //conditionalManager = nullptr;
 //reporterManager = nullptr;
 //shutdownManager = nullptr;
 //logixManager = nullptr;
 //tabbedPreferencesManager = nullptr;
#if 0
 qRegisterMetaType<CreateButtonModel>("CreateButtonModel");
 qRegisterMetaType<DefaultShutDownManager>("DefaultShutDownManager");
#endif
 //    vsdecoderManager = NULL;
 //initializer = new DefaultInstanceInitializer();
 //managerLists = new  QHash<QString,QObjectList*>();
 //sensorManager = (SensorManager*)new ProxySensorManager();
 //store(sensorManager, "SensorManager");
 //turnoutManager = (TurnoutManager*)new ProxyTurnoutManager();
 //store(turnoutManager, "TurnoutManager");
 //lightManager = (LightManager*)new ProxyLightManager();
 //store(lightManager, "LightManager");
 //reporterManager = (ReporterManager*)new ProxyReporterManager();
 //store(reporterManager, "ReporterManager");
 //log->setDebugEnabled(true);
}
#endif
void InstanceManager::setSensorManager(SensorManager* p)
{
 log->debug(" setSensorManager");
 SensorManager* apm = static_cast<SensorManager*>(getDefault("SensorManager"));
 if (qobject_cast<AbstractProxyManager*>(apm)!= nullptr) { // <?> due to type erasure
     ((ProxySensorManager*) apm)->addManager(p);
 } else {
     log->error("Incorrect setup: SensorManager default isn't an AbstractProxyManager<Sensor>");
 }
}

//void InstanceManager::addSensorManager(SensorManager* p)
//{
// //SensorManager* sensorManager = instance()->sensorManager;
//// if(qobject_cast<LnSensorManager*>(sensorManager)!=NULL)
////  return;
// //if(qobject_cast<AbstractProxyManager*>(sensorManager)!= NULL)
//    ((AbstractProxyManager*)instance()->sensorManager)->addManager(p);
//}

// Needs to have proxy manager converted to work
// with current list of managers (and robust default
// management) before this can be deprecated in favor of
// store(p, TurnoutManager.class)
void InstanceManager::setTurnoutManager(TurnoutManager* p) {
 log->debug(" setTurnoutManager");
 TurnoutManager* apm = static_cast<TurnoutManager*>(getDefault("TurnoutManager"));
 if (qobject_cast<AbstractProxyManager*>(apm) != nullptr) { // <?> due to type erasure
     ((ProxyTurnoutManager*) apm)->addManager(p);
 } else {
     log->error("Incorrect setup: TurnoutManager default isn't an AbstractProxyManager<Turnout>");
 }
}

//void InstanceManager::addTurnoutManager(TurnoutManager* p) {
// if(instance()->turnoutManager == NULL)
//    ((AbstractProxyManager*)instance()->turnoutManager)->addManager(p);
//}

void InstanceManager::setLightManager(LightManager* p) {
 log->debug(" setLightManager");
 ((AbstractProxyManager*) getDefault("LightManager"))->addManager(p);
 //store(p, LightManager.class);
}

#if 0
void InstanceManager::addLightManager(LightManager* p) {
    ((AbstractProxyManager*)instance()->lightManager)->addManager(p);
}


void InstanceManager::setConfigureManager(ConfigureManager* p)
{
 log->debug(" setConfigureManager");
 setDefault("ConfigureManager", p);

}

void InstanceManager::addConfigureManager(ConfigureManager* p)
{
 if (p!=configureManager && configureManager!=nullptr && log->isDebugEnabled()) log->debug(QString("ConfigureManager instance is being replaced: %1").arg("?"));
 if (p!=configureManager && configureManager==nullptr && log->isDebugEnabled()) log->debug(QString("ConfigureManager instance is being installed: %1").arg("?"));
 configureManager = p;
}
#endif
void InstanceManager::setThrottleManager(ThrottleManager* p)
{
    store(p, "ThrottleManager");
    //instance()->notifyPropertyChangeListener("throttlemanager", QVariant(), QVariant());
}

void InstanceManager::setSignalHeadManager(SignalHeadManager* p) {
    setDefault("SignalHeadManager", p);
}
#if 0
void InstanceManager::addSignalHeadManager(SignalHeadManager* p) {
    if (p!=signalHeadManager && signalHeadManager!=nullptr && log->isDebugEnabled()) log->debug(QString("SignalHeadManager instance is being replaced: %1").arg(p->getSystemPrefix()));
    if (p!=signalHeadManager && signalHeadManager==nullptr && log->isDebugEnabled()) log->debug(QString("SignalHeadManager instance is being installed: %1").arg(p->getSystemPrefix()));
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
void InstanceManager::setConditionalManager(ConditionalManager* p) {
    instance()->addConditionalManager(p);
}

/*protected*/ void InstanceManager::addConditionalManager(ConditionalManager* p) {
    if (p!=conditionalManager && conditionalManager!=nullptr && log->isDebugEnabled()) log->debug(QString("ConditionalManager instance is being replaced%1: ").arg(p->getSystemPrefix()));
    if (p!=conditionalManager && conditionalManager==nullptr && log->isDebugEnabled()) log->debug(QString("ConditionalManager instance is being installed: %1").arg(p->getSystemPrefix()));
    conditionalManager = p;
}

void InstanceManager::setLogixManager(LogixManager* p) {
    instance()->addLogixManager(p);
}

/*protected*/ void InstanceManager::addLogixManager(LogixManager* p)
{
 if (p!=logixManager && logixManager!=nullptr && log->isDebugEnabled()) log->debug("LogixManager instance is being replaced: "+p->objectName());
 if (p!=logixManager && logixManager==nullptr && log->isDebugEnabled()) log->debug("LogixManager instance is being installed: "+p->objectName());
 logixManager = p;
}

/**
 * @deprecated Since 3.7.4, use @{link #store} directly.
 */
//@Deprecated
void InstanceManager::setShutDownManager(ShutDownManager* p) {
    store(p, "ShutDownManager");
    setDefault("ShutDownManager", p);
}
void InstanceManager::addShutdownManager(ShutDownManager* p) {
    if (p!=shutdownManager && shutdownManager!=nullptr && log->isDebugEnabled()) log->debug(QString("ShutDownManager instance is being replaced: %1").arg(p->objectName()));
    if (p!=shutdownManager && shutdownManager==nullptr && log->isDebugEnabled()) log->debug(QString("ShutDownManager instance is being installed: %1").arg(p->objectName()));
    shutdownManager = p;
}

void InstanceManager::setTabbedPreferences(TabbedPreferences* p) {
    instance()->addTabbedPreferences(p);
}
void InstanceManager::addTabbedPreferences(TabbedPreferences* p) {
    tabbedPreferencesManager = p;
}
#endif

void InstanceManager::setConsistManager(ConsistManager* p) {
    store(p, "ConsistManager");
    //instance()->notifyPropertyChangeListener("consistmanager", QVariant(), QVariant());
}

//
// This updates the consist manager, which must be
// either built into instances of calling code or a
// new service, before this can be deprecated.
//
//@Deprecated
/*static*/ /*public*/ void InstanceManager::setCommandStation(CommandStation* p)
{
 store(p, "CommandStation");
}

/**
 * @param p CommandStation to make default
 * @deprecated Since 4.9.5, use
 * {@link #store(java.lang.Object,java.lang.Class)} directly.
 */
//@Deprecated
/*static*/ /*public*/ void InstanceManager::setAddressedProgrammerManager(AddressedProgrammerManager* p) {
    store(p, "AddressedProgrammerManager");
}

void InstanceManager::setReporterManager(ReporterManager* p) {
 log->debug(" setReporterManager");
   ((AbstractProxyManager*) getDefault("ReporterManager"))->addManager(p);
   //store(p, ReporterManager.class);
}

//void InstanceManager::addReporterManager(ReporterManager* p) {
//    ((AbstractProxyManager*)instance()->reporterManager)->addManager(p);
//}

void InstanceManager::removePropertyChangeListener(PropertyChangeListener* l)
{
    QMutexLocker locker(&mutex);
    if (listeners.contains(l))
    {
     int i = listeners.indexOf(l);
     listeners.remove(i);
    }
}
///*public*/ /*static*/ /*synchronized*/ void InstanceManager::addPropertyChangeListener(PropertyChangeListener* l) {
// //QMutex mutex;
//    QMutexLocker locker(&mutex);
//    // add only if not already registered
//    if (!listeners.contains(l)) {
//        listeners.append(l);
//    }
//}

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
/**
 * Get the property name included in the
 * {@link java.beans.PropertyChangeEvent} thrown when the default for a
 * specific class is changed.
 *
 * @param clazz the class being listened for
 * @return the property name
 */
/*public*/ /*static*/ QString InstanceManager::getDefaultsPropertyName(QString clazz) {
    return "default-" + clazz/*.getName()*/;
}

/**
 * Get the property name included in the
 * {@link java.beans.PropertyChangeEvent} thrown when the list for a
 * specific class is changed.
 *
 * @param clazz the class being listened for
 * @return the property name
 */
/*public*/ /*static*/ QString InstanceManager::getListPropertyName(/*Class<?>*/QString clazz) {
    return "list-" + clazz/*.getName()*/;
}
/* ****************************************************************************
 *                   Old Style Setters - Deprecated and migrated,
 *                                       just here for other users
 *
 *                     Check Jython scripts before removing
 * ****************************************************************************/
///**
// * @deprecated Since 3.7.1, use @{link #store} and @{link #setDefault} directly.
// */
//@Deprecated
//static public void setConditionalManager(ConditionalManager p) {
//    store(p, ConditionalManager.class);
//    setDefault(ConditionalManager.class, p);
//}
///**
// * @deprecated Since 3.7.4, use @{link #store} directly.
// */
//@Deprecated
//static public void setLogixManager(LogixManager p) {
//    store(p, LogixManager.class);
//}
///**
// * @deprecated Since 3.7.4, use @{link #store} directly.
// */
//@Deprecated
//static public void setTabbedPreferences(TabbedPreferences p) {
//    store(p, TabbedPreferences.class);
//}
///**
// * @deprecated Since 3.7.1, use @{link #store} and @{link #setDefault}
// * directly.
// */
// @Deprecated
// static public void setPowerManager(PowerManager p) {
//     store(p, PowerManager.class);
// }
/**
  * Clear all managed instances of a particular type from this
  * InstanceManager.
  *
  * @param type the type to clear
  */
//template<class T>
 /*public*/  void InstanceManager::clear(/*@Nonnull*/ /*Class<T>*/QString type) {
     log->trace(tr("Clearing managers of %1").arg(type));
     QObjectList toClear = QObjectList(getInstances(type));
     //toClear.forEach((o) ->
     foreach(QObject* o, toClear)
     {
         remove(o, type);
     }//);
     setInitializationState(type, InitializationState::NOTSET); // initialization will have to be redone
     managerLists.insert(type, QObjectList());
 }
/**
  * Get the default instance of the InstanceManager. This is used for
  * verifying the source of events fired by the InstanceManager.
  *
  * @return the default instance of the InstanceManager, creating it if
  *         needed
  */
 //@Nonnull
 /*public*/ /*static*/ InstanceManager* InstanceManager::getDefault() {
     return LazyInstanceManager::instanceManager;
 }
/*public*/ /*static*/ InstanceManager* LazyInstanceManager::instanceManager = new InstanceManager();

/*private*/ void InstanceManager::setInitializationState(QString type, InitializationState state) {
    log->trace(tr("set state %1 for %2").arg(type).arg(state));
    if (state == InitializationState::STARTED) {
        initState.insert(type, new StateHolder(state, new Exception("Thread " + QThread::currentThread()->objectName())));
    } else {
        initState.insert(type, new StateHolder(state, nullptr));
    }
}

/*private*/ InitializationState InstanceManager::getInitializationState(QString type) {
    StateHolder* holder = initState.value(type);
    if (holder == nullptr) {
        return InitializationState::NOTSET;
    }
    return holder->state;
}

/*private*/ Exception InstanceManager::getInitializationException(QString type) {
    StateHolder* holder = initState.value(type);
    if (holder == nullptr) {
        return Exception();
    }
    return holder->exception;
}

/* *************************************************************************** */
/*private*/ /*final*/ /*static*/ Logger* InstanceManager::log = LoggerFactory::getLogger("InstanceManager");

// support creating a file with initialization summary information
/*private*/ /*static*/ /*final*/ bool InstanceManager::traceFileActive = InstanceManager::log->isTraceEnabled(); // or manually force true
/*private*/ /*static*/ /*final*/ bool InstanceManager::traceFileAppend = false; // append from run to run
/*private*/ /*static*/ /*final*/ QString InstanceManager::traceFileName = "instanceManagerSequence.txt";  // use a standalone name
/*private*/ /*static*/ PrintWriter* InstanceManager::traceFileWriter = nullptr;

//static {
//        PrintWriter tempWriter = null;
//        try {
//            tempWriter = (traceFileActive
//                    ? new PrintWriter(new BufferedWriter(new FileWriter(new File(traceFileName), traceFileAppend)))
//                    : null);
//        } catch (java.io.IOException e) {
//            log.error("failed to open log file", e);
//        } finally {
//            traceFileWriter = tempWriter;
//        }
//    }
/*private*/ void InstanceManager::traceFilePrint(QString msg) {
    QString pad = StringUtils::repeat(" ", traceFileIndent * 2);
    QString threadName = "[" + QThread::currentThread()->objectName() + "]";
    QString threadNamePad = StringUtils::repeat(" ", qMax(25 - threadName.length(), 0));
    QString text = threadName + threadNamePad + "|" + pad + msg;
//    traceFileWriter->println(text);
//    traceFileWriter->flush();
    log->trace(text);
}
