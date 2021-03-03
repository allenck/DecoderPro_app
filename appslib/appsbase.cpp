#include "appsbase.h"
#include "instancemanager.h"
#include <QApplication>
#include "layoutblockmanager.h"
#include "defaultcatalogtreemanagerxml.h"
#include "profilemanager.h"
#include "configxmlmanager.h"
#include "filehistory.h"
#include "jmriuserpreferencesmanager.h"
#include "createbuttonmodel.h"
#include "file.h"
#include "defaultshutdownmanager.h"
#include "profile.h"
#include "dialogerrorhandler.h"
#include "tabbedpreferences.h"
#include "defaultidtagmanager.h"
#include "blockvaluefile.h"
#include "system.h"
#include "metatypes.h"
#include "../operations/metatypes.h"
#include "properties.h"
#include "jmriconfigurationmanager.h"
#include "jmriuserpreferencesmanager.h"
#include "appspreferencesactionfactory.h"

AppsBase::AppsBase(QObject *parent) :
    QObject(parent)
{
 new Metatypes();
 new Operations::Metatypes();
 configDeferredLoadOK = false;
}
/**
 * Base class for the core of JMRI applications.
 * <p>
 * This provides a non-GUI base for applications. Below this is the
 * {@link apps.gui3.Apps3} subclass which provides basic Swing GUI support.
 * <p>
 * There are a series of steps in the configuration:
 * <dl>
 * <dt>preInit<dd>Initialize log4j, invoked from the main()
 * <dt>ctor<dd>
 * </dl>
 * <P>
 *
 * @author	Bob Jacobsen Copyright 2009, 2010
 * @version $Revision: 28162 $
 */
///*public*/ abstract class AppsBase {

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "MS_PKGPROTECT",
//            justification = "not a library pattern")
//    static Logger log = LoggerFactory.getLogger(AppsBase.class.getName());
/*private*/ /*final*/ /*static*/ QString AppsBase::configFilename = "/JmriConfig3.xml";
/*static*/ bool AppsBase::_preInit = false;


/**
 * Initial actions before frame is created, invoked in the applications
 * main() routine.
 */
/*static*/ /*public*/ void AppsBase::preInit(QString applicationName) {
//    Log4JUtil.initLog4J();

//    try {
//        Application.setApplicationName(applicationName);
//    } catch (IllegalAccessException ex) {
//        log->error("Unable to set application name");
//    } catch (IllegalArgumentException ex) {
//        log->error("Unable to set application name");
//    }
 QApplication::setApplicationName(applicationName);
 QApplication::setOrganizationName("ACK Software");

//    log->info(Log4JUtil.startupInfo(applicationName));

    _preInit = true;
    qsrand(QTime::currentTime().msec());
}

/**
 * Create and initialize the application object.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "SC_START_IN_CTOR",
//        justification = "The thread is only called to help improve user experiance when opening the preferences, it is not critical for it to be run at this stage")
/*public*/ AppsBase::AppsBase(QString applicationName, QString configFileDef, QStringList args, QObject *parent) :
  QObject(parent)
{
 log = new Logger("AppsBase");
 if (!_preInit)
 {
  preInit(applicationName);
  setConfigFilename(configFileDef, args);
 }
//    Log4JUtil.initLog4J();
 //QTimer::singleShot(10, this, SLOT(init())); // configureProfile() once constructor is finished.
}

void AppsBase::init()
{
 configureProfile();

 installConfigurationManager();

 installShutDownManager();

 addDefaultShutDownTasks();

 installManagers();

 setAndLoadPreferenceFile();

 FileUtil::logFilePaths();
#if 0 // TODO:
    Runnable* r;
    /*
     * Once all the preferences have been loaded we can initial the
     * preferences doing it in a thread at this stage means we can let it
     * work in the background if the file doesn't exist then we do not
     * initialize it
     */
    if (preferenceFileExists /*&& bool.getbool("java.awt.headless")*/) {
        r = new Runnable() {

            /*public*/ void run() {
                try {
                    InstanceManager::tabbedPreferencesInstance().init();
                } catch (Exception ex) {
                    log->error(ex.toString());
                }
            }
        };
        Thread thr = new Thread(r);
        thr.start();
    }
#endif
#if 0
    if (bool.getbool("org.jmri.python.preload")) {
        r = new Runnable() {

            /*public*/ void run() {
                try {
                    PythonInterp.getPythonInterpreter();
                } catch (Exception ex) {
                    log->error("Error in trying to initialize python interpreter " + ex.toString());
                }
            }
        };
        Thread thr2 = new Thread(r, "initialize python interpreter");
        thr2.start();
    }
#endif
 // all loaded, initialize objects as necessary
 ((LogixManager*)InstanceManager::getDefault("LogixManager"))->activateAllLogixs();
 ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->initializeLayoutBlockPaths();
 (new DefaultCatalogTreeManagerXml())->readCatalogTrees();

}

