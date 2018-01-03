#include "createbuttommodelxml.h"
#include "loggerfactory.h"
#include "startupactionsmanager.h"
#include "instancemanager.h"
#include "createbuttonmodel.h"

/**
 * Handle XML persistence of CreateButtonModel objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @see apps.startup.CreateButtonModelFactory
 */
///*public*/ class CreateButtonModelXml extends jmri.configurexml.AbstractXmlAdapter {

/*public*/ CreateButtonModelXml::CreateButtonModelXml(QObject* parent) {
}

/**
 * Default implementation for storing the model contents
 *
 * @param o Object to store, of type CreateButtonModel
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement CreateButtonModelXml ::store(QObject* o) {
    QDomElement element = doc.createElement("perform");
    CreateButtonModel* g = (CreateButtonModel*) o;

    element.setAttribute("name", g->getClassName());
    element.setAttribute("type", "Button");
    element.setAttribute("class", "apps.CreateButtonModelXml");
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
/*public*/ bool CreateButtonModelXml ::loadDeferred() {
    return true;
}

//@Override
/*public*/ bool CreateButtonModelXml ::load(QDomElement shared, QDomElement perNode) {
    bool result = true;
    QString className = shared.attribute("name");
    CreateButtonModel* model = new CreateButtonModel();
    model->setClassName(className);
    //for (QDomElement child : shared.getChildren("property"))
    QDomNodeList children = shared.elementsByTagName("property");
    for(int i = 0; i < children.count(); i++)
    { // NOI18N
     QDomElement child = children.at(i).toElement();
     if (child.attribute("name") == ("systemPrefix") // NOI18N
             && child.attribute("value") != "") { // NOI18N
         model->setSystemPrefix(child.attribute("value")); // NOI18N
     }
    }
    ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->addAction(model);
    return result;
}

/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 * @param o       ignored
 */
//@Override
/*public*/ void CreateButtonModelXml ::load(QDomElement element, QObject* o) throw (Exception){
    log-> error("Unexpected call of load(Element, Object)");
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* CreateButtonModelXml ::log = LoggerFactory::getLogger("CreateButtonModelXml");
