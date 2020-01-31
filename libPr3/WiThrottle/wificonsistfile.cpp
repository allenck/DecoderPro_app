#include "wificonsistfile.h"
#include "consistmanager.h"
#include "loggerfactory.h"
/**
 * @author Brett Hoffman Copyright (C) 2011
 *
 */
// /*public*/ class WiFiConsistFile extends ConsistFile {

/*public*/ WiFiConsistFile::WiFiConsistFile(AbstractConsistManager* cm) {
    //super();
    consistMan = cm;
    loadStoredConsistFile("wifiConsist.xml");
    log = LoggerFactory::getLogger("WiFiConsistFile");
}

/**
 * Check to see if wifiConsist.xml file exists. If so load it. If not, check
 * for consist.xml file and load it. Once a wifiConsist.xml file exists, the
 * default file will not be loaded by this anymore.
 */
/*private*/ void WiFiConsistFile::loadStoredConsistFile(QString fileName) {
    if (checkFile(getFileLocation() + fileName)) {
        log->debug("Has " + fileName + " file.");
        try {
            readFile(getFileLocation() + fileName);
        } catch (Exception e) {
            log->warn("error reading consist file: " + e.getMessage());
        }
    } else {
        log->debug("No " + fileName + " file, will check for default file.");
        if (checkFile(defaultConsistFilename())) {
            log->debug("Has default consist.xml file, will read it.");
            try {
                readFile();
            } catch (Exception e) {
                log->warn("error reading consist file: " + e.getMessage());
            }
        } else {
            log->debug("No consist files found, will create if needed.");
        }
    }
}

/*private*/ /*final*/ /*static*/ Logger* WiFiConsistFile::log = LoggerFactory::getLogger("WiFiConsistFile");
