#include "trainmanagerxml.h"
#include "logger.h"
#include "trainmanager.h"
#include "control.h"
#include "file.h"
#include "trainmanager.h"
#include "trainschedulemanager.h"
#include "operationsmanager.h"
#include "instancemanager.h"

//TrainManagerXml::TrainManagerXml(QObject *parent) :
//  OperationsXml(parent)
//{
//}
namespace Operations
{
 /**
  * Loads and stores trains using xml files. Also stores various train parameters
  * managed by the TrainManager.
  *
  * @author Daniel Boudreau Copyright (C) 2008, 2010
  * @version $Revision: 29508 $
  */
 ///*public*/ class TrainManagerXml extends OperationsXml {


 // the directories under operations
 /*private*/ /*static*/ /*final*/ QString TrainManagerXml::BUILD_STATUS = "buildstatus"; // NOI18N
 /*private*/ /*static*/ /*final*/ QString TrainManagerXml::MANIFESTS = "manifests"; // NOI18N
 /*private*/ /*static*/ /*final*/ QString TrainManagerXml::SWITCH_LISTS = "switchLists"; // NOI18N
 /*private*/ /*static*/ /*final*/ QString TrainManagerXml::CSV_MANIFESTS = "csvManifests"; // NOI18N
 /*private*/ /*static*/ /*final*/ QString TrainManagerXml::CSV_SWITCH_LISTS = "csvSwitchLists"; // NOI18N

 /*public*/ TrainManagerXml::TrainManagerXml(QObject *parent) :
  OperationsXml(parent)
 {
  fileLoaded = false;
  log = new Logger("TrainManagerXml");
  log->setDebugEnabled(true);
  operationsFileName = "OperationsTrainRoster.xml";// NOI18N
  buildReportFileName = tr("train") + " (";
  manifestFileName = tr("train") + " (";
  switchListFileName = tr("location") + " (";
  fileType = ").txt"; // NOI18N
  fileTypeCsv = ").csv"; // NOI18N
  defaultCsvSwitchListDirectory = OperationsXml::getFileLocation()
          + OperationsXml::getOperationsDirectoryName() + File::separator + CSV_SWITCH_LISTS + File::separator;
  defaultCsvManifestDirectory = OperationsXml::getFileLocation()
          + OperationsXml::getOperationsDirectoryName() + File::separator + CSV_MANIFESTS + File::separator;
  setProperty("InstanceManagerAutoDefault", "true");
  setProperty("InstanceManagerAutoInitialize", "true");

 }

 //@Override
 /*public*/ void TrainManagerXml::writeFile(QString name) //throw FileNotFoundException, IOException
 {
  if (log->isDebugEnabled())
  {
      log->debug("writeFile " + name);
  }
  // This is taken in large part from "Java and XML" page 368
  File* file = new File(findFile(name)->fileName());
  if (file == NULL) {
      file = new File(name);
  }
  // create root element
  QDomDocument doc = QDomDocument();
  //QDomElement root = new Element("operations-config"); // NOI18N
//    QDomElement root = QDomElement();
//    root.setTagName("operations-config");
//    QDomDocument doc = newDocument(root,dtdLocation + "operations-trains.dtd"); // NOI18N
  QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
  doc.appendChild(xmlProcessingInstruction);
  QDomElement root = doc.createElement("operations-config");

  // add XSLT processing instruction
//    java.util.Map<String, String> m = new java.util.HashMap<String, String>();
//    m.put("type", "text/xsl"); // NOI18N
//    m.put("href", xsltLocation + "operations-trains.xsl"); // NOI18N
//    ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m); // NOI18N
//    doc.addContent(0, p);
  QDomProcessingInstruction p = doc.createProcessingInstruction("type", "text/xsl");
  root.appendChild(p);
  p = doc.createProcessingInstruction("href", xsltLocation + "operations-trains.xsl");
  root.appendChild(p);
  doc.appendChild(root);

  ((Operations::TrainManager*)InstanceManager::getDefault("TrainManager"))->store(root, doc);
  ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->store(root, doc);

  writeXML(file, doc);

  // done - train file now stored, so can't be dirty
  setDirty(false);
 }

 /**
  * Read the contents of a roster XML file into this object. Note that this
  * does not clear any existing entries.
  */
 //@Override
 /*public*/ void TrainManagerXml::readFile(QString name) //throw (JDOMException,IOException)
 {
  // suppress rootFromName(name) warning message by checking to see if file exists
  if (findFile(name) == nullptr) {
      log->debug(name + " file could not be found");
      fileLoaded = true; // set flag, could be the first time
      return;
  }
  // find root
  QDomElement root = rootFromName(name);
  if (root == QDomElement()) {
      log->debug(name + " file could not be read");
      return;
  }

  ((Operations::TrainManager*)InstanceManager::getDefault("TrainManager"))->load(root);
//    TrainScheduleManager.instance().load(root);

  fileLoaded = true; // set flag trains are loaded

  // now load train icons on panels
  ((Operations::TrainManager*)InstanceManager::getDefault("TrainManager"))->loadTrainIcons();

  // loading complete run startup scripts
  ((Operations::TrainManager*)InstanceManager::getDefault("TrainManager"))->runStartUpScripts();

  log->debug("Trains have been loaded!");
//    Operations::TrainLogger::instance().enableTrainLogging(Setup.isTrainLoggerEnabled());
  setDirty(false); // clear dirty flag
 }

