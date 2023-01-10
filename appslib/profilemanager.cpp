#include "profilemanager.h"
#include "file.h"
#include <QUuid>
#include "profile.h"
#include <QFileInfo>
#include "fileutil.h"
#include "xmlfile.h"
#include "propertychangeevent.h"
#include "rosterentry.h"
#include <QApplication>
#include "properties.h"
#include "system.h"
#include <QtXml>
#include "roster.h"
#include "quazip.h"
#include "quazipfile.h"
#include <QDataStream>
#include "xmlfile.h"
#include <QGlobalStatic>
#include "file.h"
#include "vptr.h"
#include "instancemanager.h"
#include "filelocationspreferences.h"
#include "rosterconfigmanager.h"
#include "fileoutputstream.h"
#include "roster.h"

//ProfileManager::ProfileManager(QObject *parent) :
//    QObject(parent)
//{

//}
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _ACTIVE_PROFILE, ("activeProfile"))
/*public*/ /*static*/ /*final*/ QString ProfileManager::ACTIVE_PROFILE = "activeProfile"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _NEXT_PROFILE, ("nextProfile"))
/*public*/ /*static*/ /*final*/ QString ProfileManager::NEXT_PROFILE = "nextProfile"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _AUTO_START, ("autoStart"))
/*private*/ /*static*/ /*final*/ QString ProfileManager::AUTO_START = "autoStart"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _CATALOG, ("profiles.xml"))
/*private*/ /*static*/ /*final*/ QString ProfileManager::AUTO_START_TIMEOUT = "autoStartTimeout"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _AUTO_START_TIMEOUT, ("autoStartTimeout"))
/*private*/ /*static*/ /*final*/ QString ProfileManager::CATALOG = *_CATALOG; //"profiles.xml"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _PROFILE, ("profile"))
/*private*/ /*static*/ /*final*/ QString ProfileManager::PROFILE = "profile"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _PROFILES, ("profiles"))
/*public*/ /*static*/ /*final*/ QString ProfileManager::PROFILES = "profiles"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _PROFILECONFIG, ("profileConfig"))
/*private*/ /*static*/ /*final*/ QString ProfileManager::PROFILECONFIG = "profileConfig"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _SEARCH_PATHS, ("searchPaths"))
/*public*/ /*static*/ /*final*/ QString ProfileManager::ProfileManager::SEARCH_PATHS = "searchPaths"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ProfileManager::DEFAULT = "default"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ProfileManager::SYSTEM_PROPERTY = "org.jmri.profile"; // NOI18N
 Q_GLOBAL_STATIC_WITH_ARGS(const char*, _DEFAULT_SEARCH_PATH, ("defaultSearchPath"))
/*public*/ /*static*/ /*final*/ QString ProfileManager::DEFAULT_SEARCH_PATH = "defaultSearchPath"; // NOI18N
/*volatile*/ /*private*/ /*static*/ ProfileManager* ProfileManager::defaultInstance = nullptr;

/**
 * Default instance of the ProfileManager
 */
//Q_GLOBAL_STATIC(ProfileManager, manager)
///*public*/ /*static*/ ProfileManager* ProfileManagerHolder::manager = /*new ProfileManager()*/manager;

/**
 * Manage JMRI configuration profiles.
 * <p>
 * This manager, and its configuration, fall outside the control of the
 * {@link jmri.ConfigureManager} since the ConfigureManager's configuration is
 * influenced by this manager.
 *
 * @author rhwood
 */
///*public*/ class ProfileManager extends Bean {

///*private*/ static final Logger log = LoggerFactory.getLogger(ProfileManager.class);

/**
 * Create a new ProfileManager. In almost all cases, the use of
 * {@link #defaultManager()} is preferred.
 */
/*public*/ ProfileManager::ProfileManager(QObject *parent)
    :  Bean(parent)
{
 common(new File(FileUtil::getPreferencesPath() + *_CATALOG));
}
/*public*/ ProfileManager::ProfileManager(File *catalog, QObject *parent) : Bean(parent)
{
 common(catalog);
}

void ProfileManager::common(File* catalog)
{
 log = new Logger("ProfileManager");
 setObjectName("ProfileManager");
 profiles =  QList<Profile*>();
 searchPaths =  QList<File*>();
 activeProfile = NULL;
 nextActiveProfile = NULL;
 configFile = NULL;
 readingProfiles = false;
 autoStartActiveProfile = false;
 defaultSearchPath = nullptr;//new File(FileUtil::getPreferencesPath());
 autoStartActiveProfileTimeout = 10;
 pcs = new SwingPropertyChangeSupport(this, nullptr);
 defaultInstance = this;

 this->catalog = catalog;
 try
 {
  this->readProfiles();
  this->findProfiles();
 }
 catch (JDOMException* ex) {
     log->error(ex->getLocalizedMessage() + ex->getMessage());
 }
 catch (IOException* ex) {
     log->error(ex->getLocalizedMessage() + ex->getMessage());
 }
 catch (FileNotFoundException* ex) {
     log->error(ex->getLocalizedMessage() + ex->getMessage());
 }

}

