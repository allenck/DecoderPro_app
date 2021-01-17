#include "abstractmanager.h"
#include <QStringList>
#include "instancemanager.h"
#include "propertychangesupport.h"
#include "configxmlmanager.h"
#include "abstractcatalogtree.h"
#include "systemnamecomparator.h"
#include "jmriconfigurationmanager.h"
#include "vetoablechangesupport.h"
#include "namedbeancomparator.h"
#include "namedbean.h"
#include "vptr.h"

/**
 * Abstract partial implementation for all Manager-type classes.
 * <P>
 * Note that this does not enforce any particular system naming convention
 * at the present time.  They're just names...
 *
 * @author      Bob Jacobsen Copyright (C) 2003
 * @version	$Revision: 19272 $
 */
AbstractManager::AbstractManager(QObject *parent) : Manager(nullptr, parent)
{
  Q_UNUSED(parent);
  log = new Logger("AbstractManager");
 _tsys = new QHash<QString, NamedBean*>;   // stores known Turnout instances by system name
 _tuser = new QHash<QString, NamedBean*>;   // stores known Turnout instances by user name
 _beans = QSet<NamedBean*>( _beans);
 //registerSelf(); // ACK this fumction must be called by the subclass in order to work!
 lastAutoNamedBeanRef = QAtomicInteger<int>(0);

 pcs = new PropertyChangeSupport((QObject*)this);
 vcs = new VetoableChangeSupport((QObject*)this);
 listeners = QList<QObject*>();
}

AbstractManager::AbstractManager(SystemConnectionMemo* memo, QObject *parent) : Manager(memo,parent)
{
  Q_UNUSED(parent);
 this->memo = memo;
  log = new Logger("AbstractManager");
 _tsys = new QHash<QString, NamedBean*>;   // stores known Turnout instances by system name
 _tuser = new QHash<QString, NamedBean*>;   // stores known Turnout instances by user name
 _beans = QSet<NamedBean*>( _beans);

 //registerSelf(); // ACK this fumction must be called by the subclass in order to work!

 pcs = new PropertyChangeSupport((QObject*)this);
 vcs = new VetoableChangeSupport((QObject*)this);
}

//abstract public class AbstractManager
//    implements Manager, java.beans.PropertyChangeListener {

//    public AbstractManager(){
//        registerSelf();
//    }

    /*public AbstractManager(int order) {
        // register the result for later configuration
        xmlorder = order;
        registerSelf();
    }*/

/**
 * By default, register this manager to store as configuration
 * information.  Override to change that.
 **/
/*protected*/ void AbstractManager::registerSelf()
{
  log->debug(tr("registerSelf for config of type %1").arg(this->metaObject()->className()));
  ConfigureManager* cm;
  cm = (ConfigureManager*)InstanceManager::getOptionalDefault("ConfigureManager");
  if (cm != NULL) {
      cm->registerConfig(this, getXMLOrder());
      log->debug(tr("registering for config of type %1").arg(this->metaObject()->className()));
  }
}

///*abstract*/ /*public*/ int AbstractManager::getXMLOrder() { return 0;}



/** {@inheritDoc} */
//@Override
/*public*/ SystemConnectionMemo* AbstractManager::getMemo() const {
    return memo;
}

///** {@inheritDoc} */
////@Override
////abstract public int getXMLOrder();
///*public*/ QString AbstractManager::makeSystemName(/*@Nonnull*/ QString s)
//{
// Manager::makeSystemName(s);
//}
///*public*/ QString AbstractManager::makeSystemName(/*@Nonnull*/ QString s, bool logErrors)
//{
// Manager::makeSystemName(s, logErrors);
//}

/** {@inheritDoc} */
//@Override
//@Nonnull
/*public*/ QString AbstractManager::makeSystemName(/*@Nonnull*/ QString s, bool logErrors, QLocale locale) const {
    try {
        return Manager::makeSystemName(s, logErrors, locale);
    } catch (IllegalArgumentException ex) {
        if (logErrors || log->isTraceEnabled()) {
            log->error(tr("Invalid system name for %1: %2").arg(getBeanTypeHandled()).arg(ex.getMessage()));
        }
        throw ex;
    }
}