 /*public*/ bool TrainManagerXml::isTrainFileLoaded() {
     return fileLoaded;
 }

    /**
     * Store the train's build report
     */
    /*public*/ File* TrainManagerXml::createTrainBuildReportFile(QString name) {
        return createFile(defaultBuildReportFilename(name), false); // don't backup
    }

    /*public*/ File* TrainManagerXml::getTrainBuildReportFile(QString name) {
        File* file = new File(defaultBuildReportFilename(name));
        return file;
    }

    /*public*/ QString TrainManagerXml::defaultBuildReportFilename(QString name) {
        return OperationsXml::getFileLocation() + OperationsXml::getOperationsDirectoryName()
                + BUILD_STATUS + File::separator + buildReportFileName + name + fileType; // NOI18N
    }

    /*public*/ void TrainManagerXml::setBuildReportName(QString name) {
        buildReportFileName = name;
    }

    /**
     * Store the train's manifest
     */
    /*public*/ File* TrainManagerXml::createTrainManifestFile(QString name) {
        return createFile(getDefaultManifestFilename(name), false); // don't backup
    }

    /*public*/ File* TrainManagerXml::getTrainManifestFile(QString name) {
        File* file = new File(getDefaultManifestFilename(name));
        return file;
    }

    /*private*/ QString TrainManagerXml::getDefaultManifestFilename(QString name) {
        return OperationsXml::getFileLocation() + OperationsXml::getOperationsDirectoryName() + File::separator + MANIFESTS
                + File::separator + manifestFileName + name + fileType;// NOI18N
    }

    /*public*/ File* TrainManagerXml::getTrainCsvManifestFile(QString name) {
        File* file = new File(getDefaultCsvManifestFilename(name));
        return file;
    }

    /*public*/ File* TrainManagerXml::createTrainCsvManifestFile(QString name) {
        return createFile(getDefaultCsvManifestFilename(name), false); // don't backup
    }

    /*private*/ QString TrainManagerXml::getDefaultCsvManifestFilename(QString name) {
        return defaultCsvManifestDirectory + manifestFileName + name + fileTypeCsv; // NOI18N
    }

    /*public*/ void TrainManagerXml::createDefaultCsvManifestDirectory() {
        createFile(defaultCsvManifestDirectory + " ", false); // don't backup
    }

    /*public*/ File* TrainManagerXml::getManifestFile(QString name, QString ext) {
        return new File(getDefaultManifestFilename(name, ext));
    }

    /*public*/ File* TrainManagerXml::createManifestFile(QString name, QString ext) {
        return createFile(getDefaultManifestFilename(name, ext), false); // don't backup
    }

    /*private*/ QString TrainManagerXml::getDefaultManifestFilename(QString name, QString ext) {
        return ((Operations::OperationsManager*)InstanceManager::getDefault("Operations::OperationsManager"))->getPath(MANIFESTS) + File::separator + "train-" + name + "." + ext; // NOI18N
    }

    /**
     * Store the switch list for a location
     */
    /*public*/ File* TrainManagerXml::createSwitchListFile(QString name) {
        return createFile(getDefaultSwitchListName(name), false); // don't backup
    }

    /*public*/ File* TrainManagerXml::getSwitchListFile(QString name) {
        File* file = new File(getDefaultSwitchListName(name));
        return file;
    }

    /*private*/ QString TrainManagerXml::getDefaultSwitchListName(QString name) {
        return OperationsXml::getFileLocation() + OperationsXml::getOperationsDirectoryName() + File::separator
                + SWITCH_LISTS + File::separator + switchListFileName + name + fileType; // NOI18N
    }

    /**
     * Store the CSV switch list for a location
     */
    /*public*/ File* TrainManagerXml::createCsvSwitchListFile(QString name) {
        return createFile(getDefaultCsvSwitchListName(name), false); // don't backup
    }

    /*public*/ File* TrainManagerXml::getCsvSwitchListFile(QString name) {
        File* file = new File(getDefaultCsvSwitchListName(name));
        return file;
    }

    /*private*/ QString TrainManagerXml::getDefaultCsvSwitchListName(QString name) {
        return defaultCsvSwitchListDirectory + switchListFileName + name + fileTypeCsv;// NOI18N
    }

    /*public*/ void TrainManagerXml::createDefaultCsvSwitchListDirectory() {
        createFile(defaultCsvSwitchListDirectory + " ", false); // don't backup
    }

    /*public*/ void TrainManagerXml::setTrainSwitchListName(QString name) {
        switchListFileName = name;
    }

    //@Override
    /*public*/ void TrainManagerXml::setOperationsFileName(QString name) {
        operationsFileName = name;
    }

    //@Override
    /*public*/ QString TrainManagerXml::getOperationsFileName() {
        return operationsFileName;
    }

    /*public*/ void TrainManagerXml::dispose(){
//        _instance = NULL;
    }

    /*public*/ void TrainManagerXml::initialize()
    {
     load();
    }
} // end Namespace