/**
 * Get the default {@link ProfileManager}.
 *
 * The default ProfileManager needs to be loaded before the InstanceManager
 * since user interaction with the ProfileManager may change how the
 * InstanceManager is configured.
 *
 * @return the default ProfileManager.
 * @since 3.11.8
 */
/*public*/ /*static*/ ProfileManager* ProfileManager::getDefault() {
 if (defaultInstance == nullptr) {
     defaultInstance = new ProfileManager();
 }
 return defaultInstance;
}
/**
 * Get the {@link Profile} that is currently in use.
 *
 * @return The in use Profile.
 */
/*public*/ Profile* ProfileManager::getActiveProfile()
{
 return activeProfile;
}

/**
 * Set the {@link Profile} to use. This method finds the Profile by Id and
 * calls {@link #setActiveProfile(jmri.profile.Profile)}.
 *
 * @param id
 */
/*public*/ void ProfileManager::setActiveProfile(QString identifier)
{
 if (identifier == NULL)
 {
  Profile* old = activeProfile;
  activeProfile = NULL;
  FileUtil::setProfilePath(NULL);
  this->firePropertyChange(ProfileManager::ACTIVE_PROFILE, VPtr<Profile>::asQVariant(old), QVariant());
  log->debug("Setting active profile to NULL");
  return;
 }
 // handle profile path
 File* profileFile = new File(identifier);
 File* profileFileWithExt = new File(profileFile->getParent(), profileFile->getName() + Profile::EXTENSION);
 if (Profile::isProfile(profileFileWithExt)) {
     profileFile = profileFileWithExt;
 }
 log->debug(tr("profileFile exists(): %1").arg(profileFile->exists()?"true":"false"));
 log->debug(tr("profileFile isDirectory(): %1").arg(profileFile->isDirectory()?"true":"false"));
 if (profileFile->exists() && profileFile->isDirectory())
 {
  if (Profile::isProfile(profileFile)) {
  try {
      log->debug(tr("try setActiveProfile with new Profile(%1)").arg(profileFile->toString()));
      this->setActiveProfile(new Profile(profileFile));
      log->debug("  success");
      return;
  } catch (IOException* ex) {
      log->error(tr("Unable to use profile path %1 to set active profile.").arg(identifier), ex);
  }
  } else {
      log->error(tr("%1 is not a profile folder.").arg(identifier));
  }
 }
 foreach (Profile* p, profiles)
 {
  log->debug(tr("Looking for profile %1, found %2").arg(identifier).arg(p->getId()));
  if (p->getId()== (identifier))
  {
   this->setActiveProfile(p);
   return;
  }
 }
 log->warn(tr("Unable to set active profile. No profile with id %1 could be found.").arg(identifier));
}

/**
 * Set the {@link Profile} to use.
 *
 * Once the {@link jmri.ConfigureManager} is loaded, this only sets the
 * Profile used at next application start.
 *
 * @param profile
 */
/*public*/ void ProfileManager::setActiveProfile(Profile* profile)
{
 Profile* old = activeProfile;
 if (profile == NULL)
 {
  activeProfile = NULL;
  FileUtil::setProfilePath(NULL);
  this->firePropertyChange(ProfileManager::ACTIVE_PROFILE, VPtr<Profile>::asQVariant(old), QVariant());
  log->debug("Setting active profile to NULL");
  return;
 }
 activeProfile = profile;
 FileUtil::setProfilePath(profile->getPath()->toString());
 this->firePropertyChange(ProfileManager::ACTIVE_PROFILE, VPtr<Profile>::asQVariant(old), VPtr<Profile>::asQVariant(profile));
 log->debug("Setting active profile to "+ profile->getId());
}

/*protected*/ Profile* ProfileManager::getNextActiveProfile() {
    return this->nextActiveProfile;
}

/*protected*/ void ProfileManager::setNextActiveProfile(Profile* profile)
{
 Profile* old = this->nextActiveProfile;
 if (profile == NULL)
 {
  this->nextActiveProfile = NULL;
  this->firePropertyChange(ProfileManager::NEXT_PROFILE, VPtr<Profile>::asQVariant(old), QVariant());
  log->debug("Setting next active profile to NULL");
  return;
 }
 this->nextActiveProfile = profile;
 this->firePropertyChange(ProfileManager::NEXT_PROFILE, VPtr<Profile>::asQVariant(old), VPtr<Profile>::asQVariant(profile));
 log->debug("Setting next active profile to "+ profile->getId());
}

/**
 * Save the active {@link Profile} and automatic start setting.
 *
 * @throws IOException
 */
/*public*/ void ProfileManager::saveActiveProfile() /*throws IOException */
{
 this->saveActiveProfile(this->getActiveProfile(), this->autoStartActiveProfile);
}

