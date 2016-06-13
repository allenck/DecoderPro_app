#include "rfidreportermanagerxml.h"

RfidReporterManagerXml::RfidReporterManagerXml(QObject *parent) :
    AbstractReporterManagerConfigXML(parent)
{
    log = new Logger("RfidReporterManagerXml");
}
/**
 * Provides load and store functionality for
 * configuring RfidReporterManagers.
 * <P>
 * Uses the store method from the abstract base class, but
 * provides a load method here.
 *
 * @author      Bob Jacobsen Copyright: Copyright (c) 2008
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @since       2.11.4
 */
// /*public*/ class RfidReporterManagerXml extends jmri.managers.configurexml.AbstractReporterManagerConfigXML {

///*public*/ RfidReporterManagerXml() {
//    super();
//}

/*public*/ void RfidReporterManagerXml::setStoreElementClass(QDomElement sensors) {
    sensors.setAttribute("class","jmri.jmrix.loconet.configurexml.RfidReporterManagerXml");
}

/*public*/ void RfidReporterManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->error("Invalid method called");
}

/*public*/ bool RfidReporterManagerXml::load(QDomElement reporters)throw (Exception) {
    // load individual sensors
    return loadReporters(reporters);
}
