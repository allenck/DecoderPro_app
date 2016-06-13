#include "internalturnoutmanagerxml.h"

InternalTurnoutManagerXml::InternalTurnoutManagerXml(QObject *parent) :
    AbstractTurnoutManagerConfigXML(parent)
{
 log = new Logger("InternalTurnoutManagerXml");
 setObjectName("InternalTurnoutManagerXml");
}
/**
 * Provides load and store functionality for
 * configuring InternalTurnoutManagers.
 * <P>
 * Uses the store method from the abstract base class, but
 * provides a load method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2006
 * @version $Revision: 17977 $
 */
// /*public*/ class InternalTurnoutManagerXml extends jmri.managers.configurexml.AbstractTurnoutManagerConfigXML {

///*public*/ InternalTurnoutManagerXml() {
//    super();
//}

/*public*/ void InternalTurnoutManagerXml::setStoreElementClass(QDomElement turnouts)
{
 turnouts.setAttribute("class","jmri.managers.configurexml.InternalTurnoutManagerXml");
}

/*public*/ void InternalTurnoutManagerXml::load(QDomElement element, QObject* o) throw (Exception){
    log->error("Invalid method called");
}

/*public*/ bool InternalTurnoutManagerXml::load(QDomElement turnouts) throw (Exception){
    // load individual turnouts
    return loadTurnouts(turnouts);
}
