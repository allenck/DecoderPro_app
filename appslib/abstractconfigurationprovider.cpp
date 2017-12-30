#include "abstractconfigurationprovider.h"
#include "fileutil.h"
#include "auxiliaryconfiguration.h"
#include "file.h"
#include "profile.h"
#include "nodeidentity.h"

/**
 *
 * @author Randall Wood
 */
///*public*/ abstract class AbstractConfigurationProvider {


/*public*/ AbstractConfigurationProvider::AbstractConfigurationProvider(Profile* project, QObject* parent) : QObject(parent)
{
 privateBackedUp = false;
 sharedBackedUp = false;
 this->project = project;
}

/**
 * Get the {@link jmri.profile.AuxiliaryConfiguration}.
 *
 * @return The AuxiliaryConfiguration.
 */
/*protected*/ /*abstract*/ AuxiliaryConfiguration* AbstractConfigurationProvider::getConfiguration() {return NULL;}

/*protected*/ /*abstract*/ File* AbstractConfigurationProvider::getConfigurationFile(bool /*shared*/) {return NULL;}

/*public*/ File* AbstractConfigurationProvider::getConfigurationDirectory(bool shared)
{
 File* dir;
 if (this->project == NULL)
 {
  dir = new File(FileUtil::getPreferencesPath(), "preferences"); // NOI18N
 }
 else
 {
  dir = new File(this->project->getPath(), /*Profile::PROFILE*/"profile");
  if (!shared) {
      dir = new File(dir, NodeIdentity::identity());
  }
 }
 FileUtil::createDirectory(dir);
 return dir;
}

/**
 * @return the privateBackedUp
 */
/*protected*/ bool AbstractConfigurationProvider::isPrivateBackedUp() {
    return privateBackedUp;
}

/**
 * @param privateBackedUp the privateBackedUp to set
 */
/*protected*/ void AbstractConfigurationProvider::setPrivateBackedUp(bool privateBackedUp) {
    this->privateBackedUp = privateBackedUp;
}

/**
 * @return the sharedBackedUp
 */
/*protected*/ bool AbstractConfigurationProvider::isSharedBackedUp() {
    return sharedBackedUp;
}

/**
 * @param sharedBackedUp the sharedBackedUp to set
 */
/*protected*/ void AbstractConfigurationProvider::setSharedBackedUp(bool sharedBackedUp) {
    this->sharedBackedUp = sharedBackedUp;
}
