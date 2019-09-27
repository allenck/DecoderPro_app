#include "abstractnamedbean.h"
#include "loggerfactory.h"
AbstractNamedBean::AbstractNamedBean(QObject *parent) : NamedBean(parent)
{
 common("", "", parent);
}

void AbstractNamedBean::common(QString sys, QString user, QObject *parent)
{
 this->parent = parent;
 this->mSystemName = sys;
 this->mUserName = user;
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
 common(sys, "", parent );
}

AbstractNamedBean:: AbstractNamedBean(QString sysName, QString user, QObject* parent) : NamedBean(sysName,parent)
{
 //Q_ASSERT(!sysName.isEmpty());
common(sysName, user, parent);
 NamedBean::setUserName(user);
}

/**
 * Get associated comment text.
 */
//@Override
QString AbstractNamedBean:: getComment() { return this->comment; }

/**
 * Set associated comment text.
 * <p>
 * Comments can be any valid text.
 * @param comment Null means no comment associated.
 */
//@Override
//@OverridingMethodsMustInvokeSuper
void AbstractNamedBean::setComment(QString comment)
{
 QString old = this->comment;
 if (comment == NULL || comment.trimmed().isEmpty()) {
     this->comment = "";
 } else {
     this->comment = comment;
 }
 firePropertyChange("Comment", old, comment);
}

//@Override
QString AbstractNamedBean::getDisplayName()
{
 return NamedBean::getDisplayName();
}
/**
 * {@inheritDoc}
 */
//@Override
//@CheckReturnValue
//@Nonnull
/*final*/ /*public*/ QString AbstractNamedBean::getDisplayName(NamedBean::DisplayOptions displayOptions) {
    return NamedBean::getDisplayName(displayOptions);
}
//@Override
/*public*/ QString AbstractNamedBean::getFullyFormattedDisplayName()
{
 QString name = getUserName();
 if (name != "" && name.length() > 0 && name != (getSystemName())) {
     name = getSystemName() + "(" + name + ")";
 } else {
     name = getSystemName();
 }
 return name;
}

//@Override
/*public synchronized*/ void AbstractNamedBean::addPropertyChangeListener(PropertyChangeListener* l, const QString beanRef, QString listenerRef)
{
 //pcs->addPropertyChangeListener(l);
 connect(this->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),l, SLOT(propertyChange(PropertyChangeEvent*)));
 if(beanRef!=NULL)
     _Register->insert(l, beanRef);
 if(listenerRef!=NULL)
     listenerRefs->insert(l, listenerRef);
 //connect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
}

//@Override
//@OverridingMethodsMustInvokeSuper
/*public synchronized*/ void AbstractNamedBean::addPropertyChangeListener(PropertyChangeListener* l)
{
 //pcs->addPropertyChangeListener(l);
 connect(this->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),l, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public synchronized*/ void AbstractNamedBean::removePropertyChangeListener(PropertyChangeListener* l)
{
 //pcs->removePropertyChangeListener(l);
 disconnect(this->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));

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
 if (pcs!=NULL)
     pcs->firePropertyChange(p,old,n);
}
///*protected*/ void AbstractNamedBean::firePropertyChange(QString p, QObject* old, QObject* n) {
// if (pcs!=NULL) pcs->firePropertyChange(p,old,n);
//}

/*public*/ void AbstractNamedBean::dispose() {
    pcs = NULL;
}

//@Override
//@CheckReturnValue
/*public*/ QString AbstractNamedBean::describeState(int state) {
    switch (state) {
        case UNKNOWN:
            return tr("Unknown");
        case INCONSISTENT:
            return tr("Inconsistent");
        default:
            return tr("Unexpected value: %1").arg(state);
    }
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

/*public java.util.*/QSet<QString> AbstractNamedBean::getPropertyKeys() {
    if (parameters == NULL || parameters->isEmpty()) return QSet<QString>();
    return parameters->keys().toSet();
}

/*public*/ void AbstractNamedBean::removeProperty(QString key) {
    if (parameters == NULL || key == NULL) {
        return;
    }
    parameters->remove(key);
}

//@Override
/*public*/ void AbstractNamedBean::vetoableChange(PropertyChangeEvent* /*evt*/) throw (PropertyVetoException)
{
}

/**
 * {@inheritDoc}
 * <p>
 * This implementation tests that the results of
 * {@link jmri.NamedBean#getSystemName()} and
 * {@link jmri.NamedBean#getUserName()} are equal for this and obj.
 *
 * @param obj the reference object with which to compare.
 * @return {@code true} if this object is the same as the obj argument;
 *         {@code false} otherwise.
 */
//@Override
/*public*/ bool AbstractNamedBean::equals(QObject* obj)
{
 // test the obj == this
 bool result = NamedBean::equals(obj);

 //if (!result && (obj != NULL) && obj instanceof AbstractNamedBean)
 if(!result && (obj != NULL && qobject_cast<AbstractNamedBean*>(obj) != NULL))
 {
  AbstractNamedBean* b = (AbstractNamedBean*) obj;
  if (this->getSystemName() == (b->getSystemName()))
  {
   QString bUserName = b->getUserName();
   if ((mUserName != NULL) && (bUserName != NULL)
           && mUserName == (bUserName))
   {
       result = true;
   }
  }
 }
 return result;
}

/**
 * calculate our hash code
 *
 * @return our hash code
 */
//@Override
//public int hashCode() {
//    int result = super.hashCode();
//    if (mSystemName != null) {
//        result = mSystemName.hashCode();
//        if (mUserName != null) {
//            result = (result * 37) + mUserName.hashCode();
//        }
//    } else if (mUserName != null) {
//        result = mUserName.hashCode();
//    }
//    return result;
//}

/**
 * {@inheritDoc}
 *
 * By default, does an alphanumeric-by-chunks comparison
 */
//@CheckReturnValue
/*public*/ int AbstractNamedBean::compareSystemNameSuffix(/*@Nonnull*/ QString suffix1, /*@Nonnull*/ QString suffix2, /*@Nonnull*/ NamedBean* /*n*/) {
    //jmri.util.AlphanumComparator ac = new jmri.util.AlphanumComparator();
    return QString::compare(suffix1, suffix2);
}

/*private*/ /*static*/ Logger* AbstractNamedBean::log = LoggerFactory::getLogger("AbstractNamedBean");
