#include "carmanagerxml.h"
#include "file.h"
#include "logger.h"
#include "control.h"
#include <QtXml>
#include "locationmanagerxml.h"
#include "carmanager.h"
#include "carroads.h"
#include "cartypes.h"
#include "carloads.h"
#include "carlengths.h"
#include "carowners.h"
#include "carcolors.h"

//CarManagerXml::CarManagerXml(QObject *parent) :
//  OperationsXml(parent)
//{
//}
namespace Operations
{
/**
 * Loads and stores cars using xml files. Also loads and stores car road names,
 * car types, car colors, car lengths, car owners, and car kernels.
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version	$Revision: 29493 $
 */
///*public*/ class CarManagerXml extends OperationsXml {

 /*public*/ CarManagerXml::CarManagerXml(QObject *parent) :
 OperationsXml(parent)
 {
  log = new Logger("CarManagerXml");
  setOperationsFileName("OperationsCarRoster.xml"); // NOI18N
 }

 /**
  * record the single instance *
  */
 /*private*/ /*static*/ CarManagerXml* CarManagerXml::_instance = NULL;

 /*public*/ /*static*/  CarManagerXml* CarManagerXml::instance() {
Logger* log = new Logger("CarManagerXml");
     if (_instance == NULL)
     {
         if (log->isDebugEnabled()) {
             log->debug("CarManagerXml creating instance");
         }
         // create and load
         _instance = new CarManagerXml();
         _instance->load();
     }
     if (Control::showInstance) {
         log->debug(tr("CarManagerXml returns instance %1").arg(_instance->metaObject()->className()));
     }
     return _instance;
 }

 /*public*/ void CarManagerXml::writeFile(QString name) //throws java.io.FileNotFoundException, java.io.IOException
  {
     if (log->isDebugEnabled()) {
         log->debug(tr("writeFile %1").arg(name));
     }
     // This is taken in large part from "Java and XML" page 368
     File* file = new File(findFile(name)->fileName());
     if (file == NULL) {
         file = new File(name);
     }
     // create root element
     doc = QDomDocument();
     QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
     doc.appendChild(xmlProcessingInstruction);
     xmlProcessingInstruction = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\" href=\"" + xsltLocation+"operations-cars.xsl\"");
     doc.appendChild(xmlProcessingInstruction);
     QDomElement root = doc.createElement("operations-config");    //      doc.createElement("operations-config");

//        QDomElement root = QDomElement();
//        root.setTagName("operations-config"); // NOI18N
     //doc = newDocument(root, dtdLocation + "operations-cars.dtd"); // NOI18N
     // add XSLT processing instruction
//        java.util.Map<QString, QString> m = new java.util.HashMap<QString, QString>();
//        m.put("type", "text/xsl"); // NOI18N
//        m.put("href", xsltLocation + "operations-cars.xsl");	// NOI18N
//        ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m); // NOI18N
//        doc.addContent(0, p);
//        QDomProcessingInstruction p = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\"");
//        root.appendChild(p);
//        p = doc.createProcessingInstruction("href", xsltLocation + "operations-cars.xsl");
//        root.appendChild(p);
     doc.appendChild(root);

     // note all comments line feeds have been changed to processor directives
     CarRoads::instance()->store(root,doc);
     CarTypes::instance()->store(root,doc);
     CarColors::instance()->store(root, doc);
     CarLengths::instance()->store(root, doc);
     CarOwners::instance()->store(root, doc);
     CarLoads::instance()->store(root, doc);
     CarManager::instance()->store(root, doc);

     writeXML(file, doc);

     // done - car file now stored, so can't be dirty
     setDirty(false);
 }

 /**
  * Read the contents of a roster XML file into this object. Note that this
  * does not clear any existing entries.
  */
 //@Override
 /*public*/ void CarManagerXml::readFile(QString name) //throws org.jdom2.JDOMException, java.io.IOException
  {
     // suppress rootFromName(name) warning message by checking to see if file exists
     if (findFile(name) == NULL) {
         log->debug(tr("%1 file could not be found").arg(name));
         return;
     }
     // find root
     QDomElement root = rootFromName(name);
     if (root == QDomElement()) {
         log->debug(tr("%1 file could not be read").arg(name));
         return;
     }

     CarRoads::instance()->load(root);
     CarTypes::instance()->load(root);
     CarColors::instance()->load(root);
     CarLengths::instance()->load(root);
     CarOwners::instance()->load(root);
     CarLoads::instance()->load(root);
     CarManager::instance()->load(root);

     log->debug("Cars have been loaded!");
//        RollingStockLogger.instance().enableCarLogging(Setup.isCarLoggerEnabled());
     // clear dirty bit
     setDirty(false);
     // clear location dirty flag, locations get modified during the loading of cars and locos
     LocationManagerXml::instance()->setDirty(false);
 }

 /*public*/ void CarManagerXml::setOperationsFileName(QString name) {
     //operationsFileName = name;
  OperationsXml::setOperationsFileName(name);
 }

 /*public*/ QString CarManagerXml::getOperationsFileName() {
     return OperationsXml::getOperationsFileName();
 }

 /*public*/ void CarManagerXml::dispose(){
     _instance = NULL;
 }
}