//void AppsBase::init()
//{
// configureProfile();
//}

/**
 * Configure the {@link jmri.profile.Profile} to use for this application.
 * <p>
 * Note that GUI-based applications must override this method, since this
 * method does not provide user feedback.
 */
/*protected*/ void AppsBase::configureProfile()
{
 QString profileFilename;
 FileUtil::createDirectory(FileUtil::getPreferencesPath());
 // Needs to be declared final as we might need to
 // refer to this on the Swing thread
 File* profileFile = NULL;
 profileFilename = getConfigFileName().replace(".xml", ".properties");
 // decide whether name is absolute or relative
 if (!(new File(profileFilename))->isAbsolute())
 {
  // must be relative, but we want it to
  // be relative to the preferences directory
  QString newPath = FileUtil::getPreferencesPath() + profileFilename;
  profileFile = new File(newPath, this);
 }
 else
 {
  profileFile = new File(profileFilename);
 }
 ProfileManager::getDefault()->setConfigFile(profileFile);
 // See if the profile to use has been specified on the command line as
 // a system property jmri.profile as a profile id.
#if 1
 if (System::getProperties()->containsKey(/*ProfileManager::SYSTEM_PROPERTY*/"org.jmri.profile"))
 {
  ProfileManager::getDefault()->setActiveProfile(System::getProperty(/*ProfileManager::SYSTEM_PROPERTY*/"org.jmri.profile"));
 }
#endif
 // @see jmri.profile.ProfileManager#migrateToProfiles JavaDoc for conditions handled here
 if (!ProfileManager::getDefault()->getConfigFile()->exists())
 { // no profile config for this app
 try
  {
   if (ProfileManager::getDefault()->migrateToProfiles(getConfigFileName()))
   {// migration or first use
    // GUI should show message here
    log->info(tr("Please ensure that the User Files location and Roster location are correct."));
   }
  }
  catch (IOException ex)
  {
   // GUI should show message here
   log->error(tr("Profiles not configurable. Using fallback per-application configuration. Error: %1").arg(ex.getMessage()));
  }
  catch (IllegalArgumentException ex)
  {
   // GUI should show message here
   log->error(tr("Profiles not configurable. Using fallback per-application configuration. Error: %1").arg(ex.getMessage()));
  }
 }
 try
 {
  // GUI should use ProfileManagerDialog->getStartingProfile here
  if (ProfileManager::getStartingProfile() != NULL)
  {
   // Manually setting the configFilename property since calling
   // Apps.setConfigFilename() does not reset the system property
   System::setProperty("org.jmri.Apps.configFilename", Profile::CONFIG_FILENAME);
   Profile* profile = ProfileManager::getDefault()->getActiveProfile();
   if (profile != nullptr) {
       log->info(tr("Starting with profile %1").arg(profile->getId()));
   } else {
       log->info("Starting without a profile");
   }
  }
  else
  {
   log->error("Specify profile to use as command line argument.");
   log->error("If starting with saved profile configuration, ensure the autoStart property is set to \"true\"");
   log->error("Profiles not configurable. Using fallback per-application configuration.");
  }
 }
 catch (IOException ex)
 {
  log->info(tr("Profiles not configurable. Using fallback per-application configuration. Error: %1").arg(ex.getMessage()));
 }
}

/*protected*/ void AppsBase::installConfigurationManager()
{
 //InstanceManager::store(new AppsPreferencesActionFactory(), "JmriPreferencesActionFactory");
 ConfigureManager* cm = (ConfigureManager*)InstanceManager::setDefault("ConfigureManager", new JmriConfigurationManager());
 FileUtil::createDirectory(FileUtil::getUserFilesPath());
// InstanceManager::setConfigureManager(cm);
// QString cfgName;
// cm->setPrefsLocation(new File(cfgName = getConfigFileName()));
// log->debug(tr("config manager installed (%1)").arg(cfgName));
// // Install Config Manager error handler
// ConfigXmlManager::setErrorHandler(new DialogErrorHandler());
 InstanceManager::store(cm, "ConfigureManager");
 InstanceManager::setDefault("ConfigureManager", cm);
 log->debug("config manager installed");
}

