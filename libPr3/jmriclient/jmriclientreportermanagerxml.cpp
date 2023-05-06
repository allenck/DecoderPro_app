#include "jmriclientreportermanagerxml.h"
#include "loggerfactory.h"

/**
 * Provides load and store functionality for configuring
 * JMRIClientReporterManagers.
 * <P>
 * Uses the store method from the abstract base class, but provides a load
 * method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2008
 * @author Paul Bender Copyright: Copyright (c) 2015
 */
///*public*/ class JMRIClientReporterManagerXml extends jmri.managers.configurexml.AbstractReporterManagerConfigXML {

/*public*/ JMRIClientReporterManagerXml::JMRIClientReporterManagerXml(QObject *parent) : AbstractReporterManagerConfigXML(parent){
    //super();
}

//@Override
/*public*/ void JMRIClientReporterManagerXml::setStoreElementClass(QDomElement reporters) {
    reporters.setAttribute("class", "jmri.jmrix.jmriclient.configurexml.JMRIClientReporterManagerXml");
}

//@Override
/*public*/ void JMRIClientReporterManagerXml::load(QDomElement element, QObject* o) /*throw (JmriConfigureXmlException)*/ {
    log->error("Invalid method called");
}

//@Override
/*public*/ bool JMRIClientReporterManagerXml::load(QDomElement shared, QDomElement perNode) {
    // load individual reporters
    return loadReporters(shared);
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* JMRIClientReporterManagerXml::log = LoggerFactory::getLogger("JMRIClientReporterManagerXml");
