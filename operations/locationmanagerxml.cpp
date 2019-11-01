#include "locationmanagerxml.h"
#include "control.h"
#include "file.h"
#include "locationmanager.h"
#include "logger.h"
#include "schedulemanager.h"
#include "instancemanager.h"

//LocationManagerXml::LocationManagerXml(QObject *parent) :
//  OperationsXml(parent)
//{
//}
namespace Operations
{
/**
 * Load and stores locations and schedules for operations.
 *
 * @author Daniel Boudreau Copyright (C) 2008 2009 2010
 * @version $Revision: 29493 $
 */
///*public*/ class LocationManagerXml extends OperationsXml {

 /*public*/ LocationManagerXml::LocationManagerXml(QObject *parent) :
OperationsXml(parent)
{
 log = new Logger("LocationManagerXml"); log->setDebugEnabled(true);
 operationsFileName = "OperationsLocationRoster.xml";
 setProperty("InstanceManagerAutoDefault", "true");
 setProperty("InstanceManagerAutoInitialize", "true");

}

 /**
  * record the single instance *
  */
 //  /*private*/ /*static*/ LocationManagerXml* LocationManagerXml::_instance = nullptr;


 /*public*/ /*static*/ /*synchronized*/ LocationManagerXml* LocationManagerXml::instance()
 {
  return static_cast<LocationManagerXml*>(InstanceManager::getDefault("LocationManagerXml"));
 }

/*public*/ void LocationManagerXml::writeFile(QString name) throw (FileNotFoundException, IOException)
{
     if (log->isDebugEnabled()) {
         log->debug(tr("writeFile %1").arg(name));
     }
     // This is taken in large part from "Java and XML" page 368
     File* file = new File(findFile(name)->fileName());
     if (file == nullptr) {
         file = new File(name);
     }
     // create root element
     QDomDocument doc = QDomDocument();
     QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
     doc.appendChild(xmlProcessingInstruction);//    QDomElement root = QDomElement("operations-config"); // NOI18N
 //    QDomDocument doc = newDocument(root, dtdLocation + "operations-config.dtd"); // NOI18N
     //QDomDocument doc;
     QDomElement root = doc.createElement("operations-config");
     //, dtdLocation + "operations-locations.dtd"); // NOI18N

     // add XSLT processing instruction
     //QMap<QString, QString> m =  QMap<QString, QString>();
     //m.put("type", "text/xsl"); // NOI18N
     //m.put("href", xsltLocation + "operations-locations.xsl"); // NOI18N
     //ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m); // NOI18N
     QDomProcessingInstruction p = doc.createProcessingInstruction("type", "text/xsl");
     root.appendChild(p);
      p = doc.createProcessingInstruction("href", tr("%1operations-locations.xsl").arg(xsltLocation));
     root.appendChild(p);
     doc.appendChild(root);


     LocationManager::instance()->store(root, doc);
     ScheduleManager::instance()->store(root, doc);

     writeXML(file, doc);

     // done - location file now stored, so can't be dirty
     setDirty(false);
 }

 /**
  * Read the contents of a roster XML file into this object. Note that this
  * does not clear any existing entries.
  */
 //@Override
 /*public*/ void LocationManagerXml::readFile(QString name) throw (JDOMException, IOException)
{
     // suppress rootFromName(name) warning message by checking to see if file exists
     if (findFile(name) == nullptr) {
         log->debug(tr("%1 file could not be found").arg(name));
         return;
     }
     // find root
     QDomElement root = rootFromName(name);
     if (root == QDomElement()) {
         log->debug(tr("%1 file could not be read").arg(name));
         return;
     }

     LocationManager::instance()->load(root);
     ScheduleManager::instance()->load(root);

     setDirty(false);
     log->debug("Locations have been loaded!");
 }

 /*public*/ void LocationManagerXml::setOperationsFileName(QString name) {
     operationsFileName = name;
 }

 /*public*/ QString LocationManagerXml::getOperationsFileName() {
     return operationsFileName;
 }

//@Override
 /*public*/ void LocationManagerXml::initialize() {
     this->load();
 }

 /*public*/ void LocationManagerXml::dispose(){
     //_instance = nullptr;
 }
}
