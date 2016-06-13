#include "performfilepanelxml.h"
#include "performfilepanel.h"

PerformFilePanelXml::PerformFilePanelXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
 setObjectName("PerformFilePanelXml");
}
/**
 * Handle XML persistance of PerformFileModel objects
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 28771 $
 * @see apps.PerformFilePanel
 */
///*public*/ class PerformFilePanelXml extends jmri.configurexml.AbstractXmlAdapter {

//    /*public*/ PerformFilePanelXml() {
//    }

/**
 * Arrange for all the model objects to be stored
 *
 * @param o Object to store, of type PerformFilePanel
 * @return null, after updating state so others are stored
 */
/*public*/ QDomElement PerformFilePanelXml::store(QObject* o)
{
    PerformFilePanel* p = (PerformFilePanel*) o;
#if 0 // TODO:
    Component[] l = p.getComponents();
    for (int i = 0; i < l.length; i++) {
        if ((l[i] != null) && (l[i].getClass().equals(PerformFilePanel.Item.class))) {
            PerformFilePanel.Item m = (PerformFilePanel.Item) l[i];
            InstanceManager.configureManagerInstance().registerPref(m.getModel());
        }
    }
#endif
    return QDomElement();
}

/**
 * Create object from XML file
 *
 * @param e Top level QDomElement to unpack.
 * @return true if successful
 */
/*public*/ bool PerformFilePanelXml::load(QDomElement e) throw (Exception)
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
/*public*/ void PerformFilePanelXml::load(QDomElement element, QObject* o) throw (Exception) {
    Logger::error("Unexpected call of load(Element, Object)");
}