/*protected*/ void ProfileManager::saveActiveProfile(Profile* profile, bool autoStart) /*throws IOException */
{
 Properties* p = new Properties();
 //FileOutputStream os = NULL;
 QTextStream* os = NULL;

 if (profile != NULL)
 {
  p->setProperty(*_ACTIVE_PROFILE, profile->getId());
  p->setProperty(*_AUTO_START, (autoStart?"true":"false"));
 }
 if (!this->configFile->exists() && !this->configFile->createNewFile())
 {
  Logger::error("Unable to create file at " + this->getConfigFile()->getAbsolutePath());
  throw new IOException("Unable to create file at " + this->getConfigFile()->getAbsolutePath()); // NOI18N
 }
 try
 {
  QFile* oFile = new QFile(this->getConfigFile()->getPath());
  if(oFile->open(QIODevice::WriteOnly))
  {
      os = new QTextStream(oFile);
      p->storeToXML(os, "Active profile configuration (saved at " + QDate::currentDate().toString() + ")"); // NOI18N
      //os->close();
      oFile->close();
  }
 }
 catch (IOException* ex)
 {
  if (os != NULL)
  {
   //os->close();
 }
  throw ex;
 }
}

/**
 * Read the active {@link Profile} and automatic start setting from the
 * ProfileManager config file.
 *
 * @see #getConfigFile()
 * @see #setConfigFile(java.io.File)
 * @throws IOException
 */
/*public*/ void ProfileManager::readActiveProfile() /*throws IOException */
{

 Properties* p = new Properties();
 QTextStream* is = NULL;
 if (this->configFile->exists())
 {
//  try
//  {
  QFile* inFile = new QFile(this->getConfigFile()->getPath());
  inFile->open(QIODevice::ReadOnly);

  QTextStream* is = new QTextStream(inFile);
  p->loadFromXML(is);
   //is.close();
  inFile->close();
//        } catch (IOException* ex) {
//            if (is != NULL) {
//                is.close();
//            }
//            throw ex;
//        }
  this->setActiveProfile(p->getProperty("activeProfile"));
  if (p->containsKey("autoStart"))
  {
   this->setAutoStartActiveProfile(p->getProperty("autoStart")== "true");
  }
 }
}

/**
 * Get an array of enabled {@link Profile} objects.
 *
 * @return The enabled Profile objects
 */
/*public*/ QList<Profile*> ProfileManager::getProfiles() {
    return profiles;//.toArray(new Profile[profiles.size()]);
}

/**
 * Get an ArrayList of {@link Profile} objects.
 *
 * @return A list of all Profile objects
 */
/*public*/ QList<Profile*>ProfileManager:: getAllProfiles() {
    return QList<Profile*>(profiles);
}

/**
 * Get the enabled {@link Profile} at index.
 *
 * @param index
 * @return A Profile
 */
/*public*/ Profile* ProfileManager::getProfiles(int index) {
    if (index >= 0 && index < profiles.size()) {
        return profiles.at(index);
    }
    return NULL;
}

/**
 * Set the enabled {@link Profile} at index.
 *
 * @param profile
 * @param index
 */
/*public*/ void ProfileManager::setProfiles(Profile* profile, int index)
{
 Profile* oldProfile = profiles.at(index);
 if (!this->readingProfiles)
 {
  profiles.replace(index, profile);
  this->fireIndexedPropertyChange(PROFILES, index, oldProfile, profile);
 }
}

/*protected*/ void ProfileManager::addProfile(Profile* profile)
{
 // temp fix
// foreach (Profile* p, profiles)
// {
//  if(p->getId() == profile->getId())
//  {
//   log->warn(tr("Attempt to store duplicate profile %1 ignored.").arg(profile->getId()));
//   return;
//  }
// }
 // end temp fix
 //if (!profiles.contains(profile)) // ACK this is only comparing the pointers to the Profile class and not comparing the Profile name and Id.
 bool bContains = false;
 foreach (Profile* p, profiles)
 {
  if(p->getId() == profile->getId() )
  {
   bContains = true;
   break;
  }
 }
 if(!bContains) // if profiles doesn't have it, add it.
 {
  profiles.append(profile);
  if (!this->readingProfiles)
  {
   int index = profiles.indexOf(profile);
   this->fireIndexedPropertyChange(PROFILES, index, QVariant(), VPtr<Profile>::asQVariant(profile));
   try
   {
    this->writeProfiles();
   }
   catch (IOException* ex)
   {
    log->warn(tr("Unable to write profiles while adding profile %1.").arg(profile->getId() + ex->getMessage()));
   }
  }
 }
}