//    /**
//     * Provide access to deprecated method temporarilly
//     * @deprecated 2.9.5 Use getSystemPrefix
//     */
//    @Deprecated
//    public char systemLetter() {
//        return getSystemPrefix().charAt(0);
//    }

// abstract methods to be extended by subclasses
// to free resources when no longer used
void AbstractManager::dispose()
{
    if (((ConfigureManager*)InstanceManager::getOptionalDefault("ConfigureManager"))!= nullptr)
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->deregister((QObject*)this);
    _tsys = new QHash<QString, NamedBean*>();   // stores known Turnout instances by system name
    _tuser = new QHash<QString, NamedBean*>();   // stores known Turnout instances by user name

    _beans.clear();
    _tsys->clear();
    _tuser->clear();

}


/**
 * Locate an instance based on a system name.  Returns NULL if no
 * instance already exists.  This is intended to be used by
 * concrete classes to implement their getBySystemName method.
 * We can't call it that here because Java doesn't have polymorphic
 * return types.
 * @return requested Turnout object or NULL if none exists
 */
QObject* AbstractManager::getInstanceBySystemName(QString systemName)
{
 return _tsys->value(systemName);
}

/**
 * Locate an instance based on a user name.  Returns NULL if no
 * instance already exists. This is intended to be used by
 * concrete classes to implement their getBySystemName method.
 * We cant call it that here because Java doesn't have polymorphic
 * return types.
 * @return requested Turnout object or NULL if none exists
 */
QObject* AbstractManager::getInstanceByUserName(QString userName) {
    return _tuser->value(userName);
}

/** {@inheritDoc} */
////@Override
///*public*/ NamedBean* AbstractManager::getBySystemName(/*@Nonnull*/ QString systemName) const {
//    return _tsys->value(systemName);
//}
    /**
     * Locate an instance based on a system name.  Returns NULL if no
     * instance already exists.
     * @param systemName System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/ NamedBean* AbstractManager::getBeanBySystemName(QString systemName)const{
        return _tsys->value(systemName);
    }

//    /**
//     * Locate an instance based on a user name.  Returns NULL if no
//     * instance already exists.
//     * @param userName System Name of the required NamedBean
//     * @return requested NamedBean object or NULL if none exists
//     */
//    /*public*/ NamedBean* AbstractManager::getBeanByUserName(QString userName) const{
//        return _tuser->value(userName);
//    }

//    /** {@inheritDoc} */
////    @Override
////    @CheckForNull
//    /*public*/ NamedBean* AbstractManager::getByUserName(/*@Nonnull*/ QString userName) const{
//        QString normalizedUserName = NamedBean::normalizeUserName(userName);
//        return !normalizedUserName.isNull() ? _tuser->value(normalizedUserName) : nullptr;
//    }

    /**
     * Locate an instance based on a name.  Returns NULL if no
     * instance already exists.
     * @param name System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/ NamedBean* AbstractManager::getNamedBean(QString name) const{
        NamedBean* b = getBeanByUserName(name);
        if(b!=NULL) return b;
        return getBeanBySystemName(name);
    }

/**
 * Remember a NamedBean Object created outside the manager.
 * <P>
 * The non-system-specific SignalHeadManagers
 * use this method extensively.
 */
