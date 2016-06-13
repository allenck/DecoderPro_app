#include "signalheadsignalmastxml.h"
#include "signalheadsignalmast.h"
#include "instancemanager.h"
#include "signalmastmanager.h"
#include "defaultsignalmastmanager.h"

SignalHeadSignalMastXml::SignalHeadSignalMastXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("SignalHeadSignalMastXml");
}
/**
 * Handle XML configuration for a DefaultSignalMastManager objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 18102 $
 */
///*public*/ class SignalHeadSignalMastXml
//            extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

// /*public*/ SignalHeadSignalMastXml() {}

/**
 * Default implementation for storing the contents of a
 * DefaultSignalMastManager
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return Element containing the complete info
 */
/*public*/ QDomElement SignalHeadSignalMastXml::store(QObject* o)
{
 SignalHeadSignalMast* p = (SignalHeadSignalMast*)o;
 QDomElement e = doc.createElement("signalmast");
 e.setAttribute("class", "jmri.implementation.configurexml.SignalHeadSignalMastXml");
 e.setAttribute("systemName", p->getSystemName());
 QDomElement e1;
 e.appendChild(e1=doc.createElement("systemName"));
 e1.appendChild(doc.createTextNode(p->getSystemName()));
 storeCommon(p, e);

 QStringList* disabledAspects = p->getDisabledAspects();
 if(!disabledAspects->isEmpty())
 {
  QDomElement el = doc.createElement("disabledAspects");
  foreach(QString aspect, *disabledAspects)
  {
   QDomElement ele = doc.createElement("disabledAspect");
   ele.appendChild(doc.createTextNode(aspect));
   el.appendChild(ele);
  }
  if(disabledAspects->size()!=0)
   e.appendChild(el);
 }
 return e;
}

/**
 * Create a DefaultSignalMastManager
 * @param element Top level Element to unpack.
 * @return true if successful
 */
/*public*/ bool SignalHeadSignalMastXml::load(QDomElement element) throw (Exception)
{
 SignalMast* m;
 QString sys = getSystemName(element);
 try
 {
  m = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->provideSignalMast(sys);
 }
 catch (Exception e)
 {
  log->error("An error occured while trying to create the signal '"+sys+"' " + e.getMessage());
  return false;
 }
 if (!getUserName(element).isNull())
  m->setUserName(getUserName(element));

 loadCommon(m, element);

 QDomElement e = element.firstChildElement("disabledAspects");
 if(!e.isNull())
 {
   //@SuppressWarnings("unchecked")
  QDomNodeList list = e.elementsByTagName("disabledAspect");
  for(int i=0; i < list.count(); i++)
  {
   QDomElement aspect = list.at(i).toElement();
   ((SignalHeadSignalMast*)m)->setAspectDisabled(aspect.text());
  }
 }
 return true;
}

/*public*/ void SignalHeadSignalMastXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}
