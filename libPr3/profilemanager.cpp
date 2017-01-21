#include "profilemanager.h"
#include "file.h"
#include <QUuid>
#include "../libPr3/profile.h"
#include <QFileInfo>
#include "fileutil.h"
#include "xmlfile.h"
#include "propertychangeevent.h"
#include "rosterentry.h"
#include <QApplication>
#include "properties.h"

//ProfileManager::ProfileManager(QObject *parent) :
//    QObject(parent)
//{

//}

/*public*/ /*static*/ /*final*/ QString ProfileManager::ACTIVE_PROFILE = "activeProfile"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ProfileManager::NEXT_PROFILE = "nextProfile"; // NOI18N
/*private*/ /*static*/ /*final*/ QString ProfileManager::AUTO_START = "autoStart"; // NOI18N
/*private*/ /*static*/ /*final*/ QString ProfileManager::CATALOG = "profiles.xml"; // NOI18N
/*private*/ /*static*/ /*final*/ QString ProfileManager::PROFILE = "profile"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ProfileManager::PROFILES = "profiles"; // NOI18N
/*private*/ /*static*/ /*final*/ QString ProfileManager::PROFILECONFIG = "profileConfig"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ProfileManager::SEARCH_PATHS = "searchPaths"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ProfileManager::SYSTEM_PROPERTY = "org.jmri.profile"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ProfileManager::DEFAULT_SEARCH_PATH = "defaultSearchPath"; // NOI18N

ProfileManager* ProfileManager::instance = NULL;

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
    :  QObject(parent) \
{
 log = new Logger("ProfileManager");
 profiles =  QList<Profile*>();
 searchPaths =  QList<File*>();
 activeProfile = NULL;
 nextActiveProfile = NULL;
 configFile = NULL;
 readingProfiles = false;
 autoStartActiveProfile = false;
 defaultSearchPath = new File(FileUtil::getPreferencesPath());

 this->catalog = new File(FileUtil::getPreferencesPath() + CATALOG);
//    try {
 this->readProfiles();
 this->findProfiles();
//    } catch (JDOMException ex) {
//        log->error(ex.getLocalizedMessage(), ex);
//    } catch (IOException ex) {
//        log->error(ex.getLocalizedMessage(), ex);
//    }
}

/**
 * Get the default {@link ProfileManager}.
 *
 * The default ProfileManager needs to be loaded before the InstanceManager
 * since user interaction with the ProfileManager may change how the
 * InstanceManager is configured.
 *
 * @return the default ProfileManager.
 */
/*public*/ /*static*/ ProfileManager* ProfileManager::defaultManager()
{
 if (instance == NULL)
 {
  instance = new ProfileManager();
 }
 return instance;
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
    return ProfileManagerHolder::manager;
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
/*public*/ void ProfileManager::setActiveProfile(QString id)
{
 if (id == NULL)
 {
  Profile* old = activeProfile;
  activeProfile = NULL;
  FileUtil::setProfilePath(NULL);
  //this->firePropertyChange(ProfileManager.ACTIVE_PROFILE, old, NULL);
  emit propertyChange(new PropertyChangeEvent(this, ProfileManager::ACTIVE_PROFILE, VPtr<Profile>::asQVariant(old), QVariant()));
  log->debug("Setting active profile to NULL");
  return;
 }
 foreach (Profile* p, profiles)
 {
  if (p->getId()== (id))
  {
   this->setActiveProfile(p);
   return;
  }
 }
 log->warn(tr("Unable to set active profile. No profile with id %1 could be found.").arg(id));
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
  //this->firePropertyChange(ProfileManager.ACTIVE_PROFILE, old, NULL);
  emit propertyChange(new PropertyChangeEvent(this, ProfileManager::ACTIVE_PROFILE, VPtr<Profile>::asQVariant(old), QVariant()));
  log->debug("Setting active profile to NULL");
  return;
 }
 activeProfile = profile;
 FileUtil::setProfilePath(profile->getPath()->toString());
 //this->firePropertyChange(ProfileManager::ACTIVE_PROFILE, old, profile);
 emit propertyChange(new PropertyChangeEvent(this, ProfileManager::ACTIVE_PROFILE, QVariant(), VPtr<Profile>::asQVariant(profile) ));
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
  //this->firePropertyChange(ProfileManager::NEXT_PROFILE, VPtr<Profile>::asQVariant(old), QVariant());
  emit propertyChange(new PropertyChangeEvent(this, ProfileManager::NEXT_PROFILE, VPtr<Profile>::asQVariant(old), QVariant()));
  log->debug("Setting next active profile to NULL");
  return;
 }
 this->nextActiveProfile = profile;
 //this->firePropertyChange(ProfileManager::NEXT_PROFILE, VPtr<Profile>::asQVariant(old), VPtr<Profile>::asQVariant(profile));
 emit propertyChange(new PropertyChangeEvent(this, ProfileManager::NEXT_PROFILE, VPtr<Profile>::asQVariant(old), VPtr<Profile>::asQVariant(profile)));
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
  p->setProperty(ACTIVE_PROFILE, profile->getId());
  p->setProperty(AUTO_START, (autoStart?"true":"false"));
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
 catch (IOException ex)
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
#if 1
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
//        } catch (IOException ex) {
//            if (is != NULL) {
//                is.close();
//            }
//            throw ex;
//        }
  this->setActiveProfile(p->getProperty(ACTIVE_PROFILE));
  if (p->containsKey(AUTO_START))
  {
   this->setAutoStartActiveProfile(p->getProperty(AUTO_START)== "true");
  }
 }
