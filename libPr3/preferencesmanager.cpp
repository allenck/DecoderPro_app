#include "preferencesmanager.h"
#include "profile.h"

class Exception;
/**
 * An API for Java Service Providers that manage preferences within JMRI. It is
 * strongly recommended that PreferencesManagers use
 * {@link jmri.util.prefs.JmriConfigurationProvider} or
 * {@link jmri.util.prefs.JmriPreferencesProvider} to store preferences.
 *
 * PreferencesManagers must provide a default public constructor, but must also
 * not perform any initialization until
 * {@link #initialize(jmri.profile.Profile)} is called as the PreferencesManager
 * may be constructed before the {@link jmri.profile.Profile} is known.
 *
 * @see jmri.util.prefs.AbstractPreferencesManager for an abstract
 * implementation that is ready to extend.
 * @author Randall Wood 2015
 */
///*public*/ interface PreferencesManager extends JmriServiceProviderInterface {

// PreferencesManager::PreferencesManager(QObject *parent) : QObject(parent) {}

/**
 * Initialize the PreferencesManager with preferences associated with the
 * provided Profile.
 *
 * Implementing classes should throw an InitializationException with a user
 * readable localized message, since it most likely be displayed to the
 * user. Implementing classes will still want to ensure that isInitialized
 * returns true if throwing an InitializationException to ensure that the
 * provider is not repeatedly initialized.
 *
 */
///*public*/ void PreferencesManager::initialize(/*@Nonnull*/ Profile* /*profile*/) /*throw (InitializationException)*/ {}

/**
 * Test if the PreferencesManager is initialized for the provided Profile.
 *
 * @return true if the provider is initialized.
 */
/*public*/ bool PreferencesManager::isInitialized(/*@Nonnull*/ Profile* /*profile*/) {return false;}

/**
     * Test if the PreferencesManager is initialized, but threw an
     * {@link InitializationException} during initialization, for the provided
     * Profile. Note that although both this method and
     * {@link #isInitialized(jmri.profile.Profile)} can be false, if
     * isInitialized(Profile) returns true, this method must return false.
     *
     * @param profile the configuration profile to test against
     * @return true if the provide is initialized with exceptions
     */
    /*public*/ bool PreferencesManager::isInitializedWithExceptions(/*@Nonnull */Profile* /*profile*/) {return false;}

    /**
     * Get the set of exceptions thrown during initialization for the provided
     * Profile.
     *
     * @param profile the configuration profile to test against
     * @return A list of exceptions. If there are no exceptions, return an empty
     *         set instead of null.
     */
    //@Nonnull
     //QList<Exception *> PreferencesManager::getInitializationExceptions(/*@Nonnull */Profile* /*profile*/) {return NULL;}

/**
 * Get the set of PreferencesProviders that must be initialized prior to
 * initializing this PreferencesManager. It is generally preferable to
 * require an Interface or an abstract Class instead of a concrete Class,
 * since that allows all (or any) concrete implementations of the required
 * class to be initialized to provide required services for the requiring
 * PreferencesManager instance.
 *
 * @return An set or list of classes. If there are no dependencies, return
 *         an empty set instead of null.
 */
/*public*/ /*@Nonnull*/
//Iterable<Class<? extends PreferencesManager>> getRequires();
//template<class T>
///*public*/ QList<T>* PreferencesManager::getRequires() {return NULL;}
QSet<QString>* PreferencesManager::getRequires() {
 return new QSet<QString>();
}
/**
 * Get the set of Classes that this PreferencesManager can be registered as
 * a provider of in the {@link jmri.InstanceManager}.
 *
 * @return An set or list of classes. If this PreferencesManager provides an
 *         instance of no other Interfaces or abstract Classes than
 *         PreferencesManager, return an empty set instead of null.
 */
/*public*/ /*@Nonnull*/
//Iterable<Class<?>> getProvides();
//template <class T>
///*public*/ QList<T>* PreferencesManager::getProvides() {return NULL;}
QSet<QString>* PreferencesManager::getProvides() {return NULL;}
