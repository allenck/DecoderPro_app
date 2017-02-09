#include "abstractnamedbean.h"

AbstractNamedBean::AbstractNamedBean(QObject *parent)
{
 this->parent = parent;
 parameters = NULL;
 _Register = new QHash<PropertyChangeListener*, QString>();
 listenerRefs = new QHash<PropertyChangeListener*, QString>();
 pcs = new PropertyChangeSupport((QObject*)this);
}

/**
 * Abstract base for the NamedBean interface.
 * <P>
 * Implements the parameter binding support.
 *
 * @author      Bob Jacobsen Copyright (C) 2001
 * @version     $Revision: 19974 $
 */
//public abstract class AbstractNamedBean implements NamedBean, java.io.Serializable {

    //private AbstractNamedBean() {
    //    mSystemName = NULL;
    //    mUserName = NULL;
    //    log.warn("Unexpected use of NULL ctor");
    //    Exception e = new Exception();
    //    e.printStackTrace();
    //}

AbstractNamedBean::AbstractNamedBean(QString sys, QObject* parent) : NamedBean(sys, parent)
{
 Q_ASSERT(!sys.isEmpty());
 this->parent = parent;
 mSystemName = sys;
 setObjectName(mSystemName);
 mUserName = "";
 parameters = NULL;
 _Register = new QHash<PropertyChangeListener*, QString>();
 listenerRefs = new QHash<PropertyChangeListener*, QString>();
 pcs = new PropertyChangeSupport((QObject*)this);
}

AbstractNamedBean:: AbstractNamedBean(QString sysName, QString user, QObject* parent) : NamedBean(sysName,parent)
{
 //Q_ASSERT(!sysName.isEmpty());
 this->parent = parent;
 mSystemName = sysName;
 setObjectName(mSystemName);
 mUserName = user;
 parameters = NULL;
 _Register = new QHash<PropertyChangeListener*, QString>();
 listenerRefs = new QHash<PropertyChangeListener*, QString>();
 pcs = new PropertyChangeSupport((QObject*)this);
 NamedBean::setUserName(user);
}

/**
 * Get associated comment text.
 */
QString AbstractNamedBean:: getComment() { return this->comment; }

/**
 * Set associated comment text.
 * <p>
 * Comments can be any valid text.
 * @param comment Null means no comment associated.
 */
void AbstractNamedBean::setComment(QString comment)
{
 QString old = this->comment;
 this->comment = comment;
 firePropertyChange("Comment", old, comment);
 //emit propertyChange(this, "Comment", old, comment);
}

QString AbstractNamedBean::getDisplayName()
{
 QString name = getUserName();
 if (name != "" && name.length() > 0)
 {
  return name;
 }
 else
 {
  return getSystemName();
 }
}



/*public synchronized*/ void AbstractNamedBean::addPropertyChangeListener(PropertyChangeListener* l, const QString beanRef, QString listenerRef)
{
 pcs->addPropertyChangeListener(l);
 if(beanRef!=NULL)
     _Register->insert(l, beanRef);
 if(listenerRef!=NULL)
     listenerRefs->insert(l, listenerRef);
}

/*public synchronized*/ void AbstractNamedBean::addPropertyChangeListener(PropertyChangeListener* l)
{
 pcs->addPropertyChangeListener(l);
}

/*public synchronized*/ void AbstractNamedBean::removePropertyChangeListener(PropertyChangeListener* l)
{
 pcs->removePropertyChangeListener(l);
 _Register->remove(l);
 listenerRefs->remove(l);
}

/*public synchronized*/ QList<PropertyChangeListener*>* AbstractNamedBean::getPropertyChangeListeners(QString name)
{
 QList<PropertyChangeListener*>* list = new QList<PropertyChangeListener*>();
 //Enumeration<PropertyChangeListener> en = register.keys();
 QHashIterator<PropertyChangeListener*, QString> en(*_Register);
 while (en.hasNext())
 {
  PropertyChangeListener* l = en.key();
  if(_Register->value(l) == (name))
  {
   list->append(l);
  }
 }
 return list;
}

/* This allows a meaning full list of places where the bean is in use!*/
/*public synchronized*/ QList<QString>* AbstractNamedBean::getListenerRefs()
{
 QList<QString>* list = new QList<QString>();
 //Enumeration<PropertyChangeListener> en = listenerRefs.keys();
 QHashIterator<PropertyChangeListener*, QString> en(*listenerRefs);
//        while (en.hasMoreElements()) {
 while(en.hasNext())
 {
  en.next();
  PropertyChangeListener* l = en.key();
  list->append(listenerRefs->value(l));
 }
 return list;
}

/*public synchronized*/ void AbstractNamedBean::updateListenerRef(PropertyChangeListener* l, QString newName)
{
 if(listenerRefs->contains(l))
 {
  listenerRefs->insert(l, newName);
 }
}

/*public synchronized*/ QString AbstractNamedBean::getListenerRef(PropertyChangeListener* l) {
    return listenerRefs->value(l);
}

/**
 * Number of current listeners. May return -1 if the
 * information is not available for some reason.
 */
/*public synchronized*/ int AbstractNamedBean::getNumPropertyChangeListeners() {
    return pcs->getPropertyChangeListeners()->length();
}

/*public synchronized*/ QList<PropertyChangeListener*>* AbstractNamedBean::getPropertyChangeListeners() {
    return pcs->getPropertyChangeListeners();
}

/*public*/ QString AbstractNamedBean::getSystemName() const  {return mSystemName;}
/*public*/ QString AbstractNamedBean::getUserName() {return mUserName;}

/*public*/ void AbstractNamedBean::setSysName(QString s)
{
 mSystemName = s;
}

/*public*/ void AbstractNamedBean::setUserName(QString s)
{
 QString old = mUserName;
 mUserName = s;
 NamedBean::setUserName(s);
 firePropertyChange("UserName", old, s);
// emit propertyChange(this, "UserName", old, s);
// emit propertyChange(new PropertyChangeEvent(this, "UserName", old, s));
}


/*protected*/ void AbstractNamedBean::firePropertyChange(QString p, QVariant old, QVariant n) {
 if (pcs!=NULL) pcs->firePropertyChange(p,old,n);
}
///*protected*/ void AbstractNamedBean::firePropertyChange(QString p, QObject* old, QObject* n) {
// if (pcs!=NULL) pcs->firePropertyChange(p,old,n);
//}

/*public*/ void AbstractNamedBean::dispose() {
    pcs = NULL;
}

/*public*/ void AbstractNamedBean::setProperty(QString key, QVariant value) {
    if (parameters == NULL)
        parameters = new QMap<QString, QVariant>();
    parameters->insert(key, value);
}

/*public*/ QVariant AbstractNamedBean::getProperty(QString key) {
    if (parameters == NULL) return QVariant();
    return parameters->value(key);
}

/*public java.util.*/QList<QString> AbstractNamedBean::getPropertyKeys() {
    if (parameters == NULL || parameters->isEmpty()) return QList<QString>();
    return parameters->keys();
}


//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractNamedBean.class.getName());
