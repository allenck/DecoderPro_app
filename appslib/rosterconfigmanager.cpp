#include "rosterconfigmanager.h"
#include "fileutilsupport.h"
#include "fileutil.h"
#include "preferences.h"
#include "profileutils.h"
#include "roster.h"
#include <QSet>
#include "file.h"

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
 directory = FileUtil::PREFERENCES;
 defaultOwner = "";
 rosters = QHash<Profile*, Roster*>();

    log->debug(tr("Roster is %1").arg(this->directory));
//    FileUtilSupport::getDefault()->addPropertyChangeListener(FileUtil::PREFERENCES, (PropertyChangeEvent evt) -> {
//        log->debug(tr("UserFiles changed from {} to {}", evt.getOldValue(), evt.getNewValue());
//        if (RosterConfigManager.this->getDirectory().equals(evt.getOldValue())) {
//            RosterConfigManager.this->setDirectory(FileUtil.PREFERENCES);
//        }
//    });
    connect(FileUtilSupport::getDefault(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(onPropertyChange(PropertyChangeEvent*)));
}

void RosterConfigManager::onPropertyChange(PropertyChangeEvent* evt)
{
 log->debug(tr("UserFiles changed from %1 to %2").arg(evt->getOldValue().toString()).arg( evt->getNewValue().toString()));
 if (this->getDirectory() == (evt->getOldValue().toString())) {
     this->setDirectory(FileUtil::PREFERENCES);
 }

}

//@Override
/*public*/ void RosterConfigManager::initialize(Profile* profile) throw (InitializationException)
{
 if (!this->isInitialized(profile))
 {
  Preferences* preferences = ProfileUtils::getPreferences(profile, "jmri/jmrit/RosterConfigManager", true);
  this->setDefaultOwner(preferences->get(DEFAULT_OWNER, this->getDefaultOwner()));
  try
  {
   this->setDirectory(preferences->get(DIRECTORY, this->getDirectory()));
  }
  catch (IllegalArgumentException ex)
  {
   this->setInitialized(profile, true);
   throw InitializationException(
//                    Bundle.getMessage(Locale.ENGLISH, "IllegalRosterLocation", preferences.get(DIRECTORY, this->getDirectory())),
//                    ex.getMessage(),
//                    ex);
   tr("\"%1\" is not a valid path").arg(preferences->get(DIRECTORY, this->getDirectory())),QString("\"%1\" is not a valid path").arg(preferences->get(DIRECTORY, this->getDirectory())), NULL);
  }
  Roster::getDefault()->setRosterLocation(this->getDirectory());
  this->setInitialized(profile, true);
 }
}

//@Override
/*public*/ void RosterConfigManager::savePreferences(Profile* profile) {
    Preferences* preferences = ProfileUtils::getPreferences(profile, "jmri/jmrit/RosterConfigManager", true);
    preferences->put(DIRECTORY, FileUtil::getPortableFilename(this->getDirectory()));
    preferences->put(DEFAULT_OWNER, this->getDefaultOwner());
//    try {
        preferences->sync();
//    } catch (BackingStoreException ex) {
//        log->error("Unable to save preferences", ex);
//    }
}

//@Override
/*public*/ /*Set<Class<? extends PreferencesManager>>*/ QSet<QString>* RosterConfigManager::getRequires() {
   // Set<Class<? extends PreferencesManager>> requires = super.getRequires();
 QSet<QString>* requires = AbstractPreferencesManager::getRequires();
    requires->insert("FileLocationsPreferences");
    return requires;
}

/**
 * @return the defaultOwner
 */
//@Nonnull
/*public*/ QString RosterConfigManager::getDefaultOwner() {
    // defaultOwner should never be null, but check anyway to ensure its not
    if (defaultOwner.isNull()) {
        defaultOwner = "";
    }
    return defaultOwner;
}

/**
 * @param defaultOwner the defaultOwner to set
 */
/*public*/ void RosterConfigManager::setDefaultOwner(QString defaultOwner) {
    if (defaultOwner.isNull()) {
        defaultOwner = "";
    }
    QString oldDefaultOwner = this->defaultOwner;
    this->defaultOwner = defaultOwner;
    firePropertyChange(DEFAULT_OWNER, oldDefaultOwner, defaultOwner);
}

/**
 * @return the directory
 */
/*public*/ QString RosterConfigManager::getDirectory() {
    if (FileUtil::PREFERENCES == (this->directory)) {
        return FileUtil::getUserFilesPath();
    }
    return this->directory;
}

/**
 * @param directory the directory to set
 */
/*public*/ void RosterConfigManager::setDirectory(QString directory)
{
 if (directory == "" || directory.isEmpty())
 {
  directory = FileUtil::PREFERENCES;
 }
 QString oldDirectory = this->directory;
 try
 {
  if (!FileUtil::getFile(directory)->isDirectory())
  {
   throw  IllegalArgumentException(tr("\"%1\" is not a valid path").arg( directory)); // NOI18N
  }
 }
 catch (FileNotFoundException ex)
 { // thrown by getFile() if directory does not exist
    throw  IllegalArgumentException(tr("\"%1\" is not a valid path").arg( directory)); // NOI18N
 }
 if (directory != (FileUtil::PREFERENCES)) {
     directory = FileUtil::getAbsoluteFilename(directory);
     if (!directory.endsWith(File::separator)) {
         directory = directory + File::separator;
     }
 }
 this->directory = directory;
 log->debug(tr("Roster changed from %1 to %2").arg(oldDirectory).arg(this->directory));
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
