#include "startuppausemodelxml.h"
#include "startupactionsmanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "startuppausemodel.h"
/**
 * Handle XML persistence for {@link apps.startup.StartupPauseModel} objects.
 *
 * @author Randall Wood (c) 2016
 * @see apps.startup.StartupPauseFactory
 */
///*public*/ class StartupPauseModelXml extends AbstractXmlAdapter {

/*private*/ /*final*/ /*static*/ Logger* StartupPauseModelXml::log = LoggerFactory::getLogger("StartupPauseModelXml");

/*public*/ StartupPauseModelXml::StartupPauseModelXml(QObject* parent) : AbstractXmlAdapter(parent){
}

//@Override
/*public*/ QDomElement StartupPauseModelXml::store(QObject* o) {
    QDomElement element = doc.createElement("perform"); // NOI18N
    element.setAttribute("name", "Pause");
    element.setAttribute("type", "Pause");
    element.setAttribute("class", "apps.StartupPauseModel");
    QDomElement property = doc.createElement("property"); // NOI18N
    property.setAttribute("name", "delay"); // NOI18N
    property.setAttribute("value", (((StartupPauseModel*) o)->getDelay()));
    element.appendChild(property);
    return element;
}

//@Override
/*public*/ bool StartupPauseModelXml::loadDeferred() {
    return true;
}

//@Override
/*public*/ bool StartupPauseModelXml::load(QDomElement shared, QDomElement perNode) throw (JmriException) {
    bool result = false;
    StartupPauseModel* model = new StartupPauseModel();
    int delay = 0;
    //for (QDomElement child : shared.getChildren("property"))
    QDomNodeList children = shared.elementsByTagName("property");
    for(int i = 0; i < children.count(); i++)
    { // NOI18N
     QDomElement child = children.at(i).toElement();
        if (child.attribute("name") == ("delay") // NOI18N
                && child.attribute("value") != "") { // NOI18N
            delay = (child.attribute("value").toInt()); // NOI18N
        }
    }
    if (delay != 0) {
        model->setDelay(delay);
    }

    // store the model
    ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->addAction(model);
    return result;
}

//@Override
/*public*/ void StartupPauseModelXml::load(QDomElement element, QObject* o) throw (Exception){
    log-> error("Unexpected call of load(Element, Object)");
}
