#include "jmriconfigurationmanager.h"
#include "preferencesmanager.h"
#include "instancemanager.h"
#include "profilemanager.h"
#include "configxmlmanager.h"
#include "profile.h"
#include "file.h"

/**
 *
 * @author Randall Wood
 */
///*public*/ class JmriConfigurationManager implements ConfigureManager {

//@SuppressWarnings("unchecked") // For types in InstanceManager.store()
/*public*/ JmriConfigurationManager::JmriConfigurationManager(QObject* parent)  : ConfigureManager(parent)
{
#if 0 // ServiceLoader hard coded for now
    ServiceLoader<PreferencesManager*> sl = ServiceLoader::load("PreferencesManager");
    for (PreferencesManager* pp : sl) {
        InstanceManager::store(pp, "PreferencesManager");
        for (Class provided : pp.getProvides()) { // use raw class so next line can compile
            InstanceManager::store(provided.cast(pp), provided);
        }
    }
#else
#include "connectionconfigmanager.h"
 PreferencesManager* pp = (PreferencesManager*)new ConnectionConfigManager();
 InstanceManager::store(pp, "PreferencesManager");
#endif
    if (ProfileManager::getDefault()->getActiveProfile() != NULL) {
        this->legacy->setPrefsLocation(new File(ProfileManager::getDefault()->getActiveProfile()->getPath(), Profile::CONFIG_FILENAME));
    }
#if 0
    if (!GraphicsEnvironment.isHeadless()) {
        ConfigXmlManager::setErrorHandler(new DialogErrorHandler());
    }
#endif
}

//@Override
/*public*/ void JmriConfigurationManager::registerPref(QObject* o) {
//    if ((o instanceof PreferencesManager)) {
//        InstanceManager.store((PreferencesManager) o, PreferencesManager.class);
//    }
 if(qobject_cast<PreferencesManager*>(o) != NULL)
    this->legacy->registerPref(o);
}

//@Override
/*public*/ void JmriConfigurationManager::removePrefItems() {
    this->legacy->removePrefItems();
}

//@Override
/*public*/ void JmriConfigurationManager::registerConfig(QObject* o) {
    this->legacy->registerConfig(o);
}

//@Override
/*public*/ void JmriConfigurationManager::registerConfig(QObject* o, int x) {
    this->legacy->registerConfig(o, x);
}

//@Override
/*public*/ void JmriConfigurationManager::registerTool(QObject* o) {
    this->legacy->registerTool(o);
}

//@Override
/*public*/ void JmriConfigurationManager::registerUser(QObject* o) {
    this->legacy->registerUser(o);
}

//@Override
/*public*/ void JmriConfigurationManager::registerUserPrefs(QObject* o) {
    this->legacy->registerUserPrefs(o);
}

//@Override
/*public*/ void JmriConfigurationManager::deregister(QObject* o) {
    this->legacy->deregister(o);
}
#if 0
//@Override
/*public*/ QObject* findInstance(Class<?> c, int index) {
    return this->legacy->findInstance(c, index);
}

//@Override
/*public*/ ArrayList<Object> getInstanceList(Class<?> c) {
    return this->legacy->getInstanceList(c);
}

//@Override
/*public*/ bool storeAll(File file) {
    return this->legacy->storeAll(file);
}

/**
 * Save preferences. Preferences are saved using either the
 * {@link jmri.util.prefs.JmriConfigurationProvider} or
 * {@link jmri.util.prefs.JmriPreferencesProvider} as appropriate to the
 * register preferences handler.
 */
//@Override
/*public*/ void storePrefs() {
    log.debug("Saving preferences...");
    Profile profile = ProfileManager.getDefault().getActiveProfile();
    InstanceManager.getList(PreferencesManager.class).stream().forEach((o) -> {
        log.debug("Saving preferences for {}", o.getClass().getName());
        o.savePreferences(profile);
    });
}

/**
 * Save preferences. This method calls {@link #storePrefs() }.
 *
 * @param file Ignored.
 */
//@Override
/*public*/ void storePrefs(File file) {
    this.storePrefs();
}

//@Override
/*public*/ void storeUserPrefs(File file) {
    this->legacy->storeUserPrefs(file);
}

//@Override
/*public*/ bool storeConfig(File file) {
    return this->legacy->storeConfig(file);
}

