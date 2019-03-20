#include "abstractserverpreferences.h"
#include "loggerfactory.h"
#include "preferences.h"
#include "profileutils.h"
#include "profilemanager.h"
#include "fileutil.h"

//abstract /*public*/ class AbstractServerPreferences extends Bean {

/*static*/ /*final*/ QString AbstractServerPreferences::XML_PREFS_ELEMENT = "AbstractServerPreferences"; // NOI18N
/*static*/ /*final*/ QString AbstractServerPreferences::PORT = "port"; // NOI18N
/*private*/ /*final*/ /*static*/ Logger* AbstractServerPreferences::log = LoggerFactory::getLogger("AbstractServerPreferences");

/*public*/ AbstractServerPreferences::AbstractServerPreferences(QString fileName, QObject *parent) {
    bool migrate = false;
    Preferences* sharedPreferences = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(), this->getClass(), true);
    try {
        if (sharedPreferences->keys().length() == 0) {
            log->info("No preferences exist.");
            migrate = true;
        }
    } catch (BackingStoreException ex) {
        log->info("No preferences file exists.");
        migrate = true;
    }
    if (migrate) {
        if (fileName != "") {
            this->openFile(fileName);
        } else {
            migrate = false;
        }
    }
    this->readPreferences(sharedPreferences);
    if (migrate) {
        try {
            log->info(tr("Migrating from old preferences in %1 to new format in %2.").arg(fileName).arg(FileUtil::getAbsoluteFilename("profile:profile")));
            sharedPreferences->sync();
        } catch (BackingStoreException ex) {
            log->error("Unable to write preferences.", ex);
        }
    }
}

/*public*/ AbstractServerPreferences::AbstractServerPreferences(QObject *parent) {
    Preferences* sharedPreferences = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(), this->getClass(), true);
    this->readPreferences(sharedPreferences);
}

/*protected*/ void AbstractServerPreferences::readPreferences(Preferences* sharedPreferences) {
    this->setPort(sharedPreferences->getInt(PORT, this->getDefaultPort()));
    this->asLoadedPort = this->getPort();
}

/*public*/ void AbstractServerPreferences::load(QDomElement child) {
    QString a;
    a = child.attribute(PORT);
    if (!a.isNull()) {
        bool bok;
            this->setPort(a.toInt(&bok));
            this->asLoadedPort = this->getPort();
        if(!bok) {
            this->setPort(getDefaultPort());
            log->error("Unable to read port. Setting to default value."/*, e*/);
        }
    }
}

/*public*/ bool AbstractServerPreferences::compareValuesDifferent(AbstractServerPreferences* prefs) {
    return this->getPort() != prefs->getPort();
}

/*public*/ void AbstractServerPreferences::apply(AbstractServerPreferences* prefs) {
    this->setPort(prefs->getPort());
}

/*public*/ QDomElement AbstractServerPreferences::store() {
    QDomElement prefs = doc.createElement(XML_PREFS_ELEMENT);
    prefs.setAttribute(PORT, (this->getPort()));
    return prefs;
}

/*public*/ /*final*/ void AbstractServerPreferences::openFile(QString fileName) {
    this->fileName = fileName;
    AbstractServerPreferencesXml* prefsXml = new AbstractServerPreferencesXml();
    doc = prefsXml->doc;
    File* file = new File(this->fileName);
    QDomElement root;
    try {
        root = prefsXml->rootFromFile(file);
    } catch (FileNotFoundException ea) {
        log->info("Could not find Server preferences file.  Normal if preferences have not been saved before.");
        root = QDomElement();
    } catch (IOException eb) {
        log->error(tr("Exception while loading server preferences: %1").arg(eb.getLocalizedMessage()));
        root = QDomElement();
    } catch (JDOMException eb) {
        log->error(tr("Exception while loading server preferences: %1").arg(eb.getLocalizedMessage()));
        root = QDomElement();
    }
    if (root != QDomElement()) {
        this->load(root);
    }
}

/*public*/ void AbstractServerPreferences::save() {
    Preferences* sharedPreferences = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(), this->getClass(), true);
    sharedPreferences->putInt(PORT, this->port);
}

/*public*/ bool AbstractServerPreferences::isDirty() {
    return (this->getPort() != this->asLoadedPort);
}

/*public*/ bool AbstractServerPreferences::isRestartRequired() {
    // return true only if the server port changes.
    return (this->getPort() != this->asLoadedPort);
}

/*public*/ int AbstractServerPreferences::getPort() {
    return this->port;
}

/*public*/ void AbstractServerPreferences::setPort(int value) {
    this->port = value;
}

/*abstract*/ /*public*/ int AbstractServerPreferences::getDefaultPort() {return -1;}

