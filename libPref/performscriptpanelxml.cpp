#include "performscriptpanelxml.h"
#include "performscriptpanel.h"

PerformScriptPanelXml::PerformScriptPanelXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
 setObjectName("PerformScriptPanelXml");
}
/**
 * Handle XML persistance of PerformScriptModel objects
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 28771 $
 * @see apps.PerformScriptPanel
 */
///*public*/ class PerformScriptPanelXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/ PerformScriptPanelXml() {
//}

/**
 * Arrange for all the model objects to be stored
 *
 * @param o Object to store, of type PerformScriptPanel
 * @return NULL, after updating state so others are stored
 */
/*public*/ QDomElement PerformScriptPanelXml::store(QObject* o)
{
    PerformScriptPanel* p = (PerformScriptPanel*) o;
#if 0 // TODO:
    Component[] l = p.getComponents();
    for (int i = 0; i < l.length; i++) {
        if ((l[i] != NULL) && (l[i].getClass().equals(PerformScriptPanel.Item.class))) {
            PerformScriptPanel.Item m = (PerformScriptPanel.Item) l[i];
            InstanceManager.configureManagerInstance().registerPref(m.getModel());
        }
    }
#endif
    return QDomElement();
}

/**
 * Create object from XML file, but this method should never be invoked.
 *
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
/*public*/ bool PerformScriptPanelXml::load(QDomElement element) throw (Exception)
{
 Logger::error("load(Element) should not have been invoked");
 return false;
}

/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 * @param o       ignored
 */
/*public*/ void PerformScriptPanelXml::load(QDomElement element, QObject* o)throw (Exception)
{
 Logger::error("Unexpected call of load(Element, Object)");
}