/*protected*/ void ProfileManager::removeProfile(Profile* profile)
{
 try
 {
  int index = profiles.indexOf(profile);
  if (index >= 0)
  {
   if (profiles.contains(profile))
   {
    profiles.removeAt(profiles.indexOf(profile));
    this->fireIndexedPropertyChange(PROFILES, index, VPtr<Profile>::asQVariant(profile), QVariant());
    this->writeProfiles();
   }
   if (profile==(this->getNextActiveProfile()))
   {
    this->setNextActiveProfile(NULL);
    this->saveActiveProfile(this->getActiveProfile(), this->autoStartActiveProfile);
   }
  }
 }
 catch (IOException* ex)
 {
  log->warn(QString("Unable to write profiles while removing profile %1.").arg( profile->getId()));
 }
}

/**
 * Get the paths that are searched for Profiles when presenting the user
 * with a list of Profiles. Profiles that are discovered in these paths are
 * automatically added to the catalog->
 *
 * @return Paths that may contain profiles.
 */
/*public*/ QList<File*> ProfileManager::getSearchPaths()
{
// QVector<File*> v = QVector<File*>(searchPaths.size());
// return v.toList();
 return searchPaths;
}

/**
 * Get the search path at index.
 *
 * @param index
 * @return A path that may contain profiles.
 */
/*public*/ File* ProfileManager::getSearchPaths(int index) {
    if (index >= 0 && index < searchPaths.size()) {
        return searchPaths.at(index);
    }
    return NULL;
}

/*protected*/ void ProfileManager::addSearchPath(File* path) /*throws IOException*/
{
 //if (!searchPaths.contains(path)) // ACK this is just comparing the pointer to the File class and not the actual path.
 bool bContains = false;
 foreach (File* f, searchPaths)
 {
  if(f->getCanonicalFile() == path->getCanonicalFile())
  {
   bContains = true;
   break;
  }
 }
 if(!bContains)
 {
  searchPaths.append(path);
  if (!this->readingProfiles)
  {
   int index = searchPaths.indexOf(path);
   this->fireIndexedPropertyChange(SEARCH_PATHS, index, NULL, path);
   this->writeProfiles();
  }
  this->findProfiles(path);
 }
}
#if 1
/*protected*/ void ProfileManager::removeSearchPath(File* path) /*throws IOException*/
{
 if (searchPaths.contains(path))
 {
  int index = searchPaths.indexOf(path);
  searchPaths.removeAt(searchPaths.indexOf(path));
  this->fireIndexedPropertyChange(SEARCH_PATHS, index, path, NULL);
  this->writeProfiles();
 }
}
#endif
//@Nonnull
/*protected*/ File* ProfileManager::getDefaultSearchPath() {
    return this->defaultSearchPath;
}

/*protected*/ void ProfileManager::setDefaultSearchPath(/*@Nonnull*/ File* defaultSearchPath) /*throws IOException*/
{
 if (defaultSearchPath == NULL)
 {
  throw  NullPointerException();
 }
 if (defaultSearchPath!=(this->defaultSearchPath)) {
     File* oldDefault = this->defaultSearchPath;
     this->defaultSearchPath = defaultSearchPath;
     this->propertyChangeSupport->firePropertyChange(DEFAULT_SEARCH_PATH, oldDefault, this->defaultSearchPath);
     this->writeProfiles();
 }
}

/*private*/ void ProfileManager::readProfiles()
{
 try
 {
  bool reWrite = false;
  if (!catalog->exists())
  {
   this->writeProfiles();
  }
  if (!catalog->canRead())
  {
   return;
  }
  this->readingProfiles = true;
  //Document doc = (new SAXBuilder()).build(catalog);
  XmlFile* xmlFile = new XmlFile();
  QDomElement root = xmlFile->rootFromFile(new QFile(catalog->toString()));
  QDomDocument doc = xmlFile->doc;
  profiles.clear();

  //for (QDomElement e : doc.getRootElement().getChild(PROFILES).getChildren())
  QDomNodeList nodes = root.firstChildElement(*_PROFILES).childNodes();
  qDebug() << "profile count = " << nodes.count();
  for(int i = 0; i < nodes.count(); i++)
  {
   QDomElement e = nodes.at(i).toElement();
   QString path = e.attribute(/*Profile::PATH*/"path");
   File* pp;
   try
   {
    pp = FileUtil::getFile(nullptr, path);
    qDebug() << "read profile at: " <<  pp->toString();
    Profile* p = new Profile(pp);
    this->addProfile(p);
   }
   catch (FileNotFoundException* ex)
   {
    File* fp = new File(path);
    log->info(tr("Cataloged profile \"%1\" not in expected location\nSearching for it in %2").arg( e.attribute(/*Profile::ID*/ "id")).arg(fp->getParentFile()->toString()));
    this->findProfiles(fp->getParentFile());
    reWrite = true;
   }
  }
  searchPaths.clear();
  nodes = root.firstChildElement(*_SEARCH_PATHS).childNodes();
  //for (QDomElement e : doc.getRootElement().getChild(SEARCH_PATHS).getChildren())
  for(int i = 0; i < nodes.count(); i++)
  {
   QDomElement e = nodes.at(i).toElement();
 //  if(e.attribute("path") == "") continue;
   File* path = FileUtil::getFile(e.attribute(/*Profile::PATH*/"path"));
   if (!searchPaths.contains(path))
   {
    this->addSearchPath(path);
   }
   if (e.attribute("default")=="true")
   {
    this->defaultSearchPath = path;
   }
  }
  if (searchPaths.isEmpty())
  {
   this->addSearchPath(FileUtil::getFile(nullptr, FileUtil::getPreferencesPath()));
  }
  this->readingProfiles = false;
  if (reWrite)
  {
   this->writeProfiles();
  }
 }
 catch (JDOMException* ex)
 {
  this->readingProfiles = false;
  throw ex;
 }
 catch (IOException* ex)
 {
  this->readingProfiles = false;
  throw ex;
 }
}

