#include "dccsignalmastxml.h"
#include "dccsignalmast.h"
#include "instancemanager.h"
#include "signalmastmanager.h"

DccSignalMastXml::DccSignalMastXml(QObject *parent) :
  AbstractNamedBeanManagerConfigXML(parent)
{
}
/**
 * Handle XML configuration for a DefaultSignalMastManager objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 18102 $
 */
///*public*/  class DccSignalMastXml
//        extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

///*public*/  DccSignalMastXml() {
//}

/**
 * Default implementation for storing the contents of a
 * DefaultSignalMastManager
 *
 * @param o Object to store, of type TripleDccSignalHead
 * @return QDomElement containing the complete info
 */
/*public*/  QDomElement DccSignalMastXml::store(QObject* o)
{
 DccSignalMast* p = (DccSignalMast*) o;
 QDomElement e = doc.createElement("dccsignalmast");
 e.setAttribute("class", /*this.getClass().getName()*/"jmri.implementation.configurexml.DccSignalMastXml");
 e.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->getSystemName())));

 storeCommon(p, e);
 QDomElement unlit = doc.createElement("unlit");
 if (p->allowUnLit()) {
     unlit.setAttribute("allowed", "yes");
     unlit.appendChild(doc.createElement("aspect").appendChild(doc.createTextNode(QString::number(p->getUnlitId()))));
 } else {
     unlit.setAttribute("allowed", "no");
 }
 e.appendChild(unlit);
 SignalAppearanceMap* appMap = p->getAppearanceMap();
 if (appMap != NULL) {
  QStringListIterator aspects(appMap->getAspects());
     while (aspects.hasNext()) {
         QString key = aspects.next();
         QDomElement el = doc.createElement("aspect");
         el.setAttribute("defines", key);
         el.appendChild(doc.createElement("number").appendChild(doc.createTextNode(QString::number(p->getOutputForAppearance(key)))));
         e.appendChild(el);
     }
 }
 QStringList* disabledAspects = p->getDisabledAspects();
 if (disabledAspects != NULL)
 {
  QDomElement el = doc.createElement("disabledAspects");
  foreach (QString aspect, *disabledAspects)
  {
   QDomElement ele = doc.createElement("disabledAspect");
   ele.appendChild(doc.createTextNode(aspect));
   el.appendChild(ele);
  }
  if (disabledAspects->size() != 0)
  {
   e.appendChild(el);
  }
 }
 return e;
}

/**
 * Create a DefaultSignalMastManager
 *
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
/*public*/  bool DccSignalMastXml::load(QDomElement shared, QDomElement perNode)  throw(JmriConfigureXmlException)
{
 DccSignalMast* m;
 QString sys = getSystemName(shared);
 m = new DccSignalMast(sys);

 if (getUserName(shared) != NULL) {
     m->setUserName(getUserName(shared));
 }

 return loadCommonDCCMast(m, shared);
}

/*protected*/ bool DccSignalMastXml::loadCommonDCCMast(DccSignalMast* m, QDomElement element)
{
 loadCommon(m, element);
 if (!element.firstChildElement("unlit").isNull()) {
     QDomElement unlit = element.firstChildElement("unlit");
     if (!unlit.attribute("allowed").isNull()) {
         if (unlit.attribute("allowed")==("no")) {
             m->setAllowUnLit(false);
         } else {
             m->setAllowUnLit(true);
             m->setUnlitId(unlit.firstChildElement("aspect").text().toInt());
         }
     }
 }
 QDomNodeList list = element.elementsByTagName("aspect");
 for (int i = 0; i < list.size(); i++) {
     QDomElement e = list.at(i).toElement();
     QString aspect = e.attribute("defines");
     int number = -1;
     bool bok;
         QString value = e.firstChildElement("number").text();
         number = value.toInt(&bok);

         if(!bok)
          Logger::error("failed to convert DCC number");
     m->setOutputForAppearance(aspect, number);
 }
 QDomElement e = element.firstChildElement("disabledAspects");
 if (!e.isNull())
 {
     list = e.elementsByTagName("disabledAspect");
     //for (QDomElement aspect : list) {
     for(int i=0; i < list.size(); i++)
     {
      QDomElement aspect = list.at(i).toElement();
         m->setAspectDisabled(aspect.text());
     }
 }

 static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->Register(m);
 return true;

}

/*public*/  void DccSignalMastXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception)
{
    Logger::error("Invalid method called");
}
