#include "se8csignalheadxml.h"
#include "se8csignalhead.h"
#include "turnout.h"
#include "instancemanager.h"
#include "signalheadmanager.h"

SE8cSignalHeadXml::SE8cSignalHeadXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("SE8cSignalHeadXml");
}
/**
 * Handle XML configuration for SE8cSignalHead objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @version $Revision: 17977 $
 */
// /*public*/ class SE8cSignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

// /*public*/ SE8cSignalHeadXml() {}

/**
 * Default implementation for storing the contents of a
 * SE8cSignalHead
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement SE8cSignalHeadXml::store(QObject* o) {
    SE8cSignalHead* p = (SE8cSignalHead*)o;

    QDomElement element = doc.createElement("signalhead");
    element.setAttribute("class", "jmri.jmrix.loconet.configurexml.SE8cSignalHeadXml");
    //element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->getSystemName())));
    QDomElement systemname = doc.createElement("systemName");
    systemname.appendChild(doc.createTextNode(p->getSystemName()));
    element.appendChild(systemname);

    // include contents
    element.setAttribute("systemName", p->getSystemName());

    storeCommon(p, element);

    element.appendChild(addTurnoutElement(p->getLow(), "low"));
    element.appendChild(addTurnoutElement(p->getHigh(), "high"));

    return element;
}

QDomElement SE8cSignalHeadXml::addTurnoutElement(NamedBeanHandle<Turnout*>* to, QString which) {
    QDomElement el = doc.createElement("turnoutname");
    el.setAttribute("defines", which);
    el.appendChild(doc.createTextNode(to->getName()));
    return el;
}
QDomElement SE8cSignalHeadXml::addTurnoutElement(Turnout* to) {
    QString user = to->getUserName();
    QString sys = to->getSystemName();

    QDomElement el = doc.createElement("turnout");
    el.setAttribute("systemName", sys);
    if (user!="") el.setAttribute("userName", user);

    return el;
}

/**
 * Create a SE8cSignalHead
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool SE8cSignalHeadXml::load(QDomElement element) throw (Exception){
    QDomNodeList l = element.elementsByTagName("turnoutname");
    if (l.size() == 0) l = element.elementsByTagName("turnout");  // older form
    NamedBeanHandle<Turnout*>* low = loadTurnout(l.at(0).toElement());
    NamedBeanHandle<Turnout*>* high = loadTurnout(l.at(1).toElement());
    // put it together
    QString sys = getSystemName(element);
    QString uname = getUserName(element);
    SignalHead* h;
    if (uname == "")
        h = (SignalHead*)new SE8cSignalHead(sys, low, high);
    else
        h = (SignalHead*)new SE8cSignalHead(sys, low, high, uname);

    loadCommon(h, element);

    static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->Register(h);
    return true;
}

/**
 * Needs to handle two types of element:
 *    turnoutname is new form
 *    turnout is old form
 */
NamedBeanHandle<Turnout*>* SE8cSignalHeadXml::loadTurnout(QDomElement e)
{
    //QDomElement e = (QDomElement)o;

 if (e.tagName()==("turnout"))
 {
  QString name = e.attribute("systemName");
  Turnout* t;
  if (e.attribute("userName")!="" &&
                e.attribute("userName")!=(""))
  {
   name = e.attribute("userName");
   t = InstanceManager::turnoutManagerInstance()->getTurnout(name);
  }
  else
  {
   t = (Turnout*)InstanceManager::turnoutManagerInstance()->getBySystemName(name);
  }
        return ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, t);
    } else {
        QString name = e.text();
        Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(name);
        return ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, t);
    }
}

/*public*/ void SE8cSignalHeadXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}
