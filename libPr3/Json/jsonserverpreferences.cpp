#include "jsonserverpreferences.h"
#include "xmlfile.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "file.h"
#include "preferences.h"
#include "profileutils.h"
#include "profilemanager.h"
#include "fileutil.h"

// /*public*/ class JsonServerPreferences extends Bean {

/*public*/ /*static*/ /*final*/ int JsonServerPreferences::DEFAULT_PORT = 2056;
/*static*/ /*final*/ QString JsonServerPreferences::XML_PREFS_ELEMENT = "JSONServerPreferences"; // NOI18N
/*static*/ /*final*/ QString JsonServerPreferences::HEARTBEAT_INTERVAL = "heartbeatInterval"; // NOI18N
/*static*/ /*final*/ QString JsonServerPreferences::PORT = "port"; // NOI18N
// initial defaults if prefs not found
/*private*/ /*final*/ /*static*/ Logger* JsonServerPreferences::log = LoggerFactory::getLogger("JsonServerPreferences");

/*public*/ /*static*/ JsonServerPreferences* JsonServerPreferences::getDefault() {
    if (InstanceManager::getNullableDefault("JsonServerPreferences") == NULL) {
        QString fileName = FileUtil::getUserFilesPath() + "networkServices" + File::separator + "JsonServerPreferences.xml"; // NOI18N
        if ((new File(fileName))->exists()) {
            InstanceManager::store(new JsonServerPreferences(fileName), "JsonServerPreferences");
        } else {
            InstanceManager::store(new JsonServerPreferences(), "JsonServerPreferences");
        }
    }
    return (JsonServerPreferences*)InstanceManager::getDefault("JsonServerPreferences");
}

/*public*/ JsonServerPreferences::JsonServerPreferences(QString fileName, QObject* parent) : Bean(parent) {
 common();
    bool migrate = false;
    Preferences* sharedPreferences = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(), "jmri/jmris/json/JsonServerPreferences", true);
    try {
        if (sharedPreferences->keys().length() == 0) {
            log->info("No JsonServer preferences exist.");
            migrate = true;
        }
    } catch (BackingStoreException ex) {
        log->info("No preferences file exists.");
        migrate = true;
    }
    if (migrate) {
        if (fileName != NULL) {
            try {
                this->openFile(fileName);
            } catch (FileNotFoundException ex) {
                migrate = false;
            }
        } else {
            migrate = false;
        }
    }
    this->readPreferences(sharedPreferences);
    if (migrate) {
        try {
            log->info(tr("Migrating from old JsonServer preferences in %1 to new format in %2.").arg(fileName).arg(FileUtil::getAbsoluteFilename("profile:profile")));
            sharedPreferences->sync();
        } catch (BackingStoreException ex) {
            log->error("Unable to write JsonServer preferences.", ex.getMessage());
        }
    }
}

/*public*/ JsonServerPreferences::JsonServerPreferences(QObject* parent) : Bean(parent)
{
 common();

    Preferences* sharedPreferences = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(), "jmri/jmris/json/JsonServerPreferences", true);
    this->readPreferences(sharedPreferences);
}

/*private*/ void JsonServerPreferences::readPreferences(Preferences* sharedPreferences) {
    this->setHeartbeatInterval(sharedPreferences->getInt(HEARTBEAT_INTERVAL, this->getHeartbeatInterval()));
    this->setPort(sharedPreferences->getInt(PORT, this->getPort()));
    this->asLoadedHeartbeatInterval = this->getHeartbeatInterval();
    this->asLoadedPort = this->getPort();
}

/*public*/ void JsonServerPreferences::load(QDomElement child) {
    QString a;
    a = child.attribute(HEARTBEAT_INTERVAL, "15000");
    if (a != NULL) {
        try {
            this->setHeartbeatInterval(a.toInt());
            this->asLoadedHeartbeatInterval = this->getHeartbeatInterval();
        } catch (DataConversionException e) {
            this->setHeartbeatInterval(15000);
            log->error("Unable to read heartbeat interval. Setting to default value.", e.getMessage());
        }
    }
    a = child.attribute(PORT,"2056");
    if (a != NULL) {
        try {
            this->setPort(a.toInt());
            this->asLoadedPort = this->getPort();
        } catch (DataConversionException e) {
            this->setPort(2056);
            log->error("Unable to read port. Setting to default value.", e.getMessage());
        }
    }
}
void JsonServerPreferences::common()
{
 heartbeatInterval = 15000;
 port = DEFAULT_PORT;
 // as loaded prefences
 asLoadedHeartbeatInterval = 15000;
 asLoadedPort = DEFAULT_PORT;
}

/*public*/ bool JsonServerPreferences::compareValuesDifferent(JsonServerPreferences* prefs) {
    if (this->getHeartbeatInterval() != prefs->getHeartbeatInterval()) {
        return true;
    }
    return this->getPort() != prefs->getPort();
}

/*public*/ void JsonServerPreferences::apply(JsonServerPreferences* prefs) {
    this->setHeartbeatInterval(prefs->getHeartbeatInterval());
    this->setPort(prefs->getPort());
}

/*public*/ /*final*/ void JsonServerPreferences::openFile(QString fileName) throw (FileNotFoundException) {
    JsonServerPreferencesXml* prefsXml = new JsonServerPreferencesXml();
    File* file = new File(fileName);
    QDomElement root;
    try {
        root = prefsXml->rootFromFile(file);
    } catch (FileNotFoundException ea) {
        log->info("Could not find JSON Server preferences file.  Normal if preferences have not been saved before.");
        throw ea;
    } catch (IOException /*| JDOMException*/ eb) {
        log->error(tr("Exception while loading JSON server preferences: %1").arg(eb.getLocalizedMessage()));
        root = QDomElement();
    }
    if (root != QDomElement()) {
        this->load(root);
    }
}

/*public*/ void JsonServerPreferences::save() {
    Preferences* sharedPreferences = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(), "jmri/jmris/json/JsonServerPreferences", true);
    sharedPreferences->putInt(HEARTBEAT_INTERVAL, this->heartbeatInterval);
    sharedPreferences->putInt(PORT, this->port);
}

/*public*/ bool JsonServerPreferences::isDirty() {
    return (this->getHeartbeatInterval() != this->asLoadedHeartbeatInterval
            || this->getPort() != this->asLoadedPort);
}

/*public*/ bool JsonServerPreferences::isRestartRequired() {
    // Once the JsonServer heartbeat interval can be updated, return true
    // only if the server port changes.
    return (this->getHeartbeatInterval() != this->asLoadedHeartbeatInterval
            || this->getPort() != this->asLoadedPort);
}

/*public*/ int JsonServerPreferences::getHeartbeatInterval() {
    return this->heartbeatInterval;
}

/*public*/ void JsonServerPreferences::setHeartbeatInterval(int value) {
    this->heartbeatInterval = value;
}

/*public*/ int JsonServerPreferences::getPort() {
    return this->port;
}

/*public*/ void JsonServerPreferences::setPort(int value) {
    this->port = value;
}

