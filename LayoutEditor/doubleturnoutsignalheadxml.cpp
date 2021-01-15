#include "doubleturnoutsignalheadxml.h"
#include "instancemanager.h"
#include "abstractsignalheadmanager.h"
#include "abstractturnoutmanager.h"
#include "doubleturnoutsignalhead.h"

//DoubleTurnoutSignalHeadXml::DoubleTurnoutSignalHeadXml(QQObject* *parent) :
//    AbstractNamedBeanManagerConfigXML(parent)
//{
//}
/**
 * Handle XML configuration for DoubleTurnoutSignalHead* objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008
 * @version $Revision: 17977 $
 */
///*public*/ class DoubleTurnoutSignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

/*public*/ DoubleTurnoutSignalHeadXml::DoubleTurnoutSignalHeadXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("DoubleTurnoutSignalHeadXml");
}

/**
 * Default implementation for storing the contents of a
 * DoubleTurnoutSignalHead*
 * @param o QObject* to store, of type TripleTurnoutSignalHead
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement DoubleTurnoutSignalHeadXml::store(QObject* o) {
    DoubleTurnoutSignalHead* p = (DoubleTurnoutSignalHead*)o;

    QDomElement element = doc.createElement("signalhead");
    element.setAttribute("class", "jmri.implementation.configurexml.DoubleTurnoutSignalHeadXml");

    // include contents
    element.setAttribute("systemName", p->getSystemName());
    QDomElement e1;
    element.appendChild(e1=doc.createElement("systemName"));
    e1.appendChild(doc.createTextNode(p->getSystemName()));

    storeCommon(p, element);

    element.appendChild(addTurnoutElement(p->getGreen(), "green"));
    element.appendChild(addTurnoutElement(p->getRed(), "red"));

    return element;
}

QDomElement DoubleTurnoutSignalHeadXml::addTurnoutElement(NamedBeanHandle<Turnout*>* to, QString which) {
    QDomElement el = doc.createElement("turnoutname");
    el.setAttribute("defines", which);
    el.appendChild(doc.createTextNode(to->getName()));
    return el;
}
QDomElement DoubleTurnoutSignalHeadXml::addTurnoutElement(Turnout* to) {
    QString user = to->getUserName();
    QString sys = to->getSystemName();

    QDomElement el = doc.createElement("turnout");
    el.setAttribute("systemName", sys);
    if (user!=NULL) el.setAttribute("userName", user);

    return el;
}

/**
 * Create a DoubleTurnoutSignalHead*
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool DoubleTurnoutSignalHeadXml::load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException)
{
 QDomNodeList l = shared.elementsByTagName("turnoutname");
 if (l.size() == 0) l = shared.elementsByTagName("turnout");
 NamedBeanHandle<Turnout*>* green = loadTurnout(l.at(0).toElement());
 NamedBeanHandle<Turnout*>* red = loadTurnout(l.at(1).toElement());
 // put it together
 QString sys = getSystemName(shared);
 QString uname = getUserName(shared);
 SignalHead* h;
 if (uname == "")
     h = (SignalHead*)new DoubleTurnoutSignalHead(sys, green, red);
 else
     h = (SignalHead*)new DoubleTurnoutSignalHead(sys, uname, green, red);

 loadCommon(h, shared);

 static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->Register(h);
 return true;
}

/**
 * Needs to handle two types of element:
 *    turnoutname is new form
 *    turnout is old form
 */
NamedBeanHandle<Turnout*>* DoubleTurnoutSignalHeadXml::loadTurnout(/*QObject o*/QDomElement e)
{
    //QDomElement e = (QDomElement)o;

 if (e.tagName()==("turnout"))
 {
  QString name = e.attribute("systemName");
  Turnout*t;
  if (e.attribute("userName")!=NULL &&
          e.attribute("userName")!=(""))
  {
   name = e.attribute("userName");
   t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(name);
  }
  else
  {
   t = (Turnout*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getBySystemName(name);
  }
  return ((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, t);
 }
 else
 {
  QString name = e.text();
  Turnout* t = ((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->provideTurnout(name);
  return ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, t);
 }
}

/*public*/ void DoubleTurnoutSignalHeadXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception)
{
 log->error("Invalid method called");
}
