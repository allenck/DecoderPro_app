#include "abstractproxysensormanager.h"
#include "exceptions.h"
#include <QSet>
#include "proxyreportermanager.h"
#include "proxyturnoutmanager.h"
#include "proxysensormanager.h"
#include "proxylightmanager.h"
#include "abstractturnoutmanager.h"
#include "abstractsensormanager.h"
#include "abstractlightmanager.h"
#include "abstractreportermanager.h"
#include "lnturnoutmanager.h"
#include "loggerfactory.h"
#include "namedbeancomparator.h"
#include "vetoablechangesupport.h"
#include "internalsystemconnectionmemo.h"
#include "connectionconfigmanager.h"
#include "connectionconfig.h"

// NOTE: This class is a replacement for AbstractProxyManager that
// implements SensorManager instead of AbstractManager

AbstractProxySensorManager::AbstractProxySensorManager(QObject *parent)
    : SensorManager(new DefaultSystemConnectionMemo(), parent)
{
 mgrs = QList<AbstractManager*>();
 internalManager = nullptr;
 defaultManager = nullptr;
 addedOrderList = QStringList();
 log->setDebugEnabled(true);
 propertyListenerList = QVector<PropertyChangeListener*>();
 namedPropertyListenerMap = QMap<QString, QVector<PropertyChangeListener*>*>();
 propertyVetoListenerList = QVector<VetoableChangeListener*>();
 namedPropertyVetoListenerMap = QMap<QString, QVector<VetoableChangeListener*>*>();


 //registerSelf();
}
/**
 * Implementation of a Manager that can serves as a proxy
 * for multiple system-specific implementations.
 * <p>
 * Automatically includes an Internal system, which
 * need not be separately added any more.
 * <p>
 * Encapsulates access to the "Primary" manager,
 * used by default.
 * <p>
 * Internally, this is done by using a list of all
 * non-Internal managers, plus a separate reference to the
 * internal manager.
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2010
 * @version	$Revision: 18422 $
 */
//abstract public class AbstractProxyManager implements Manager {

/**
 * Number of managers available through
 * getManager(i) and getManagerList(),
 * including the Internal manager
 */
///*protected*/ int AbstractProxySensorManager::nMgrs() const
//{
// // make sure internal present
// initInternal();
// return mgrs.size();
//}

///*protected*/ Manager* AbstractProxySensorManager::getMgr(int index) const
//{
// // make sure internal present
// initInternal();

// if (index < mgrs.size())
//  return mgrs.value(index);
// else
// {
//  throw  IllegalArgumentException("illegal index "+QString::number(index));
// }
//}

/**
 * Returns a list of all managers, including the
 * internal manager.  This is not a live list.
 */
/*public*/ QList<AbstractManager*> AbstractProxySensorManager::getManagerList() const
{
 // make sure internal present
 initInternal();
 QList<AbstractManager*> retval = QList<AbstractManager*>(mgrs);
 return retval;
}

/**
 * Returns a list of all managers, with the default
 * at the start and internal default at the end.
 *
 * @return the list of managers
 */
/*public*/ QList<AbstractManager*> AbstractProxySensorManager::getDisplayOrderManagerList() const {
 // make sure internal present
 initInternal();

 QList<AbstractManager*> retval =  QList<AbstractManager*>();
 if (defaultManager != nullptr)
 {
  retval.append((AbstractManager*)defaultManager);
 }
 foreach (Manager* manager, mgrs) {
  AbstractManager* am = (AbstractManager*)(manager->self());
  if ((manager != defaultManager) && (manager != internalManager)) {
      retval.append(am);
  }
 }
 if (internalManager != nullptr && internalManager != defaultManager) {
  retval.append((AbstractManager*)internalManager);
 }
 return retval;
}

/*public*/ AbstractManager* AbstractProxySensorManager::getInternalManager() const {
    initInternal();
    return internalManager;
}

/**
 * Returns the set default or, if not present, the internal manager as defacto default
 */
/*public*/ AbstractManager* AbstractProxySensorManager::getDefaultManager() const {
    return defaultManager != nullptr ? defaultManager : getInternalManager();
}

