#include "rfidreportermanagerxml.h"
#include "loggerfactory.h"
/**
 * Provides load and store functionality for configuring RfidReporterManagers.
 * <P>
 * Uses the store method from the abstract base class, but provides a load
 * method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2008
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
// /*public*/ class RfidReporterManagerXml extends jmri.managers.configurexml.AbstractReporterManagerConfigXML {

    /*public*/ RfidReporterManagerXml::RfidReporterManagerXml(QObject *parent) : AbstractReporterManagerConfigXML(parent){
        //super();
    }

    //@Override
    /*public*/ void RfidReporterManagerXml::setStoreElementClass(QDomElement sensors) {
        sensors.setAttribute("class", "jmri.jmrix.rfid.configurexml.RfidReporterManagerXml");
    }

    //@Override
    /*public*/ void RfidReporterManagerXml::load(QDomElement element, QObject* o) throw  (Exception){
        log->error("Invalid method called");
    }

    //@Override
    /*public*/ bool RfidReporterManagerXml::load(QDomElement shared, QDomElement /*perNode*/) {
        // load individual sensors
        return loadReporters(shared);
    }

    /*private*/ /*static*/ /*final*/ Logger* RfidReporterManagerXml::log = LoggerFactory::getLogger("RfidReporterManagerXml");