#endif
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
  //this->fireIndexedPropertyChange(PROFILES, index, oldProfile, profile);
  emit indexedPropertyChange(new IndexedPropertyChangeEvent(this, PROFILES,  VPtr<Profile>::asQVariant(oldProfile), VPtr<Profile>::asQVariant(profile), index));
 }
}

/*protected*/ void ProfileManager::addProfile(Profile* profile)
{
 if (!profiles.contains(profile))
 {
  profiles.append(profile);
  if (!this->readingProfiles)
  {
   int index = profiles.indexOf(profile);
//            this->fireIndexedPropertyChange(PROFILES, index, NULL, profile);
//            try {
   this->writeProfiles();
//            } catch (IOException ex) {
//                log->warn("Unable to write profiles while adding profile {}.", profile.getId(), ex);
//            }
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
    //this->fireIndexedPropertyChange(PROFILES, index, VPtr<Profile>::asQVariant(profile), QVariant());
    emit indexedPropertyChange(new IndexedPropertyChangeEvent(this, PROFILES,  VPtr<Profile>::asQVariant(profile), QVariant(), index ));
    this->writeProfiles();
   }
   if (profile==(this->getNextActiveProfile()))
   {
    this->setNextActiveProfile(NULL);
    this->saveActiveProfile(this->getActiveProfile(), this->autoStartActiveProfile);
   }
  }
 }
 catch (IOException ex)
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
 if (!searchPaths.contains(path))
 {
  searchPaths.append(path);
  if (!this->readingProfiles)
  {
   int index = searchPaths.indexOf(path);
//            this->fireIndexedPropertyChange(SEARCH_PATHS, index, NULL, path);
   emit indexedPropertyChange(new IndexedPropertyChangeEvent(this, SEARCH_PATHS, QVariant(), VPtr<File>::asQVariant(path),index));
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
  //this->fireIndexedPropertyChange(SEARCH_PATHS, index, path, NULL);
  emit indexedPropertyChange(new IndexedPropertyChangeEvent(this, SEARCH_PATHS,  VPtr<File>::asQVariant(path),QVariant(),index));
  this->writeProfiles();
 }
}
#endif
//@Nonnull
/*protected*/ File* ProfileManager::getDefaultSearchPath() {
    return this->defaultSearchPath;
}

