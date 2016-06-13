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

AbstractProxyManager::AbstractProxyManager(QObject *parent)
    : AbstractManager(parent)
{
 mgrs = new /*java.util.ArrayList*/QList<AbstractManager*>();
 internalManager = NULL;
 registerSelf();
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
    return mgrs->size()+1;
}

/*protected*/ AbstractManager* AbstractProxyManager::getMgr(int index)
{
 if (index < mgrs->size())
  return mgrs->value(index);
 else
  if (index == mgrs->size())
   return getInternal();
  else throw new IllegalArgumentException("illegal index "+index);
}

/**
 * Returns a list of all managers, including the
 * internal manager.  This is not a live list.
 */
/*public*/ QList<Manager*> AbstractProxyManager::getManagerList()
{
 //@SuppressWarnings("unchecked")
 //QList<Manager*> retval = (QList<Manager*>)mgrs->clone();
 QList<Manager*> retval;
 foreach(AbstractManager* m, *mgrs)
  retval.append((Manager*)m);
 retval.append((Manager*)getInternal());
 return retval;
}

/*public*/ void AbstractProxyManager::addManager(Manager* m)
{
 mgrs->append((AbstractManager*)(m));
 AbstractManager* am = (AbstractManager*)m;
 //if(log.isDebugEnabled()) log.debug(tr("added manager ") +((AbstractManager*)m)->objectName());
 connect(am->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));
}

/*private*/ AbstractManager* AbstractProxyManager::getInternal()
{
 if (internalManager == NULL)
 {
  if(qobject_cast<ProxyReporterManager*>(this)!=NULL)
  {
   ProxyReporterManager* m = (ProxyReporterManager*)this;
   internalManager = m->makeInternalManager();
  }
  else
  if(qobject_cast<ProxyTurnoutManager*>(this)!=NULL)
  {
   ProxyTurnoutManager* m = (ProxyTurnoutManager*)this;
   internalManager = m->makeInternalManager();
  }
  else
  if(qobject_cast<ProxySensorManager*>(this)!=NULL)
  {
   ProxySensorManager* m = (ProxySensorManager*)this;
   internalManager = m->makeInternalManager();
  }
  else
  if(qobject_cast<ProxyLightManager*>(this)!=NULL)
  {
   ProxyLightManager* m = (ProxyLightManager*)this;
   internalManager = m->makeInternalManager();
  }
  else
   internalManager = makeInternalManager();
 }
 connect(internalManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));
 return internalManager;
}

/*abstract protected*/ AbstractManager* AbstractProxyManager::makeInternalManager() const
{
 return NULL;
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
 if (t != NULL) return t;
 return getBeanBySystemName(name);
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
 * @return Never NULL under normal circumstances
 */
/*protected*/ NamedBean* AbstractProxyManager::provideNamedBean(QString name)
{
 NamedBean* t = getNamedBean(name);
 if (t!=NULL) return t;
 // Doesn't exist. If the systemName was specified, find that system
 int index = matchTentative(name);
 if (index >= 0) return makeBean(index, name, "");
 log.debug("Did not find manager for name "+name+", defer to default");
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

 return NULL; // Should not get here! this should be overriden by the actual class
#if 0
 AbstractManager* mgr = mgrs->at(index);
 if(qobject_cast<AbstractTurnoutManager*>(mgr)!=NULL)
 {
  return (NamedBean*) ((AbstractTurnoutManager*)mgr)->newTurnout(systemName, userName);
 }
 else if(qobject_cast<AbstractSensorManager*>(mgr)!=NULL)
 {
  return (NamedBean*) ((AbstractSensorManager*)mgr)->newSensor(systemName, userName);
 }
 else if(qobject_cast<AbstractLightManager*>(mgr)!=NULL)
 {
  return (NamedBean*) ((AbstractLightManager*)mgr)->newLight(systemName, userName);
 }
 else if(qobject_cast<AbstractReporterManager*>(mgr)!=NULL)
 {
  return (NamedBean*) ((AbstractReporterManager*)mgr)->newReporter(systemName, userName);
 }
 return NULL;
#endif
}


/*public*/ NamedBean* AbstractProxyManager::getBeanBySystemName(QString systemName)
{
 NamedBean* t = NULL;
 for (int i=0; i<nMgrs(); i++)
 {
  AbstractManager* mgr = getMgr(i);
  if(mgr == NULL) return NULL;
  t = (NamedBean*)mgr->getInstanceBySystemName(systemName);
  if (t!=NULL)
   return t;
 }
 return NULL;
}

/*public*/ NamedBean* AbstractProxyManager::getBeanByUserName(QString userName)
{
 NamedBean* t = NULL;
 for (int i=0; i<nMgrs(); i++)
 {
  t = (NamedBean*)getMgr(i)->getInstanceByUserName(userName);
  if (t!=NULL) return t;
 }
 return NULL;
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
    // if the systemName is specified, find that system
    int i = matchTentative(systemName);
    if (i >= 0)
        return makeBean(i, systemName, userName);

    // did not find a manager, allow it to default to the primary
    log.debug("Did not find manager for system name "+systemName+", delegate to primary");
    int iI = nMgrs()-1;
    return makeBean(iI, systemName, userName);
}

/*public*/ void AbstractProxyManager::dispose() {
    for (int i=0; i<mgrs->size(); i++)
        mgrs->value(i)->dispose();
    mgrs->clear();
    if (internalManager != NULL) internalManager->dispose(); // don't make if not made yet
}

/**
 * Find the index of a matching manager.
 * Returns -1 if there is no match, which is not considered an
 * error
 */
/*protected*/ int AbstractProxyManager::matchTentative(QString systemname)
{
 Q_ASSERT(mgrs->count()> 0);
 for (int i = 0; i<nMgrs(); i++)
 {
  if ( systemname.startsWith(((AbstractProxyManager*)getMgr(i))->getSystemPrefix()+((AbstractProxyManager*)getMgr(i))->typeLetter()))
  {
   return i;
  }
  //return -1;
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
    if (index < 0) throw new IllegalArgumentException("System name "+systemname+" failed to match");
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
  AbstractManager* mgr = getMgr(i);
  mgr->addPropertyChangeListener(l);
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
/*public synchronized*/ void AbstractProxyManager::removePropertyChangeListener(PropertyChangeListener* l)
{
 for (int i = 0; i<nMgrs(); i++)
 {
  AbstractManager* mgr = getMgr(i);
  mgr->addPropertyChangeListener(l);
  disconnect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
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
 AbstractManager* mgr = getMgr(0);
 if(qobject_cast<ProxySensorManager*>(this)!=NULL)
     return ((AbstractSensorManager*)mgr)->typeLetter();
 return mgr->typeLetter();
}

/**
 * @return A system name from a user input, typically a number,
 * from the primary system.
 */
/*public*/ QString AbstractProxyManager::makeSystemName(QString s) {
    return getMgr(0)->makeSystemName(s);
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

void AbstractProxyManager::on_propertyChange(PropertyChangeEvent *e)
{
 emit this->propertyChange(e);
}
    // initialize logging
    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractProxyManager.class.getName());
