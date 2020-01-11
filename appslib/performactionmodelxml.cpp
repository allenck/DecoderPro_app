#include "performactionmodelxml.h"
#include "performactionmodel.h"
#include "instancemanager.h"
#include "startupactionsmanager.h"
#include "loggerfactory.h"

/**
 * Handle XML persistence of PerformActionModel objects.
 *
 * @author Bob Jacobsen Copyright (c) 2003
 * @see apps.startup.PerformActionModelFactory
 */
///*public*/ class PerformActionModelXml extends jmri.configurexml.AbstractXmlAdapter {

/*public*/ PerformActionModelXml::PerformActionModelXml(QObject* parent)  : AbstractXmlAdapter(parent){
}

/**
 * Default implementation for storing the model contents
 *
 * @param o Object to store, of type PerformActonModel
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement PerformActionModelXml::store(QObject* o) {
    QDomElement element = doc.createElement("perform");
    PerformActionModel* g = (PerformActionModel*) o;

    element.setAttribute("name", g->getClassName());
    element.setAttribute("type", "Action");
    element.setAttribute("class", "apps.configurexml.PerformActionModelXml");
    element.setAttribute("title", g->getTitle());
    QDomElement property = doc.createElement("property"); // NOI18N
    property.setAttribute("name", "systemPrefix"); // NOI18N
    property.setAttribute("value", g->getSystemPrefix());
    element.appendChild(property);
    return element;
}

/**
 * Object should be loaded after basic GUI constructed
 *
 * @return true to defer loading
 * @see jmri.configurexml.AbstractXmlAdapter#loadDeferred()
 * @see jmri.configurexml.XmlAdapter#loadDeferred()
 */
//@Override
/*public*/ bool PerformActionModelXml::loadDeferred() {
    return true;
}

//@Override
/*public*/ bool PerformActionModelXml::load(QDomElement shared, QDomElement /*perNode*/) throw (Exception)
{
 bool result = true;
 QString className = shared.attribute("name");
 QString title = shared.attribute("title");
 PerformActionModel* model = new PerformActionModel();
 Exception* exception = NULL;
 model->setClassName(className);
 model->setTitle(title);
 //for (QDomElement child : shared.getChildren("property"))
 QDomNodeList children = shared.elementsByTagName("property");
 for(int i = 0; i < children.count(); i++)
 { // NOI18N
  QDomElement child = children.at(i).toElement();
  if (child.attribute("name")==("systemPrefix") // NOI18N
          && child.attribute("value") != "")
  { // NOI18N
   model->setSystemPrefix(child.attribute("value")); // NOI18N
  }
 }
 ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->addAction(model);
 if (exception != NULL) {
     throw *exception;
 }
 return result;
}

/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 * @param o       ignored
 */
//@Override
/*public*/ void PerformActionModelXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Unexpected call of load(Element, Object)");
}
// initialize logging
/*private*/ /*final*/ /*static*/ Logger* PerformActionModelXml::log = LoggerFactory::getLogger("PerformActionModelXml");