/*public*/ void AbstractProxySensorManager::addManager(AbstractManager* m)
{
 // check for already present
 //if (mgrs.contains(m))
 for( AbstractManager* mgr: mgrs)
 {
  if(mgr->self()->metaObject()->className() == m->self()->metaObject()->className())
  {
  // already present, complain and skip
  log->warn(tr("Manager already present: %1").arg(m->self()->metaObject()->className()));
  return;
  }
 }
 mgrs.append(/*static_cast<AbstractManager*>(m->self())*/m);

 if (defaultManager == nullptr)
     defaultManager = m;  // 1st one is default

 AbstractManager* am = static_cast<AbstractManager*>(m->self());
 //propertyVetoListenerList.stream().forEach((l) ->
 foreach(VetoableChangeListener* l, propertyVetoListenerList)
 {
     am->addVetoableChangeListener(l);
 }//);
 //propertyListenerList.stream().forEach((l) ->
 foreach(PropertyChangeListener* l, propertyListenerList)
 {
     am->addPropertyChangeListener(l);
 }//);
 //namedPropertyVetoListenerMap.entrySet().forEach((e) ->
 QMapIterator<QString, QVector<VetoableChangeListener*>*> e(namedPropertyVetoListenerMap);
 while(e.hasNext())
 {
  e.next();
//     e.getValue().forEach((l) ->
  foreach(VetoableChangeListener* l, *e.value())
  {
      am->addVetoableChangeListener(e.key(), l);
  }//);
 }//);
 //namedPropertyListenerMap.entrySet().forEach((e) ->
 QMapIterator<QString, QVector<PropertyChangeListener*>*> e1(namedPropertyListenerMap);
 while(e1.hasNext())
 {
  e1.next();
     //e.getValue().forEach((l) ->
  foreach(PropertyChangeListener* l, *e1.value())
     {
         am->addPropertyChangeListener(e1.key(), l);
     }//);
 }//);

 m->addDataListener(this);
 recomputeNamedBeanSet();

 if (log->isDebugEnabled())
 {
     log->debug(QString("added manager ") + QString(m->self()->metaObject()->className()));
 }
}

/*private*/ AbstractManager* AbstractProxySensorManager::initInternal() const
{
 if (internalManager == nullptr) {
     log->debug("create internal manager when first requested");
     internalManager = makeInternalManager();
 }
 return internalManager;
}

///*abstract protected*/ Manager* AbstractProxySensorManager::makeInternalManager() const
//{
// return (Manager*)((InternalSystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo"))->getSensorManager();
//}

/**
 * Locate via user name, then system name if needed.
 * Subclasses use this to provide e.g. getSensor, getTurnout, etc
 * via casts.
 *
 * @param name
 * @return Null if nothing by that name exists
 */
/*public*/ NamedBean* AbstractProxySensorManager::getNamedBean(QString name) const
{
 NamedBean* t = getByUserName(name);
 if (t != nullptr) return t;
 return getBySystemName(name);
}

/**
 * Enforces, and as a user convenience converts to, the standard form for a system name
 * for the NamedBeans handled by this manager and its submanagers.
 * <p>
 * Attempts to match by system prefix first.
 * <p>
 *
 * @param inputName System name to be normalized
 * @throws NamedBean.BadSystemNameException If the inputName can't be converted to normalized form
 * @return A system name in standard normalized form
 */
//@Override
//@CheckReturnValue
///*public*/ /*@Nonnull*/ QString AbstractProxySensorManager::normalizeSystemName(/*@Nonnull*/ QString inputName) const /*throw (NamedBean::BadSystemNameException)*/ {
//    int index = matchTentative(inputName);
//    if (index >= 0) {
//        return getMgr(index)->normalizeSystemName(inputName);
//    }
//    log->debug("normalizeSystemName did not find manager for name " + inputName + ", defer to default");
//    return getMgr(0)->normalizeSystemName(inputName);
//}

/**
 * Locate via user name, then system name if needed.
 * If that fails, create a new NamedBean: If the name
 * is a valid system name, it will be used for the new
 * NamedBean.  Otherwise, the makeSystemName method
 * will attempt to turn it into a valid system name.
 * Subclasses use this to provide e.g. getSensor, getTurnout, etc
 * via casts.
 *
 * @param name
 * @return Never nullptr under normal circumstances
 */
///*protected*/ NamedBean* AbstractProxySensorManager::provideNamedBean(QString name)
//{
// NamedBean* t = getNamedBean(name);
// if (t!=nullptr) return t;
// // Doesn't exist. If the systemName was specified, find that system
// int index = matchTentative(name);
// if (index >= 0) return makeBean(index, name, "");
// log->debug("Did not find manager for name "+name+", defer to default");
////    int iI = nMgrs()-1;
////    return makeBean(iI,getMgr(iI)->makeSystemName(name), "");
// QString newSysName = getMgr(0)->makeSystemName(name);
// return makeBean(0,newSysName,"");
//}

/**
 * Defer creation of the proper type to the subclass
 * @param index Which manager to invoke
 */
