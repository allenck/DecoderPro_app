#include "abstractproxylightmanager.h"
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

// NOTE: This class is a replacement for AbstractProxyManager that
// implements LightManager instead of AbstractManager

AbstractProxyLightManager::AbstractProxyLightManager(QObject *parent)
    : LightManager(new SystemConnectionMemo(), parent)
{
 mgrs = QList<Manager*>();
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
/*protected*/ int AbstractProxyLightManager::nMgrs()
{
 // make sure internal present
 initInternal();
 return mgrs.size();
}

/*protected*/ Manager* AbstractProxyLightManager::getMgr(int index)
{
 // make sure internal present
 initInternal();

 if (index < mgrs.size())
  return mgrs.value(index);
 else
 {
  throw  IllegalArgumentException("illegal index "+QString::number(index));
 }
}

/**
 * Returns a list of all managers, including the
 * internal manager.  This is not a live list.
 */
/*public*/ QList<Manager*> AbstractProxyLightManager::getManagerList()
{
 // make sure internal present
 initInternal();
 QList<Manager*> retval = QList<Manager*>(mgrs);
 return retval;
}

/**
 * Returns a list of all managers, with the default
 * at the start and internal default at the end.
 *
 * @return the list of managers
 */
/*public*/ QList<Manager*> AbstractProxyLightManager::getDisplayOrderManagerList() {
    // make sure internal present
    initInternal();

    QList<Manager*> retval =  QList<Manager*>();
    if (defaultManager != nullptr) { retval.append(defaultManager); }
    foreach (Manager* manager, mgrs) {
        if (manager != defaultManager && manager != internalManager) {
            retval.append(manager);
        }
    }
    if (internalManager != nullptr && internalManager != defaultManager) {
        retval.append(internalManager);
    }
    return retval;
}

/*public*/ Manager* AbstractProxyLightManager::getInternalManager() {
    initInternal();
    return internalManager;
}

/**
 * Returns the set default or, if not present, the internal manager as defacto default
 */
/*public*/ Manager* AbstractProxyLightManager::getDefaultManager() {
    if (defaultManager != nullptr) return defaultManager;

    return getInternalManager();
}

/*public*/ void AbstractProxyLightManager::addManager(Manager* m)
{
 // check for already present
 if (mgrs.contains(m))
 {
  // already present, complain and skip
  log->warn(tr("Manager already present: %1").arg(m->metaObject()->className()));
  return;
 }
 mgrs.append(static_cast<AbstractManager*>(m));

 if (defaultManager == nullptr) defaultManager = m;  // 1st one is default
 AbstractManager* am = static_cast<AbstractManager*>(m);
 connect(am->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 updateOrderList();
 //updateNamedBeanSet();

 if (log->isDebugEnabled())
 {
     log->debug(QString("added manager ") + QString(m->metaObject()->className()));
 }
}

/*private*/ Manager* AbstractProxyLightManager::initInternal()
{
 if (internalManager == nullptr) {
     log->debug("create internal manager when first requested");
     internalManager = makeInternalManager();
 }
 return internalManager;
}

/*abstract protected*/ Manager* AbstractProxyLightManager::makeInternalManager() const
{
 return nullptr;
}

/**
 * Locate via user name, then system name if needed.
 * Subclasses use this to provide e.g. getSensor, getTurnout, etc
 * via casts.
 *
 * @param name
 * @return Null if nothing by that name exists
 */
/*public*/ NamedBean* AbstractProxyLightManager::getNamedBean(QString name)
{
 NamedBean* t = getBeanByUserName(name);
 if (t != nullptr) return t;
 return getBeanBySystemName(name);
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
/*public*/ /*@Nonnull*/ QString AbstractProxyLightManager::normalizeSystemName(/*@Nonnull*/ QString inputName) /*throw (NamedBean::BadSystemNameException)*/ {
    int index = matchTentative(inputName);
    if (index >= 0) {
        return getMgr(index)->normalizeSystemName(inputName);
    }
    log->debug("normalizeSystemName did not find manager for name " + inputName + ", defer to default");
    return getMgr(0)->normalizeSystemName(inputName);
}

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
/*protected*/ NamedBean* AbstractProxyLightManager::provideNamedBean(QString name)
{
 NamedBean* t = getNamedBean(name);
 if (t!=nullptr) return t;
 // Doesn't exist. If the systemName was specified, find that system
 int index = matchTentative(name);
 if (index >= 0) return makeBean(index, name, "");
 log->debug("Did not find manager for name "+name+", defer to default");
//    int iI = nMgrs()-1;
//    return makeBean(iI,getMgr(iI)->makeSystemName(name), "");
 QString newSysName = getMgr(0)->makeSystemName(name);
 return makeBean(0,newSysName,"");
}

/**
 * Defer creation of the proper type to the subclass
 * @param index Which manager to invoke
 */
/*abstract protected*/ NamedBean* AbstractProxyLightManager::makeBean(int /*index*/, QString /*systemName*/, QString /*userName*/) /*const*/
{
// Q_UNUSED(index);
// Q_UNUSED(systemName);
// Q_UNUSED(userName);
//// if(qobject_cast<ProxyReporterManager*>(this)!=NULL)
////  return ProxyReporterManager::makeBean(index, systemName, userName);

 return nullptr; // Should not get here! this should be overriden by the actual class
}

//@Override
/*public*/ NamedBean* AbstractProxyLightManager::getBeanBySystemName(QString systemName)
{
 //NamedBean* t = nullptr;
 foreach (Manager* m, this->mgrs) {
     NamedBean* b = m->getBeanBySystemName(systemName);
     if (b != nullptr) {
         return b;
     }
 }
 return nullptr;
}

//@Override
/*public*/ NamedBean* AbstractProxyLightManager::getBeanByUserName(QString userName)
{
 foreach (Manager* m, this->mgrs) {
     NamedBean* b = m->getBeanByUserName(userName);
     if (b != nullptr) {
         return b;
     }
 }
 return nullptr;
}


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
/*public*/ NamedBean* AbstractProxyLightManager::newNamedBean(QString systemName, QString userName) {
 // make sure internal present
 initInternal();

    // if the systemName is specified, find that system
    int i = matchTentative(systemName);
    if (i >= 0)
        return makeBean(i, systemName, userName);

    // did not find a manager, allow it to default to the primary
    log->debug("Did not find manager for system name "+systemName+", delegate to primary");
    int iI = nMgrs()-1;
    return makeBean(iI, systemName, userName);
    //return makeBean(mgrs.entryIndex(getDefaultManager()), systemName, userName);

}

/*public*/ void AbstractProxyLightManager::dispose() {
    for (int i=0; i<mgrs.size(); i++)
        mgrs.value(i)->dispose();
    mgrs.clear();
    if (internalManager != nullptr) internalManager->dispose(); // don't make if not made yet
}

/**
 * Find the index of a matching manager.
 * Returns -1 if there is no match, which is not considered an
 * error
 */
/*protected*/ int AbstractProxyLightManager::matchTentative(QString systemname)
{
 //Q_ASSERT(mgrs->count()> 0);
 for (int i = 0; i<nMgrs(); i++)
 {
  Manager* mgr = getMgr(i);
#ifdef QT_DEBUG
  QString pfx = ((AbstractManager*)mgr)->getSystemPrefix();
  char tl = ((AbstractProxyLightManager*)mgr)->typeLetter();
#endif
  if ( systemname.startsWith(((AbstractManager*)mgr)->getSystemPrefix()+((AbstractProxyLightManager*)mgr)->typeLetter()))
  {
   return i;
  }
 }
 return -1;
}

/**
 * Find the index of a matching manager.
 * Throws IllegalArgumentException if there is no match,
 * here considered to be an error that must be reported.
 */
/*protected*/ int AbstractProxyLightManager::match(QString systemname) {
    int index = matchTentative(systemname);
    if (index < 0) throw  IllegalArgumentException("System name "+systemname+" failed to match");
    return index;
}

/**
 * Remember a NamedBean Object created outside the manager.
 * <P>
 * Forwards the register request to the matching system
 */
/*public*/ void AbstractProxyLightManager::Register(NamedBean* s) {
    QString systemName = s->getSystemName();
    getMgr(match(systemName))->Register(s);
}

/**
 * Forget a NamedBean Object created outside the manager.
 * <P>
 * Forwards the deregister request to the matching system
 */
/*public*/ void AbstractProxyLightManager::deregister(NamedBean* s) {
    QString systemName = s->getSystemName();
    getMgr(match(systemName))->deregister(s);
}

/*public synchronized*/ void AbstractProxyLightManager::addPropertyChangeListener(PropertyChangeListener* l)
{
 for (int i = 0; i<nMgrs(); i++)
 {
  Manager* mgr = getMgr(i);
  mgr->addPropertyChangeListener(l);
  connect(((AbstractManager*)mgr)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
/*public synchronized*/ void AbstractProxyLightManager::removePropertyChangeListener(PropertyChangeListener* l)
{
 for (int i = 0; i<nMgrs(); i++)
 {
  Manager* mgr = getMgr(i);
  //mgr->addPropertyChangeListener(l);
  disconnect(((AbstractManager*)mgr)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractProxyLightManager::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    if (!namedPropertyListenerMap.contains(propertyName)) {
        namedPropertyListenerMap.insert(propertyName, new QVector<PropertyChangeListener*>());
    }
    if (!namedPropertyListenerMap.value(propertyName)->contains(listener)) {
        namedPropertyListenerMap.value(propertyName)->append(listener);
    }
    for (Manager/*<E>*/* m : mgrs) {
        m->addPropertyChangeListener(propertyName, listener);
    }
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ QVector<PropertyChangeListener*> AbstractProxyLightManager::getPropertyChangeListeners() {
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
/*public*/ QVector<PropertyChangeListener*> AbstractProxyLightManager::getPropertyChangeListeners(QString propertyName) {
    if (!namedPropertyListenerMap.contains(propertyName)) {
        namedPropertyListenerMap.insert(propertyName, new QVector<PropertyChangeListener*>());
    }
    QVector<PropertyChangeListener*>* listeners = namedPropertyListenerMap.value(propertyName);
    return *listeners;//(new PropertyChangeListener[listeners.size()]);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractProxyLightManager::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    if (!namedPropertyListenerMap.contains(propertyName)) {
        namedPropertyListenerMap.insert(propertyName, new QVector<PropertyChangeListener*>());
    }
    namedPropertyListenerMap.value(propertyName)->removeOne(listener);
    for (Manager/*<E>*/* m : mgrs) {
        m->removePropertyChangeListener(propertyName, listener);
    }
}

/**
 * @return The system-specific prefix letter for the primary implementation
 */
/*public*/ QString AbstractProxyLightManager::getSystemPrefix() {
//    try {
      return getMgr(0)->getSystemPrefix();
//        } catch(IndexOutOfBoundsException* ie) {
//          return "?";
//        }
}

/**
 * @return The type letter for turnouts
 */
/*public*/ char AbstractProxyLightManager::typeLetter()
{
 return getDefaultManager()->typeLetter();
}

/**
 * @return A system name from a user input, typically a number,
 * from the primary system.
 */
/*public*/ QString AbstractProxyLightManager::makeSystemName(QString s) {
    return getMgr(0)->makeSystemName(s);
}

/** {@inheritDoc} */
//@CheckReturnValue
//@Override
/*public*/ int AbstractProxyLightManager::getObjectCount() {
    int count = 0;
    for (Manager/*<E>*/* m : mgrs) { count += m->getObjectCount(); }
    return count;
}

/*public*/ QStringList AbstractProxyLightManager::getSystemNameArray() {
    //TreeSet<QString> ts = new TreeSet<String>(new SystemNameComparator());
    QSet<QString>* ts = new QSet<QString>();
    for (int i = 0; i<nMgrs(); i++) {
        //ts->add( getMgr(i).getSystemNameList() );
        QStringList snl = getMgr(i)->getSystemNameList();
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
/*public*/ QStringList AbstractProxyLightManager::getSystemNameList() {
    //TreeSet<QString> ts = new TreeSet<String>(new SystemNameComparator());
    QSet<QString>* ts = new QSet<QString>();
    for (int i = 0; i<nMgrs(); i++) {
        //ts.addAll(getMgr(i).getSystemNameList());
        QStringList snl = getMgr(i)->getSystemNameList();
        foreach(QString s, snl)
         ts->insert(s);
    }
    //return new ArrayList<String>(ts);
    QStringList arr = ts->toList();
    return arr;
}

/*protected*/ void AbstractProxyLightManager::updateOrderList() {
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
/*public*/ QStringList AbstractProxyLightManager::getSystemNameAddedOrderList() {
    addedOrderList = QStringList();  // need to start maintaining it
    updateOrderList();
    //return Collections.unmodifiableList(addedOrderList);
    return addedOrderList;
}

/** {@inheritDoc} */
//@Override
//@Deprecated  // will be removed when Manager method is removed due to @Override
//@Nonnull
/*public*/ QList<NamedBean*>* AbstractProxyLightManager::getNamedBeanList() {
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


/*protected*/ void AbstractProxyLightManager::updateNamedBeanSet()
{
 //if (namedBeanSet.isEmpty()) return; // only maintain if requested
 namedBeanSet.clear();
 for (Manager* m : mgrs)
 {
  //namedBeanSet.addAll(m.getNamedBeanSet());
  foreach(NamedBean* bean, m->getNamedBeanSet())
     namedBeanSet.insert(bean);
 }
}

/** {@inheritDoc} */
//@Override
//@Nonnull
/*public*/ /*SortedSet<E>*/QSet<NamedBean*> AbstractProxyLightManager::getNamedBeanSet() {
    namedBeanSet = QSet<NamedBean*>();//new TreeSet<>(new NamedBeanComparator());
    updateNamedBeanSet();
    //return Collections.unmodifiableSortedSet(namedBeanSet);
    QList<NamedBean*> list = namedBeanSet.toList();
    qSort(list.begin(), list.end(), NamedBeanComparator::compare);
    return list.toSet();
}

/**
 * Get a list of all user names.
 */
/*public*/ QStringList AbstractProxyLightManager::getUserNameList()
{
 //TreeSet<QString> ts = new TreeSet<String>(new SystemNameComparator());
 QSet<QString>* ts = new QSet<QString>();
 for (int i = 0; i<nMgrs(); i++)
 {
  //ts.addAll(getMgr(i).getSystemNameList());
  QStringList snl = getMgr(i)->getSystemNameList();
  foreach(QString s, snl)
  {
   AbstractNamedBean* bean = (AbstractNamedBean*)getMgr(i)->getBeanBySystemName(s);
   QString userName = bean->getUserName();
   if(userName != "")
    ts->insert(userName);
  }
 }
 //return new ArrayList<String>(ts);
 QStringList arr = ts->toList();
 return arr;
}

void AbstractProxyLightManager::propertyChange(PropertyChangeEvent */*e*/)
{
 //emit this->propertyChange(e);
}
// initialize logging
/*private*/ /*final*/ /*static*/ Logger* AbstractProxyLightManager::log = LoggerFactory::getLogger("AbstractProxyLightManager");
