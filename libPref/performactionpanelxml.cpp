#include "performactionpanelxml.h"
#include "performactionpanel.h"
#include "instancemanager.h"
#include <QBoxLayout>

PerformActionPanelXml::PerformActionPanelXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
}
/**
 * Handle XML persistance of PerformActionPanel objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 28771 $
 * @see apps.PerformActionPanel
 */
///*public*/ class PerformActionPanelXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/ PerformActionPanelXml() {
//}

/**
 * Arrange for all the model objects to be stored
 *
 * @param o Object to store, of type PerformActionPanel
 * @return NULL, after updating state so others are stored
 */
/*public*/ QDomElement PerformActionPanelXml::store(QObject* o)
{
 PerformActionPanel* p = (PerformActionPanel*) o;
 //Component[] l = p->getComponents();
 QObjectList l = p->layout()->children();
 for (int i = 0; i < l.length(); i++)
 {
#if 0 // TODO:
  if ((l[i] != NULL) && (l[i]->metaObject()->className()==s("PerformActionPanel")))
  {
   PerformActionPanel::Item m = (PerformActionPanel::Item) l[i];
   InstanceManager.configureManagerInstance().registerPref(m.updatedModel());
  }
#endif
 }
 return QDomElement();
}

/**
 * Create object from XML file
 *
 * @param e Top level QDomElement to unpack.
 * @return true if successful
 */
/*public*/ bool PerformActionPanelXml::load(QDomElement e)  throw (Exception)
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
/*public*/ void PerformActionPanelXml::load(QDomElement element, QObject* o) throw (Exception)
{
 Logger::error("Unexpected call of load(Element, Object)");
}
