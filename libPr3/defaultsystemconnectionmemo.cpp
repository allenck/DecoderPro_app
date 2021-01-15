#include "defaultsystemconnectionmemo.h"
#include "conflictingsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "systemconnectionmemomanager.h"
#include "instancemanager.h"
#include "startupactionfactory.h"
#include "nmraconsistmanager.h"

/**
 * Lightweight abstract class to denote that a system is active, and provide
 * general information.
 * <p>
 * Objects of specific subtypes of this are registered in the
 * {@link InstanceManager} to activate their particular system.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 */
// /*public*/ abstract class DefaultSystemConnectionMemo extends Bean implements SystemConnectionMemo, Disposable {


//@SuppressWarnings("deprecation")
/*protected*/ DefaultSystemConnectionMemo::DefaultSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString userName, QObject *parent)
    : SystemConnectionMemo(parent)
{
if(!log)
log = LoggerFactory::getLogger("DefaultSystemConnectionMemo");

    classObjectMap = QMap</*Class<?>*/QString,Manager*>();
    if (qobject_cast<ConflictingSystemConnectionMemo*>(this)) {
        this->prefix = prefix;
        this->userName = userName;
        return;
    }
    log->debug(tr("SystemConnectionMemo created for prefix \"%1\" user name \"%2\"").arg(prefix).arg(userName));
    if (!setSystemPrefix(prefix)) {
        int x = 2;
        while (!setSystemPrefix(prefix + x)) {
            x++;
        }
        log->debug(tr("created system prefix %1%2").arg(prefix).arg(x));
    }

    if (!setUserName(userName)) {
        int x = 2;
        while (!setUserName(userName + x)) {
            x++;
        }
        log->debug(tr("created user name %1%2").arg(prefix).arg(x));
    }
    // reset to null so these get set by the first setPrefix/setUserName
    // call after construction
    this->prefixAsLoaded = QString();
    this->userNameAsLoaded = QString();
}

/**
 * Register with the SystemConnectionMemoManager and InstanceManager with proper
 * ID for later retrieval as a generic system.
 * <p>
 * This operation should occur only when the SystemConnectionMemo is ready for use.
 */
/*public*/ void DefaultSystemConnectionMemo::_register() {
    log->debug(tr("register as SystemConnectionMemo, really of type %1", this->metaObject()->className()));
    SystemConnectionMemoManager::getDefault()->_register(this);
}

/**
 * Provide access to the system prefix string.
 * <p>
 * This was previously called the "System letter".
 *
 * @return System prefix
 */
/*public*/ QString DefaultSystemConnectionMemo::getSystemPrefix() const{
    return prefix;
}

/**
 * Set the system prefix.
 *
 * @param systemPrefix prefix to use for this system connection
 * @throws java.lang.NullPointerException if systemPrefix is null
 * @return true if the system prefix could be set
 */
/*public*/ /*final*/ bool DefaultSystemConnectionMemo::setSystemPrefix(/*@Nonnull*/ QString systemPrefix) {
//        Objects.requireNonNull(systemPrefix);
    // return true if systemPrefix is not being changed
    if (systemPrefix == prefix) {
        if (this->prefixAsLoaded.isNull()) {
            this->prefixAsLoaded = systemPrefix;
        }
        return true;
    }
    QString oldPrefix = prefix;
    if (SystemConnectionMemoManager::getDefault()->isSystemPrefixAvailable(systemPrefix)) {
        prefix = systemPrefix;
        if (this->prefixAsLoaded.isNull()) {
            this->prefixAsLoaded = systemPrefix;
        }
        this->propertyChangeSupport->firePropertyChange(/*SYSTEM_PREFIX*/"ConnectionPrefixChanged", oldPrefix, systemPrefix);
        return true;
    }
    log->debug(tr("setSystemPrefix false for \"%1\"").arg(systemPrefix));
    return false;
}

/**
 * Provide access to the system user name string.
 * <p>
 * This was previously fixed at configuration time.
 *
 * @return User name of the connection
 */
/*public*/ QString DefaultSystemConnectionMemo::getUserName() const{
    return userName;
}

/**
 * Set the user name for the system connection.
 *
 * @param userName user name to use for this system connection
 * @throws java.lang.NullPointerException if name is null
 * @return true if the user name could be set.
 */
