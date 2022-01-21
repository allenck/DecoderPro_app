#include "rosterconfigmanager.h"
#include "fileutilsupport.h"
#include "fileutil.h"
#include "preferences.h"
#include "profileutils.h"
#include "roster.h"
#include <QSet>
#include "file.h"
#include "vptr.h"
#include "profilemanager.h"

//RosterConfigManager::RosterConfigManager()
//{

//}
/**
 * Load and store the Roster configuration.
 *
 * This only configures the Roster when initialized so that configuration
 * changes made by users do not affect the running instance of JMRI, but only
 * take effect after restarting JMRI.
 *
 * @author Randall Wood (C) 2015
 */
// /*public*/ class RosterConfigManager extends AbstractPreferencesManager {


    /*public*/ /*static*/ /*final*/ QString RosterConfigManager::DIRECTORY = "directory";
    /*public*/ /*static*/ /*final*/ QString RosterConfigManager::DEFAULT_OWNER = "defaultOwner";
//    /*private*/ static /*final*/ Logger log = LoggerFactory.getLogger(RosterConfigManager.class);

/*public*/ RosterConfigManager::RosterConfigManager()
{
 log = new Logger("RosterConfigManager");
 //directory = FileUtil::PREFERENCES;
 //defaultOwner = "";
 directories = QHash<Profile*, QString>();
 defaultOwners = QHash<Profile*, QString>();
 rosters = QHash<Profile*, Roster*>();

//    log->debug(tr("Roster is %1").arg(this->directory));
//    FileUtilSupport::getDefault()->SwingPropertyChangeSupport::addPropertyChangeListener(FileUtil::PREFERENCES, (PropertyChangeEvent evt) -> {
//        log->debug(tr("UserFiles changed from {} to {}", evt.getOldValue(), evt.getNewValue());
//        if (RosterConfigManager.this->getDirectory().equals(evt.getOldValue())) {
//            RosterConfigManager.this->setDirectory(FileUtil.PREFERENCES);
//        }
//    });
    //connect(FileUtilSupport::getDefault(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(onPropertyChange(PropertyChangeEvent*)));
 FileUtilSupport::getDefault()->addPropertyChangeListener(/*FileUtil::PREFERENCES*/"preference:", (PropertyChangeListener*)this);
}

void RosterConfigManager::propertyChange(PropertyChangeEvent* evt)
{
 FileUtil::Property* oldValue =  VPtr<FileUtil::Property>::asPtr(evt->getOldValue());
 FileUtil::Property* newValue =  VPtr<FileUtil::Property>::asPtr(evt->getNewValue());
 if(oldValue == nullptr) return;
 Profile* project = oldValue->getKey();
 log->debug(tr("UserFiles changed from %1 to %2").arg(evt->getOldValue().toString()).arg( evt->getNewValue().toString()));
 if (this->getDirectory() == (evt->getOldValue().toString())) {
     this->setDirectory(project, FileUtil::PREFERENCES);
 }

}

//@Override
/*public*/ void RosterConfigManager::initialize(Profile* profile) /*throw new (InitializationException)*/
{
 if (!this->isInitialized(profile))
 {
  Preferences* preferences = ProfileUtils::getPreferences(profile, "jmri/jmrit/RosterConfigManager", true);
  this->setDefaultOwner(profile, preferences->get(DEFAULT_OWNER, this->getDefaultOwner()));
  try
  {
   this->setDirectory(profile, preferences->get(DIRECTORY, this->getDirectory()));
  }
  catch (IllegalArgumentException* ex)
  {
   this->setInitialized(profile, true);
   throw new InitializationException(
//                    Bundle.getMessage(Locale.ENGLISH, "IllegalRosterLocation", preferences.get(DIRECTORY, this->getDirectory())),
//                    ex->getMessage(),
//                    ex);
   tr("\"%1\" is not a valid path").arg(preferences->get(DIRECTORY, this->getDirectory())),QString("\"%1\" is not a valid path").arg(preferences->get(DIRECTORY, this->getDirectory())), NULL);
  }
  //Roster::getDefault()->setRosterLocation(this->getDirectory());
  getRoster(profile)->setRosterLocation(this->getDirectory());
  this->setInitialized(profile, true);
 }
}

//@Override
/*public*/ void RosterConfigManager::savePreferences(Profile* profile) {
    Preferences* preferences = ProfileUtils::getPreferences(profile, "jmri.jmrit.RosterConfigManager", true);
    preferences->put(DIRECTORY, FileUtil::getPortableFilename(this->getDirectory()));
    preferences->put(DEFAULT_OWNER, this->getDefaultOwner());
    try {
        preferences->sync();
    } catch (BackingStoreException* ex) {
        log->error("Unable to save preferences", ex);
    }
}
/**
 * Get the default owner for the active profile.
 *
 * @return the default owner
 */
