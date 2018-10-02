#include "preferencesbean.h"
#include "propertychangesupport.h"
#include "profile.h"

/**
 * Bean that implements some common code for preferences objects.
 *
 * @author Randall Wood (C) 2017
 */
// /*public*/ abstract class PreferencesBean extends Bean {

/**
 * Property indicating preferences item do/do not need to be saved.
 *
 * {@value #DIRTY}
 */
/*public*/ /*static*/ /*final*/ QString PreferencesBean::DIRTY = "dirty"; // NOI18N
/*public*/ /*static*/ /*final*/ QString PreferencesBean::RESTART_REQUIRED = "restartRequired"; // NOI18N

/**
 * Create the PreferencesBean.
 *
 * @param profile the Profile this PreferencesBean is associated with; if
 * null is not associated with a Profile, but applies application wide
 */
/*public*/ PreferencesBean::PreferencesBean(Profile* profile, QObject* parent) : Bean(parent)
{
 restartRequired = false;
 _isDirty = false;

    this->profile = profile;
}

/**
 * Get the profile associated with this PreferencesBean.
 *
 * @return the profile
 */
//@Nonnull
/*public*/ Profile* PreferencesBean::getProfile() {
    return this->profile;
}

/**
 * Check if this preferences bean has a state that needs to be saved.
 *
 * @return true if unsaved; false otherwise
 */
/*public*/ bool PreferencesBean::isDirty() {
    return this->_isDirty;
}

/**
 * Check if this preferences bean requires the application to be restarted
 * to take effect.
 *
 * @return true if a restart is required; false otherwise
 */
/*public*/ bool PreferencesBean::isRestartRequired() {
    return this->restartRequired;
}

/**
 * Set if restart needs to be required for some preferences to take effect.
 */
/*protected*/ void PreferencesBean::setRestartRequired() {
    if (!this->restartRequired) {
        this->restartRequired = true;
        this->firePropertyChange(RESTART_REQUIRED, false, true);
    }
}

/**
 * Set if preferences need to be saved.
 *
 * @param value true to indicate need to save; false otherwise
 */
/*protected*/ void PreferencesBean::setIsDirty(bool value) {
    bool old = this->_isDirty;
    if (old != value) {
        this->_isDirty = value;
        this->firePropertyChange(DIRTY, old, value);
    }
}

//@Override
/*protected*/ void PreferencesBean::firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue) {
    this->propertyChangeSupport->firePropertyChange(propertyName, oldValue, newValue);
    if (DIRTY != (propertyName)) {
        this->setIsDirty(true);
    }
}

//@Override
/*protected*/ void PreferencesBean::firePropertyChange(QString propertyName, bool oldValue, bool newValue) {
    this->propertyChangeSupport->firePropertyChange(propertyName, oldValue, newValue);
    if (DIRTY != (propertyName)) {
        this->setIsDirty(true);
    }
}

//@Override
/*protected*/ void PreferencesBean::firePropertyChange(QString propertyName, int oldValue, int newValue) {
    this->propertyChangeSupport->firePropertyChange(propertyName, oldValue, newValue);
    if (DIRTY != (propertyName)) {
        this->setIsDirty(true);
    }
}
