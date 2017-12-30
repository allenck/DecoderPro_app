#include "jmriconfigurationmanager.h"
#include "profilemanager.h"
#include "configxmlmanager.h"
#include "profile.h"
#include "instancemanager.h"
#include "fileutil.h"
#include "file.h"
#include "preferencesmanager.h"
#include "serviceloader.h"
#include "jlist.h"
#include <QMessageBox>
#include <QApplication>
#include <QLayout>
#include <QLabel>

//JmriConfigurationManager::JmriConfigurationManager()
//{

//}
/**
 *
 * @author Randall Wood
 */
// /*public*/ class JmriConfigurationManager implements ConfigureManager {


//@SuppressWarnings("unchecked") // For types in InstanceManager.store()
/*public*/ JmriConfigurationManager::JmriConfigurationManager(QObject* parent) : ConfigXmlManager(parent)
{
 setObjectName("JmriConfigurationManager");
 log = new Logger("JmriConfigurationManager");
 legacy = new ConfigXmlManager();
 initializationExceptions = new QHash<PreferencesManager*, InitializationException*>();
 initialized = new QList<PreferencesManager*>();

 //ServiceLoader<PreferencesManager> sl = ServiceLoader.load(PreferencesManager.class);
#if 0
    ServiceLoader<PreferencesManager>* sl = ServiceLoader<PreferencesManager>::load("PreferencesManager");

    for (PreferencesManager pp : sl) {
        InstanceManager.store(pp, PreferencesManager.class);
        for (Class provided : pp.getProvides()) { // use raw class so next line can compile
            InstanceManager.store(provided.cast(pp), provided);
        }
    }
#else
 QList<QString> lst = QList<QString>()
  << "StartupActionsManager" << "GuiLafPreferencesManager" << "SystemConsolePreferencesManager"
     << "FileLocationsPreferences" << "ManagerDefaultSelector" << "WarrantPreferences" << "RosterConfigManager"
     << "ProgrammerConfigManager" << "ConnectionConfigManager" << "JmriJTablePersistenceManager";

 foreach (QString name, lst)
 {
  PreferencesManager* pp = (PreferencesManager*)InstanceManager::getNullableDefault(name);
//  QList<PreferencesManager*> l = pp->getProvides();
//  foreach (PreferencesManager* provided, *pp->getProvides())
//  {
//   InstanceManager::store(provided, name);
//  }
  if(pp == NULL)
   continue;
  InstanceManager::store(pp, "PreferencesManager");
 }
#endif
// if (ProfileManager::getDefault() == NULL)
//  ProfileManagerHolder::manager = new ProfileManager();
    if (ProfileManager::getDefault()->getActiveProfile() != NULL) {
        this->legacy->setPrefsLocation(new File(ProfileManager::getDefault()->getActiveProfile()->getPath(), /*Profile::CONFIG_FILENAME*/"ProfileConfig.xml"));
    }
#if 0
    if (!GraphicsEnvironment.isHeadless()) {
        ConfigXmlManager.setErrorHandler(new DialogErrorHandler());
    }
#endif
}

