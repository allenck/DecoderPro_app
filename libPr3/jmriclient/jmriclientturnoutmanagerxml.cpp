#include "jmriclientturnoutmanagerxml.h"
#include "loggerfactory.h"
/**
 * Provides load and store functionality for configuring
 * JMRIClientTurnoutManagers.
 * <P>
 * Uses the store method from the abstract base class, but provides a load
 * method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2008
 */
//public class JMRIClientTurnoutManagerXml extends jmri.managers.configurexml.AbstractTurnoutManagerConfigXML {

/*public*/ JMRIClientTurnoutManagerXml::JMRIClientTurnoutManagerXml(QObject* parent)
 :AbstractTurnoutManagerConfigXML(parent)
{
    //super();
}

//@Override
/*public*/ void JMRIClientTurnoutManagerXml::setStoreElementClass(QDomElement turnouts) {
    turnouts.setAttribute("class", "jmri.jmrix.jmriclient.configurexml.JMRIClientTurnoutManagerXml");
}

//@Override
/*public*/ void JMRIClientTurnoutManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}

//@Override
/*public*/ bool JMRIClientTurnoutManagerXml::load(QDomElement shared, QDomElement perNode) throw (Exception) {
    // load individual turnouts
    return loadTurnouts(shared, perNode);
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* JMRIClientTurnoutManagerXml::log = LoggerFactory::getLogger("JMRIClientTurnoutManagerXml");