/*public*/ void AbstractManager::Register(NamedBean* s) const
{
#if 0
 QString systemName;
 QString userName;
 QString cName = QString(s->metaObject()->className());
// if(qobject_cast<AbstractCatalogTree*>(s))
// {
//  systemName = ((AbstractCatalogTree*)s)->getSystemName();
//  Q_ASSERT(!systemName.isEmpty());
//  userName = ((AbstractCatalogTree*)s)->getUserName();
// }
// else

 systemName = s->getSystemName();
 NamedBean* existingBean = getBeanBySystemName(systemName);

 Q_ASSERT(!systemName.isEmpty());
 _tsys->insert(systemName, s);
  userName = s->getUserName();

 if (userName != NULL) _tuser->insert(userName, s);
 firePropertyChange("length", QVariant(), /*Integer.valueOf*/(_tsys->size()));
 // listen for name and state changes to forward
 s->addPropertyChangeListener((PropertyChangeListener*)this, QString(""), QString("Manager"));
 
 if(qobject_cast<TreeModel*>(s) != NULL)
 {
  connect((AbstractCatalogTree*)s, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else {
 AbstractNamedBean* ab = (AbstractNamedBean*)s;
 connect(ab->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}
    emit beanCreated(s);
#endif
  QString systemName = s->getSystemName();
  Q_ASSERT(!systemName.isEmpty());
  NamedBean* existingBean = getBeanBySystemName(systemName);
  if (existingBean != nullptr)
  {
   if (s == existingBean)
   {
       log->debug(tr("the named bean is registered twice: %1").arg(systemName));
   }
   else {
       log->error(tr("systemName is already registered: %1").arg(systemName));
       throw  NamedBean::DuplicateSystemNameException("systemName is already registered: " + systemName);
   }
  }
  else
  {
      // Check if the manager already has a bean with a system name that is
      // not equal to the system name of the new bean, but there the two
      // system names are treated as the same. For example LT1 and LT01.
      if (_beans.contains(s)) {
          //final AtomicReference<String> oldSysName = new AtomicReference<>();
       QSet<QString> oldSysName = QSet<QString>();
          //NamedBeanComparator<NamedBean*> c = new NamedBeanComparator<NamedBean*>();
       NamedBeanComparator<NamedBean*>* c = new NamedBeanComparator<NamedBean*>();

          //_beans.forEach((NamedBean t) ->
          foreach (NamedBean* t, _beans)
          {
              if (c->compare(s, t) == 0) {
                  oldSysName.insert(t->getSystemName());
              }
          }//);
//          if (!systemName.equals(oldSysName.get())) {
           if(oldSysName.contains(systemName))
           {
              QString msg = tr("systemName is already registered. Current system name: %1. New system name: %2").arg(
                      systemName).arg(systemName);
              log->error(msg);
              throw  NamedBean::DuplicateSystemNameException(msg);
          }
      }
  }

  // clear caches
//  cachedSystemNameArray = null;
//  cachedSystemNameList = null;
//  cachedNamedBeanList = null;

  // save this bean
  _beans.insert(s);
  _tsys->insert(systemName, s);
  registerUserName(s);

  // notifications
  int position = getPosition(s);
//  fireDataListenersAdded(position, position, s);
  fireIndexedPropertyChange("beans", position, QVariant(), VPtr<NamedBean>::asQVariant(s));
  firePropertyChange("length", QVariant(), _beans.size());
  // listen for name and state changes to forward
  s->addPropertyChangeListener((PropertyChangeListener*)this);
  AbstractNamedBean* ab = (AbstractNamedBean*)s;
  connect(ab->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

}
  // not efficient, but does job for now
/*private*/ int AbstractManager::getPosition(NamedBean* s) const{
    int position = 0;
    QSetIterator<NamedBean*> iter(_beans);
    while (iter.hasNext()) {
        if (s == iter.next()) return position;
        position++;
    }
    return -1;
}

/**
 * Invoked by {@link #register(NamedBean)} to register the user name of the
 * bean.
 *
 * @param s the bean to register
 */
/*protected*/ void AbstractManager::registerUserName(NamedBean *s) const {
    QString userName = s->getUserName();
    if (userName == "") {
        return;
    }

    handleUserNameUniqueness(s);
    // since we've handled uniqueness,
    // store the new bean under the name
    _tuser->insert(userName, s);
}

/**
 * Invoked by {@link #registerUserName(NamedBean)} to ensure uniqueness of
 * the NamedBean during registration.
 *
 * @param s the bean to register
 */
/*protected*/ void AbstractManager::handleUserNameUniqueness(NamedBean* s) const {
    QString userName = s->getUserName();
    if (userName != "") {
        // enforce uniqueness of user names
        // by setting username to null in any existing bean with the same name
        // Note that this is not a "move" operation for the user name
        if (_tuser->value(userName) != nullptr && _tuser->value(userName) != s) {
            _tuser->value(userName)->setUserName("");
        }
    }
}

/**
 * Forget a NamedBean Object created outside the manager.
 * <P>
 * The non-system-specific RouteManager
 * uses this method.
 */
/*public*/ void AbstractManager::deregister(NamedBean* s)const{
 int position = getPosition(s);
 // clear caches
// cachedSystemNameArray = null;
// cachedSystemNameList = null;
// cachedNamedBeanList = null;

 // stop listening for user name changes
    s->removePropertyChangeListener((PropertyChangeListener*)this);

    // remove bean from local storage
    QString systemName = s->getSystemName();
    _beans.remove(s);
    _tsys->remove(systemName);
    QString userName = s->getUserName();
    if (userName != "")
     _tuser->remove(userName);
//    fireDataListenersRemoved(position, position, s);
    fireIndexedPropertyChange("beans", position, VPtr<NamedBean>::asQVariant(s), QVariant());
    firePropertyChange("length", QVariant(), /*Integer.valueOf*/(_tsys->size()));
    // listen for name and state changes to forward
//    emit beanDeleted(s);
}

/**
 * The PropertyChangeListener interface in this class is
 * intended to keep track of user name changes to individual NamedBeans.
 * It is not completely implemented yet. In particular, listeners
 * are not added to newly registered objects.
 *
 * @param e the event
 */
/*public*/ void AbstractManager::propertyChange(PropertyChangeEvent* e)
{
 if(e->getPropertyName() == "length")
  firePropertyChange(e->getPropertyName(), e->getOldValue(), e->getNewValue());

 if (e->getPropertyName() == ("UserName"))
 {
     QString old = e->getOldValue().toString();  // previous user name
     QString now = e->getNewValue().toString();  // current user name
//     try { // really should always succeed
         QObject* t = e->getSource();
         if (old != nullptr) {
             _tuser->remove(old); // remove old name for this bean
         }
         if (now != nullptr) {
             // was there previously a bean with the new name?
             if (_tuser->value(now) != nullptr && _tuser->value(now) != t) {
                 // If so, clear. Note that this is not a "move" operation
                 _tuser->value(now)->setUserName("");
             }

             _tuser->insert(now, (NamedBean*)t); // put new name for this bean
         }
//     } catch (ClassCastException ex) {
//         log.error("Received event of wrong type {}", e.getSource().getClass().getName(), ex);
//     }

     // called DisplayListName, as DisplayName might get used at some point by a NamedBean
     firePropertyChange("DisplayListName", old, now); //IN18N
 }
}

/** {@inheritDoc} */
//@Override
//@CheckReturnValue
/*public*/ int AbstractManager::getObjectCount() { return _beans.size();                                }

QStringList AbstractManager::getSystemNameArray()
{
 QStringList arr;// = new QStringList();
 QStringListIterator en(_tsys->keys());
 int i=0;
 while (en.hasNext())
 {
  arr.append(en.next());
  i++;
 }
//        java.util.Arrays.sort(arr
 //arr.sort();
 return arr;
}

QStringList AbstractManager::getSystemNameList()
{
    QStringList arr; // =  QList<QString>();
    QStringList out;// = new QStringList();
//    Enumeration<String> en = _tsys.keys();
    QHashIterator<QString, NamedBean*> en(*_tsys);
    int i=0;
    while (en.hasNext())
    {
     //arr[i] = en.nextElement();
     en.next();
     arr.append(en.key());
     i++;
    }
// TODO;   make arr QMap //jmri.util.StringUtil.sort(arr);
    qSort(arr.begin(), arr.end(), SystemNameComparator::compare);
    for (i=0; i<arr.length(); i++)
     out.append(arr[i]);
    return out;
}

/*public*/ QList<NamedBean*> *AbstractManager::getNamedBeanList() {
        return new QList<NamedBean*>(_tsys->values());
}

NamedBeanComparator<NamedBean*> comparator = NamedBeanComparator<NamedBean*>();

bool sortLessThanconst( NamedBean* s1,  NamedBean* s2)
{
  //NamedBeanComparator<NamedBean*> comparator = NamedBeanComparator<NamedBean*>();
 return comparator.compare(s1, s2) < 0;
}
/** {@inheritDoc} */
//@Override
/*public*/ /*SortedSet<E>*/QSet<NamedBean*> AbstractManager::getNamedBeanSet() {
    //return Collections.unmodifiableSortedSet(_beans);
 //return QList<NamedBean*>(_tsys->values().toSet());
 QList<NamedBean*> list = QList<NamedBean*>(_tsys->values());
 //NamedBeanComparator<NamedBean*> comparator = NamedBeanComparator<NamedBean*>();
 qSort(list.begin(), list.end(), sortLessThanconst);
 return list.toSet();
}

QStringList AbstractManager::AbstractManager::getUserNameList()
{
    QStringList arr;// = new QStringList();
    QStringList out;// = new QStringList();
//    Enumeration<String> en = _tsys.keys();
    QHashIterator<QString, NamedBean*> en(*_tuser);
    int i=0;
    while (en.hasNext())
    {
     //arr[i] = en.nextElement();
     en.next();
     arr.append(en.key());
     i++;
    }
// TODO;   make arr QMap //jmri.util.StringUtil.sort(arr);
    for (i=0; i<arr.length(); i++) out.append(arr[i]);
    return out;
}

/*public synchronized */void AbstractManager::addPropertyChangeListener(PropertyChangeListener* l)
{
 pcs->addPropertyChangeListener(l);
 //connect(l, SIGNAL(signalPropertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public synchronized */void AbstractManager::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractManager::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    pcs->addPropertyChangeListener(propertyName, listener);
}

/*public*/ QVector<PropertyChangeListener *> AbstractManager::getPropertyChangeListeners()
{
 return pcs->getPropertyChangeListeners();
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ QVector<PropertyChangeListener*> AbstractManager::getPropertyChangeListeners(QString propertyName) {
    return pcs->getPropertyChangeListeners(propertyName);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractManager::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    pcs->removePropertyChangeListener(propertyName, listener);
}

void AbstractManager::firePropertyChange(QString p, QVariant old, QVariant n) const
{ pcs->firePropertyChange(p,old,n);}

void AbstractManager::fireIndexedPropertyChange(QString p, int pos, QVariant old, QVariant n) const
{
 pcs->fireIndexedPropertyChange(p,pos,old,n);
}

QHash<QString, NamedBean*>* AbstractManager::getSystemNameHash()
{
 return _tsys;
}


/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ /*synchronized*/ void AbstractManager::addVetoableChangeListener(VetoableChangeListener* l) {
    vcs->addVetoableChangeListener(l);
    //connect(InstanceManager::sensorManagerInstance()->vcs, SIGNAL(vetoablePropertyChange(PropertyChangeEvent*)), this, SLOT(vetoableChange(PropertyChangeEvent*)));

}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ /*synchronized*/ void AbstractManager::removeVetoableChangeListener(VetoableChangeListener* l) {
    vcs->removeVetoableChangeListener(l);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractManager::addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
    vcs->addVetoableChangeListener(propertyName, listener);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ QVector<VetoableChangeListener*> AbstractManager::getVetoableChangeListeners() {
    return vcs->getVetoableChangeListeners();
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ QVector<VetoableChangeListener*> AbstractManager::getVetoableChangeListeners(QString propertyName) {
    return vcs->getVetoableChangeListeners(propertyName);
}

/** {@inheritDoc} */
//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractManager::removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
    vcs->removeVetoableChangeListener(propertyName, listener);
}

/**
 * Method to inform all registered listerners of a vetoable change. If the
 * propertyName is "CanDelete" ALL listeners with an interest in the bean
 * will throw an exception, which is recorded returned back to the invoking
 * method, so that it can be presented back to the user. However if a
 * listener decides that the bean can not be deleted then it should throw an
 * exception with a property name of "DoNotDelete", this is thrown back up
 * to the user and the delete process should be aborted.
 *
 * @param p   The programmatic name of the property that is to be changed.
 *            "CanDelete" will enquire with all listerners if the item can
 *            be deleted. "DoDelete" tells the listerner to delete the item.
 * @param old The old value of the property.
 * @param n   The new value of the property.
 * @throws PropertyVetoException - if the recipients wishes the delete to be
 *                               aborted.
 */
//@OverridingMethodsMustInvokeSuper
/*protected*/ void AbstractManager::fireVetoableChange(QString p, QVariant old, QVariant n) /*throws PropertyVetoException*/
{
    PropertyChangeEvent* evt = new PropertyChangeEvent(this, p, old, n);
#if 0
    if (p ==("CanDelete"))
    { //IN18N
        QString message;// = new StringBuilder();
        for (VetoableChangeListener vc : vcs.getVetoableChangeListeners()) {
            try {
                vc.vetoableChange(evt);
            } catch (PropertyVetoException e) {
                if (e.getPropertyChangeEvent().getPropertyName().equals("DoNotDelete")) { //IN18N
                    log.info(e.getMessage());
                    throw e;
                }
                message.append(e.getMessage());
                message.append("<hr>"); //IN18N
            }
        }
        throw new PropertyVetoException(message.toString(), evt);
    } else {
        try {
            vcs.fireVetoableChange(evt);
        } catch (PropertyVetoException e) {
            log.error("Change vetoed.", e);
        }
    }
#endif
    emit vetoablePropertyChange(evt);
}

//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractManager::vetoableChange(PropertyChangeEvent* evt) //throw PropertyVetoException
{
#if 1 // TODO:
 if ("CanDelete" == (evt->getPropertyName())) { //IN18N
     QString message;// = new StringBuilder();
     message.append(tr("Found in the following <b>%1s</b>").arg(getBeanTypeHandled()))
             .append("<ul>");
     bool found = false;
     for (NamedBean* nb : _beans) {
         try {
             nb->vetoableChange(evt);
         } catch (PropertyVetoException e) {
             if (e.getPropertyChangeEvent()->getPropertyName() == ("DoNotDelete")) { //IN18N
                 throw e;
             }
             found = true;
             message.append("<li>")
                     .append(e.getMessage())
                     .append("</li>");
         }
     }
     message.append("</ul>")
             .append(tr("It will be removed from the %1s").arg(getBeanTypeHandled()));
     if (found) {
         throw  PropertyVetoException(message, evt);
     }
 } else {
     for (NamedBean* nb : _beans) {
         try {
             nb->vetoableChange(evt);
         } catch (PropertyVetoException e) {
             throw e;
         }
     }
 }
#endif
}
/**
 * {@inheritDoc}
 *
 * @return {@link jmri.Manager.NameValidity#INVALID} if system name does not
 *         start with
 *         {@link #getSystemNamePrefix()}; {@link jmri.Manager.NameValidity#VALID_AS_PREFIX_ONLY}
 *         if system name equals {@link #getSystemNamePrefix()}; otherwise
 *         {@link jmri.Manager.NameValidity#VALID} to allow Managers that do
 *         not perform more specific validation to be considered valid.
 */
//@Override
/*public*/ AbstractManager::NameValidity AbstractManager::validSystemNameFormat(QString systemName) const {
 if (getSystemNamePrefix() == (systemName)) {
     return NameValidity::VALID_AS_PREFIX_ONLY;
 }
// return getSystemNamePrefix() == (systemName)
//            ? NameValidity::VALID_AS_PREFIX_ONLY
//            : systemName.startsWith(getSystemNamePrefix())
//            ? NameValidity::VALID
//            : NameValidity::INVALID;
 return systemName.startsWith(getSystemNamePrefix()) ? NameValidity::VALID : NameValidity::INVALID;

}

/**
 * {@inheritDoc}
 *
 * The implementation in {@link AbstractManager} should be final, but is not
 * for four managers that have arbitrary prefixes.
 */
//@Override
/*public*/ /*final*/ QString AbstractManager::getSystemPrefix() const {
   QString prefix =  memo->getSystemPrefix();
   return prefix;
}

/**
 * Enforces, and as a user convenience converts to, the standard form for a
 * system name for the NamedBeans handled by this manager.
 *
 * @param inputName System name to be normalized
 * @throws NamedBean.BadSystemNameException If the inputName can't be
 *                                          converted to normalized form
 * @return A system name in standard normalized form
 */
 //@CheckReturnValue
 //@Override
 //@Nonnull
/*public*/ QString AbstractManager::normalizeSystemName(/*@Nonnull*/ QString inputName) const //throws NamedBean.BadSystemNameException
{
    return inputName;
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractManager::addDataListener(/*ManagerDataListener<E>*/QObject* e) {
    if (e != nullptr) listeners.append(e);
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractManager::removeDataListener(/*ManagerDataListener<E>*/QObject* e) {
    if (e != nullptr) listeners.removeOne(e);
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractManager::setDataListenerMute(bool m) {
    if (muted && !m) {
        // send a total update, as we haven't kept track of specifics
        ManagerDataEvent/*<E>*/* e = new ManagerDataEvent(this, ManagerDataEvent::CONTENTS_CHANGED, 0, getObjectCount()-1, nullptr);
//        for (ManagerDataListener<E> listener : listeners) {
//            listener.contentsChanged(e);
//        }
        emit notifyContentsChanged(e);
    }
    this->muted = m;
}

/*protected*/ void AbstractManager::fireDataListenersAdded(int start, int end, NamedBean* changedBean) {
    if (muted) return;
    ManagerDataEvent/*<E>*/* e = new ManagerDataEvent(this, ManagerDataEvent::INTERVAL_ADDED, start, end, changedBean);
//    for (ManagerDataListener<E> m : listeners) {
//        m.intervalAdded(e);
//    }
    emit notifyIntervalAdded(e);
}
/*protected*/ void AbstractManager::fireDataListenersRemoved(int start, int end, NamedBean* changedBean) {
    if (muted) return;
    ManagerDataEvent/*<E>*/* e = new ManagerDataEvent(this, ManagerDataEvent::INTERVAL_REMOVED, start, end, changedBean);
//    for (ManagerDataListener<E> m : listeners) {
//        m.intervalRemoved(e);
//    }
    emit notifyIntervalRemoved(e);
}

/*public*/ void AbstractManager::updateAutoNumber(QString systemName) const{
    /* The following keeps track of the last created auto system name.
     currently we do not reuse numbers, although there is nothing to stop the
     user from manually recreating them */
    if (systemName.startsWith(getSystemNamePrefix() + ":AUTO:")) {
        bool bok;
            int autoNumber = systemName.mid(8).toInt(&bok);
            //lastAutoNamedBeanRef.accumulateAndGet(autoNumber, Math::max);
            //lastAutoNamedBeanRef.fetchAndAddAcquire(autoNumber);
            lastAutoNamedBeanRef = autoNumber;
        if(!bok) {
            log->warn(tr("Auto generated SystemName %1 is not in the correct format").arg(systemName));
        }
    }
}

/*public*/ QString AbstractManager::getAutoSystemName() const{
    //int nextAutoBlockRef = lastAutoNamedBeanRef.fetchAndAddAcquire(1);//   .incrementAndGet();
    int nextAutoBlockRef = lastAutoNamedBeanRef++;
    QString b = QString(getSystemNamePrefix() + ":AUTO:");
    QString nextNumber = paddedNumber.format(nextAutoBlockRef);
    b.append(nextNumber);
    return b;
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractManager.class.getName());
