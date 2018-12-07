#include "rfidsensormanagerxml.h"
#include "loggerfactory.h"

/**
 * Provides load and store functionality for configuring RfidSensorManagers.
 * <P>
 * Uses the store method from the abstract base class, but provides a load
 * method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2006, 2007, 2008
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
// /*public*/ class RfidSensorManagerXml extends jmri.managers.configurexml.AbstractSensorManagerConfigXML {

    /*public*/ RfidSensorManagerXml::RfidSensorManagerXml(QObject* parent) : AbstractSensorManagerConfigXML(parent){
        //super();
    }

    //@Override
    /*public*/ void RfidSensorManagerXml::setStoreElementClass(QDomElement sensors) {
        sensors.setAttribute("class", "jmri.jmrix.rfid.configurexml.RfidSensorManagerXml");
    }

    //@Override
    /*public*/ void RfidSensorManagerXml::load(QDomElement /*element*/, QObject* o) throw (Exception){
        log->error("Invalid method called");
    }

    //@Override
    /*public*/ bool RfidSensorManagerXml::load(QDomElement shared, QDomElement /*perNode*/) throw (JmriConfigureXmlException) {
        // load individual sensors
        return loadSensors(shared);
    }

    /*private*/ /*static*/ /*final*/ Logger* RfidSensorManagerXml::log = LoggerFactory::getLogger("RfidSensorManagerXml");