/*public*/ /*final*/ bool DefaultSystemConnectionMemo::setUserName(/*@Nonnull*/ QString userName) {
//        Objects.requireNonNull(userName);
    if (userName == (this->userName)) {
        if (this->userNameAsLoaded.isNull()) {
            this->userNameAsLoaded = userName;
        }
        return true;
    }
    QString oldUserName = this->userName;
    if (SystemConnectionMemoManager::getDefault()->isUserNameAvailable(userName)) {
        this->userName = userName;
        if (this->userNameAsLoaded.isNull()) {
            this->userNameAsLoaded = userName;
        }
        this->propertyChangeSupport->firePropertyChange(/*USER_NAME*/"ConnectionNameChanged", oldUserName, userName);
        return true;
    }
    return false;
}

/**
 * Check if this connection provides a specific manager type. This method
 * <strong>must</strong> return false if a manager for the specific type is
 * not provided, and <strong>must</strong> return true if a manager for the
 * specific type is provided.
 *
 * @param c The class type for the manager to be provided
 * @return true if the specified manager is provided
 * @see #get(java.lang.Class)
 */
//@OverridingMethodsMustInvokeSuper
/*public*/ bool DefaultSystemConnectionMemo::provides(/*Class<?>*/QString c) {
    if (disabled) {
        return false;
    }
    if (c == ("ConsistManager")) {
        return classObjectMap.value(c) != nullptr || provides("CommandStation") || provides("AddressedProgrammerManager");
    } else {
        return classObjectMap.contains(c);
    }
}

/**
 * Get a manager for a specific type. This method <strong>must</strong>
 * return a non-null value if {@link #provides(java.lang.Class)} is true for
 * the type, and <strong>must</strong> return null if provides() is false
 * for the type.
 *
 * @param <T>  Type of manager to get
 * @param type Type of manager to get
 * @return The manager or null if provides() is false for T
 * @see #provides(java.lang.Class)
 */
//@OverridingMethodsMustInvokeSuper
//@SuppressWarnings("unchecked") // dynamic checking done on cast of getConsistManager
/*public*/ /*<T> T*/Manager *DefaultSystemConnectionMemo::get(/*Class<?>*/QString type) {
    if (disabled) {
        return nullptr;
    }
    if (type == ("ConsistManager")) {
        return /*(T)*/ (Manager*)getConsistManager();
    } else {
        return /*(T)*/ classObjectMap.value(type); // nothing, by default
    }
}

/*public*/ void DefaultSystemConnectionMemo::dispose() {
//        Set<Class<?>> keySet = new HashSet<>(classObjectMap.keySet());
//        keySet.forEach(this::removeRegisteredObject);
 QList<QString> keySet = classObjectMap.keys();
 foreach (QString t, keySet) {
  removeRegisteredObject(t);
 }
    SystemConnectionMemoManager::getDefault()->deregister(this);
}

/*private*/ /*<T> */void DefaultSystemConnectionMemo::removeRegisteredObject(/*Class<T>*/QString c) {
    Manager* object = get(c);
    if (object != nullptr) {
        InstanceManager::deregister(object, c);
        deregister(object, c);
        disposeIfPossible(c, object);
    }
}

/*private*/ /*<T>*/ void DefaultSystemConnectionMemo::disposeIfPossible(/*Class<T>*/QString c, Manager* object) {
#if 0 // TODO:
    if(object instanceof Disposable) {
        try {
            ((Disposable)object).dispose();
        } catch (Exception e) {
            log.warn("Exception while disposing object of type {} in memo of type {}.", c.getName(), this.getClass().getName(), e);
        }
    }
#endif
}

/**
 * Get if the System Connection is currently Disabled.
 *
 * @return true if Disabled, else false.
 */
/*public*/ bool DefaultSystemConnectionMemo::getDisabled() {
    return disabled;
}

/**
 * Set if the System Connection is currently Disabled.
 * <p>
 * disabledAsLoaded is only set once.
 * Sends PropertyChange on change of disabled status.
 *
 * @param disabled true to disable, false to enable.
 */
/*public*/ void DefaultSystemConnectionMemo::setDisabled(bool disabled) {
    if (this->disabledAsLoaded == false) {
        // only set first time
        this->disabledAsLoaded = disabled;
    }
    if (disabled != this->disabled) {
        bool oldDisabled = this->disabled;
        this->disabled = disabled;
        this->propertyChangeSupport->firePropertyChange(DISABLED, oldDisabled, disabled);
    }
}

/**
 * Get the Comparator to be used for two NamedBeans. This is typically an
 * {@link NamedBeanComparator}, but may be any Comparator that works for
 * this connection type.
 *
 * @param <B>  the type of NamedBean
 * @param type the class of NamedBean
 * @return the Comparator
 */