//@Nonnull
/*public*/ QString RosterConfigManager::getDefaultOwner() {
    return getDefaultOwner(ProfileManager::getDefault()->getActiveProfile());
}

/**
 * Get the default owner for the specified profile.
 *
 * @param profile the profile to get the default owner for
 * @return the default owner
 */
//@Nonnull
/*public*/ QString RosterConfigManager::getDefaultOwner(/*@CheckForNull*/ Profile* profile) {
    QString owner = defaultOwners.value(profile);
    // defaultOwner should never be null, but check anyway to ensure its not
    if (owner == "") {
        owner = ""; // NOI18N
        defaultOwners.insert(profile, owner);
    }
    return owner;
}

//@Override
/*public*/ /*Set<Class<? extends PreferencesManager>>*/ QSet<QString>* RosterConfigManager::getRequires() {
   // Set<Class<? extends PreferencesManager>> requires = super.getRequires();
 QSet<QString>* requires = AbstractPreferencesManager::getRequires();
    requires->insert("FileLocationsPreferences");
    return requires;
}

/**
 * Get the roster directory for the active profile.
 *
 * @return the directory
 */
//@Nonnull
/*public*/ QString RosterConfigManager::getDirectory() {
    return getDirectory(ProfileManager::getDefault()->getActiveProfile());
}

/**
 * Get the roster directory for the specified profile.
 *
 * @param profile the profile to get the directory for
 * @return the directory
 */
//@Nonnull
/*public*/ QString RosterConfigManager::getDirectory(/*@CheckForNull*/ Profile* profile) {
    QString directory = directories.value(profile);
    if (directory == "") {
        directory = FileUtil::PREFERENCES;
    }
    if (FileUtil::PREFERENCES == (directory)) {
        return FileUtil::getUserFilesPath();
    }
    return directory;
}

/**
 * @param defaultOwner the defaultOwner to set
 */
/*public*/ void RosterConfigManager::setDefaultOwner(/*@CheckForNull*/ Profile* profile, /*@CheckForNull*/ QString defaultOwner) {
    if (defaultOwner.isNull()) {
        defaultOwner = "";
    }
    QString oldDefaultOwner = this->defaultOwners.value(profile);
    this->defaultOwners.insert(profile, defaultOwner);
    firePropertyChange(DEFAULT_OWNER, oldDefaultOwner, defaultOwner);
}

/**
 * Set the roster directory for the specified profile.
 *
 * @param profile   the profile to set the directory for
 * @param directory the directory to set
 */
/*public*/ void RosterConfigManager::setDirectory(/*@CheckForNull*/ Profile* profile, /*@CheckForNull*/ QString directory) 
{
 if (directory == "" || directory.isEmpty()) 
 {
  directory = FileUtil::PREFERENCES;
 }
 QString oldDirectory = this->directories.value(profile);
 try 
 {
  if (!FileUtil::getFile(directory)->isDirectory()) 
  {
   throw new  IllegalArgumentException(tr("\"%1\" is not a valid path").arg(directory)); // NOI18N
  }
 } 
 catch (FileNotFoundException* ex) 
 { // thrown by getFile() if directory does not exist
  throw new  IllegalArgumentException(tr("\"%1\" is not a valid path").arg(directory)); // NOI18N
 }
 if (directory != (FileUtil::PREFERENCES)) {
     directory = FileUtil::getAbsoluteFilename(directory);
     if (!directory.endsWith(File::separator)) {
         directory = directory + File::separator;
     }
 }
 this->directories.insert(profile, directory);
 log->debug(tr("Roster changed from %1 to %2").arg(oldDirectory).arg(this->directories.value(profile)));
 firePropertyChange(DIRECTORY, oldDirectory, directory);
}

/**
 * Get the roster for the profile.
 *
 * @param profile the profile to get the roster for
 * @return the roster for the profile
 */
//@Nonnull
/*public*/ Roster* RosterConfigManager::getRoster(/*@CheckForNull*/ Profile* profile) {
    Roster* roster = rosters.value(profile);
    if (roster == nullptr) {
        roster = new Roster();
        rosters.insert(profile, roster);
    }
    return roster;
}
/**
 * Set the roster for the profile.
 *
 * @param profile the profile to set the roster for
 * @param roster the roster for the profile
 * @return the roster just set, so this method can be used in a chain
 */
//@Nonnull
/*public*/ Roster* RosterConfigManager::setRoster(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ Roster* roster) {
    rosters.insert(profile, roster);
    return getRoster(profile);
}
