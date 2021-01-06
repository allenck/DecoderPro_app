#ifndef INSTANCEMANAGER_H
#define INSTANCEMANAGER_H

#include "appslib_global.h"
#include <QObject>
#include <QHash>
#include <QString>
#include <QList>
#include <QVector>
#include "logger.h"
#include "powermanager.h"
#include "sensormanager.h"
//#include "programmermanager.h"
#include "turnoutmanager.h"
#include "reportermanager.h"
#include "sectionmanager.h"
#include "blockmanager.h"
#include "audiomanager.h"
#include "memorymanager.h"
#include "conditionalmanager.h"
#include "shutdownmanager.h"
#include "logixmanager.h"
#include "dccconsistmanager.h"
#include "instanceinitializer.h"
//#include "abstractproxymanager.h"
#include "proxyreportermanager.h"
#include "proxysensormanager.h"
#include "throttlemanager.h"
#include "proxyturnoutmanager.h"
#include "defaultinstanceinitializer.h"
#include "../libPr3/routemanager.h"
#include "lightmanager.h"
//#include "rfid/transpondingtagmanager.h"
#include "audiomanager.h"
#include "metermanager.h"

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
/*private*/ enum InitializationState {
    NOTSET, // synonymous with no value for this stored
    NOTSTARTED,
    STARTED,
    FAILED,
    DONE
};

/*static*/ /*private*/ /*final*/ class StateHolder {

   InitializationState state;
   Exception* exception;
public:
   StateHolder(InitializationState state, Exception* exception) {
       this->state = state;
       this->exception = exception;
   }
   friend class InstanceManager;
};

