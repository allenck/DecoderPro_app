#include "operationssetupxml.h"
#include "control.h"
#include "setup.h"
#include "trainmanifestheadertext.h"
#include "trainmanifesttext.h"
#include "trainswitchlisttext.h"
#include "version.h"
#include "instancemanager.h"

namespace Operations
{
 OperationsSetupXml::OperationsSetupXml(QObject *parent) :
   OperationsXml(parent)
 {
  log = new Logger("OperationsSetupXml");
  operationsFileName = "Operations.xml"; // NOI18N
  setProperty("InstanceManagerAutoDefault", "true");
  setProperty("InstanceManagerAutoInitialize", "true");

 }
 /**
  * Loads and stores the operation setup using xml files.
  *
  * @author Daniel Boudreau Copyright (C) 2008, 2010
  * @version $Revision: 29493 $
  */
 ///*public*/ class OperationsSetupXml extends OperationsXml {

 ///*public*/ OperationsSetupXml() {
 //}

 /*public*/ void OperationsSetupXml::writeFile(QString name) //throw (FileNotFoundException, IOException)
 {
     if (log->isDebugEnabled()) {
         log->debug(tr("writeFile %1").arg(name));
     }
     // This is taken in large part from "Java and XML" page 368
     QFile* file = findFile(name);
     if (file == NULL) {
         file = new QFile(name);
     }
     // create root element
     doc = QDomDocument("operations-config");
     QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
     doc.appendChild(xmlProcessingInstruction);//    QDomElement root = QDomElement("operations-config"); // NOI18N
 //    QDomDocument doc = newDocument(root, dtdLocation + "operations-config.dtd"); // NOI18N
     //QDomDocument doc;

     QDomElement root = doc.createElement("operations-config");

     // add XSLT processing instruction
 //    java.util.Map<String, String> m = new java.util.HashMap<String, String>();
 //    m.put("type", "text/xsl"); // NOI18N
 //    m.put("href", xsltLocation + "operations-config.xsl"); // NOI18N
 //    ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m); // NOI18N
 //    doc.addContent(0, p);
     QDomProcessingInstruction p = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\" href=\"/xml/XSLT/operations-config.xsl\"");
     doc.appendChild(p);
     doc.appendChild(root);
     root.appendChild(doc.createComment(tr("Written by JMRI version %1 on %1").arg(Version::getCanonicalVersion()).arg(QDateTime::currentDateTime().toString())));

     // add top-level elements
     Setup::setDoc(doc);
     root.appendChild(Setup::store());

     // add manifest header text strings
     root.appendChild(TrainManifestHeaderText::store(doc));

     // add manifest text strings
     root.appendChild(TrainManifestText::store(doc));

     // add switch list text strings
     root.appendChild(TrainSwitchListText::store(doc));

     // add control elements
     Control::setDoc(doc);
     root.appendChild(Control::store());

     writeXML(file, doc);

     // done, so can't be dirty
     setDirty(false);
 }

 //@Override
 /*public*/ void OperationsSetupXml::readFile(QString name) //throw (JDOMException, IOException)
 {
     // suppress rootFromName(name) warning message by checking to see if file exists
     if (findFile(name) == NULL) {
         log->debug(tr("%1 file could not be found").arg(name));
         return;
     }
     // find root
     QDomElement root = rootFromName(name);
     if (root == QDomElement())
     {
      log->debug(tr("%1 file could not be read").arg(name));
      return;
     }
     Setup::load(root);

     // load manifest header text strings
     TrainManifestHeaderText::load(root);

     // load manifest text strings
     TrainManifestText::load(root);

     // load switch list text strings
     TrainSwitchListText::load(root);

     // load control settings
     Control::load(root);
 }

 /*public*/ void OperationsSetupXml::setOperationsFileName(QString name) {
     operationsFileName = name;
 }

 /*public*/ QString OperationsSetupXml::getOperationsFileName() {
     return operationsFileName;
 }


 //static Logger log = LoggerFactory.getLogger(OperationsSetupXml.class.getName());

 /*public*/ void OperationsSetupXml::dispose(){
//     _instance = NULL;
 }

 //@Override
 /*public*/ void OperationsSetupXml::initialize() {
     load();
 }
}
