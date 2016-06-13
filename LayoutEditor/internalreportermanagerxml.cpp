#include "internalreportermanagerxml.h"
#include "lnreportermanagerxml.h"
#include "rfidreportermanagerxml.h"

InternalReporterManagerXml::InternalReporterManagerXml(QObject *parent) :
    AbstractReporterManagerConfigXML(parent)
{
    log = new Logger("InternalReporterManagerXml");
}

/**
 * Provides load and store functionality for
 * configuring InternalReporterManagers.
 * <P>
 * Uses the store method from the abstract base class, but
 * provides a load method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2010
 * @version $Revision: 17977 $
 */
// /*public*/ class InternalReporterManagerXml extends jmri.managers.configurexml.AbstractReporterManagerConfigXML {

///*public*/ InternalReporterManagerXml() {
//    super();
//}

/*public*/ void InternalReporterManagerXml::setStoreElementClass(QDomElement sensors)
{
 sensors.setAttribute("class","jmri.jmrix.loconet.configurexml.InternalSensorManagerXml");
}

/*public*/ void InternalReporterManagerXml::load(QDomElement element, QObject* o) throw (Exception) {
 log->error("Invalid method called");
}

/*public*/ bool InternalReporterManagerXml::load(QDomElement reporters) throw (Exception){
    // load individual reporters
    return loadReporters(reporters);
}