/*protected*/ void ProfileManager::setDefaultSearchPath(/*@Nonnull*/ File* defaultSearchPath) /*throws IOException*/ {
    if (defaultSearchPath == NULL) {
        throw new NullPointerException();
    }
    if (defaultSearchPath!=(this->defaultSearchPath)) {
        File* oldDefault = this->defaultSearchPath;
        this->defaultSearchPath = defaultSearchPath;
        //this->propertyChangeSupport.firePropertyChange(DEFAULT_SEARCH_PATH, oldDefault, this->defaultSearchPath);
        emit propertyChange(new PropertyChangeEvent(this, DEFAULT_SEARCH_PATH, oldDefault, this->defaultSearchPath));
        this->writeProfiles();
    }
}
/*private*/ void ProfileManager::readProfiles() /*throws JDOMException, IOException*/
{
//    try {
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
 QDomNodeList nodes = root.firstChildElement(PROFILES).childNodes();
 for(int i = 0; i < nodes.count(); i++)
 {
  QDomElement e = nodes.at(i).toElement();
  File* pp = FileUtil::getFile(e.attribute(Profile::PATH));
  if(!pp->exists())
  {
   log->info(tr("Cataloged profile \"%1\" not in expected location\nSearching for it in %2").arg(e.attribute(Profile::ID)).arg(pp->getParentFile()->getName()));
   this->findProfiles(pp->getParentFile());
   reWrite = true;
  }
  //try {
  Profile* p = new Profile(pp);
  this->addProfile(p);
//            } catch (FileNotFoundException ex) {
//                log->info("Cataloged profile \"{}\" not in expected location\nSearching for it in {}", e.attribute(Profile.ID), pp.getParentFile());
//                this->findProfiles(pp.getParentFile());
//                reWrite = true;
//            }
 }
 searchPaths.clear();
 nodes = root.firstChildElement(SEARCH_PATHS).childNodes();
 //for (QDomElement e : doc.getRootElement().getChild(SEARCH_PATHS).getChildren())
 for(int i = 0; i < nodes.count(); i++)
 {
  QDomElement e = nodes.at(i).toElement();
  File* path = FileUtil::getFile(e.attribute(Profile::PATH));
  if (!searchPaths.contains(path))
  {
   this->addSearchPath(path);
  }
 }
 if (searchPaths.isEmpty())
 {
  this->addSearchPath(FileUtil::getFile(FileUtil::getPreferencesPath()));
 }
 this->readingProfiles = false;
 if (reWrite)
 {
  this->writeProfiles();
 }
//    } catch (JDOMException ex) {
//        this->readingProfiles = false;
//        throw ex;
//    } catch (IOException ex) {
//        this->readingProfiles = false;
//        throw ex;
//    }
}

/*private*/ void ProfileManager::writeProfiles() /*throws IOException*/
{
#if 1
//    FileWriter fw = NULL;
 QDomDocument doc;
 //doc.setRootElement(new Element(PROFILECONFIG));
 QDomElement root = doc.createElement(PROFILECONFIG);
 doc.appendChild(root);

 // add XSLT processing instruction
 QDomProcessingInstruction p = doc.createProcessingInstruction("xml-stylesheet", "type= \"text/xsl\", href=\""+XmlFile::xsltLocation+"DecoderID.xsl\"");
 doc.appendChild(p);

 QDomElement profilesElement = doc.createElement(PROFILES);
 QDomElement pathsElement = doc.createElement(SEARCH_PATHS);
 foreach (Profile* p, this->profiles)
 {
  QDomElement e = doc.createElement(PROFILE);
  e.setAttribute(Profile::ID, p->getId());
  e.setAttribute(Profile::PATH, FileUtil::getPortableFilename(p->getPath(), true, true));
  profilesElement.appendChild(e);
 }
 foreach (File* f, this->searchPaths)
 {
  QDomElement e = doc.createElement(Profile::PATH);
  e.setAttribute(Profile::PATH, FileUtil::getPortableFilename(f->getPath(), true, true));
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
//    } catch (IOException ex) {
//        // close fw if possible
//        if (fw != NULL) {
//            fw.close();
//        }
//        // rethrow the error
//        throw ex;
//    }
 XmlFile* xmlFile = new XmlFile();
 xmlFile->writeXML(catalog, doc);
#endif
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
      log->error(QString("ProfileManager::findProfiles: There was an error reading directory \"%1\". Filter: \"%2\"").arg(searchPath->getPath()).arg(filter1->getDescription()));
   return;
  }
  foreach (File* pp, profilePaths)
  {
//        try {
   Profile* p = new Profile(pp);
   this->addProfile(p);
//        } catch (IOException ex) {
//            log->error("Error attempting to read Profile at {}", pp, ex);
//        }
  }
}
bool ProfileManager::FileFilter1::accept(File* pathname)
{
 return (pathname->isDirectory() && pathname->list().contains(Profile::PROPERTIES));
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
        File* pp = new File(FileUtil::getPreferencesPath() + pid);
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
    FileUtil::copy(config, new File(profile->getPath(), Profile::CONFIG_FILENAME, NULL));
    FileUtil::copy(new File(config->getParentFile(), "UserPrefs" + config->getName()), new File(profile->getPath(), "UserPrefs" + Profile::CONFIG_FILENAME)); // NOI18N
    this->addProfile(profile);
    log->info(QString("Migrated \"%1\" config to profile \"%2\"").arg(name).arg(name));
    return profile;
}

