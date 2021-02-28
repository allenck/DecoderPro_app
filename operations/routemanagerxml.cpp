#include "routemanagerxml.h"
#include "control.h"
#include <QtXml>
#include "routemanager.h"
#include "file.h"
#include "instancemanager.h"

namespace Operations
{
//RouteManagerXml::RouteManagerXml(QObject *parent) :
//  OperationsXml(parent)
//{
//}
/**
 * Loads and stores routes using xml files.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2009
 * @version $Revision: 29493 $
 */
///*public*/ class RouteManagerXml extends OperationsXml {

/*public*/ RouteManagerXml::RouteManagerXml(QObject *parent) :
OperationsXml(parent)
{
 log = new Logger("RouteManagerXml");
 operationsFileName = "OperationsRouteRoster.xml"; // NOI18N
 setProperty("InstanceManagerAutoDefault", "true");
 setProperty("InstanceManagerAutoInitialize", "true");

}

/*public*/ void RouteManagerXml::writeFile(QString name) //throws java.io.FileNotFoundException, java.io.IOException
{
    if (log->isDebugEnabled()) {
        log->debug(tr("writeFile %1").arg(name));
    }
    // This is taken in large part from "Java and XML" page 368
    File* file = new  File(findFile(name)->fileName());
    if (file == NULL) {
        file = new File(name);
    }
    // create root element
    QDomDocument doc = QDomDocument();
    QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
    doc.appendChild(xmlProcessingInstruction);
    //    QDomElement root = QDomElement("operations-config"); // NOI18N
    //    QDomDocument doc = newDocument(root, dtdLocation + "operations-config.dtd"); // NOI18N
    //QDomDocument doc;
    QDomElement root = doc.createElement("operations-config");

    // add XSLT processing instruction
//    QMap<QString, QString> m =  QMap<QString, QString>();
//    m.insert("type", "text/xsl"); // NOI18N
//    m.insert("href", xsltLocation + "operations-routes.xsl"); // NOI18N
    //ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m); // NOI18N
    QDomProcessingInstruction p = doc.createProcessingInstruction("type", "text/xsl");
    root.appendChild(p);
     p = doc.createProcessingInstruction("href", tr("%1operations-routes.xsl").arg(xsltLocation));
    root.appendChild(p);
    doc.appendChild(root);

    ((RouteManager*)InstanceManager::getDefault("RouteManager"))->store(root, doc);

    writeXML(file, doc);

    // done - route file now stored, so can't be dirty
    setDirty(false);
}

/**
 * Read the contents of a roster XML file into this object. Note that this
 * does not clear any existing entries.
 */
//@Override
/*public*/ void RouteManagerXml::readFile(QString name) throw (JDOMException, IOException)
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

    ((RouteManager*)InstanceManager::getDefault("RouteManager"))->load(root);

    // clear dirty bit
    setDirty(false);
 }

 /*public*/ void RouteManagerXml::setOperationsFileName(QString name) {
     operationsFileName = name;
 }

 /*public*/ QString RouteManagerXml::getOperationsFileName() {
     return operationsFileName;
 }


 /*public*/ void RouteManagerXml::dispose(){
//    _instance = NULL;
 }

 //@Override
 /*public*/ void RouteManagerXml::initialize() {
     load();
 }

} // end namespace
