#include "profileproperties.h"
#include "jmripreferencesprovider.h"
#include "loggerfactory.h"
#include "profile.h"
#include "exceptions.h"

// /*public*/ class ProfileProperties implements AuxiliaryProperties {


/*private*/ /*final*/ /*static*/ Logger* ProfileProperties::log = LoggerFactory::getLogger("ProfileProperties");

/*public*/ ProfileProperties::ProfileProperties(Profile* project, QObject* parent) : AuxiliaryProperties(parent)
{
 this->path = project->getPath();
}

/**
 * Package protected constructor used in
 * {@link jmri.profile.Profile#Profile(java.io.File, boolean)}.
 *
 * @param path Path to a partially constructed Profile
 */
ProfileProperties::ProfileProperties(File* path, QObject* parent) : AuxiliaryProperties(parent)
{
    this->path = path;
}

//@Override
//@SuppressFBWarnings(value = "deprecation", justification = "Avoids errors passing partly constructed object.")
//@SuppressWarnings("deprecation") // silence deprecation notice in IDEs
/*public*/ QString ProfileProperties::get(QString key, bool shared)
{
    return JmriPreferencesProvider::getPreferences(path, NULL, shared)->node(/*Profile::PROFILE*/"profile")->get(key, NULL);
}

//@Override
//@SuppressFBWarnings(value = "deprecation", justification = "Avoids errors passing partly constructed object.")
//@SuppressWarnings("deprecation")
/*public*/ QList<QString> ProfileProperties::listKeys(bool shared) {
    try {
        QStringList keys = JmriPreferencesProvider::getPreferences(path, NULL, shared)->node(Profile::PROFILE)->keys();
        return QList<QString>(keys);
    } catch (BackingStoreException ex) {
        log->error("Unable to read properties.", ex);
        return QList<QString>();
    }
}

//@Override
//@SuppressFBWarnings(value = "deprecation", justification = "Avoids errors passing partly constructed object.")
//@SuppressWarnings("deprecation")
/*public*/ void ProfileProperties::put(QString key, QString value, bool shared) {
    JmriPreferencesProvider::getPreferences(path, "", shared)->node(Profile::PROFILE)->put(key, value);
}
