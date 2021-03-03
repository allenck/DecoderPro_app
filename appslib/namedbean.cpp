/* Default implementation for class NamedBean */
#include "namedbean.h"
#include <QSet>
#include <QString>
#include "manager.h"
#include "alphanumcomparator.h"

//const int NamedBean::UNKNOWN      = 0x01;
//const int NamedBean::INCONSISTENT = 0x08;
//#endif

/**
 * Format used for {@link #getDisplayName(DisplayOptions)} when displaying
 * the user name and system name without quoation marks around the user
 * name.
 */
/*public*/ /*static*/ /*final*/ QString NamedBean::DISPLAY_NAME_FORMAT = "%1 (%2)";

/**
 * Format used for {@link #getDisplayName(DisplayOptions)} when displaying
 * the user name and system name with quoation marks around the user name.
 */
/*public*/ /*static*/ /*final*/ QString NamedBean::QUOTED_NAME_FORMAT = "\"%1\" (%2)";

/**
 * Property of changed state.
 */
/*public*/ /*static*/ /*final*/ QString NamedBean::PROPERTY_STATE = "state";

NamedBean::NamedBean(QObject *parent) : QObject(parent)
{
// _parent = parent;
// _state = UNKNOWN;
}

NamedBean::NamedBean(QString /*name*/, QObject *parent) : QObject(parent)
{
// _parent = parent;
// _name = name;
// _state = UNKNOWN;
// _systemName = name;
}
NamedBean::NamedBean(const NamedBean & /*other*/): QObject()
{
// this->_parent = other._parent;
// this->_name = other._name;
// this->_state = other._state;
// this->_systemName = other._systemName;
// this->_userName = other._userName;
}

QString NamedBean::getUserName()const { return "";}
void NamedBean::setUserName(QString /*s*/) {}

/**
 * Get user name if it exists, otherwise return System name.
 *
 * @return the user name or system-specific name
 */
//@CheckReturnValue
//@Nonnull
/*public*/ /*default*/ QString NamedBean::getDisplayName() {
    return getDisplayName(DisplayOptions::DISPLAYNAME);
}

// QString NamedBean::getSystemName() const { return "";}
/**
 * Get the name to display, formatted per {@link NamedBean.DisplayOptions}.
 *
 * @param options the DisplayOptions to use
 * @return the display name formatted per options
 */
//@CheckReturnValue
//@Nonnull
/*public*/ /*default*/ QString NamedBean::getDisplayName(DisplayOptions options) {
    QString userName = getUserName();
    QString systemName = getSystemName();
    // since there are two undisplayable states for the user name,
    // empty or null, if user name is empty, make it null to avoid
    // repeatedly checking for both those states later
    if (!userName .isNull() && userName.isEmpty()) {
        userName = "";
    }
    switch (options) {
        case USERNAME_SYSTEMNAME:
            return userName != "" ? QString(DISPLAY_NAME_FORMAT).arg(userName).arg(systemName) : systemName;
        case QUOTED_USERNAME_SYSTEMNAME:
            return userName != "null" ? QString(QUOTED_NAME_FORMAT).arg(userName).arg(systemName) : getDisplayName(DisplayOptions::QUOTED_SYSTEMNAME);
        case SYSTEMNAME:
            return systemName;
        case QUOTED_SYSTEMNAME:
            return QString("\"%1\"").arg(systemName);
        case QUOTED_USERNAME:
        case QUOTED_DISPLAYNAME:
            return QString("\"%s\"").arg(userName != "" ? userName : systemName);
        case USERNAME:
        case DISPLAYNAME:
        default:
            return userName != "" ? userName : systemName;
    }
}

void NamedBean::addPropertyChangeListener(PropertyChangeListener */*l*/)
{

}
void NamedBean::addPropertyChangeListener(PropertyChangeListener */*l*/, QString /*name*/, const QString /*listenerRef*/)
{

}
/**
 * Request a call-back when a bound property changes. Bound properties are
 * the known state, commanded state, user and system names.
 *
 * @param propertyName The name of the property to listen to
 * @param listener     The listener. This may change in the future to be a
 *                         subclass of NamedProprtyChangeListener that
 *                         carries the name and listenerRef values
 *                         internally
 * @param name         The name (either system or user) that the listener
 *                         uses for this namedBean, this parameter is used
 *                         to help determine when which listeners should be
 *                         moved when the username is moved from one bean to
 *                         another
 * @param listenerRef  A textual reference for the listener, that can be
 *                         presented to the user when a delete is called
 */
/*public*/ void addPropertyChangeListener(/*@Nonnull*/ QString /*propertyName*/, /*@Nonnull*/ PropertyChangeListener* /*listener*/,
                                                  QString /*name*/, QString /*listenerRef*/) {}
/**
* Add a {@link java.beans.PropertyChangeListener} for a specific property.
*
* @param propertyName The name of the property to listen on.
* @param listener     The PropertyChangeListener to be added
*/
/*public*/ void addPropertyChangeListener(/*@CheckForNull*/ QString /*propertyName*/, /*@CheckForNull*/ PropertyChangeListener* /*listener*/) {}

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
QVector<PropertyChangeListener *> NamedBean::getPropertyChangeListenersByReference(QString /*name*/)
{
    return QVector<PropertyChangeListener *>();
}
void NamedBean::dispose()
{

}
void NamedBean::setState(int s) {}
//{
// _state = s;
//}
int NamedBean::getState() { return 0;}
/**
 * Provide human-readable, localized version of state value.
 * <P>
 * This method is intended for use when presenting to a human operator.
 *
 * @param state the state to describe
 * @return the state in localized form
 */
//@CheckReturnValue
/*public*/ QString NamedBean::describeState(int /*state*/) {return "";}

QString NamedBean::getComment() { return "";}
void NamedBean::setComment(QString /*comment*/) {}

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
    AlphanumComparator ac = AlphanumComparator();
    QString o1 = this->getSystemName();
    QString o2 = n2->getSystemName();

    int p1len = Manager::getSystemPrefixLength(o1);
    int p2len = Manager::getSystemPrefixLength(o2);

    int comp = ac.compare(o1.mid(0, p1len), o2.mid(0, p2len));
    if (comp != 0) return comp;

    QChar c1 = o1.at(p1len);
    QChar c2 = o2.at(p2len);

    if (c1 != c2) {
        return (c1 > c2) ? +1 : -1 ;
    } else {
        return this->compareSystemNameSuffix(o1.mid(p1len+1), o2.mid(p2len+1), n2);
    }
}

/*public*/ bool NamedBean::equals(QObject* /*obj*/)
{
 return false;
}


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