///*abstract protected*/ NamedBean* AbstractProxySensorManager::makeBean(int /*index*/, QString /*systemName*/, QString /*userName*/) /*const*/
//{
//// Q_UNUSED(index);
//// Q_UNUSED(systemName);
//// Q_UNUSED(userName);
////// if(qobject_cast<ProxyReporterManager*>(this)!=NULL)
//////  return ProxyReporterManager::makeBean(index, systemName, userName);

// return nullptr; // Should not get here! this should be overriden by the actual class
//}

/** {@inheritDoc} */
//@Override
//@CheckReturnValue
//@CheckForNull
/*public*/ Sensor* AbstractProxySensorManager::getBySystemName(/*@Nonnull */ QString systemName) const {
 Manager/*<E>*/* m = getManager(systemName);
         if (m == nullptr) {
             log->debug("getBySystemName did not find manager from name {}, defer to default manager", systemName);
             m = getDefaultManager();
         }
         return (Sensor*)((AbstractManager*)m->self())->getBySystemName(systemName);
}

/** {@inheritDoc} */
//@Override
//@CheckReturnValue
//@CheckForNull
/*public*/ Sensor* AbstractProxySensorManager::getByUserName(/*@Nonnull*/ QString userName) const{
    for (Manager* m : this->mgrs) {
        NamedBean* b = ((AbstractSensorManager*)m)->getByUserName(userName);
        if (b != nullptr) {
            return (Sensor*)b;
        }
    }
    return nullptr;
}

//@Override
///*public*/ NamedBean* AbstractProxySensorManager::getBeanBySystemName(QString systemName) const
//{
// // System names can be matched to managers by system and type at front of name
// int index = matchTentative(systemName);
// if (index >= 0) {
//     Manager* m = getMgr(index);
//     return m->getBeanBySystemName(systemName);
// }
// log->debug(tr("getBeanBySystemName did not find manager from name %1, defer to default manager").arg(systemName)); // NOI18N
// return getDefaultManager()->getBeanBySystemName(systemName);
//}

//@Override
///*public*/ NamedBean* AbstractProxySensorManager::getBeanByUserName(QString userName) const
//{
// foreach (Manager* m, this->mgrs) {
//     NamedBean* b = m->getBeanByUserName(userName);
//     if (b != nullptr) {
//         return b;
//     }
// }
// return nullptr;
//}


/**
 * Return an instance with the specified system and user names.
 * Note that two calls with the same arguments will get the same instance;
 * there is only one Sensor object representing a given physical turnout
 * and therefore only one with a specific system or user name.
 *<P>
 * This will always return a valid object reference for a valid request;
 * a new object will be
 * created if necessary. In that case:
 *<UL>
 *<LI>If a NULL reference is given for user name, no user name will be associated
 *    with the NamedBean object created; a valid system name must be provided
 *<LI>If a NULL reference is given for the system name, a system name
 *    will _somehow_ be inferred from the user name.  How this is done
 *    is system specific.  Note: a future extension of this interface
 *    will add an exception to signal that this was not possible.
 *<LI>If both names are provided, the system name defines the
 *    hardware access of the desired turnout, and the user address
 *    is associated with it.
 *</UL>
 * Note that it is possible to make an inconsistent request if both
 * addresses are provided, but the given values are associated with
 * different objects.  This is a problem, and we don't have a
 * good solution except to issue warnings.
 * This will mostly happen if you're creating NamedBean when you should
 * be looking them up.
 * @return requested NamedBean object (never NULL)
 */
///*public*/ NamedBean* AbstractProxySensorManager::newNamedBean(QString systemName, QString userName) {
// // make sure internal present
// initInternal();

//    // if the systemName is specified, find that system
//    int i = matchTentative(systemName);
//    if (i >= 0)
//        return makeBean(i, systemName, userName);

//    // did not find a manager, allow it to default to the primary
//    log->debug("Did not find manager for system name "+systemName+", delegate to primary");
//    int iI = nMgrs()-1;
//    return makeBean(iI, systemName, userName);
//    //return makeBean(mgrs.entryIndex(getDefaultManager()), systemName, userName);
//}

/*public*/ void AbstractProxySensorManager::dispose() {
    for (int i=0; i<mgrs.size(); i++)
        mgrs.value(i)->dispose();
    mgrs.clear();
    if (internalManager != nullptr) internalManager->dispose(); // don't make if not made yet
}
/**
 * Get the manager for the given system name.
 *
 * @param systemName the given name
 * @return the requested manager or null if there is no matching manager
 */
