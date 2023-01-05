#include "lntcppreferences.h"
#include "webserverpreferences.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "profilemanager.h"
#include "profileutils.h"
#include "preferences.h"
#include "properties.h"
#include "fileinputstream.h"
#include "file.h"
#include "exceptions.h"
#include "fileutil.h"

/**
 * Preferences for the LocoNet over TCP server.
 *
 * @author Randall Wood (C) 2017
 */
// /*public*/ class LnTcpPreferences extends PreferencesBean {
/*public*/ /*final*/ /*static*/ QString LnTcpPreferences::PORT = "1234";//WebServerPreferences::PORT;

/*private*/ /*static*/ /*final*/ QString LnTcpPreferences::PORT_NUMBER_KEY = "PortNumber";
/*private*/ /*static*/ /*final*/ QString LnTcpPreferences::SETTINGS_FILE_NAME = "LocoNetOverTcpSettings.ini";

/*public*/ /*static*/ LnTcpPreferences* LnTcpPreferences::getDefault()
{
 LnTcpPreferences* pref;
 if((pref = (LnTcpPreferences*) InstanceManager::getOptionalDefault("LnTcpPreferences"))== NULL)
   return (LnTcpPreferences*)InstanceManager::setDefault("LnTcpPreferences", new LnTcpPreferences());
 return pref;
}

/*private*/ /*final*/ /*static*/ Logger* LnTcpPreferences::log = LoggerFactory::getLogger("LnTcpPreferences");

/*public*/ LnTcpPreferences::LnTcpPreferences(QObject* parent) : PreferencesBean(ProfileManager::getDefault()->getActiveProfile(),parent){
    //super(ProfileManager.getDefault().getActiveProfile());
     port = 1234;

    Preferences* sharedPreferences = ProfileUtils::getPreferences(PreferencesBean::getProfile(), this->metaObject()->className(), true);
    this->readPreferences(sharedPreferences);
}

/*private*/ void LnTcpPreferences::readPreferences(Preferences* sharedPreferences) {
    bool migrate = false;
    try {
        if (sharedPreferences->keys().length() == 0) {
            log->debug("No LocoNetOverTCP preferences exist.");
            migrate = true;
        }
    } catch (BackingStoreException* ex) {
        log->debug("No preferences file exists.");
        migrate = true;
    }
    if (!migrate) {
        this->port = sharedPreferences->getInt(PORT, this->getPort());
        this->setIsDirty(false);
    } else {
        Properties* settings = new Properties();
        File* file = new File(FileUtil::getUserFilesPath(), SETTINGS_FILE_NAME);
        log->debug(tr("Opening settings file %1").arg(file->toString()));
        try
        {
         if(!file->exists())
          return;
         FileInputStream* stream = new FileInputStream(file);
         bool ok;
            settings->load(stream);
            this->port = settings->getProperty(PORT_NUMBER_KEY, QString::number(this->getPort())).toInt(&ok);
            if(!ok) throw new IOException();
            this->setIsDirty(true);
        } catch (FileNotFoundException* ex) {
            log->debug("old preferences file not found");
        } catch (IOException* ex) {
            log->debug("exception reading old preferences file" + ex->getMessage());
        }
    }
}

/*public*/ void LnTcpPreferences::savePreferences() {
    Preferences* sharedPreferences = ProfileUtils::getPreferences(this->getProfile(), this->metaObject()->className(), true);
    sharedPreferences->putInt(PORT, this->getPort());
    try {
        sharedPreferences->sync();
        setIsDirty(false);  //  Resets only when stored
    } catch (BackingStoreException* ex) {
        log->error("Exception while saving web server preferences", ex);
    }
}

bool LnTcpPreferences::isPreferencesValid() {
    return this->port > 0 && this->port < 65536;
}

/**
 * Get the port used by the LocoNetOverTCP server.
 *
 * @return the port
 */
/*public*/ int LnTcpPreferences::getPort() {
    return port;
}

/**
 * Set the port used by the LocoNetOverTCP server.
 *
 * @param value the port
 */
/*public*/ void LnTcpPreferences::setPort(int value) {
    int old = this->port;
    if (old != value) {
        this->port = value;
        this->firePropertyChange(PORT, old, value);
        this->setRestartRequired();
    }
}