/*protected*/ void AppsBase::installManagers() {
 // record startup
 ((FileHistory*)InstanceManager::getDefault("FileHistory"))->addOperation("app", QApplication::applicationName(), NULL);

 // install the abstract action model that allows items to be added to the, both
 // CreateButton and Perform Action Model use a common Abstract class
 InstanceManager::store(new CreateButtonModel(), "CreateButtonModel");

}

/*protected*/ void AppsBase::setAndLoadPreferenceFile()
{
 FileUtil::createDirectory(FileUtil::getUserFilesPath());
 /*final*/ File* file;
 File* sharedConfig = nullptr;
 try {
     sharedConfig = FileUtil::getFile(FileUtil::PROFILE + Profile::SHARED_CONFIG);
     if (!sharedConfig->canRead()) {
         sharedConfig = nullptr;
     }
 } catch (FileNotFoundException ex) {
     // ignore - this only means that sharedConfig does not exist.
 }
 if (sharedConfig != nullptr) {
     file = sharedConfig;
 }
 else if (!(new File(getConfigFileName()))->isAbsolute())
 {
     // must be relative, but we want it to
     // be relative to the preferences directory
     file = new File(FileUtil::getUserFilesPath() + getConfigFileName());
 } else {
     file = new File(getConfigFileName());
 }
 // don't try to load if doesn't exist, but mark as not OK
 if (!file->exists()) {
     preferenceFileExists = false;
     configOK = false;
     log->info(tr("No pre-existing config file found, searched for '%1'").arg(file->getPath()));
     return;
 }
 preferenceFileExists = true;

 // ensure the UserPreferencesManager has loaded. Done on GUI
         // thread as it can modify GUI objects
 //ThreadingUtil.runOnGUI(() -> {
     InstanceManager::getDefault("UserPreferencesManager");
 //});

 try
 {
  ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
  if (cm != NULL)
  {
   configOK = cm->load(file);
  }
  else
  {
   configOK = false;
  }
  if (log->isDebugEnabled())
  {
   log->debug(tr("end load config file ") + file->getName() + ", OK=" + (configOK?"true":"false"));
  }
 }
 catch (Exception e)
 {
  configOK = false;
 }

 // To avoid possible locks, deferred load should be
 // performed on the Swing thread
//    if (SwingUtilities.isEventDispatchThread()) {
 configDeferredLoadOK = doDeferredLoad(file);
//    } else {
//        try {
//            // Use invokeAndWait method as we don't want to
//            // return until deferred load is completed
//            SwingUtilities.invokeAndWait(new Runnable() {

//                /*public*/ void run() {
//                    configDeferredLoadOK = doDeferredLoad(file);
//                }
//            });
//        } catch (Exception ex) {
//            log->error("Exception creating system console frame: " + ex);
//        }
//    }
}

//abstract protected void addToActionModel();
/*private*/ bool AppsBase::doDeferredLoad(File* file) {
    bool result = false;
    if (log->isDebugEnabled()) {
        log->debug("start deferred load from config file " + file->getName());
    }
    try
    {
     ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
     if (cm != NULL) {
         result = cm->loadDeferred(file);
     } else {
         log->error("Failed to get default configure manager");
         result = false;
     }
    } catch (JmriException e) {
        log->error("Unhandled problem loading deferred configuration: " + e.getMessage());
        result = false;
    }
    if (log->isDebugEnabled()) {
        log->debug("end deferred load from config file " + file->getName() + ", OK=" + result);
    }
    return result;
}

/*protected*/ void AppsBase::installShutDownManager()
{
 InstanceManager::setDefault("ShutDownManager", new DefaultShutDownManager());
}

/*protected*/ void AppsBase::addDefaultShutDownTasks()
{
    // add the default shutdown task to save blocks
    // as a special case, register a ShutDownTask to write out blocks
    ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->
      _register(new WriteBlocksShutDownTask("Writing Blocks", this));
#if 0 // done
    {

     /*public*/ bool execute() {
         // Save block values prior to exit, if necessary
         log->debug("Start writing block info");
         try {
             new BlockValueFile().writeBlockValues();
         } //catch (org.jdom2.JDOMException jde) { log->error("Exception writing blocks: "+jde); }
         catch (java.io.IOException ioe) {
             log->error("Exception writing blocks: " + ioe);
         }

         // continue shutdown
         return true;
     }
 });
