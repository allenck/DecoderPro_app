#include "tripleturnoutsignalheadxml.h"
#include "tripleturnoutsignalhead.h"
#include "instancemanager.h"
#include "signalheadmanager.h"

TripleTurnoutSignalHeadXml::TripleTurnoutSignalHeadXml(QObject *parent) :
    DoubleTurnoutSignalHeadXml(parent)
{
}
/**
 * Handle XML configuration for TripleTurnoutSignalHead objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2008
 * @version $Revision: 17977 $
 */
// /*public*/ class TripleTurnoutSignalHeadXml extends DoubleTurnoutSignalHeadXml {

// /*public*/ TripleTurnoutSignalHeadXml() {}

/**
 * Default implementation for storing the contents of a
 * TripleTurnoutSignalHead
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement TripleTurnoutSignalHeadXml::store(QObject* o) {
    TripleTurnoutSignalHead* p = (TripleTurnoutSignalHead*)o;

    QDomElement element = doc.createElement("signalhead");
    //element.setAttribute("class", this->getClass().getName());
    element.setAttribute("class", "jmri.implementation.configurexml.TripleTurnoutSignalHead");

    // include contents
    element.setAttribute("systemName", p->getSystemName());
    element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->getSystemName())));

    storeCommon(p, element);

    element.appendChild(addTurnoutElement(p->getGreen(), "green"));
    element.appendChild(addTurnoutElement(p->getYellow(), "yellow"));
    element.appendChild(addTurnoutElement(p->getRed(), "red"));

    return element;
}

/**
 * Create a TripleTurnoutSignalHead
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool TripleTurnoutSignalHeadXml::load(QDomElement element) throw (Exception)
{
    QDomNodeList l = element.elementsByTagName("turnoutname");
    if (l.size() == 0) l = element.elementsByTagName("turnout");
    NamedBeanHandle<Turnout*>* green = loadTurnout(l.at(0).toElement());
    NamedBeanHandle<Turnout*>* yellow = loadTurnout(l.at(1).toElement());
    NamedBeanHandle<Turnout*>* red = loadTurnout(l.at(2).toElement());

    // put it together
    QString sys = getSystemName(element);
    QString uname = getUserName(element);
    SignalHead* h;
    if (uname == NULL)
        h = (SignalHead*)new TripleTurnoutSignalHead(sys, green, yellow, red);
    else
        h = (SignalHead*)new TripleTurnoutSignalHead(sys, uname, green, yellow, red);

    loadCommon(h, element);

    InstanceManager::signalHeadManagerInstance()->Register(h);
    return true;
}

/*public*/ void TripleTurnoutSignalHeadXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    Logger* log = new Logger("TripleTurnoutSignalHeadXml");
    log->error("Invalid method called");
}
