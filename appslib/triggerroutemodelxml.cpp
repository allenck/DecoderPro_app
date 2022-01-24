#include "triggerroutemodelxml.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "startupactionsmanager.h"
#include "triggerroutemodel.h"

/**
 * Handle XML persistence for {@link apps.startup.TriggerRouteModel} objects
 * and set the defined {@link jmri.Route} during application start.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @author Ken Cameron Copyright: 2014(c)
 * @author Randall Wood (c) 2016
 * @see apps.startup.TriggerRouteModelFactory
 */
///*public*/ class TriggerRouteModelXml extends AbstractXmlAdapter {

    /*private*/ /*final*/ /*static*/ Logger* TriggerRouteModelXml::log = LoggerFactory::getLogger("TriggerRouteModelXml");

/*public*/ TriggerRouteModelXml::TriggerRouteModelXml(QObject* parent) : AbstractXmlAdapter(parent){
}

/**
 * Default implementation for storing the model contents
 *
 * @param o Object to store, of type PerformActonModel
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement TriggerRouteModelXml::store(QObject* o) {
    QDomElement e = doc.createElement("perform"); // NOI18N
    e.setAttribute("name", ((TriggerRouteModel*) o)->getName());
    e.setAttribute("type", "Action");
    e.setAttribute("class", "apps.TriggerRouteModelXml");
    return e;
}

/**
 * Object should be loaded after basic GUI constructed
 *
 * @return true to defer loading
 * @see jmri.configurexml.AbstractXmlAdapter#loadDeferred()
 * @see jmri.configurexml.XmlAdapter#loadDeferred()
 */
//@Override
/*public*/ bool TriggerRouteModelXml::loadDeferred() {
    return true;
}

//@Override
/*public*/ bool TriggerRouteModelXml::load(QDomElement shared, QDomElement perNode) /*throw (JmriException)*/ {
    bool result = true;
    QString userName = shared.attribute("name");

    TriggerRouteModel* m = new TriggerRouteModel();
    m->setUserName(userName);

    // store the model
    ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->addAction((StartupModel*)m);
    return result;
}

/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 * @param o       ignored
 */
//@Override
/*public*/ void TriggerRouteModelXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->error("Unexpected call of load(Element, Object)");
}
