#include "jmriclientsensormanagerxml.h"
#include "loggerfactory.h"
/**
 * Provides load and store functionality for configuring
 * JMRIClientSensorManagers.
 * <P>
 * Uses the store method from the abstract base class, but provides a load
 * method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2008
 */
///*public*/ class JMRIClientSensorManagerXml extends jmri.managers.configurexml.AbstractSensorManagerConfigXML {

/*public*/ JMRIClientSensorManagerXml::JMRIClientSensorManagerXml(QObject* parent) : AbstractSensorManagerConfigXML(parent){
    //super();
}

//@Override
/*public*/ void JMRIClientSensorManagerXml::setStoreElementClass(QDomElement sensors) {
    sensors.setAttribute("class", "jmri.jmrix.jmriclient.configurexml.JMRIClientSensorManagerXml");
}

//@Override
/*public*/ void JMRIClientSensorManagerXml::load(QDomElement element, QObject* o) throw (Exception){
    log->error("Invalid method called");
}

//@Override
/*public*/ bool JMRIClientSensorManagerXml::load(QDomElement shared, QDomElement perNode) /*throw (JmriConfigureXmlException)*/ {
    // load individual sensors
    return loadSensors(shared);
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* JMRIClientSensorManagerXml::log = LoggerFactory::getLogger("JMRIClientSensorManagerXml");

