#include "internallightmanagerxml.h"

InternalLightManagerXml::InternalLightManagerXml(QObject *parent) :
  AbstractLightManagerConfigXML(parent)
{
 setObjectName("InternalLightManagerXml");
}
/**
 * Provides load and store functionality for configuring InternalLightManagers.
 * <P>
 * Uses the store method from the abstract base class, but provides a load
 * method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 28746 $
 */
///*public*/ class InternalLightManagerXml extends jmri.managers.configurexml.AbstractLightManagerConfigXML {

///*public*/ InternalLightManagerXml() {
//    super();
//}

/*public*/ void InternalLightManagerXml::setStoreElementClass(QDomElement lights) {
 lights.setAttribute("class", "jmri.managers.configurexml.InternalLightManagerXml");
}

/*public*/ bool InternalLightManagerXml::load(QDomElement shared, QDomElement perNode)throw (Exception) {
    // load individual lights
    loadLights(shared);
    return true;
}
