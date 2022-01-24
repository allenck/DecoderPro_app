#include "lnlightmanagerxml.h"

LnLightManagerXml::LnLightManagerXml(QObject *parent) :AbstractLightManagerConfigXML(parent)
{
}

LnLightManagerXml::~LnLightManagerXml()
{
}

/**
 * Provides load and store functionality for
 * configuring LnLightManagers.
 * <P>
 * Uses the store method from the abstract base class, but
 * provides a load method here.
 * <P>
 * @author Dave Duchamp Copyright (c) 2006
 * @version $Revision: 27930 $
 */
///*public*/ class LnLightManagerXml extends jmri.managers.configurexml.AbstractLightManagerConfigXML {

///*public*/ LnLightManagerXml() {
//    super();
//}

/*public*/ void LnLightManagerXml::setStoreElementClass(QDomElement lights) {
    lights.setAttribute("class","jmri.jmrix.loconet.configurexml.LnLightManagerXml");
}

/*public*/ void LnLightManagerXml::load(QDomElement element, QObject* o)  throw (Exception)
{
    Logger::error("Invalid method called");
}

/*public*/ bool LnLightManagerXml::load(QDomElement shared, QDomElement perNode) throw (Exception) {
    // load individual lights
    return loadLights(shared);
}
