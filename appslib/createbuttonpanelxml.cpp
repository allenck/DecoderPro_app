#include "createbuttonpanelxml.h"
#include "createbuttonpanel.h"
#include "instancemanager.h"
#include "abstractactionmodel.h"

CreateButtonPanelXml::CreateButtonPanelXml(QObject* parent) :
    AbstractXmlAdapter(parent)
{
 log= new Logger("CreateButtonPanelXml");
}
/**
 * Handle XML persistance of CreateButtonPanel objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 27930 $
 * @see apps.CreateButtonPanel
 */
// /*public*/ class CreateButtonPanelXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/ CreateButtonPanelXml() {
//}

/**
 * Arrange for all the model objects to be stored
 * @param o QObject* to store, of type CreateButtonPanel
 * @return NULL, after updating state so others are stored
 */
/*public*/ QDomElement CreateButtonPanelXml::store(QObject* o)
{
 CreateButtonPanel* p = (CreateButtonPanel*) o;
 QObjectList l = p->children();
 for (int i = 0; i<l.length(); i++)
 {
  if ( (l[i]!= NULL) && (l[i]->metaObject()->className() ==  ("CreateButtonPanel::Item")))
  {
   /*CreateButtonPanel::*/Item* m = (/*CreateButtonPanel::*/Item*) l[i];
   InstanceManager::configureManagerInstance()->registerPref((AbstractActionModel*)m->updatedModel());
  }
 }
 return QDomElement();
}

/**
 * Create object from XML file
 * @param e Top level QDomElement to unpack.
  */
/*public*/ bool CreateButtonPanelXml::load(QDomElement /*e*/)  throw (Exception){
    log->error("load(Element) should not have been invoked");
    return false;
}

/**
 * Update static data from XML file
 * @param element Top level QDomElement to unpack.
 * @param o  ignored
 */
/*public*/ void CreateButtonPanelXml::load(QDomElement /*element*/, QObject* /*o*/)throw (Exception) {
    log->error("Unexpected call of load(Element, Object)");
}
