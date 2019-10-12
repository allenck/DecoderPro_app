#include "abstractproxymanager.h"
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

AbstractProxyManager::AbstractProxyManager(QObject *parent)
    : AbstractManager(parent)
{
 mgrs = QList<Manager*>();
 internalManager = nullptr;
 defaultManager = nullptr;
 addedOrderList = QStringList();
 log->setDebugEnabled(true);
 listeners = QList<QObject*>();
 propertyListenerList = QVector<PropertyChangeListener*>();
 namedPropertyListenerMap = QMap<QString, QVector<PropertyChangeListener*>* >();
 propertyVetoListenerList = QVector<VetoableChangeListener*> ();
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
/*protected*/ int AbstractProxyManager::nMgrs()
{
 // make sure internal present
 initInternal();
 return mgrs.size();
}

/*protected*/ Manager* AbstractProxyManager::getMgr(int index)
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
/*public*/ QList<Manager*> AbstractProxyManager::getManagerList()
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
/*public*/ QList<Manager*> AbstractProxyManager::getDisplayOrderManagerList() {
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

/*public*/ Manager* AbstractProxyManager::getInternalManager() {
    initInternal();
    return internalManager;
}

/**
 * Returns the set default or, if not present, the internal manager as defacto default
 */
/*public*/ Manager* AbstractProxyManager::getDefaultManager() {
    if (defaultManager != nullptr) return defaultManager;

    return getInternalManager();
}

/*public*/ void AbstractProxyManager::addManager(Manager* m)
{
 // check for already present
 for (Manager* check : mgrs)
 {
  if (m == check) { // can't use contains(..) because of Comparator.equals is on the prefix
      // already present, complain and skip
      log->warn(tr("Manager already present: %1").arg(QString(m->metaObject()->className()))); // NOI18N
      return;
  }
 }
 mgrs.append(static_cast<AbstractManager*>(m));
 if (defaultManager == nullptr) defaultManager = m;  // 1st one is default

 //propertyVetoListenerList.stream().forEach((l) ->
 foreach(VetoableChangeListener*l, propertyVetoListenerList)
 {
             m->addVetoableChangeListener(l);
 }//);
 //propertyListenerList.stream().forEach((l) ->
 foreach(PropertyChangeListener* l, propertyListenerList)
 {
     m->addPropertyChangeListener(l);
 }//);
#if 0
 //namedPropertyVetoListenerMap.entrySet().forEach((e) ->
 foreach(QVector<PropertyChangeListener*> e,  namedPropertyVetoListenerMap.values())
 {
     //e.getValue().forEach((l) -> {
         foreach(PropertyChangeListener*l, e)
         {
         m.addVetoableChangeListener(e.getKey(), l);
     });
 });
 namedPropertyListenerMap.entrySet().forEach((e) -> {
     e.getValue().forEach((l) -> {
         m.addPropertyChangeListener(e.getKey(), l);
     });
 });

#endif
 m->addDataListener(this);
  recomputeNamedBeanSet();

 if (log->isDebugEnabled())
 {
     log->debug(QString("added manager ") + QString(m->metaObject()->className()));
 }
}

/*private*/ Manager* AbstractProxyManager::initInternal()
{
 if (internalManager == nullptr) {
     log->debug("create internal manager when first requested");
     internalManager = makeInternalManager();
 }
 return internalManager;
}