/*private*/ void ProfileManager::writeProfiles() /*throw (IOException)*/
{
 if (!(File(FileUtil::getPreferencesPath()).canWrite()))
 {
     return;
 }

//    FileWriter fw = NULL;
 QDomDocument doc;
 QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
 doc.appendChild(xmlProcessingInstruction);

 //doc.setRootElement(new Element(PROFILECONFIG));
 QDomElement root = doc.createElement(*_PROFILECONFIG);
 doc.appendChild(root);

 QDomElement profilesElement = doc.createElement(*_PROFILES);
 QDomElement pathsElement = doc.createElement(*_SEARCH_PATHS);
 foreach (Profile* p, this->profiles)
 {
  QDomElement e = doc.createElement(*_PROFILE);
  e.setAttribute(/*Profile::ID*/"id", p->getId());
  e.setAttribute(/*Profile::PATH*/"path", FileUtil::getPortableFilename(p->getPath(), true, true));
  profilesElement.appendChild(e);
 }
 foreach (File* f, this->searchPaths)
 {
  QDomElement e = doc.createElement(/*Profile::PATH*/"path");
  e.setAttribute(/*Profile::PATH*/"path", FileUtil::getPortableFilename(f->getPath(), true, true));
  pathsElement.appendChild(e);
 }
 root.appendChild(profilesElement);
 root.appendChild(pathsElement);
//    try {
//        fw = new FileWriter(catalog);
//        XMLOutputter fmt = new XMLOutputter();
//        fmt.setFormat(Format.getPrettyFormat()
//                            .setLineSeparator(System.getProperty("line.separator"))
//                            .setTextMode(Format.TextMode.PRESERVE));
//        fmt.output(doc, fw);
//        fw.close();
//    } catch (IOException* ex) {
//        // close fw if possible
//        if (fw != NULL) {
//            fw.close();
//        }
//        // rethrow the error
//        throw ex;
//    }
 XmlFile* xmlFile = new XmlFile();
 xmlFile->writeXML(catalog, doc);
}

/*private*/ void ProfileManager::findProfiles()
{
 foreach (File* searchPath, this->searchPaths)
 {
  this->findProfiles(searchPath);
 }
}

/*private*/ void ProfileManager::findProfiles(File* searchPath)
{
 FileFilter1* filter1 = new FileFilter1;
 QList<File*> profilePaths = searchPath->listFiles(/*new FileFilter()*/ filter1);
// {
//        @Override
//        /*public*/ bool accept(File pathname) {
//            return (pathname.isDirectory() && Arrays.asList(pathname.list()).contains(Profile::PROPERTIES));
//        }
//    });
  if (profilePaths.isEmpty())
  {
   log->error(QString("ProfileManager::findProfiles: There was an error reading directory %1.").arg(searchPath->getPath()));
   return;
  }
  foreach (File* pp, profilePaths)
  {
   try
   {
    Profile* p = new Profile(pp);
    this->addProfile(p);
   }
   catch (IOException* ex) {
       log->error(tr("Error attempting to read Profile at %1").arg(pp->toString()), ex);
   }
  }
}

bool ProfileManager::FileFilter1::accept(File* pathname)
{
// return (pathname->isDirectory() && pathname->list().contains(Profile::PROPERTIES));
 //this->pathname = pathname;
 return Profile::isProfile(pathname);
}

QString ProfileManager::FileFilter1::getDescription()
{
 return tr("%1 is not a profile").arg(pathname->getPath());
}

/**
 * Get the file used to configure the ProfileManager.
 *
 * @return the appConfigFile
 */
/*public*/ File* ProfileManager::getConfigFile() {
    return configFile;
}

/**
 * Set the file used to configure the ProfileManager. This is set on a
 * per-application basis.
 *
 * @param configFile the appConfigFile to set
 */
/*public*/ void ProfileManager::setConfigFile(File* configFile)
{
 this->configFile = configFile;
 log->debug("Using config file "+ configFile->getName());
}

/**
 * Should the app automatically start with the active {@link Profile}
 * without offering the user an opportunity to change the Profile?
 *
 * @return true if the app should start without user interaction
 */
/*public*/ bool ProfileManager::isAutoStartActiveProfile()
{
 return (this->getActiveProfile() != NULL && autoStartActiveProfile);
}

