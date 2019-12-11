#include "turnoutsignalmastxml.h"
#include "turnoutsignalmast.h"
#include "defaultsignalmastmanager.h"
#include "instancemanager.h"
#include "signalappearancemap.h"

TurnoutSignalMastXml::TurnoutSignalMastXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("TurnoutSignalMastXml");
 setObjectName("TurnoutSignalMastXml");
}
/**
 * Handle XML configuration for a DefaultSignalMastManager objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 18102 $
 */
// /*public*/ class TurnoutSignalMastXml
//            extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

// /*public*/ TurnoutSignalMastXml() {}

/**
 * Default implementation for storing the contents of a
 * DefaultSignalMastManager
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return Element containing the complete info
 */
/*public*/ QDomElement TurnoutSignalMastXml::store(QObject* o)
{
 TurnoutSignalMast* p = (TurnoutSignalMast*)o;
 QDomElement e = doc.createElement("turnoutsignalmast");
 e.setAttribute("class", "jmri.implementation.configurexml.TurnoutSignalMastXml");
 QDomElement sysName = doc.createElement("systemName");
 sysName.appendChild(doc.createTextNode(p->getSystemName()));
 //e.setAttribute("systemName",p->getSystemName());
 e.appendChild(sysName);

 storeCommon(p, e);
 SignalAppearanceMap* appMap = p->getAppearanceMap();
 if(appMap!=NULL)
 {
  QStringListIterator aspects(appMap->getAspects());
  while(aspects.hasNext())
  {
   QString key = aspects.next();
   QDomElement el = doc.createElement("aspect");
   el.setAttribute("defines", key);
   QDomElement turnout = doc.createElement("turnout");
   turnout.appendChild(doc.createTextNode(p->getTurnoutName(key)));
   el.appendChild(turnout);

   if(p->getTurnoutState(key)==Turnout::CLOSED)
   {
    QDomElement turnoutstate = doc.createElement("turnoutstate");
    turnoutstate.appendChild(doc.createTextNode("closed"));
    el.appendChild(turnoutstate);
   }
   else
   {
    QDomElement turnoutstate = doc.createElement("turnoutstate");
    turnoutstate.appendChild(doc.createTextNode("thrown"));
    el.appendChild(turnoutstate);
   }
   e.appendChild(el);
  }
 }
  QStringList* disabledAspects = p->getDisabledAspects();
 if(disabledAspects!=NULL)
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
 if(p->resetPreviousStates())
 {
  e.appendChild(doc.createElement("resetPreviousStates"));
  e.appendChild(doc.createTextNode("yes"));
 }
 return e;
}

/**
 * Create a DefaultSignalMastManager
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool TurnoutSignalMastXml::load(QDomElement shared, QDomElement /*perNode*/)
{
 QString sys = getSystemName(shared);
 TurnoutSignalMast* m = new TurnoutSignalMast(sys);

 if (getUserName(shared) != NULL)
  m->setUserName(getUserName(shared));

 loadCommon(m, shared);

 if (shared.firstChildElement("unlit") != QDomElement())
 {
  QDomElement unlit = shared.firstChildElement("unlit");
  if (unlit.attribute("allowed") != "")
  {
   if (unlit.attribute("allowed") == ("no"))
   {
    m->setAllowUnLit(false);
   }
   else
   {
    m->setAllowUnLit(true);
    QString turnout = unlit.firstChildElement("turnout").text();
    QString turnoutState = unlit.firstChildElement("turnoutstate").text();
    int turnState = Turnout::THROWN;
    if (turnoutState == ("closed")) {
        turnState = Turnout::CLOSED;
    }
       m->setUnLitTurnout(turnout, turnState);
   }
  }
 }

 QDomNodeList list = shared.elementsByTagName("aspect");
 for (int i = 0; i < list.size(); i++)
 {
  QDomElement e = list.at(i).toElement();
  QString aspect = e.attribute("defines");
  QString turnout = e.firstChildElement("turnout").text();
  QString turnoutState = e.firstChildElement("turnoutstate").text();
  int turnState = Turnout::THROWN;
  if(turnoutState==("closed"))
   turnState = Turnout::CLOSED;
  m->setTurnout(aspect, turnout, turnState);
 }
 QDomElement e = shared.firstChildElement("disabledAspects");
 if(!e.isNull())
 {
  list = e.elementsByTagName("disabledAspect");
  for(int i=0; i <list.count(); i++)
  {
   QDomElement aspect = list.at(i).toElement();
   m->setAspectDisabled(aspect.text());
  }
 }
 if (( !shared.firstChildElement("resetPreviousStates").isNull()) &&
        shared.firstChildElement("resetPreviousStates").text()==("yes") )
 {
  m->resetPreviousStates(true);
 }

 static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->Register(m);

 return true;
}

/*public*/ void TurnoutSignalMastXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TurnoutSignalMastXml.class.getName());
//}