#endif
}
WriteBlocksShutDownTask::WriteBlocksShutDownTask(QString text, AppsBase *base) : AbstractShutDownTask(text)
{
 this->base = base;
}
/*public*/ bool WriteBlocksShutDownTask::execute()
{
    // Save block values prior to exit, if necessary
    base->log->debug("Start writing block info");
    try {
        (new BlockValueFile())->writeBlockValues();
    } //catch (org.jdom2.JDOMException jde) { log->error("Exception writing blocks: "+jde); }
    catch (IOException ioe) {
        Logger::error("Exception writing blocks: " + ioe.getMessage());
    }

    // continue shutdown
    return true;
}


/**
 * Final actions before releasing control of app to user, invoked explicitly
 * after object has been constructed, e.g. in main().
 */
/*protected*/ void AppsBase::start()
{
    log->debug("main initialization done");
}

/**
 * Set up the configuration file name at startup.
 * <P>
 * The Configuration File name variable holds the name used to load the
 * configuration file during later startup processing. Applications invoke
 * this method to handle the usual startup hierarchy: <UL> <LI>If an
 * absolute filename was provided on the command line, use it <LI>If a
 * filename was provided that's not absolute, consider it to be in the
 * preferences directory <LI>If no filename provided, use a default name
 * (that's application specific) </UL>
 * This name will be used for reading and writing the preferences. It need
 * not exist when the program first starts up. This name may be proceeded
 * with <em>config=</em>.
 *
 * @param def Default value if no other is provided
 * @param args Argument array from the main routine
 */
/*static*/ /*protected*/ void AppsBase::setConfigFilename(QString def, QStringList args)
{
 Logger* log = new Logger("AppsBase");
 // save the configuration filename if present on the command line

 if (args.length() >= 1 && args[0] != NULL && args[0]!=("") && !args[0].contains("="))
 {
  def = args[0];
  log->debug("Config file was specified as: " + args[0]);
 }
 foreach (QString arg, args)
 {
  QStringList split = arg.split("="/*, 2*/);
  if (split.at(0).toLower()==("config"))
  {
   def = split[1];
   log->debug("Config file was specified as: " + arg);
  }
 }
 if (def != NULL)
 {
  setJmriSystemProperty("configFilename", def);
  log->debug("Config file set to: " + def);
 }
}

// We will use the value stored in the system property
// TODO: change to return profile-name/profile.xml
/*static*/ /*public*/ QString AppsBase::getConfigFileName()
{
 if (System::getProperty("org.jmri.Apps.configFilename") != NULL)
 {
  return System::getProperty("org.jmri.Apps.configFilename");
 }
 return configFilename;
}

/*static*/ /*protected*/ void AppsBase::setJmriSystemProperty(QString key, QString value)
{
#if 1
 Logger* log = new Logger("AppsBase");
 try
 {
  QString current = System::getProperty("org.jmri.Apps." + key);
  if (current == NULL)
  {
   System::setProperty("org.jmri.Apps." + key, value);
  }
  else if (current!=(value))
  {
   log->warn("JMRI property " + key + " already set to " + current
              + ", skipping reset to " + value);
  }
 }
 catch (Exception e)
 {
  Logger::error("Unable to set JMRI property " + key + " to " + value
                + "due to exception: " + e.getMessage());
 }
#endif
}

/**
 * The application decided to quit, handle that.
 */
/*static*/ /*public*/ bool AppsBase::handleQuit() {
    Logger* log  = new Logger("AppsBase");

    log->debug("Start handleQuit");
    try {
        return ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->shutdown();
    } catch (Exception e) {
        log->error("Continuing after error in handleQuit");
    }
    return false;
}

/**
 * The application decided to restart, handle that.
 */
/*static*/ /*public*/ bool AppsBase::handleRestart() {
    Logger* log = new Logger("AppsBase");
    log->debug("Start handleRestart");
    try {
        return ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->restart();
    } catch (Exception e) {
        log->error("Continuing after error in handleRestart");
    }
    return false;
}