//    /*public*/ abstract <B extends NamedBean> Comparator<B> getNamedBeanComparator(Class<B> type);

/**
 * Provide a factory for getting startup actions.
 * <p>
 * This is a bound, read-only, property under the name "actionFactory".
 *
 * @return the factory
 */
//@Nonnull
/*public*/ StartupActionFactory* getActionFactory() {
//        return new ResourceBundleStartupActionFactory(getActionModelResourceBundle());
 return nullptr;
}

//    /*protected*/ abstract ResourceBundle getActionModelResourceBundle();

/**
 * Add actions to the action list.
 *
 * @deprecated since 4.19.7 without direct replacement
 */
//@Deprecated
/*protected*/ /*final*/ void DefaultSystemConnectionMemo::addToActionList() {
    // do nothing
}

/**
 * Remove actions from the action list.
 *
 * @deprecated since 4.19.7 without direct replacement
 */
//@Deprecated
/*protected*/ /*final*/ void DefaultSystemConnectionMemo::removeFromActionList() {
    // do nothing
}

/**
 * Get if connection is dirty.
 * Checked fields are disabled, prefix, userName
 *
 * @return true if changed since loaded
 */
/*public*/ bool DefaultSystemConnectionMemo::isDirty() {
    return ((this->disabledAsLoaded == false || this->disabledAsLoaded != this->disabled)
            || (this->prefixAsLoaded.isNull() || this->prefixAsLoaded != (this->prefix))
            || (this->userNameAsLoaded.isNull() || this->userNameAsLoaded !=(this->userName)));
}

/*public*/ bool DefaultSystemConnectionMemo::isRestartRequired() {
    return this->isDirty();
}

/**
 * Provide access to the ConsistManager for this particular connection.
 *
 * @return the provided ConsistManager or null if the connection does not
 *         provide a ConsistManager
 */
/*public*/ ConsistManager* DefaultSystemConnectionMemo::getConsistManager() {
#if 0
    return (ConsistManager*) classObjectMap.computeIfAbsent(ConsistManager.class,(Class c) -> { return generateDefaultConsistManagerForConnection(); });
#else
    return nullptr;
#endif
}

/*private*/ ConsistManager* DefaultSystemConnectionMemo::generateDefaultConsistManagerForConnection(){
    if (provides("CommandStation")) {
        return new NmraConsistManager((CommandStation*)get("CommandStation"));
    } else if (provides("AddressedProgrammerManager")) {
        return new DccConsistManager((AddressedProgrammerManager*)get("AddressedProgrammerManager"));
    }
    return nullptr;
}

/*public*/ void DefaultSystemConnectionMemo::setConsistManager(ConsistManager* c) {
    store((Manager*)c, "ConsistManager");
    InstanceManager::store((QObject*)c, "ConsistManager");
}

/*public*/ /*<T>*/ void DefaultSystemConnectionMemo::store(/*@Nonnull*/ Manager* item, /*@Nonnull Class<T>*/QString type){
    classObjectMap.insert(type,item);
}

/*public*/ /*<T>*/ void DefaultSystemConnectionMemo::deregister(/*@Nonnull T*/Manager* item, /*@Nonnull Class<T>*/QString type){
    classObjectMap.remove(type/*,item*/);
}


/**
 * Default interval 250ms.
 * {@inheritDoc}
 */
//@Override
/*public*/ int DefaultSystemConnectionMemo::getDefaultOutputInterval(){
    return 250;
}

/**
 * Get the connection specific OutputInterval (in ms) to wait between/before commands
 * are sent, configured in AdapterConfig.
 * Used in {@link jmri.implementation.AbstractTurnout#setCommandedStateAtInterval(int)}.
 */
/*public*/ int DefaultSystemConnectionMemo::getOutputInterval() {
    log->debug(tr("Getting interval %1").arg(_interval));
    return _interval;
}

/*public*/ void DefaultSystemConnectionMemo::setOutputInterval(int newInterval) {
    log->debug(tr("Setting interval from %1 to %2").arg(_interval).arg(newInterval));
    this->propertyChangeSupport->firePropertyChange(INTERVAL, _interval, newInterval);
    _interval = newInterval;
}

/*private*/ /*static*/ /*final*/ Logger* DefaultSystemConnectionMemo::log = LoggerFactory::getLogger("DefaultSystemConnectionMemo");