/**
 * Set if the app will next start without offering the user an opportunity
 * to change the {@link Profile}.
 *
 * @param autoStartActiveProfile the autoStartActiveProfile to set
 */
/*public*/ void ProfileManager::setAutoStartActiveProfile(bool autoStartActiveProfile)
{
 this->autoStartActiveProfile = autoStartActiveProfile;
}

/**
 * Create a default profile if no profiles exist.
 *
 * @return A new profile or NULL if profiles already exist.
 * @throws IOException
 */
/*public*/ Profile* ProfileManager::createDefaultProfile() /*throws IllegalArgumentException, IOException*/
{
 if (this->getAllProfiles().isEmpty())
 {
        QString pn = tr("My JMRI Railroad");
        QString pid = FileUtil::sanitizeFilename(pn);
        File* pp = new File(FileUtil::getPreferencesPath() + pid + Profile::EXTENSION);
        Profile* profile = new Profile(pn, pid, pp);
        this->addProfile(profile);
        this->setAutoStartActiveProfile(true);
        log->info(QString("Created default profile \"%1\"").arg( pn));
        return profile;
    } else {
        return NULL;
    }
}

/**
 * Copy a JMRI configuration not in a profile and its user preferences to a
 * profile.
 *
 * @param config
 * @param name
 * @return The profile with the migrated configuration.
 * @throws IllegalArgumentException
 * @throws IOException
 */
/*public*/ Profile* ProfileManager::migrateConfigToProfile(File* config, QString name) /*throws IllegalArgumentException, IOException*/ {
    QString pid = FileUtil::sanitizeFilename(name);
    File* pp = new File(FileUtil::getPreferencesPath(), pid, NULL);
    Profile* profile = new Profile(name, pid, pp);
    FileUtil::copy(config, new File(profile->getPath(), /*Profile::CONFIG_FILENAME*/"ProfileConfig.xml", NULL));
    FileUtil::copy(new File(config->getParentFile(), "UserPrefs" + config->getName()), new File(profile->getPath(), QString("UserPrefs") + /*Profile::CONFIG_FILENAME*/"ProfileConfig.xml")); // NOI18N
    this->addProfile(profile);
    log->info(QString("Migrated \"%1\" config to profile \"%2\"").arg(name).arg(name));
    return profile;
}


/**
 * Migrate a JMRI application to using {@link Profile}s.
 * <p>
 * Migration occurs when no profile configuration exists, but an application
 * configuration exists. This method also handles the situation where an
 * entirely new user is first starting JMRI, or where a user has deleted all
 * their profiles.
 * <p>
 * When a JMRI application is starting there are eight potential
 * Profile-related states requiring preparation to use profiles:
 * <table>
 * <caption>Matrix of states determining if migration required.</caption>
 * <tr>
 * <th>Profile Catalog</th>
 * <th>Profile Config</th>
 * <th>App Config</th>
 * <th>Action</th>
 * </tr>
 * <tr>
 * <td>YES</td>
 * <td>YES</td>
 * <td>YES</td>
 * <td>No preparation required - migration from earlier JMRI complete</td>
 * </tr>
 * <tr>
 * <td>YES</td>
 * <td>YES</td>
 * <td>NO</td>
 * <td>No preparation required - JMRI installed after profiles feature
 * introduced</td>
 * </tr>
 * <tr>
 * <td>YES</td>
 * <td>NO</td>
 * <td>YES</td>
 * <td>Migration required - other JMRI applications migrated to profiles by
 * this user, but not this one</td>
 * </tr>
 * <tr>
 * <td>YES</td>
 * <td>NO</td>
 * <td>NO</td>
 * <td>No preparation required - prompt user for desired profile if multiple
 * profiles exist, use default otherwise</td>
 * </tr>
 * <tr>
 * <td>NO</td>
 * <td>NO</td>
 * <td>NO</td>
 * <td>New user - create and use default profile</td>
 * </tr>
 * <tr>
 * <td>NO</td>
 * <td>NO</td>
 * <td>YES</td>
 * <td>Migration required - need to create first profile</td>
 * </tr>
 * <tr>
 * <td>NO</td>
 * <td>YES</td>
 * <td>YES</td>
 * <td>No preparation required - catalog will be automatically
 * regenerated</td>
 * </tr>
 * <tr>
 * <td>NO</td>
 * <td>YES</td>
 * <td>NO</td>
 * <td>No preparation required - catalog will be automatically
 * regenerated</td>
 * </tr>
 * </table>
 * This method returns true if a migration occurred, and false in all other
 * circumstances.
 *
 * @param configFilename the name of the app config file
 * @return true if a user's existing config was migrated, false otherwise
 * @throws java.io.IOException      if unable to to create a Profile
 * @throws IllegalArgumentException if profile already exists for configFilename
 */
