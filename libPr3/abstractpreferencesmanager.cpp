#include "abstractpreferencesmanager.h"
#include <QHash>
#include <QSet>
#include "instancemanager.h"
#include "loggerfactory.h"
AbstractPreferencesManager::AbstractPreferencesManager(QObject* parent) : Bean(parent)
{
}
/**
 * An abstract PreferencesManager that implements some of the boilerplate that
 * PreferencesManager implementations would otherwise require.
 *
 * @author Randall Wood (C) 2015
 */
///*public*/ abstract class AbstractPreferencesManager extends Bean implements PreferencesManager {


//@Override
/*public*/ bool AbstractPreferencesManager::isInitialized(/*@Nonnull*/ Profile* profile) {
//    return this->initialized.getOrDefault(profile, false)
//            && this->exceptions.getOrDefault(profile, new QList<Exception>()).isEmpty();
 return this->initialized.value(profile, false)
   && this->exceptions.value(profile, new QList<Exception*>())->isEmpty();
}

//@Override
/*public*/ bool AbstractPreferencesManager::isInitializedWithExceptions(/*@Nonnull*/ Profile* profile) {
//    return this->initialized.getOrDefault(profile, false)
//            && !this->exceptions.getOrDefault(profile, new QList<Exception>()).isEmpty();
 bool b  = this->initialized.value(profile, false)
   && !this->exceptions.value(profile, new QList<Exception*>())->isEmpty();
 return b;
}

//@Override
/*public*/ QList<Exception *> AbstractPreferencesManager::getInitializationExceptions(/*@Nonnull*/ Profile* profile) {
    //return new QList<Exception>(this->exceptions.getOrDefault(profile, new QList<Exception>()));
 return  QList<Exception*>(*this->exceptions.value(profile, new QList<Exception*>()));
}

/**
 * Test if the manager is being initialized.
 *
 * @param profile the profile against which the manager is being initialized
 * @return true if being initialized; false otherwise
 */
/*protected*/ bool AbstractPreferencesManager::isInitializing(/*@Nonnull*/ Profile* profile)
{
 return !this->initialized.value(profile, false) && this->initializing.value(profile, false);
}
#if 0
/**
 * Get the set of PreferencesProviders that must be initialized prior to
 * initializing this PreferencesManager. It is generally preferable to
 * require an Interface or an abstract Class instead of a concrete Class,
 * since that allows all (or any) concrete implementations of the required
 * class to be initialized to provide required services for the requiring
 * PreferencesManager instance.
 *
 * This implementation includes a default dependency on the
 * {@link jmri.jmrix.ConnectionConfigManager}.
 *
 * @return An set of classes. If there are no dependencies, return an empty
 *         set instead of null.
 */
//@Override
/*@Nonnull*/
/*public*/ Set<Class<? extends PreferencesManager>> getRequires() {
    Set<Class<? extends PreferencesManager>> requires = new HashSet<>();
    requires.add(ConnectionConfigManager.class);
    return requires;
}
#else
/*public*/ QSet<QString>* AbstractPreferencesManager::getRequires()
{
 QSet<QString>* requires = new QSet<QString>();
 requires->insert("ConnectionConfigManager");
 return requires;
}
#endif

#if 0
/**
 * Get the set of Classes that this PreferencesManager can be registered as
 * a provider of in the {@link jmri.InstanceManager}.
 *
 * This implementation returns the class of the object against which this
 * method is called.
 *
 * @return An set of classes. If this PreferencesManager provides an
 *         instance of no other Interfaces or abstract Classes than
 *         PreferencesManager, return an empty set instead of null.
 */
////@Override
///*@Nonnull*/
/*public*/ Set<Class<?>> getProvides() {
    Set<Class<?>> provides = new HashSet<>();
    provides.add(this->getClass());
    return provides;
}
#else
/*public*/ QSet<QString>* AbstractPreferencesManager::getProvides()
{
 QSet<QString>* provides = new QSet<QString>();
 provides->insert(this->metaObject()->className());
 return provides;
}

#endif
/**
 * Set the initialized state for the given profile. Sets
 * {@link #isInitializing(jmri.profile.Profile)} to false if setting
 * initialized to false.
 *
 * @param profile     the profile to set initialized against
 * @param initialized the initialized state to set
 */