//@Override
/*public*/ bool storeUser(File file) {
    return this->legacy->storeUser(file);
}

//@Override
/*public*/ bool load(File file) throws JmriException {
    return this.load(file, false);
}

//@Override
/*public*/ bool load(URL file) throws JmriException {
    return this.load(file, false);
}

//@Override
/*public*/ bool load(File file, bool registerDeferred) throws JmriException {
    return this.load(FileUtil.fileToURL(file), registerDeferred);
}

//@Override
/*public*/ bool load(URL file, bool registerDeferred) throws JmriException {
    log.debug("loading {} ...", file);
    try {
        if (file == null
                || (new File(file.toURI())).getName().equals("ProfileConfig.xml") //NOI18N
                || (new File(file.toURI())).getName().equals(Profile.CONFIG)) {
            List<PreferencesManager> providers = new ArrayList<>(InstanceManager.getList(PreferencesManager.class));
            providers.stream().forEach((provider) -> {
                this.initializeProvider(provider, ProfileManager.getDefault().getActiveProfile());
            });
            if (!this.initializationExceptions.isEmpty()) {
                if (!GraphicsEnvironment.isHeadless()) {
                    String[] errors = new String[this.initializationExceptions.size()];
                    int i = 0;
                    for (InitializationException e : this.initializationExceptions.values()) {
                        errors[i] = e.getLocalizedMessage();
                        i++;
                    }
                    Object list;
                    if (this.initializationExceptions.size() == 1) {
                        list = errors[0];
                    } else {
                        list = new JList<>(errors);
                    }
                    JOptionPane.showMessageDialog(null,
                            new Object[]{
                                list,
                                "<html><br></html>", // Add a visual break between list of errors and notes // NOI18N
                                Bundle.getMessage("InitExMessageLogs"), // NOI18N
                                Bundle.getMessage("InitExMessagePrefs"), // NOI18N
                            },
                            Bundle.getMessage("InitExMessageTitle", Application.getApplicationName()), // NOI18N
                            JOptionPane.ERROR_MESSAGE);
                    (new TabbedPreferencesAction()).actionPerformed();
                }
            }
            if (file != null && (new File(file.toURI())).getName().equals("ProfileConfig.xml")) { // NOI18N
                log.debug("Loading legacy configuration...");
                return this->legacy->load(file, registerDeferred);
            }
            return this.initializationExceptions.isEmpty();
        }
    } catch (URISyntaxException ex) {
        log.error("Unable to get File for {}", file);
        throw new JmriException(ex.getMessage(), ex);
    }
    return this->legacy->load(file, registerDeferred);
    // return true; // always return true once legacy support is dropped
}

//@Override
/*public*/ bool loadDeferred(File file) throws JmriException {
    return this->legacy->loadDeferred(file);
}

//@Override
/*public*/ bool loadDeferred(URL file) throws JmriException {
    return this->legacy->loadDeferred(file);
}

//@Override
/*public*/ URL find(String filename) {
    return this->legacy->find(filename);
}

//@Override
/*public*/ bool makeBackup(File file) {
    return this->legacy->makeBackup(file);
}

/*private*/ bool initializeProvider(PreferencesManager provider, Profile profile) {
    if (!provider.isInitialized(profile)) {
        log.debug("Initializing provider {}", provider.getClass());
        for (Class<? extends PreferencesManager> c : provider.getRequires()) {
            InstanceManager.getList(c).stream().forEach((p) -> {
                this.initializeProvider(p, profile);
            });
        }
        try {
            provider.initialize(profile);
        } catch (InitializationException ex) {
            // log all initialization exceptions, but only retain for GUI display the
            // first initialization exception for a provider
            InitializationException put = this.initializationExceptions.putIfAbsent(provider, ex);
            log.error("Exception initializing {}: {}", provider.getClass().getName(), ex.getMessage());
            if (put != null) {
                log.error("Additional exception initializing {}: {}", provider.getClass().getName(), ex.getMessage());
            }
        }
        log.debug("Initialized provider {}", provider.getClass());
    }
    return provider.isInitialized(profile);
}

/*public*/ QMap<PreferencesManager*, InitializationException> getInitializationExceptions() {
    return new HashMap<>(initializationExceptions);
}
#endif
