#include "abstractmanager.h"
#include <QStringList>
#include "instancemanager.h"
#include "propertychangesupport.h"
#include "configxmlmanager.h"
#include "abstractcatalogtree.h"
#include "systemnamecomparator.h"
#include "jmriconfigurationmanager.h"
/**
 * Abstract partial implementation for all Manager-type classes.
 * <P>
 * Note that this does not enforce any particular system naming convention
 * at the present time.  They're just names...
 *
 * @author      Bob Jacobsen Copyright (C) 2003
 * @version	$Revision: 19272 $
 */
AbstractManager::AbstractManager(QObject *parent)
{
  Q_UNUSED(parent);
  log = new Logger("AbstractManager");
 _tsys = new QHash<QString, NamedBean*>;   // stores known Turnout instances by system name
 _tuser = new QHash<QString, NamedBean*>;   // stores known Turnout instances by user name

 //registerSelf(); // this fumction must be called by the subclass in order to work!

 pcs = new PropertyChangeSupport((QObject*)this);

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
void AbstractManager::registerSelf()
{
  log->debug(tr("registerSelf for config of type %1").arg(this->metaObject()->className()));
  ConfigureManager* cm;
  try
  {
   cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
  }
  catch(ClassNotFoundException ex) { cm = NULL;}
  if (cm != NULL) {
      cm->registerConfig(this, getXMLOrder());
      log->debug(tr("registering for config of type %1").arg(this->metaObject()->className()));
  }

}
/*public*/ QString AbstractManager::normalizeSystemName(/*@Nonnull*/ QString inputName) {return "";} //throws NamedBean.BadSystemNameException

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
  connect((AbstractCatalogTree*)s, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));
 }
 else {
 AbstractNamedBean* ab = (AbstractNamedBean*)s;
 connect(ab->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));
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
/*public*/ void AbstractManager::on_propertyChange(PropertyChangeEvent* e)
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

/*public*/ QList<NamedBean*>* AbstractManager::getNamedBeanList() {
        return new QList<NamedBean*>(_tsys->values());
    }
QStringList AbstractManager::getUserNameList()
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
void AbstractManager::firePropertyChange(QString p, QVariant old, QVariant n)
{ pcs->firePropertyChange(p,old,n);}

QHash<QString, NamedBean*>* AbstractManager::getSystemNameHash()
{
 return _tsys;
}


//@Override
//@OverridingMethodsMustInvokeSuper
/*public*/ void AbstractManager::vetoableChange(PropertyChangeEvent* evt) //throw PropertyVetoException
{
#if 0 // TODO:
    if ("CanDelete" == (evt->getPropertyName())) { //IN18N
        QString message;// = new StringBuilder();
        message.append(tr("Found in the following <b>%1s</b>").arg(getBeanTypeHandled()))
                .append("<ul>");
        bool found = false;
        for (NamedBean* nb : _tsys->values()) {
            try {
                nb->vetoableChange(evt);
            } catch (/*PropertyVetoException*/ Exception e) {
                if (e.getPropertyChangeEvent().getPropertyName() == ("DoNotDelete")) { //IN18N
                    throw e;
                }
                found = true;
                message.append("<li>")
                        .append(e.getMessage())
                        .append("</li>");
            }
        }
        message.append("</ul>")
                .append(Bundle.getMessage("VetoWillBeRemovedFrom", getBeanTypeHandled()));
        if (found) {
            throw new PropertyVetoException(message.toString(), evt);
        }
    } else {
        for (NamedBean nb : _tsys.values()) {
            try {
                nb.vetoableChange(evt);
            } catch (PropertyVetoException e) {
                throw e;
            }
        }
    }
#endif
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