/*public*/ bool ProfileManager::migrateToProfiles(/*@Nonnull*/ QString configFilename)  {
    File* appConfigFile = new File(configFilename);
    bool didMigrate = false;
    if (!appConfigFile->isAbsolute()) {
        appConfigFile = new File(FileUtil::getPreferencesPath() + configFilename);
    }
    if (this->getAllProfiles().isEmpty()) { // no catalog and no profile config
        if (!appConfigFile->exists()) { // no catalog and no profile config and no app config: new user
            this->setActiveProfile(this->createDefaultProfile());
            this->saveActiveProfile();
        } else { // no catalog and no profile config, but an existing app config: migrate user who never used profiles before
            this->setActiveProfile(this->migrateConfigToProfile(appConfigFile, QApplication::applicationName()));
            this->saveActiveProfile();
            didMigrate = true;
        }
    } else if (appConfigFile->exists()) { // catalog and existing app config, but no profile config: migrate user who used profile with other JMRI app
        try {
            this->setActiveProfile(this->migrateConfigToProfile(appConfigFile, QApplication::applicationName()));
        } catch (IllegalArgumentException* ex) {
            if (ex->getMessage().startsWith("A profile already exists at ")) {
                // caused by attempt to migrate application with custom launcher
                // strip ".xml" from configFilename name and use that to create profile
                this->setActiveProfile(this->migrateConfigToProfile(appConfigFile, appConfigFile->getName().mid(0, appConfigFile->getName().length() - 4)));
            } else {
                // throw the exception so it can be dealt with, since other causes need user attention
                // (most likely cause is a read-only settings directory)
                throw ex;
            }
        }
        this->saveActiveProfile();
        didMigrate = true;
    } // all other cases need no prep
    return didMigrate;
}

/**
 * Export the {@link jmri.profile.Profile} to a zip file.
 *
 * @param profile                 The profile to export
 * @param target                  The file to export the profile into
 * @param exportExternalUserFiles If the User Files are not within the
 *                                    profile directory, should they be
 *                                    included?
 * @param exportExternalRoster    It the roster is not within the profile
 *                                    directory, should it be included?
 * @throws java.io.IOException     if unable to write a file during the
 *                                     export
 * @throws org.jdom2.JDOMException if unable to create a new profile
 *                                     configuration file in the exported
 *                                     Profile
 * @throws InitializationException if unable to read profile to export
 */
/*public*/ void ProfileManager::_export(/*@Nonnull*/ Profile* profile, /*@Nonnull*/ File* target, bool exportExternalUserFiles,
        bool exportExternalRoster) /*throw (IOException, JDOMException, InitializationException)*/ {
    if (!target->exists() && !target->createNewFile()) {
        throw new IOException("Unable to create file " + target->toString());
    }
    QString tempDirPath = System::getProperty("java.io.tmpdir") + File::separator + "JMRI" + System::currentTimeMillis(); // NOI18N
    FileUtil::createDirectory(tempDirPath);
    File* tempDir = new File(tempDirPath);
    File* tempProfilePath = new File(tempDir, profile->getPath()->getName());
    FileUtil::copy(profile->getPath(), tempProfilePath);
    Profile* tempProfile = new Profile(tempProfilePath);
    ((FileLocationsPreferences*)InstanceManager::getDefault("FileLocationsPreferences"))->initialize(profile);
    ((FileLocationsPreferences*)InstanceManager::getDefault("FileLocationsPreferences"))->initialize(tempProfile);
    ((RosterConfigManager*)InstanceManager::getDefault("RosterConfigManager"))->initialize(profile);
    ((RosterConfigManager*)InstanceManager::getDefault("RosterConfigManager"))->initialize(tempProfile);
    if (exportExternalUserFiles) {
        FileUtil::copy(new File(FileUtil::getUserFilesPath(profile)), tempProfilePath);
        FileUtil::setUserFilesPath(tempProfile, FileUtil::getProfilePath(tempProfile));
        ((FileLocationsPreferences*)InstanceManager::getDefault("FileLocationsPreferences"))->savePreferences(tempProfile);
    }
    if (exportExternalRoster) {
        FileUtil::copy(new File(Roster::getRoster(profile)->getRosterIndexPath()), new File(tempProfilePath, "roster.xml")); // NOI18N
        FileUtil::copy(new File(Roster::getRoster(profile)->getRosterLocation(), "roster"), new File(tempProfilePath, "roster")); // NOI18N
        ((RosterConfigManager*)InstanceManager::getDefault("RosterConfigManager"))->setDirectory(profile, FileUtil::getPortableFilename(profile, tempProfilePath));
        ((RosterConfigManager*)InstanceManager::getDefault("RosterConfigManager"))->savePreferences(profile);
    }
#if 0
    try (FileOutputStream out = new FileOutputStream(target); ZipOutputStream zip = new ZipOutputStream(out)) {
        this.exportDirectory(zip, tempProfilePath, tempProfilePath.getPath());
    }
#endif
    FileUtil::_delete(tempDir);
}


