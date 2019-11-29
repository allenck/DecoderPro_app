#include "abstractconfigurationprovider.h"
#include "fileutil.h"
#include "auxiliaryconfiguration.h"
#include "file.h"
#include "profile.h"
#include "nodeidentity.h"
#include "loggerfactory.h"

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
  if (!shared)
  {
   File* nodeDir = new File(dir, NodeIdentity::storageIdentity());
   if (!nodeDir->exists())
   {
    bool success = NodeIdentity::copyFormerIdentity(dir, nodeDir);
    if (! success)
     log->debug(tr("copyFormerIdentity(%1, %2) did not copy").arg(dir->toString()).arg(nodeDir->toString()));
   }
   dir = new File(dir, NodeIdentity::storageIdentity());
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

/*private*/ /*static*/ Logger* AbstractConfigurationProvider::log = LoggerFactory::getLogger("AbstractConfigurationProvider");