//@CheckForNull
/*protected*/ Manager/*<E>*/* AbstractProxySensorManager::getManager(/*@Nonnull*/ QString systemName) const {
    // make sure internal present
    initInternal();
    for (AbstractManager/*<E>*/* m : getManagerList()) {
        if (systemName.startsWith(m->getSystemNamePrefix())) {
            return m;
        }
    }
    return nullptr;
}

/**
 * Find the index of a matching manager.
 * Returns -1 if there is no match, which is not considered an
 * error
 */
///*protected*/ int AbstractProxySensorManager::matchTentative(QString systemname) const
//{
// //Q_ASSERT(mgrs->count()> 0);
// for (int i = 0; i<nMgrs(); i++)
// {
//  Manager* mgr = getMgr(i);
//#ifdef QT_DEBUG
//  QString pfx = ((AbstractManager*)mgr)->getSystemPrefix();
//  char tl = ((AbstractManager*)mgr)->typeLetter();
//#endif
//  if ( systemname.startsWith(((AbstractManager*)mgr)->getSystemPrefix()+((AbstractManager*)mgr)->typeLetter()))
//  {
//   return i;
//  }
// }
// return -1;
//}

/**
 * Find the index of a matching manager.
 * Throws IllegalArgumentException if there is no match,
 * here considered to be an error that must be reported.
 */
///*protected*/ int AbstractProxySensorManager::match(QString systemname) const {
//    int index = matchTentative(systemname);
//    if (index < 0) throw  IllegalArgumentException("System name "+systemname+" failed to match");
//    return index;
//}

/**
 * Get the manager for the given system name or the default manager if there
 * is no matching manager.
 *
 * @param systemName the given name
 * @return the requested manager or the default manager if there is no
 *         matching manager
 */
//@Nonnull
/*protected*/ Manager/*<E>*/* AbstractProxySensorManager::getManagerOrDefault(/*@Nonnull*/ QString systemName) {
    Manager/*<E>*/* manager = getManager(systemName);
    if (manager == nullptr) {
        manager = getDefaultManager();
    }
    return manager;
}

/**
 * Shared method to create a systemName based on the address base, the prefix and manager class.
 *
 * @param curAddress base address to use
 * @param prefix system prefix to use
 * @param beanType Bean Type for manager (method is used for Turnout and Sensor Managers)
 * @return a valid system name for this connection
 * @throws JmriException if systemName cannot be created
 */
QString AbstractProxySensorManager::createSystemName(QString curAddress, QString prefix, QString beanType) const throw (JmriException) {
    for (Manager/*<E>*/* m : mgrs) {
        if (prefix == (m->getSystemPrefix()) && beanType == (m->getNamedBeanClass())) {
            try {
                if (beanType == "Turnout") {
                    return ((TurnoutManager*) m)->createSystemName(curAddress, prefix);
                } else if (beanType == "Sensor") {
                    return ((SensorManager*) m)->createSystemName(curAddress, prefix);
                }
//                else if (beanType == "Light") {
//                    return ((LightManager*) m)->createSystemName(curAddress, prefix);
//                }
//                else if (beanType == "Reporter") {
//                    return ((ReporterManager*) m)->createSystemName(curAddress, prefix);
//                }
                else {
                    log->warn("createSystemName requested for incompatible Manager");
                }
            } catch (JmriException ex) {
                throw ex;
            }
        }
    }
    throw  JmriException("Manager could not be found for System Prefix " + prefix);
}

//@Nonnull
/*public*/ QString AbstractProxySensorManager::createSystemName(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix) const throw (JmriException) {
    return createSystemName(curAddress, prefix, getNamedBeanClass());
}

//@SuppressWarnings("deprecation") // user warned by actual manager class
/*public*/ QString AbstractProxySensorManager::getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, char typeLetter) throw (JmriException) {
    for (Manager/*<E>*/* m : mgrs) {
        log->debug(tr("NextValidAddress requested for %1").arg(curAddress));
        if (prefix ==(m->getSystemPrefix()) && typeLetter == m->typeLetter()) {
            try {
                switch (typeLetter) { // use #getDefaultManager() instead?
                    case 'T':
                        return ((TurnoutManager*) m)->getNextValidAddress(curAddress, prefix);
                    case 'S':
                        return ((SensorManager*) m)->getNextValidAddress(curAddress, prefix);
                    case 'R':
                        return ((ReporterManager*) m)->getNextValidAddress(curAddress, prefix);
                    default:
                        return QString();
                }
            } catch (JmriException ex) {
                throw ex;
            }
        }
    }
    return QString();
}