/*abstract protected*/ Manager* AbstractProxyManager::makeInternalManager() const
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
/*public*/ NamedBean* AbstractProxyManager::getNamedBean(QString name)
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
/*public*/ /*@Nonnull*/ QString AbstractProxyManager::normalizeSystemName(/*@Nonnull*/ QString inputName) /*throw (NamedBean::BadSystemNameException)*/ {
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
/*protected*/ NamedBean* AbstractProxyManager::provideNamedBean(QString name)
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
/*abstract protected*/ NamedBean* AbstractProxyManager::makeBean(int /*index*/, QString /*systemName*/, QString /*userName*/) /*const*/
{
// Q_UNUSED(index);
// Q_UNUSED(systemName);
// Q_UNUSED(userName);
//// if(qobject_cast<ProxyReporterManager*>(this)!=NULL)
////  return ProxyReporterManager::makeBean(index, systemName, userName);

 return nullptr; // Should not get here! this should be overriden by the actual class
}

//@Override
/*public*/ NamedBean* AbstractProxyManager::getBeanBySystemName(QString systemName)
{
 // System names can be matched to managers by system and type at front of name
 int index = matchTentative(systemName);
 if (index >= 0) {
     Manager/*<E>*/* m = getMgr(index);
     return m->getBeanBySystemName(systemName);
 }
 log->debug(tr("getBeanBySystemName did not find manager from name %1, defer to default manager").arg(systemName)); // NOI18N
 return getDefaultManager()->getBeanBySystemName(systemName);
}

//@Override
/*public*/ NamedBean* AbstractProxyManager::getBeanByUserName(QString userName)
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
/*public*/ NamedBean* AbstractProxyManager::newNamedBean(QString systemName, QString userName) {
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
}

/*public*/ void AbstractProxyManager::dispose() {
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
/*protected*/ int AbstractProxyManager::matchTentative(QString systemname)
{
 //Q_ASSERT(mgrs->count()> 0);
 for (Manager* m : mgrs)
 {
  QString str = m->getSystemPrefix();
  if ( systemname.startsWith(m->getSystemPrefix()+m->typeLetter()))
  {
   return mgrs.indexOf(m);
  }
 }
 return -1;
}

/**
 * Find the index of a matching manager.
 * Throws IllegalArgumentException if there is no match,
 * here considered to be an error that must be reported.
 */
/*protected*/ int AbstractProxyManager::match(QString systemname) {
    int index = matchTentative(systemname);
    if (index < 0) throw  IllegalArgumentException("System name "+systemname+" failed to match");
    return index;
}

/**
 * Remember a NamedBean Object created outside the manager.
 * <P>
 * Forwards the register request to the matching system
 */
/*public*/ void AbstractProxyManager::Register(NamedBean* s) {
    QString systemName = s->getSystemName();
    getMgr(match(systemName))->Register(s);
}

/**
 * Forget a NamedBean Object created outside the manager.
 * <P>
 * Forwards the deregister request to the matching system
 */
/*public*/ void AbstractProxyManager::deregister(NamedBean* s) {
    QString systemName = s->getSystemName();
    getMgr(match(systemName))->deregister(s);
}

/*public synchronized*/ void AbstractProxyManager::addPropertyChangeListener(PropertyChangeListener* l)
{
 for (int i = 0; i<nMgrs(); i++)
 {
  Manager* mgr = getMgr(i);
  mgr->addPropertyChangeListener(l);
  connect(((AbstractManager*)mgr)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
/*public synchronized*/ void AbstractProxyManager::removePropertyChangeListener(PropertyChangeListener* l)
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
/*public*/ void AbstractProxyManager::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    if (!namedPropertyListenerMap.contains(propertyName)) {
        namedPropertyListenerMap.insert(propertyName,  new QVector<PropertyChangeListener*>());
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
/*public*/ QVector<PropertyChangeListener *> AbstractProxyManager::getPropertyChangeListeners() {
    QVector<PropertyChangeListener*> listeners = QVector<PropertyChangeListener*>(propertyListenerList);
    for (QVector<PropertyChangeListener*>* list : namedPropertyListenerMap.values()) {
        //listeners.addAll(list);
     foreach (PropertyChangeListener* listener, *list) {
      listeners.append(listener);
     }
    }
    return listeners; //new PropertyChangeListener[listeners.size()]);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ QVector<PropertyChangeListener *> AbstractProxyManager::getPropertyChangeListeners(QString propertyName) {
    if (!namedPropertyListenerMap.contains(propertyName)) {
        namedPropertyListenerMap.insert(propertyName,  new QVector<PropertyChangeListener*>());
    }
    QVector<PropertyChangeListener*>* listeners = namedPropertyListenerMap.value(propertyName);
    return *listeners; //new PropertyChangeListener[listeners.size()]);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractProxyManager::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    if (!namedPropertyListenerMap.contains(propertyName)) {
        namedPropertyListenerMap.insert(propertyName, new QVector<PropertyChangeListener*>());
    }
    namedPropertyListenerMap.value(propertyName)->removeOne(listener);
    for (Manager/*<E>*/* m : mgrs) {
        m->removePropertyChangeListener(propertyName, listener);
    }
}
/** {@inheritDoc} */
//@Override
/*public*/ /*synchronized*/ void AbstractProxyManager::addVetoableChangeListener(VetoableChangeListener* l) {
    if (!propertyVetoListenerList.contains(l)) {
        propertyVetoListenerList.append(l);
    }
    for (Manager/*<E>*/ *m : mgrs) {
        m->addVetoableChangeListener(l);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ /*synchronized*/ void AbstractProxyManager::removeVetoableChangeListener(VetoableChangeListener* l) {
    if (propertyVetoListenerList.contains(l)) {
        propertyVetoListenerList.removeOne(l);
    }
    for (Manager/*<E>*/* m : mgrs) {
        m->removeVetoableChangeListener(l);
    }
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractProxyManager::addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
    if (!namedPropertyVetoListenerMap.contains(propertyName)) {
        namedPropertyVetoListenerMap.insert(propertyName, new QVector<VetoableChangeListener*>());
    }
    if (!namedPropertyVetoListenerMap.value(propertyName)->contains(listener)) {
        namedPropertyVetoListenerMap.value(propertyName)->append(listener);
    }
    for (Manager/*<E>*/* m : mgrs) {
        m->addVetoableChangeListener(propertyName, listener);
    }
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ QVector<VetoableChangeListener*> AbstractProxyManager::getVetoableChangeListeners() {
    QList<VetoableChangeListener*> listeners =  QList<VetoableChangeListener*>(propertyVetoListenerList.toList());
    for (QVector<VetoableChangeListener*>* list : namedPropertyVetoListenerMap.values()) {
        //listeners.addAll(list);
     foreach(VetoableChangeListener* l, *list)
      listeners.append(l);
    }
    return listeners.toVector(); //new VetoableChangeListener[listeners.size()]);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ QVector<VetoableChangeListener*> AbstractProxyManager::getVetoableChangeListeners(QString propertyName) {
    if (!namedPropertyVetoListenerMap.contains(propertyName)) {
        namedPropertyVetoListenerMap.insert(propertyName, new QVector<VetoableChangeListener*>());
    }
    QVector<VetoableChangeListener*>* listeners = namedPropertyVetoListenerMap.value(propertyName);
    //return listeners.toArray(new VetoableChangeListener[listeners->size()]);
    return *listeners;
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractProxyManager::removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
    if (!namedPropertyVetoListenerMap.contains(propertyName)) {
        namedPropertyVetoListenerMap.insert(propertyName, new QVector<VetoableChangeListener*>());
    }
    namedPropertyVetoListenerMap.value(propertyName)->removeOne(listener);
    for (Manager/*<E>*/* m : mgrs) {
        m->removeVetoableChangeListener(propertyName, listener);
    }
}

/**
 * @return The system-specific prefix letter for the primary implementation
 */
/*public*/ QString AbstractProxyManager::getSystemPrefix() {
//    try {
      return getMgr(0)->getSystemPrefix();
//        } catch(IndexOutOfBoundsException* ie) {
//          return "?";
//        }
}

//    /**
//     * Provide 1st char of systemPrefix for now
//     * @deprecated
//     */
//    @Deprecated
//    public char systemLetter() {
//        return getSystemPrefix().charAt(0);
//    }

/**
 * @return The type letter for turnouts
 */
/*public*/ char AbstractProxyManager::typeLetter()
{
 return getDefaultManager()->typeLetter();
}

/**
 * @return A system name from a user input, typically a number,
 * from the primary system.
 */
/*public*/ QString AbstractProxyManager::makeSystemName(QString s) {
    return getMgr(0)->makeSystemName(s);
}

/** {@inheritDoc} */
//@CheckReturnValue
//@Override
/*public*/ int AbstractProxyManager::getObjectCount() {
    int count = 0;
    for (Manager/*<E>*/* m : mgrs) { count += m->getObjectCount(); }
    return count;
}
/*public*/ QStringList AbstractProxyManager::getSystemNameArray() {
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
/*public*/ QStringList AbstractProxyManager::getSystemNameList() {
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

/*protected*/ void AbstractProxyManager::updateOrderList() {
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
/*public*/ QStringList AbstractProxyManager::getSystemNameAddedOrderList() {
    addedOrderList = QStringList();  // need to start maintaining it
    updateOrderList();
    //return Collections.unmodifiableList(addedOrderList);
    return addedOrderList;
}

/** {@inheritDoc} */
//@Override
//@Deprecated  // will be removed when Manager method is removed due to @Override
//@Nonnull
/*public*/ QList<NamedBean*>* AbstractProxyManager::getNamedBeanList() {
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


/*protected*/ void AbstractProxyManager::updateNamedBeanSet()
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

/*protected*/ void AbstractProxyManager::recomputeNamedBeanSet() {
        if (namedBeanSet.isEmpty()) return; // only maintain if requested
        namedBeanSet.clear();
        for (Manager/*<E>*/* m : mgrs) {
            namedBeanSet.unite(m->getNamedBeanSet());
        }
    }

/** {@inheritDoc} */
//@Override
//@Nonnull
/*public*/ /*SortedSet<E>*/QSet<NamedBean*> AbstractProxyManager::getNamedBeanSet() {
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
/*public*/ QStringList AbstractProxyManager::getUserNameList()
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

void AbstractProxyManager::propertyChange(PropertyChangeEvent */*e*/)
{
 //emit this->propertyChange(e);
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractProxyManager::addDataListener(/*ManagerDataListener<E>*/QObject* e) {
    if (e != nullptr)
    {
     listeners.append(e);
     ManagerDataListener* listener = (ManagerDataListener*)e;
     connect(this, SIGNAL(notifyContentsChanged(ManagerDataEvent*)), listener, SLOT(contentsChanged(ManagerDataEvent*)));
     connect(this, SIGNAL(notifyIntervalAdded(ManagerDataEvent*)), listener, SLOT(intervalAdded(ManagerDataEvent*)));
     connect(this, SIGNAL(notifyIntervalRemoved(ManagerDataEvent*)), listener, SLOT(intervalRemoved(ManagerDataEvent*)));
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractProxyManager::removeDataListener(/*ManagerDataListener<E>*/QObject* e) {
    if (e != nullptr)
    {
     listeners.removeOne(e);
     disconnect(this, SIGNAL(notifyContentsChanged(ManagerDataEvent*)), (ManagerDataListener*)e, SLOT(contentsChanged(Manager::ManagerDataEvent*)));
     disconnect(this, SIGNAL(notifyIntervalAdded(ManagerDataEvent*)), (ManagerDataListener*)e, SLOT(intervalAdded(Manager::ManagerDataEvent*)));
     disconnect(this, SIGNAL(notifyIntervalRemoved(ManagerDataEvent*)), (ManagerDataListener*)e, SLOT(intervalRemoved(Manager::ManagerDataEvent*)));
    }
}


/**
 * {@inheritDoc}
 * From Manager.ManagerDataListener, receives notifications from underlying
 * managers.
 */
//@Override
/*public*/ void AbstractProxyManager::contentsChanged(Manager::ManagerDataEvent/*<E>*/* e) {
}

/**
 * {@inheritDoc}
 * From Manager.ManagerDataListener, receives notifications from underlying
 * managers.
 */
//@Override
/*public*/ void AbstractProxyManager::intervalAdded(AbstractProxyManager::ManagerDataEvent/*<E>*/* e) {
    if (!namedBeanSet.isEmpty() && e->getIndex0() == e->getIndex1()) {
        // just one element added, and we have the object reference
        namedBeanSet.insert(e->getChangedBean());
    } else {
        recomputeNamedBeanSet();
    }

    if (muted) return;

    int offset = 0;
    for (Manager/*<E>*/* m : mgrs) {
        if (m == e->getSource()) break;
        offset += m->getObjectCount();
    }

    ManagerDataEvent/*<E>*/* eOut = new ManagerDataEvent/*<E>*/(this, Manager::ManagerDataEvent::INTERVAL_ADDED, e->getIndex0()+offset, e->getIndex1()+offset, e->getChangedBean());

//    for (ManagerDataListener<E> m : listeners) {
//        m.intervalAdded(eOut);
//    }
    emit notifyIntervalAdded(eOut);
}

/**
 * {@inheritDoc}
 * From Manager.ManagerDataListener, receives notifications from underlying
 * managers.
 */
//@Override
/*public*/ void AbstractProxyManager::intervalRemoved(AbstractProxyManager::ManagerDataEvent/*<E>*/* e) {
    recomputeNamedBeanSet();

    if (muted) return;

    int offset = 0;
    for (Manager/*<E>*/* m : mgrs) {
        if (m == e->getSource()) break;
        offset += m->getObjectCount();
    }

    ManagerDataEvent/*<E>*/* eOut = new ManagerDataEvent/*<E>*/(this, Manager::ManagerDataEvent::INTERVAL_REMOVED, e->getIndex0()+offset, e->getIndex1()+offset, e->getChangedBean());

//    for (ManagerDataListener<E> m : listeners) {
//        m.intervalRemoved(eOut);
//    }
    emit notifyIntervalRemoved(eOut);
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractProxyManager::setDataListenerMute(bool m) {
    if (muted && !m)
    {
        // send a total update, as we haven't kept track of specifics
        ManagerDataEvent/*<E>*/* e = new ManagerDataEvent/*<E>*/(this, ManagerDataEvent::CONTENTS_CHANGED, 0, getObjectCount()-1, nullptr);
//        for (ManagerDataListener<E> listener : listeners) {
//            listener.contentsChanged(e);
//        }
        emit notifyContentsChanged(e);
    }
    this->muted = m;
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* AbstractProxyManager::log = LoggerFactory::getLogger("AbstractProxyManager");
