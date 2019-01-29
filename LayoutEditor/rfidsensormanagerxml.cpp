#include "rfid/rfidsensormanagerxml.h"

RfidSensorManagerXml::RfidSensorManagerXml(QObject *parent) :
    AbstractSensorManagerConfigXML(parent)
{
 log = new Logger("RfidSensorManagerXml");
}
/**
 * Provides load and store functionality for
 * configuring RfidSensorManagers.
 * <P>
 * Uses the store method from the abstract base class, but
 * provides a load method here.
 *
 * @author      Bob Jacobsen Copyright: Copyright (c) 2003, 2006, 2007, 2008
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @since       2.11.4
 */
// /*public*/ class RfidSensorManagerXml extends jmri.managers.configurexml.AbstractSensorManagerConfigXML {

///*public*/ RfidSensorManagerXml() {
//    super();
//}

/*public*/ void RfidSensorManagerXml::setStoreElementClass(QDomElement sensors) {
    sensors.setAttribute("class",/*this.getClass().getName()*/"jmri.jmrix.rfid.configurexml.RfidSensorManagerXml");
}

/*public*/ void RfidSensorManagerXml::load(QDomElement /*element*/, QObject* /*o*/)  throw (Exception)
{
    log->error("Invalid method called");
}

/*public*/ bool RfidSensorManagerXml::load(QDomElement sensors) throw (JmriConfigureXmlException)
{
    // load individual sensors
    return loadSensors(sensors);
}