/**
 * Migrate a JMRI application to using {@link Profile}s.
 *
 * Migration occurs when no profile configuration exists, but an application
 * configuration exists. This method also handles the situation where an
 * entirely new user is first starting JMRI, or where a user has deleted all
 * their profiles.
 * <p>
 * When a JMRI application is starting there are eight potential
 * Profile-related states requiring preparation to use profiles:
 * <table>
 * <tr><th>Profile Catalog</th><th>Profile Config</th><th>App
 * Config</th><th>Action</th></tr>
 * <tr><td>YES</td><td>YES</td><td>YES</td><td>No preparation required -
 * migration from earlier JMRI complete</td></tr>
 * <tr><td>YES</td><td>YES</td><td>NO</td><td>No preparation required - JMRI
 * installed after profiles feature introduced</td></tr>
 * <tr><td>YES</td><td>NO</td><td>YES</td><td>Migration required - other
 * JMRI applications migrated to profiles by this user, but not this
 * one</td></tr>
 * <tr><td>YES</td><td>NO</td><td>NO</td><td>No preparation required -
 * prompt user for desired profile if multiple profiles exist, use default
 * otherwise</td></tr>
 * <tr><td>NO</td><td>NO</td><td>NO</td><td>New user - create and use
 * default profile</td></tr>
 * <tr><td>NO</td><td>NO</td><td>YES</td><td>Migration required - need to
 * create first profile</td></tr>
 * <tr><td>NO</td><td>YES</td><td>YES</td><td>No preparation required -
 * catalog will be automatically regenerated</td></tr>
 * <tr><td>NO</td><td>YES</td><td>NO</td><td>No preparation required -
 * catalog will be automatically regenerated</td></tr>
 * </table>
 * This method returns true if a migration occurred, and false in all other
 * circumstances.
 *
 * @param configFilename
 * @return true if a user's existing config was migrated, false otherwise
 * @throws IllegalArgumentException
 * @throws IOException
 */