//@Override
/*public*/ void JmriConfigurationManager::registerPref(QObject* o) {
    //if ((o instanceof PreferencesManager)) {
    if(qobject_cast<PreferencesManager*>(o) != NULL)
    {
        InstanceManager::store((PreferencesManager*) o, "PreferencesManager");
    }
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

//@Override
/*public*/ QObject* JmriConfigurationManager::findInstance(QString c, int index) {
    return this->legacy->findInstance(c, index);
}

//@Override
/*public*/ QList<QObject*> JmriConfigurationManager::getInstanceList(QString c) {
    return this->legacy->getInstanceList(c);
}

//@Override
/*public*/ bool JmriConfigurationManager::storeAll(File* file) {
    return this->legacy->storeAll(file);
}

/**
 * Save preferences. Preferences are saved using either the
 * {@link jmri.util.prefs.JmriConfigurationProvider} or
 * {@link jmri.util.prefs.JmriPreferencesProvider} as appropriate to the
 * register preferences handler.
 */
//@Override
/*public*/ void JmriConfigurationManager::storePrefs()
{
 log->debug("Saving preferences...");
 Profile* profile = ProfileManager::getDefault()->getActiveProfile();
//    InstanceManager::getList(PreferencesManager.class).stream().forEach((o) -> {
//        log.debug("Saving preferences for {}", o.getClass().getName());
//        o.savePreferences(profile);
//    });
 foreach (QObject* o, *InstanceManager::getList("PreferencesManager"))
 {
  log->debug(tr("Saving preferences for %1").arg(o->metaObject()->className()));
  ((PreferencesManager*)o)->savePreferences(profile);
 }
}

/**
 * Save preferences. This method calls {@link #storePrefs() }.
 *
 * @param file Ignored.
 */
//@Override
/*public*/ void JmriConfigurationManager::storePrefs(File* file) {
    this->storePrefs();
}

//@Override
/*public*/ void JmriConfigurationManager::storeUserPrefs(File* file) {
    this->legacy->storeUserPrefs(file);
}

//@Override
/*public*/ bool JmriConfigurationManager::storeConfig(File* file) {
    return this->legacy->storeConfig(file);
}

//@Override
/*public*/ bool JmriConfigurationManager::storeUser(File* file)
{
    return this->legacy->storeUser(file);
}

//@Override
/*public*/ bool JmriConfigurationManager::load(File* file)  throw (JmriException)
{
    return this->load(file, false);
}

//@Override
/*public*/ bool JmriConfigurationManager::load( QUrl file)  throw (JmriException)
{
    return this->load(file, false);
}

//@Override
/*public*/ bool JmriConfigurationManager::load(File* file, bool registerDeferred)  throw (JmriException)
{
    return this->load(FileUtil::fileToURL(file), registerDeferred);
}

//@Override
/*public*/ bool JmriConfigurationManager::load(QUrl file, bool registerDeferred)  throw (JmriException)
{
 log->debug(tr("loading %1 ...").arg(file.fileName()));
 try {
  if (file.isEmpty()
          || (File(file.toDisplayString()).getName() == ("ProfileConfig.xml")) //NOI18N
          || (File(file.toDisplayString()).getName() == (/*Profile::CONFIG*/"profile.xml")))
  {
   Profile* profile = ProfileManager::getDefault()->getActiveProfile();
   QObjectList* providers =  InstanceManager::getList("PreferencesManager");
   //providers.stream().forEach((provider) -> {
   foreach(QObject* provider, *providers)
   {
    this->initializeProvider((PreferencesManager*)provider, profile);
   }//);
   //foreach(QObject* provider, *providers)
   if (!this->initializationExceptions->isEmpty())
   {
//                if (!GraphicsEnvironment.isHeadless()) {
    QList<QString>* errors = new QList<QString>();
    //this.initialized.forEach((provider) ->
    foreach(PreferencesManager* provider, *this->initialized)
    {
     QList<Exception*>* exceptions = provider->getInitializationExceptions(profile);
     if (!exceptions->isEmpty()) {
         //exceptions.forEach((exception) ->
      foreach(Exception* exception, *exceptions)
      {
          errors->append(exception->getLocalizedMessage());
      } //);
     } else if (this->initializationExceptions->value(provider) != NULL) {
         errors->append(this->initializationExceptions->value(provider)->getLocalizedMessage());
     }
    } //);
    QObject* list = NULL;
    if (errors->size() == 1) {
//                        list = *errors->at(0);
    } else {
        list = new JList(*errors);
    }
#if 0
    JOptionPane.showMessageDialog(NULL,
            new Object[]{
                (list instanceof JList) ? Bundle.getMessage("InitExMessageListHeader") : NULL,
                list,
                "<html><br></html>", // Add a visual break between list of errors and notes // NOI18N
                Bundle.getMessage("InitExMessageLogs"), // NOI18N
                Bundle.getMessage("InitExMessagePrefs"), // NOI18N
            },
            Bundle.getMessage("InitExMessageTitle", Application.getApplicationName()), // NOI18N
            JOptionPane.ERROR_MESSAGE);
    (new TabbedPreferencesAction()).actionPerformed();
#else
     QMessageBox box(QMessageBox::Critical, tr("Error initializing %1").arg(QApplication::applicationName()), QString("<html><br></html>") + tr("Please check the logs for more details.") + tr("The Preferences window will open so this can be fixed."));
     if(errors->size()==1)
       box.layout()->addWidget(new QLabel(errors->at(0)));
     else
      box.layout()->addWidget(new JList(*errors));
     box.exec();
#endif
//                }

   }
   if (!file.isEmpty() && (File(file.toDisplayString())).getName() == ("ProfileConfig.xml"))
   { // NOI18N
    log->debug("Loading legacy configuration...");
    return this->legacy->load(file, registerDeferred);
   }
   return this->initializationExceptions->isEmpty();
  }
 }
 catch (/*URISyntax*/Exception ex)
 {
     log->error(tr("Unable to get File* for %1").arg(file.toDisplayString()));
     throw new JmriException(ex.getMessage()+ex.getLocalizedMessage());
 }
 return this->legacy->load(file, registerDeferred);
 // return true; // always return true once legacy support is dropped
}

//@Override
/*public*/ bool JmriConfigurationManager::loadDeferred(File* file)  throw (JmriException)
{
    return this->legacy->loadDeferred(file);
}

//@Override
/*public*/ bool JmriConfigurationManager::loadDeferred( QUrl file)  throw (JmriException)
{
    return this->legacy->loadDeferred(file);
}

//@Override
/*public*/  QUrl JmriConfigurationManager::find(QString filename) {
    return this->legacy->find(filename);
}

//@Override
/*public*/ bool JmriConfigurationManager::makeBackup(File* file) {
    return this->legacy->makeBackup(file);
}

/*private*/ void JmriConfigurationManager::initializeProvider( PreferencesManager* provider, Profile* profile)
{
 if (!provider->isInitialized(profile) && !provider->isInitializedWithExceptions(profile))
 {
  log->debug(tr("Initializing provider %1").arg(provider->metaObject()->className()));
//        foreach (QString extends PreferencesManager> c : provider.getRequires()) {
//            InstanceManager.getList(c).stream().forEach((p) -> {
//                this.initializeProvider(p, profile);
//            });
//        }
  foreach(QString classname, *provider->getRequires())
  {
   PreferencesManager* p = (PreferencesManager*) InstanceManager::getDefault(classname);
   if(p != NULL)
   this->initializeProvider(p,profile);
  }
  try {
      provider->initialize(profile);
  }
  catch (InitializationException ex)
  {
   // log all initialization exceptions, but only retain for GUI display the
   // first initialization exception for a provider
   //            InitializationException put = this->initializationExceptions->putIfAbsent(provider, ex);
   bool bPut = this->initializationExceptions->contains(provider);
   if(!bPut)
    this->initializationExceptions->insert((PreferencesManager*)provider, &ex);
   log->error(tr("Exception initializing %1: %2").arg(provider->metaObject()->className()).arg(ex.getMessage()));
   if (bPut)
   {
       log->error(tr("Additional exception initializing %1: %1").arg(provider->metaObject()->className()).arg(ex.getMessage()));
   }
  }
  this->initialized->append(provider);
  log->debug(tr("Initialized provider %1").arg(provider->metaObject()->className()));
 }
}