/*protected*/ void AbstractPreferencesManager::setInitialized(/*@Nonnull*/ Profile* profile, bool initialized) {
    this->initialized.insert(profile, initialized);
    if (initialized) {
        this->setInitializing(profile, false);
    }
}

/**
 * Protect against circular attempts to initialize during initialization.
 *
 * @param profile      the profile for which initializing is ongoing
 * @param initializing the initializing state to set
 */
/*protected*/ void AbstractPreferencesManager::setInitializing(/*@Nonnull*/ Profile* profile, bool initializing) {
    this->initializing.insert(profile, initializing);
}

/**
 * Add an error to the list of exceptions.
 *
 * @param profile   the profile against which the manager is being
 *                  initialized
 * @param exception the exception to add
 */
/*protected*/ void AbstractPreferencesManager::addInitializationException(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ Exception* exception) {
    if (this->exceptions.value(profile) == NULL) {
        this->exceptions.insert(profile, new QList<Exception*>());
    }
    this->exceptions.value(profile)->append(exception);
}

/**
 * Require that instances of the specified classes have initialized
 * correctly. This method should only be called from within
 * {@link #initialize(jmri.profile.Profile)}, generally immediately after
 * the PreferencesManager verifies that it is not already initialized. If
 * this method is within a try-catch block, the exception it generates
 * should be re-thrown by initialize(profile).
 *
 * @param profile the profile against which the manager is being initialized
 * @param classes the manager classes for which all calling
 *                {@link #isInitialized(jmri.profile.Profile)} must return
 *                true against all instances of
 * @param message the localized message to display if an
 *                InitializationExcpetion is thrown
 * @throws InitializationException  if any instance of any class in classes
 *                                  returns false on isIntialized(profile)
 * @throws IllegalArgumentException if any member of classes is not also in
 *                                  the set of classes returned by
 *                                  {@link #getRequires()}
 */
/*protected*/ void AbstractPreferencesManager::requiresNoInitializedWithExceptions(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ /*Set<Class<? extends PreferencesManager>> */QSet<QString>* classes, /*@Nonnull*/ QString message) //throws InitializationException
{
#if 0
 classes.stream().filter((clazz) -> (!this->getRequires().contains(clazz))).forEach((clazz) ->
 {
     throw new IllegalArgumentException("Class " + clazz.getClass().getName() + " not marked as required by " + this->metaObject()->className();
 });
#else
 foreach(QString clazz, *classes)
 {
  if (!this->getRequires()->contains(clazz))
   throw new IllegalArgumentException("Class " + clazz + " not marked as required by " + this->metaObject()->className());
 }
#endif
 foreach (/*Class<? extends PreferencesManager>*/QString clazz , classes->toList())
 {
  foreach (QObject* instance,  *InstanceManager::getList(clazz))
  {
   if (((AbstractPreferencesManager*)instance)->isInitializedWithExceptions(profile))
   {
       InitializationException* exception =  new InitializationException("Refusing to initialize", message,NULL);
       log->debug(tr("throw exception on class '%1' msg: '%2', local msg '%3'").arg(clazz).arg(exception->getMessage()).arg(exception->getLocalizedMessage()));
       this->addInitializationException(profile, exception);
       this->setInitialized(profile, true);
       //throw exception;
   }
  }
 }
}

/**
 * Require that instances of the specified classes have initialized
 * correctly. This method should only be called from within
 * {@link #initialize(jmri.profile.Profile)}, generally immediately after
 * the PreferencesManager verifies that it is not already initialized. If
 * this method is within a try-catch block, the exception it generates
 * should be re-thrown by initialize(profile).
 *
 * @param profile the profile against which the manager is being initialized
 * @param classes the manager classes for which all calling
 *                {@link #isInitialized(jmri.profile.Profile)} must return
 *                true against all instances of
 * @param message the localized message to display if an
 *                InitializationExcpetion is thrown
 * @throws InitializationException  if any instance of any class in classes
 *                                  returns false on isIntialized(profile)
 * @throws IllegalArgumentException if any member of classes is not also in
 *                                  the set of classes returned by
 *                                  {@link #getRequires()}
 */
/*protected*/ void AbstractPreferencesManager::requiresNoInitializedWithExceptions(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ QString message) //throws InitializationException
{
    this->requiresNoInitializedWithExceptions(profile, this->getRequires(), message);
}

Logger* AbstractPreferencesManager::log = LoggerFactory::getLogger("AbstractPreferencesManager");