/*public*/ QString AbstractProxySensorManager::getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, bool ignoreInitialExisting, char typeLetter) throw (JmriException) {
    for (Manager/*<E>*/* m : mgrs) {
        log->debug(tr("NextValidAddress requested for %1").arg(curAddress));
        if (prefix == (m->getSystemPrefix()) && typeLetter == m->typeLetter()) {
            try {
                switch (typeLetter) { // use #getDefaultManager() instead?
//                    case 'T':
//                        return ((TurnoutManager*) m)->getNextValidAddress(curAddress, prefix, ignoreInitialExisting);
                    case 'S':
                        return ((SensorManager*) m)->getNextValidAddress(curAddress, prefix, ignoreInitialExisting);
//                    case 'L':
//                        return ((LightManager*) m)->getNextValidAddress(curAddress, prefix, ignoreInitialExisting);
//                    case 'R':
//                        return ((ReporterManager*) m)->getNextValidAddress(curAddress, prefix, ignoreInitialExisting);
                    default:
                        return QString();
                }
            } catch (JmriException ex) {
                throw ex;
            }
        }
    }
    return QString();
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractProxySensorManager::deleteBean(/*@Nonnull*/ NamedBean* s, /*@Nonnull*/ QString property) throw (PropertyVetoException) {
    Manager/*<E>*/* m = getManager(s->getSystemName());
    if (m != nullptr) {
        m->deleteBean(s, property);
    }
}

/**
 * Try to create a system manager. If this proxy manager is able to create
 * a system manager, the concrete class must implement this method.
 *
 * @param memo the system connection memo for this connection
 * @return the new manager or null if it's not possible to create the manager
 */
/*protected*/ AbstractManager/*<E>*/* AbstractProxySensorManager::createSystemManager(/*@Nonnull*/ SystemConnectionMemo* memo) const {
    return nullptr;
}

/**
 * Try to create a system manager.
 *
 * @param systemPrefix the system prefix
 * @return the new manager or null if it's not possible to create the manager
 */
/*private*/ AbstractManager/*<E>*/* AbstractProxySensorManager::createSystemManager(/*@Nonnull*/ QString systemPrefix) const{
    AbstractManager/*<E>*/* m = nullptr;

    ConnectionConfigManager* manager = (ConnectionConfigManager*)InstanceManager::getNullableDefault("ConnectionConfigManager");
    if (manager == nullptr) return nullptr;

    QVector<ConnectionConfig*> connections = manager->getConnections();

    for (ConnectionConfig* connection : connections) {
        if (systemPrefix == (connection->getAdapter()->getSystemPrefix())) {
            m = createSystemManager(connection->getAdapter()->getSystemConnectionMemo());
        }
        if (m != nullptr) break;
    }
//        if (m == null) throw new RuntimeException("Manager not created");
    return m;
}

/**
 * Remember a NamedBean Object created outside the manager.
 * <P>
 * Forwards the register request to the matching system
 */
/*public*/ void AbstractProxySensorManager::Register(NamedBean* s) const {
 Manager/*<E>*/* m = getManager(s->getSystemName());
 if (m == nullptr) {
     QString systemPrefix = Manager::getSystemPrefix(s->getSystemName());
     m = createSystemManager(systemPrefix);
 }
 if (m != nullptr) {
     m->Register(s);
 } else {
     log->error(tr("Unable to register %1 in this proxy manager. No system specific manager supports this bean.").arg(s->getSystemName()));
 }
}

/**
 * {@inheritDoc}
 * <p>
 * Forwards the deregister request to the matching system.
 *
 * @param s the name
 */
//@Override
/*public*/ void AbstractProxySensorManager::deregister(/*@Nonnull*/ NamedBean* s) {
    Manager/*<E>*/* m = getManager(s->getSystemName());
    if (m != nullptr) {
        m->deregister(s);
    }
}

/*public synchronized*/ void AbstractProxySensorManager::addPropertyChangeListener(PropertyChangeListener* l)
{
// if (!propertyListenerList.contains(l)) {
//     propertyListenerList.append(l);
// }
 AbstractManager::addPropertyChangeListener(l);
 for (Manager/*<E>*/* m : mgrs) {
  ((AbstractManager*)m->self())->addPropertyChangeListener(l);
  //connect(((AbstractManager*)mgr)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l->self(), SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
/*public synchronized*/ void AbstractProxySensorManager::removePropertyChangeListener(PropertyChangeListener* l)
{
// if (propertyListenerList.contains(l)) {
//     propertyListenerList.removeOne(l);
// }
 AbstractManager::removePropertyChangeListener(l);
 for (Manager/*<E>*/* m : mgrs) {
  ((AbstractManager*)m->self())->addPropertyChangeListener(l);
  //disconnect(((AbstractManager*)mgr)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l->self(), SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractProxySensorManager::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
//    if (!namedPropertyListenerMap.contains(propertyName)) {
//        namedPropertyListenerMap.insert(propertyName, new QVector<PropertyChangeListener*>());
//    }
//    if (!namedPropertyListenerMap.value(propertyName)->contains(listener)) {
//        namedPropertyListenerMap.value(propertyName)->append(listener);
//    }
    AbstractManager::addPropertyChangeListener(propertyName, listener);
            boundPropertyNames.append(propertyName);
    for (Manager/*<E>*/* m : mgrs) {
        ((AbstractManager*)m->self())->addPropertyChangeListener(propertyName, listener);
    }
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ QVector<PropertyChangeListener*> AbstractProxySensorManager::getPropertyChangeListeners() {
    QList<PropertyChangeListener*> listeners = QList<PropertyChangeListener*>(propertyListenerList.toList());
    for (QVector<PropertyChangeListener*>* list : namedPropertyListenerMap.values()) {
        //listeners.addAll(list);
     foreach(PropertyChangeListener* listener, *list)
      listeners.append(listener);
    }
    return listeners.toVector();//(new PropertyChangeListener[listeners.size()]);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ QVector<PropertyChangeListener*> AbstractProxySensorManager::getPropertyChangeListeners(QString propertyName) {
    if (!namedPropertyListenerMap.contains(propertyName)) {
        namedPropertyListenerMap.insert(propertyName, new QVector<PropertyChangeListener*>());
    }
    QVector<PropertyChangeListener*>* listeners = namedPropertyListenerMap.value(propertyName);
    return *listeners;//(new PropertyChangeListener[listeners.size()]);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractProxySensorManager::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
//    if (!namedPropertyListenerMap.contains(propertyName)) {
//        namedPropertyListenerMap.insert(propertyName, new QVector<PropertyChangeListener*>());
//    }
//    namedPropertyListenerMap.value(propertyName)->removeOne(listener);
 AbstractManager::removePropertyChangeListener(propertyName, listener);
 for (Manager/*<E>*/* m : mgrs) {
     ((AbstractManager*)m->self())->removePropertyChangeListener(propertyName, listener);
 }
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ /*synchronized*/ void AbstractProxySensorManager::addVetoableChangeListener(VetoableChangeListener* listener) {
    AbstractManager::addVetoableChangeListener(listener);
    //connect(InstanceManager::sensorManagerInstance()->vcs, SIGNAL(vetoablePropertyChange(PropertyChangeEvent*)), this, SLOT(vetoableChange(PropertyChangeEvent*)));
    for (Manager/*<E>*/* m : mgrs) {
        ((AbstractManager*)m->self())->addVetoableChangeListener(listener);
    }

}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ /*synchronized*/ void AbstractProxySensorManager::removeVetoableChangeListener(VetoableChangeListener* l) {
    AbstractManager::removeVetoableChangeListener(l);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractProxySensorManager::addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
    AbstractManager::addVetoableChangeListener(propertyName, listener);
    for (Manager/*<E>*/* m : mgrs) {
        ((AbstractManager*)m->self())->addVetoableChangeListener(propertyName, listener);
    }
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
///*public*/ QVector<VetoableChangeListener*> AbstractProxySensorManager::getVetoableChangeListeners() {
//    return vcs->getVetoableChangeListeners();
//}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
///*public*/ QVector<VetoableChangeListener*> AbstractProxySensorManager::getVetoableChangeListeners(QString propertyName) {
//    return vcs->getVetoableChangeListeners(propertyName);
//}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractProxySensorManager::removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
    AbstractManager::removeVetoableChangeListener(propertyName, listener);
    for (Manager/*<E>*/* m : mgrs) {
        ((AbstractManager*)m->self())->removeVetoableChangeListener(propertyName, listener);
    }

}

/**
 * {@inheritDoc}
 *
 * @return The system connection memo for the manager returned by
 *         {@link #getDefaultManager()}, or the Internal system connection
 *         memo if there is no default manager
 */
//@Override
//@Nonnull
/*public*/ SystemConnectionMemo* AbstractProxySensorManager::getMemo() const{
    try {
        return getDefaultManager()->getMemo();
    } catch (IndexOutOfBoundsException ex) {
        return (SystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo");
    }
}

/**
 * @return The system-specific prefix letter for the primary implementation
 */
/*public*/ QString AbstractProxySensorManager::getSystemPrefix() const {
//    try {
      return getDefaultManager()->getSystemPrefix();
//        } catch(IndexOutOfBoundsException* ie) {
//          return "?";
//        }
}

/**
 * @return The type letter for turnouts
 */
/*public*/ char AbstractProxySensorManager::typeLetter() const
{
 return getDefaultManager()->typeLetter();
}

/**
 * @return A system name from a user input, typically a number,
 * from the primary system.
 */
/*public*/ QString AbstractProxySensorManager::makeSystemName(QString s) const {
    return mgrs.at(0)->makeSystemName(s);
}

/** {@inheritDoc} */
//@CheckReturnValue
//@Override
/*public*/ int AbstractProxySensorManager::getObjectCount() {
    int count = 0;
    for (Manager/*<E>*/* m : mgrs) { count += m->getObjectCount(); }
    return count;
}

/*public*/ QStringList AbstractProxySensorManager::getSystemNameArray() {
    //TreeSet<QString> ts = new TreeSet<String>(new SystemNameComparator());
    QSet<QString>* ts = new QSet<QString>();
    for (Manager/*<E>*/* m : mgrs) {
        //ts->add( getMgr(i).getSystemNameList() );
        QStringList snl =m->getSystemNameList();
        foreach(QString s, snl)
         ts->insert(s);
    }
//        QStringList* arr;// = new String[ts.size()];
//        Iterator<QString> it = ts.iterator();
//        int i=0;
//        while(it.hasNext()) {
//            arr[i++] = it.next();
//        }
    QStringList arr = (ts->toList());
    return arr;
}

/**
 * Get a list of all system names.
 */
/*public*/ QStringList AbstractProxySensorManager::getSystemNameList() {
    //TreeSet<QString> ts = new TreeSet<String>(new SystemNameComparator());
    QSet<QString>* ts = new QSet<QString>();
    for (Manager/*<E>*/* m : mgrs) {
        //ts.addAll(getMgr(i).getSystemNameList());
        QStringList snl = m->getSystemNameList();
        foreach(QString s, snl)
         ts->insert(s);
    }
    //return new ArrayList<String>(ts);
    QStringList arr = ts->toList();
    return arr;
}

/*protected*/ void AbstractProxySensorManager::updateOrderList() {
    if (addedOrderList.isEmpty()) return; // only maintain if requested
    addedOrderList.clear();
    for (Manager* m : mgrs) {
        //addedOrderList.addAll(m.getSystemNameAddedOrderList());
     for(QString name : m->getSystemNameAddedOrderList() )
      addedOrderList.append(name);
    }
}

/** {@inheritDoc} */
//@Override
//@Deprecated  // will be removed when Manager method is removed due to @Override
/*public*/ QStringList AbstractProxySensorManager::getSystemNameAddedOrderList() {
    addedOrderList = QStringList();  // need to start maintaining it
    updateOrderList();
    //return Collections.unmodifiableList(addedOrderList);
    return addedOrderList;
}

/** {@inheritDoc} */
//@Override
//@Deprecated  // will be removed when Manager method is removed due to @Override
//@Nonnull
/*public*/ QList<NamedBean*>* AbstractProxySensorManager::getNamedBeanList() {
    // by doing this in order by manager and from each managers ordered sets, its finally in order
    QList<NamedBean*>* tl = new QList<NamedBean*>();
    for (Manager*  m : mgrs) {
        //tl.addAll(m.getNamedBeanSet());
     foreach(NamedBean* bean, m->getNamedBeanSet())
      tl->append(bean);
    }
    //return Collections.unmodifiableList(tl);
    return tl;
}

/*protected*/ void AbstractProxySensorManager::recomputeNamedBeanSet() {
 if (namedBeanSet == nullptr) return; // only maintain if requested
 namedBeanSet->clear();
 for (Manager/*<E>*/* m : mgrs) {
     namedBeanSet->unite(((AbstractManager*)m)->getNamedBeanSet());
 }
}


NamedBeanComparator<NamedBean*> comparator3 = NamedBeanComparator<NamedBean*>();

bool sortLessThanconst3( NamedBean* s1,  NamedBean* s2)
{
 return comparator3.compare(s1, s2) < 0;
}

/** {@inheritDoc} */
//@Override
//@Nonnull
/*public*/ /*SortedSet<E>*/QSet<NamedBean*> AbstractProxySensorManager::getNamedBeanSet() {
 if (namedBeanSet == nullptr) {
     namedBeanSet = new QSet<NamedBean*>();//new TreeSet<>(new NamedBeanComparator<>());
     recomputeNamedBeanSet();
 }

 //return Collections.unmodifiableSortedSet(namedBeanSet);
 QList<NamedBean*> list = namedBeanSet->toList();
 qSort(list.begin(), list.end(), sortLessThanconst3); //NamedBeanComparator<NamedBean*>::compare);
 return list.toSet();
}

///**
// * Get a list of all user names.
// */
///*public*/ QStringList AbstractProxySensorManager::getUserNameList()
//{
// //TreeSet<QString> ts = new TreeSet<String>(new SystemNameComparator());
// QSet<QString>* ts = new QSet<QString>();
// for (int i = 0; i<nMgrs(); i++)
// {
//  //ts.addAll(getMgr(i).getSystemNameList());
//  QStringList snl = getMgr(i)->getSystemNameList();
//  foreach(QString s, snl)
//  {
//   AbstractNamedBean* bean = (AbstractNamedBean*)getMgr(i)->getBeanBySystemName(s);
//   QString userName = bean->getUserName();
//   if(userName != "")
//    ts->insert(userName);
//  }
// }
// //return new ArrayList<String>(ts);
// QStringList arr = ts->toList();
// return arr;
//}

void AbstractProxySensorManager::propertyChange(PropertyChangeEvent *e)
{
 emit this->propertyChange(e);
}
// initialize logging
/*private*/ /*final*/ /*static*/ Logger* AbstractProxySensorManager::log = LoggerFactory::getLogger("AbstractProxyTurnoutManager");

//++++++++++++++++++++++++++++++++++++++++++++++++
// stuff in AbstractProvidingProxyManager
/**
 * Locate via user name, then system name if needed. If that fails, create a
 * new NamedBean: If the name is a valid system name, it will be used for
 * the new NamedBean. Otherwise, the makeSystemName method will attempt to
 * turn it into a valid system name. Subclasses use this to create provider methods such as
 * getSensor or getTurnout via casts.
 *
 * @param name the user name or system name of the bean
 * @return an existing or new NamedBean
 * @throws IllegalArgumentException if name is not usable in a bean
 */
/*protected*/ NamedBean* AbstractProxySensorManager::provideNamedBean(QString name) throw (IllegalArgumentException) {
    // make sure internal present
    initInternal();

    NamedBean* t = getNamedBean(name);
    if (t != nullptr) {
        return t;
    }
    // Doesn't exist. If the systemName was specified, find that system
    Manager/*<E>*/* manager = getManager(name);
    if (manager != nullptr) {
        return makeBean(manager, name, "");
    }
    log->debug(tr("provideNamedBean did not find manager for name %1, defer to default").arg(name)); // NOI18N
    return makeBean(getDefaultManager(), getDefaultManager()->makeSystemName(name), "");
}

/**
 * Return an instance with the specified system and user names. Note that
 * two calls with the same arguments will get the same instance; there is
 * i.e. only one Sensor object representing a given physical sensor and
 * therefore only one with a specific system or user name.
 * <p>
 * This will always return a valid object reference for a valid request; a
 * new object will be created if necessary. In that case:
 * <ul>
 * <li>If a null reference is given for user name, no user name will be
 * associated with the NamedBean object created; a valid system name must be
 * provided
 * <li>If a null reference is given for the system name, a system name will
 * _somehow_ be inferred from the user name. How this is done is system
 * specific. Note: a future extension of this interface will add an
 * exception to signal that this was not possible.
 * <li>If both names are provided, the system name defines the hardware
 * access of the desired turnout, and the user address is associated with
 * it.
 * </ul>
 * Note that it is possible to make an inconsistent request if both
 * addresses are provided, but the given values are associated with
 * different objects. This is a problem, and we don't have a good solution
 * except to issue warnings. This will mostly happen if you're creating
 * NamedBean when you should be looking them up.
 *
 * @param systemName the system name
 * @param userName   the user name
 * @return requested NamedBean object (never null)
 */
/*public*/ NamedBean* AbstractProxySensorManager::newNamedBean(QString systemName, QString userName) {
    // make sure internal present
    initInternal();

    // if the systemName is specified, find that system
    AbstractManager/*<E>*/* m = (AbstractManager*)getManager(systemName);
    if (m != nullptr) {
        return makeBean(m, systemName, userName);
    }

    // did not find a manager, allow it to default to the primary
    log->debug(tr("Did not find manager for system name %1, delegate to primary").arg(systemName)); // NOI18N
    return makeBean(getDefaultManager(), systemName, userName);
}

/**
 * Defer creation of the proper type to the subclass.
 *
 * @param manager    the manager to invoke
 * @param systemName the system name
 * @param userName   the user name
 * @return a bean
 */
//abstract protected E makeBean(Manager<E> manager, String systemName, String userName);
