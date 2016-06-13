#include "lnturnoutmanagerxml.h"

LnTurnoutManagerXml::LnTurnoutManagerXml(QObject *parent) :
    AbstractTurnoutManagerConfigXML(parent)
{
 log = new Logger("LnTurnoutManagerXml");
 setObjectName("LnTurnoutManagerXml");
}
/**
 * Provides load and store functionality for
 * configuring LnTurnoutManagers.
 * <P>
 * Uses the store method from the abstract base class, but
 * provides a load method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 17977 $
 */
///*public*/ class LnTurnoutManagerXml extends jmri.managers.configurexml.AbstractTurnoutManagerConfigXML {

///*public*/ LnTurnoutManagerXml() {
//    super();
//}

/*public*/ void LnTurnoutManagerXml::setStoreElementClass(QDomElement turnouts) {
    turnouts.setAttribute("class","jmri.jmrix.loconet.configurexml.LnTurnoutManagerXml");
}

/*public*/ void LnTurnoutManagerXml::load(QDomElement element, QObject* o) throw (Exception){
    log->error("Invalid method called");
}

/*public*/ bool LnTurnoutManagerXml::load(QDomElement turnouts) throw (Exception){

    // load individual turnouts
    return loadTurnouts(turnouts);
}
