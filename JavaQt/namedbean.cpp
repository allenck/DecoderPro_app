/* Default implementation for class NamedBean */
#include "namedbean.h"
#include <QSet>
#include <QString>
#include "manager.h"

//const int NamedBean::UNKNOWN      = 0x01;
//const int NamedBean::INCONSISTENT = 0x08;
//#endif
NamedBean::NamedBean(QObject *parent)
{
 _parent = parent;
 _state = UNKNOWN;
}

NamedBean::NamedBean(QString name, QObject *parent)
{
 _parent = parent;
 _name = name;
 _state = UNKNOWN;
 _systemName = name;
}
NamedBean::NamedBean(const NamedBean & other): QObject()
{
 this->_parent = other._parent;
 this->_name = other._name;
 this->_state = other._state;
 this->_systemName = other._systemName;
 this->_userName = other._userName;
}

QString NamedBean::getUserName() { return _userName;}
void NamedBean::setUserName(QString s)
{
 _userName = s;
}
QString NamedBean::getSystemName() { return _systemName;}
QString NamedBean::getDisplayName() { return _displayName;}

void NamedBean::addPropertyChangeListener(PropertyChangeListener */*l*/)
{

}
void NamedBean::addPropertyChangeListener(PropertyChangeListener */*l*/, QString /*name*/, const QString /*listenerRef*/)
{

}
void NamedBean::removePropertyChangeListener(PropertyChangeListener */*l*/)
{

}
void NamedBean::updateListenerRef(PropertyChangeListener */*l*/, QString /*newName*/)
{

}
QString NamedBean::getListenerRef(PropertyChangeListener */*l*/)
{
    return "";
}
QList<QString>* NamedBean::getListenerRefs()
{
    //return QStringList();
 return NULL;
}
int NamedBean::getNumPropertyChangeListeners()
{
    return 0;
}
QList<PropertyChangeListener*>* NamedBean::getPropertyChangeListeners(QString /*name*/)
{
    return NULL;
}
void NamedBean::dispose()
{

}
void NamedBean::setState(int s)
{
 _state = s;
}
int NamedBean::getState() { return _state;}
/**
 * Provide human-readable, localized version of state value.
 * <P>
 * This method is intended for use when presenting to a human operator.
 *
 * @param state the state to describe
 * @return the state in localized form
 */
//@CheckReturnValue
/*public*/ QString describeState(int state) {return "";}

QString NamedBean::getComment() { return _comment;}
void NamedBean::setComment(QString comment)
{
 _comment = comment;
}
void NamedBean::setProperty(QString /*key*/, QVariant /*value*/)
{

}
QVariant NamedBean::getProperty(QString /*key*/)
{
 return QVariant();
}

/**
 * Remove the key/value pair against the NamedBean.
 */
/*public*/ void removeProperty(/*@Nonnull*/ QString /*key*/) {}
/**
 * Retrieve the complete current set of keys.
 *
 * @return empty set if none
 */
//@CheckReturnValue
//@Nonnull
/*public*/ QSet<QString> NamedBean::getPropertyKeys() {return QSet<QString>();}

/**
 * For instances in the code where we are dealing with just a bean and a
 * message needs to be passed to the user or in a log.
 *
 * @return a string of the bean type, eg Turnout, Sensor etc
 */
//@CheckReturnValue
//@Nonnull
/*public*/ QString NamedBean::getBeanType() {return "";}

/**
 * Enforces, and as a user convenience converts to, the standard form for a
 * user name.
 * <p>
 * This implementation just does a trim(), but later versions might e.g. do
 * more extensive things.
 *
 * @param inputName User name to be normalized
 * @throws BadUserNameException If the inputName can't be converted to
 *                              normalized form
 * @return A user name in standard normalized form or null if inputName was
 *         null
 */
//@CheckReturnValue
//@CheckForNull
/*static*/ /*public*/ QString NamedBean::normalizeUserName(/*@CheckForNull*/ QString inputName) //throw (NamedBean::BadUserNameException)
{
    QString result = inputName;
    if (result != NULL) {
        result = result.trimmed();
    }
    return result;
}

/**
 * Provide a comparison between the system names of two beans.
 * This provides a implementation for e.g. {@link java.util.Comparator}.
 * @return 0 if the names are the same, -1 if the first argument orders before
 * the second argument's name, +1 if the first argument's name  orders after the second argument's name.
 * The comparison is alphanumeric on the system prefix, then alphabetic on the
 * type letter, then system-specific comparison on the two suffix parts
 * via the {@link compareSystemNameSuffix} method.
 *
 * @param n2 The second NamedBean in the comparison ("this" is the first one)
 * @return -1,0,+1 for ordering if the names are well-formed; may not provide proper ordering if the names are not well-formed.
 */
//@CheckReturnValue
/*public*/ /*default*/ int NamedBean::compareTo(/*@Nonnull*/ NamedBean* n2) {
    //jmri.util.AlphanumComparator ac = new jmri.util.AlphanumComparator();
    QString o1 = this->getSystemName();
    QString o2 = n2->getSystemName();

    int p1len = Manager::getSystemPrefixLength(o1);
    int p2len = Manager::getSystemPrefixLength(o2);

    //int comp = ac.compare(o1.substring(0, p1len), o2.substring(0, p2len));
    int comp = QString::compare(o1.mid(0,p1len),o2.mid(0, p2len));
    if (comp != 0) return comp;

    QChar c1 = o1.at(p1len);
    QChar c2 = o2.at(p2len);

    if (c1 != c2) {
        return (c1 > c2) ? +1 : -1 ;
    } else {
        return this->compareSystemNameSuffix(o1.mid(p1len+1), o2.mid(p2len+1), n2);
    }
}

/*public*/ bool NamedBean::equals(QObject* /*obj*/) {return false;}

/**
 * Compare the suffix of this NamedBean's name with the
 * suffix of the argument NamedBean's name for the {@link #compareTo} operation.
 * This is intended to be a system-specific comparison that understands the various formats, etc.
 *
 * @param suffix1 The suffix for the 1st bean in the comparison
 * @param suffix2 The suffix for the 2nd bean in the comparison
 * @param n2 The other (second) NamedBean in the comparison
 * @return -1,0,+1 for ordering if the names are well-formed; may not provide proper ordering if the names are not well-formed.
 */
//@CheckReturnValue
/*public*/ int NamedBean::compareSystemNameSuffix(/*@Nonnull*/ QString /*suffix1*/, /*@Nonnull*/ QString /*suffix2*/, /*@Nonnull*/ NamedBean* /*n2*/) {return 0;}