//class TranspondingTagManager;
class SignalSpeedMap;
class PrintWriter;
class RouteManager;
class BlockManager;
class SectionManager;
class TabbedPreferences;
class TransitManager;
class LightManager;
class SignalHeadManager;
class SignalMastManager;
class SignalSystemManager;
class SignalGroupManager;
class SignalMastLogicManager;
class LayoutBlockManager;
class CatalogTreeManager;
class ProxyLightManager;
class APPSLIBSHARED_EXPORT InstanceManager : public QObject
{
    Q_OBJECT
public:
    Q_DECL_DEPRECATED InstanceManager(QObject *parent = 0);
/**
 * Store an object of a particular type for later
 * retrieval via {@link #getDefault} or {@link #getList}.
 * @param item The object of type T to be stored
 * @param type The class Object for the item's type.  This will be used
 *               as the key to retrieve the object later.
 */
 //template<class T>
 static /*public*/  void store(/*@Nonnull*/ QObject* item, /*@Nonnull Class<T> */ QString type);

/**
 * Retrieve a list of all objects of type T that were
 * registered with {@link #store}.
 * @param type The class Object for the items' type.
 */
//static public <T> List<Object> getList(Class<T> type)
//template<class T>
static QObjectList *getList(QString type);
/**
 * Deregister all objects of a particular type.
 * @param type The class Object for the items to be removed.
 */
//static public <T> void reset(Class<T> type) {
static void reset(QString type);
/**
 * Remove an object of a particular type
 * that had earlier been registered with {@link #store}.
 * @param item The object of type T to be deregistered
 * @param type The class Object for the item's type.
 */
// static public <T> void deregister(T item, Class<T> type)
static void deregister(QObject* item, QString type);
/**
 * Retrieve the last object of type T that was
 * registered with {@link #store}.
 * <p>
 * Someday, we may provide another way to set the default
 * but for now it's the last one stored, see the
 * {@link #setDefault} method.
 */
//@SuppressWarnings("unchecked")   // checked by construction
// static public <T> T getDefault(Class<T> type) {
static QObject* getDefault(QString type);
//template<class T>
//static <T> T getDefault(class<T> type);
static /*public*/ QObject* getNullableDefault(QString type);
static /*public*/ QObject* getOptionalDefault(QString type);
/*public*/ static QString getDefaultsPropertyName(QString clazz);
/*public*/ static QString getListPropertyName(/*Class<?>*/QString clazz);
/*public*/ static InstanceManager* getDefault();

static /*public*/ AudioManager* AudioManagerInstance();
/**
 * Set an object of type T as the default for that type.
 *<p>
 * Also registers (stores) the object if not already present.
 *<p>
 * Now, we do that moving the item to the back of the list;
 * see the {@link #getDefault} method
 */
//static public <T> void setDefault(Class<T> type, T val)
static QObject* setDefault(QString type, QObject* val);
/**
 * Dump generic content of InstanceManager
 * by type.
 */
static QString contentsToString();
/*public*/ static /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
/*public*/ static /*synchronized*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* l) ;
/*public*/ static /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
/*public*/ static /*synchronized*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* l);
static ThrottleManager* throttleManagerInstance();
static void setTurnoutManager(TurnoutManager* p);

static /*public*/  bool containsDefault(/*@Nonnull*/ QString type);
/*public*/ static /*<T>*/ bool isInitialized(/*@Nonnull*/ QString type);
static MemoryManager* memoryManagerInstance();
static void setSensorManager(SensorManager* p);
static void setLightManager(LightManager* p);
static void setThrottleManager(ThrottleManager* p);
static void setReporterManager(ReporterManager* p);
//template<class T>
/*public*/ /*<T>*/ QObjectList* getInstances(/*@Nonnull Class<T>*/ QString type);
/*public*/ void clearAll();
//template<class T>
/*public*/  void clear(/*@Nonnull*/ /*Class<T>*/QString type);
/*public*/ /*<T>*/ void remove(/*@Nonnull T*/QObject* item, /*@Nonnull Class<T>*/QString type);
template<class T>
static /*public*/ T* getNullableDefaultT(QString type)
{
 return (T*)getDefault()->getInstance(type);
}
static /*public*/ void setIdTagManager(IdTagManager *p);
static /*public*/ void setMeterManager(MeterManager* p);


signals:
  void propertyChange(PropertyChangeEvent*);

public slots:
  static SensorManager* sensorManagerInstance();
  static TurnoutManager* turnoutManagerInstance();
  static LightManager* lightManagerInstance();
  /*public*/ QObject* getInstance(/*@Nonnull Class<T>*/QString type);
  static ProxyTurnoutManager* proxyTurnoutManagerInstance();
  static ProxySensorManager* proxySensorManagerInstance();
  static ProxyLightManager* proxyLightManagerInstance();
  static ProxyReporterManager* proxyReporterManagerInstance();



private:
 QHash<QString,QObjectList*> managerLists;
 /*private*/ /*final*/ QMap</*Class<?>*/QString, QObject*> initializers;// = new HashMap<>();
 PropertyChangeSupport* pcs;
 /*private*/ /*final*/ QMap</*Class<?>*/QString, StateHolder*> initState;// = new HashMap<>();
 //Logger* log;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("InstanceManager");
 // data members to hold contact with the property listeners
 static QVector<PropertyChangeListener*> listeners;
 static QMutex mutex;
 // support checking for overlapping intialization
 /*private*/ void setInitializationState(QString type, InitializationState state);
 /*private*/ InitializationState getInitializationState(QString type) ;
 /*private*/ Exception* getInitializationException(QString type);
 // support creating a file with initialization summary information
 /*private*/ static /*final*/ bool traceFileActive;// = log.isTraceEnabled(); // or manually force true
 /*private*/ static /*final*/ bool traceFileAppend;// = false; // append from run to run
 /*private*/ int traceFileIndent = 1; // used to track overlap, but note that threads are parallel
 /*private*/ static /*final*/ QString traceFileName;// = "instanceManagerSequence.txt";  // use a standalone name
 /*private*/ static PrintWriter* traceFileWriter;
 /*private*/ void traceFilePrint(QString msg);

protected:

 /**
  * The "root" object is the instance manager that's answering
  * requests for other instances. Protected access to allow
  * changes during JUnit testing.
  */
// @edu.umd.cs.findbugs.annotations.SuppressWarnings(
//     value="MS_PKGPROTECT",
//     justification="Protected access to allow changes during JUnit testing.")
 static InstanceManager* root;

 void notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue);
 friend class RosterFrame;
 friend class SignalSpeedMap;
 friend class LazyInstanceManager;
};

/**
 * A class for lazy initialization of the singleton class InstanceManager.
 * https://www.ibm.com/developerworks/library/j-jtp03304/
 */
/*private*/ /*static*/ class LazyInstanceManager {
public:
    /*public*/ static InstanceManager* instanceManager;// = new InstanceManager();
 /**
  * Replace the (static) InstanceManager.
  */
 /*public*/ /*synchronized*/ static void resetInstanceManager() {
     try {
         instanceManager = new InstanceManager();
     } catch (Exception e) {
         instanceManager->log->error("can't create new InstanceManager");
     }
 }
};
#endif // INSTANCEMANAGER_H
