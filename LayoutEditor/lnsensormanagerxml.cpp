#include "lnsensormanagerxml.h"

LnSensorManagerXml::LnSensorManagerXml(QObject *parent) :
    AbstractSensorManagerConfigXML(parent)
{
 setObjectName("LnSensorManagerXml");
}
/**
 * Provides load and store functionality for
 * configuring LnSensorManagers.
 * <P>
 * Uses the store method from the abstract base class, but
 * provides a load method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 17977 $
 */
///*public*/ class LnSensorManagerXml extends jmri.managers.configurexml.AbstractSensorManagerConfigXML {

///*public*/ LnSensorManagerXml() {
//    super();
//}

/*public*/ void LnSensorManagerXml::setStoreElementClass(QDomElement sensors) {
    sensors.setAttribute("class","jmri.jmrix.loconet.configurexml.LnSensorManagerXml");
}

/*public*/ void LnSensorManagerXml::load(QDomElement element, QObject* o) throw (JmriConfigureXmlException) {
    log->error("Invalid method called");
}

/*public*/ bool LnSensorManagerXml::load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException) {
    // load individual sensors
    loadSensors(shared);
    return true;
}
