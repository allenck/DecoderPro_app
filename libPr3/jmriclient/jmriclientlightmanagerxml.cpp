#include "jmriclientlightmanagerxml.h"
#include "loggerfactory.h"

/**
 * Provides load and store functionality for configuring
 * JMRIClientLightManagers.
 * <P>
 * Uses the store method from the abstract base class, but provides a load
 * method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2008
 */
///*public*/ class JMRIClientLightManagerXml extends jmri.managers.configurexml.AbstractLightManagerConfigXML {

/*public*/ JMRIClientLightManagerXml::JMRIClientLightManagerXml(QObject *parent) : AbstractLightManagerConfigXML(parent){
    //super();
}

//@Override
/*public*/ void JMRIClientLightManagerXml::setStoreElementClass(QDomElement lights) {
    lights.setAttribute("class", "jmri.jmrix.jmriclient.configurexml.JMRIClientLightManagerXml");
}

//@Override
/*public*/ void JMRIClientLightManagerXml::load(QDomElement element, QObject* o) throw (Exception){
    log->error("Invalid method called");
}

//@Override
/*public*/ bool JMRIClientLightManagerXml::load(QDomElement shared, QDomElement perNode) {
    // load individual lights
    return loadLights(shared);
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* JMRIClientLightManagerXml::log = LoggerFactory::getLogger("JMRIClientLightManagerXml");