/*public*/ bool ProfileManager::migrateToProfiles(QString configFilename) /*throws IllegalArgumentException, IOException*/
{
 File* appConfigFile = new File(configFilename);
 bool didMigrate = false;
 if (!appConfigFile->isAbsolute())
 {
  appConfigFile = new File(FileUtil::getPreferencesPath() + File::separator + configFilename);
 }
 if (this->getAllProfiles().isEmpty())
 { // no catalog and no profile config
  if (!appConfigFile->exists())
  { // no catalog and no profile config and no app config: new user
   this->setActiveProfile(this->createDefaultProfile());
            this->saveActiveProfile();
  }
  else
  { // no catalog and no profile config, but an existing app config: migrate user who never used profiles before
   this->setActiveProfile(this->migrateConfigToProfile(appConfigFile, QApplication::applicationName()));
   this->saveActiveProfile();
   didMigrate = true;
  }
 }
 else if (appConfigFile->exists())
 { // catalog and existing app config, but no profile config: migrate user who used profile with other JMRI app
  try
  {
   this->setActiveProfile(this->migrateConfigToProfile(appConfigFile, QApplication::applicationName()));
  }
  catch (IllegalArgumentException ex)
  {
   if (ex.getMessage().startsWith("A profile already exists at "))
   {
    // caused by attempt to migrate application with custom launcher
    // strip ".xml" from configFilename name and use that to create profile
    this->setActiveProfile(this->migrateConfigToProfile(appConfigFile, appConfigFile->getName().mid(0, appConfigFile->getName().length() - 4)));
   }
   else
   {
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
#if 0
/**
 * Export the {@link jmri.profile.Profile} to a JAR file.
 *
 * @param profile The profile to export
 * @param target The file to export the profile into
 * @param exportExternalUserFiles If the User Files are not within the
 * profile directory, should they be included?
 * @param exportExternalRoster It the roster is not within the profile
 * directory, should it be included?
 * @throws IOException
 * @throws org.jdom2.JDOMException
 */
/*public*/ void export(Profile profile, File target, boolean exportExternalUserFiles, boolean exportExternalRoster) throws IOException, JDOMException {
    if (!target.exists()) {
        target.createNewFile();
    }
    String tempDirPath = System.getProperty("java.io.tmpdir") + File.separator + "JMRI" + System.currentTimeMillis(); // NOI18N
    FileUtil.createDirectory(tempDirPath);
    File tempDir = new File(tempDirPath);
    File tempProfilePath = new File(tempDir, profile.getPath().getName());
    FileUtil.copy(profile.getPath(), tempProfilePath);
    File config = new File(tempProfilePath, "ProfileConfig.xml"); // NOI18N
    Document doc = (new SAXBuilder()).build(config);
    if (exportExternalUserFiles) {
        FileUtil.copy(new File(FileUtil.getUserFilesPath()), tempProfilePath);
        QDomElement fileLocations = doc.getRootElement().getChild("fileLocations"); // NOI18N
        for (Object fl : fileLocations.getChildren()) {
            if (((Element) fl).getAttribute("defaultUserLocation") != NULL) { // NOI18N
                ((Element) fl).setAttribute("defaultUserLocation", "profile:"); // NOI18N
            }
        }
    }
    if (exportExternalRoster) {
        FileUtil.copy(new File(Roster.defaultRosterFilename()), new File(tempProfilePath, "roster.xml")); // NOI18N
        FileUtil.copy(new File(Roster.getFileLocation(), "roster"), new File(tempProfilePath, "roster")); // NOI18N
        QDomElement roster = doc.getRootElement().getChild("roster"); // NOI18N
        roster.removeAttribute("directory"); // NOI18N
    }
    if (exportExternalUserFiles || exportExternalRoster) {
        FileWriter fw = new FileWriter(config);
        XMLOutputter fmt = new XMLOutputter();
        fmt.setFormat(Format.getPrettyFormat()
                            .setLineSeparator(System.getProperty("line.separator"))
                            .setTextMode(Format.TextMode.PRESERVE));
        fmt.output(doc, fw);
        fw.close();
    }
    FileOutputStream out = new FileOutputStream(target);
    ZipOutputStream zip = new ZipOutputStream(out);
    this->exportDirectory(zip, tempProfilePath, tempProfilePath.getPath());
    zip.close();
    out.close();
    FileUtil.delete(tempDir);
}

/*private*/ void exportDirectory(ZipOutputStream zip, File source, String root) throws IOException {
    for (File file : source.listFiles()) {
        if (file.isDirectory()) {
            if (!Profile.isProfile(file)) {
                ZipEntry entry = new ZipEntry(this->relativeName(file, root));
                entry.setTime(file.lastModified());
                zip.putNextEntry(entry);
                this->exportDirectory(zip, file, root);
            }
            continue;
        }
        this->exportFile(zip, file, root);
    }
}

/*private*/ void exportFile(ZipOutputStream zip, File source, String root) throws IOException {
    byte[] buffer = new byte[1024];
    int length;

    FileInputStream input = new FileInputStream(source);
    ZipEntry entry = new ZipEntry(this->relativeName(source, root));
    entry.setTime(source.lastModified());
    zip.putNextEntry(entry);
    while ((length = input.read(buffer)) > 0) {
        zip.write(buffer, 0, length);
    }
    zip.closeEntry();
    input.close();
}

/*private*/ String relativeName(File file, String root) {
    String path = file.getPath();
    if (path.startsWith(root)) {
        path = path.substring(root.length());
    }
    if (file.isDirectory() && !path.endsWith("/")) {
        path = path + "/";
    }
    return path.replaceAll(File.separator, "/");
}
#endif
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
 if (ProfileManager::defaultManager()->getActiveProfile() == NULL)
 {
  ProfileManager::defaultManager()->readActiveProfile();
  // Automatically start with only profile if only one profile
  if (ProfileManager::defaultManager()->getProfiles().length() == 1)
  {
   ProfileManager::defaultManager()->setActiveProfile(ProfileManager::defaultManager()->getProfiles(0));
   // Display profile selector if user did not choose to auto start with last used profile
  }
  else if (!ProfileManager::defaultManager()->isAutoStartActiveProfile())
  {
   return NULL;
  }
 }
 return ProfileManager::defaultManager()->getActiveProfile();
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
 return QUuid::createUuid().toString();
}

void ProfileManager::profileNameChange(Profile* profile, QString oldName) {
    //this->firePropertyChange(new PropertyChangeEvent(profile, Profile::NAME, oldName, profile->getName()));
    emit propertyChange(new PropertyChangeEvent(profile, Profile::NAME, oldName, profile->getName()));
}
//private static class ProfileManagerHolder {

        /**
         * Default instance of the ProfileManager
         */
        /*public*/ /*static*/ ProfileManager* ProfileManager::ProfileManagerHolder::manager = new ProfileManager();
    //};
