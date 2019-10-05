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

 //registerSelf(); // ACK this fumction must be called by the subclass in order to work!

 pcs = new PropertyChangeSupport((QObject*)this);
 vcs = new VetoableChangeSupport((QObject*)this);
}
AbstractManager::AbstractManager(SystemConnectionMemo* memo, QObject *parent) : Manager(memo,parent)
{
  Q_UNUSED(parent);
 this->memo = memo;
  log = new Logger("AbstractManager");
 _tsys = new QHash<QString, NamedBean*>;   // stores known Turnout instances by system name
 _tuser = new QHash<QString, NamedBean*>;   // stores known Turnout instances by user name

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
/*public*/ QString AbstractManager::normalizeSystemName(/*@Nonnull*/ QString /*inputName*/) {return "";} //throws NamedBean.BadSystemNameException

///*abstract*/ /*public*/ int AbstractManager::getXMLOrder() { return 0;}


QString AbstractManager::makeSystemName(QString s)
{
 if(s.startsWith(getSystemPrefix()+typeLetter()))
  return s;
 QString prefix = getSystemPrefix();
 char type = typeLetter();
 return prefix+type+s;
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

    /**
     * Locate an instance based on a system name.  Returns NULL if no
     * instance already exists.
     * @param systemName System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/ NamedBean* AbstractManager::getBeanBySystemName(QString systemName){
        return _tsys->value(systemName);
    }

    /**
     * Locate an instance based on a user name.  Returns NULL if no
     * instance already exists.
     * @param userName System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/ NamedBean* AbstractManager::getBeanByUserName(QString userName){
        return _tuser->value(userName);
    }

    /**
     * Locate an instance based on a name.  Returns NULL if no
     * instance already exists.
     * @param name System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/ NamedBean* AbstractManager::getNamedBean(QString name){
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
/*public*/ void AbstractManager::Register(NamedBean* s)
{
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
 {
 systemName = s->getSystemName();
 Q_ASSERT(!systemName.isEmpty());
 _tsys->insert(systemName, s);
  userName = s->getUserName();
 }
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
}

/**
 * Forget a NamedBean Object created outside the manager.
 * <P>
 * The non-system-specific RouteManager
 * uses this method.
 */
/*public*/ void AbstractManager::deregister(NamedBean* s) {
    s->removePropertyChangeListener((PropertyChangeListener*)this);
    QString systemName = s->getSystemName();
    _tsys->remove(systemName);
    QString userName = s->getUserName();
    if (userName != NULL) _tuser->remove(userName);
    firePropertyChange("length", QVariant(), /*Integer.valueOf*/(_tsys->size()));
    // listen for name and state changes to forward
    emit beanDeleted(s);
}

/**
 * The PropertyChangeListener interface in this class is
 * intended to keep track of user name changes to individual NamedBeans.
 * It is not completely implemented yet. In particular, listeners
 * are not added to newly registered objects.
 */
/*public*/ void AbstractManager::propertyChange(PropertyChangeEvent* e)
{
 if(e->getPropertyName() == "length")
  firePropertyChange(e->getPropertyName(), e->getOldValue(), e->getNewValue());

 if (e->getPropertyName()==("UserName"))
 {
  QString old = e->getOldValue().toString();  // OldValue is actually system name
  QString now = e->getNewValue().toString();
  NamedBean* t = (NamedBean*)e->getSource();
  //NamedBean* t = NULL;  // TODO: fix this
  if (!old.isEmpty()) _tuser->remove(old);
  if (!now.isEmpty()) _tuser->insert(now, t);

  //called DisplayListName, as DisplayName might get used at some point by a NamedBean
  firePropertyChange("DisplayListName", old, now);
 }
}

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

/** {@inheritDoc} */
//@Override
/*public*/ /*SortedSet<E>*/QSet<NamedBean*> AbstractManager::getNamedBeanSet() {
    //return Collections.unmodifiableSortedSet(_beans);
 //return QList<NamedBean*>(_tsys->values().toSet());
 QList<NamedBean*> list = QList<NamedBean*>(_tsys->values());
 qSort(list.begin(), list.end(), NamedBeanComparator::compare);
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

/*public*/ QList<PropertyChangeListener*>* AbstractManager::getPropertyChangeListeners()
{
 return pcs->getPropertyChangeListeners();
}

void AbstractManager::firePropertyChange(QString p, QVariant old, QVariant n)
{ pcs->firePropertyChange(p,old,n);}

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
        for (NamedBean* nb : _tsys->values()) {
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
        for (NamedBean* nb : _tsys->values()) {
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
/*public*/ AbstractManager::NameValidity AbstractManager::validSystemNameFormat(QString systemName) {
    return getSystemNamePrefix() == (systemName)
            ? NameValidity::VALID_AS_PREFIX_ONLY
            : systemName.startsWith(getSystemNamePrefix())
            ? NameValidity::VALID
            : NameValidity::INVALID;
}

/**
 * {@inheritDoc}
 *
 * The implementation in {@link AbstractManager} should be final, but is not
 * for four managers that have arbitrary prefixes.
 */
//@Override
/*public*/ /*final*/ QString AbstractManager::getSystemPrefix() {
    return memo->getSystemPrefix();
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
/*public*/ QString normalizeSystemName(/*@Nonnull*/ QString inputName) //throws NamedBean.BadSystemNameException
{
    return inputName;
}
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractManager.class.getName());
