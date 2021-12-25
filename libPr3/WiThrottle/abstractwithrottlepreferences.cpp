#include "abstractwithrottlepreferences.h"
#include "file.h"
#include "logger.h"

AbstractWiThrottlePreferences::AbstractWiThrottlePreferences(QObject *parent) :
  QObject(parent)
{
 log = new Logger("AbstractWiThrottlePreferences");
}
/**
 * @author Brett Hoffman Copyright (C) 2010
 * @version $Revision: 28746 $
 */
//abstract /*public*/ class AbstractWiThrottlePreferences {


/*public*/ void AbstractWiThrottlePreferences::openFile(QString fileName) {
    this->fileName = fileName;
    AbstractWiThrottlePreferencesXml* prefsXml = new AbstractWiThrottlePreferencesXml();
    File* file = new File(this->fileName);
    QDomElement root;
    try {
        root = prefsXml->rootFromFile(file);
    } catch (FileNotFoundException* ea) {
        log->info("Could not find WiThrottle preferences file.  Normal if preferences have not been saved before.");
        root = QDomElement();
    } catch (Exception* eb) {
        Logger::error("Exception while loading throttles preferences: " + eb->getMessage());
        root = QDomElement();
    }
    if (root != QDomElement()) {
        load(root.firstChildElement("WiThrottlePreferences"));
    }
}

/*abstract*/ void AbstractWiThrottlePreferences::load(QDomElement child) {}

/*abstract*/ QDomElement AbstractWiThrottlePreferences::store() {return QDomElement();}

/*public*/ void AbstractWiThrottlePreferences::save() {
 if (fileName == "") {
        return;
    }

    XmlFile* xmlFile = new XmlFile();
    xmlFile->makeBackupFile(fileName);
    File* file = new File(fileName);
    try {
        File* parentDir = file->getParentFile();
        if (!parentDir->exists()) {
            if (!parentDir->mkdir()) {
                log->warn("Could not create parent directory for prefs file :" + fileName);
                return;
            }
        }
        if (file->createNewFile()) {
            log->debug("Creating new WiThrottle prefs file: " + fileName);
        }
    } catch (Exception* ea) {
        Logger::error("Could not create WiThrottle preferences file.");
    }

    try {
        QDomDocument doc;
        QDomElement root = doc.createElement("withrottle-prefs");
        //QDomDocument doc = XmlFile.newDocument(root);
        root.appendChild(store());
        xmlFile->writeXML(file, doc);
    } catch (Exception* eb) {
        log->warn("Exception in storing WiThrottle xml: " + eb->getMessage());
    }
}

///*public*/ AbstractWiThrottlePreferences() {
//}