/*private*/ bool ProfileManager::exportDirectory(QuaZipFile* outFile, File* source, QString root) //throws IOException
{
 foreach (File* file, source->listFiles())
 {
  if (file->isDirectory())
  {
   //QFile* fileInfo = new QFile(fileInfo->fileName();)
   if (!Profile::isProfile(file))
   {
    exportDirectory(outFile, file, root);
   }
  }
  else
  {
   exportFile(outFile, file, root);
  }
 }
}

/*private*/ bool ProfileManager::exportFile(QuaZipFile* outFile, File* source, QString root) //throws IOException
{
 QFile* inFile = new QFile(source->getPath());
 QFileInfo fileInfo = QFileInfo(source->getAbsolutePath());
 //QString entryName;
 char c;

// if (root != "")
// {
//  entryName = root + "/" + fileInfo.fileName();
// }
// else
// {
//  entryName = fileInfo.fileName();
// }
 QString relName = relativeName(source, root);

 //ZipEntry zipEntry = new ZipEntry(entryName);
 if(!inFile->open(QIODevice::ReadOnly))
  return false;

 if(!outFile->open(QIODevice::WriteOnly, QuaZipNewInfo(relName, fileInfo.filePath())))
  return false;
 while (inFile->getChar(&c) )
     outFile->putChar(c);

 if (outFile->getZipError() != ZIP_OK)
 {
  return false;
 }

 outFile->close();

 if (outFile->getZipError() != ZIP_OK)
 {
     return false;
 }

 inFile->close();
 return true;
}

/*private*/ QString ProfileManager::relativeName(File* file, QString root)
    {
    QString path = file->getPath();
    if (path.startsWith(root)) {
        path = path.mid(root.length());
    }
    if (file->isDirectory() && !path.endsWith("/")) {
        path = path + "/";
    }
    return path.replace(File::separator, "/");
}

/**
 * Get the active profile.
 *
 * This method initiates the process of setting the active profile when a
 * headless app launches.
 *
 * @return The active {@link Profile}
 * @throws IOException
 * @see ProfileManagerDialog#getStartingProfile(java.awt.Frame)
 */
/*public*/ /*static*/ Profile* ProfileManager::getStartingProfile() /*throws IOException*/
{
 if (ProfileManager::getDefault()->getActiveProfile() == nullptr)
 {
  ProfileManager::getDefault()->readActiveProfile();
  // Automatically start with only profile if only one profile
  if (ProfileManager::getDefault()->getProfiles().length() == 1)
  {
   ProfileManager::getDefault()->setActiveProfile(ProfileManager::getDefault()->getProfiles(0));
   // Display profile selector if user did not choose to auto start with last used profile
  }
  else if (!ProfileManager::getDefault()->isAutoStartActiveProfile())
  {
   return nullptr;
  }
 }
 return ProfileManager::getDefault()->getActiveProfile();
}

/**
 * Generate a reasonably pseudorandom unique id.
 * <p>
 * This can be used to generate the id for a
 * {@link jmri.profile.NullProfile}. Implementing applications should save
 * this value so that the id of a NullProfile is consistent across
 * application launches.
 *
 * @return String of alphanumeric characters.
 */
/*public*/ /*static*/ QString ProfileManager::createUniqueId() {
    //return Integer.toHexString(Float.floatToIntBits((float) Math.random()));
    QString uuid = QUuid::createUuid().toString();
 return uuid.mid(1,8);
}

void ProfileManager::profileNameChange(Profile* profile, QString oldName) {
    this->firePropertyChange(new PropertyChangeEvent(profile, Profile::NAME, oldName, profile->getName()));
}
/**
 * Seconds to display profile selector before automatically starting.
 *
 * If 0, selector will not automatically dismiss.
 *
 * @return Seconds to display selector.
 */
/*public*/ int ProfileManager::getAutoStartActiveProfileTimeout() {
    return this->autoStartActiveProfileTimeout;
}

/**
 * Set the number of seconds to display the profile selector before
 * automatically starting.
 *
 * If negative or greater than 300 (5 minutes), set to 0 to prevent
 * automatically starting with any profile.
 *
 * Call {@link #saveActiveProfile() } after setting this to persist the
 * value across application restarts.
 *
 * @param autoStartActiveProfileTimeout Seconds to display profile selector
 */
/*public*/ void ProfileManager::setAutoStartActiveProfileTimeout(int autoStartActiveProfileTimeout) {
    int old = this->autoStartActiveProfileTimeout;
    if (autoStartActiveProfileTimeout < 0 || autoStartActiveProfileTimeout > 500) {
        autoStartActiveProfileTimeout = 0;
    }
    if (old != autoStartActiveProfileTimeout) {
        this->autoStartActiveProfileTimeout = autoStartActiveProfileTimeout;
        pcs->firePropertyChange("autoStartTimeout", old, this->autoStartActiveProfileTimeout);
    }
}
//private static class ProfileManagerHolder {

//};
