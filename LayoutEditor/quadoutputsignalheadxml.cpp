#include "quadoutputsignalheadxml.h"
#include "quadoutputsignalhead.h"
#include "instancemanager.h"
#include "signalheadmanager.h"

QuadOutputSignalHeadXml::QuadOutputSignalHeadXml(QObject *parent) :
    TripleTurnoutSignalHeadXml(parent)
{
}
/**
 * Handle XML configuration for QuadOutputSignalHead objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 17977 $
 */
///*public*/ class QuadOutputSignalHeadXml extends TripleTurnoutSignalHeadXml {

//    /*public*/ QuadOutputSignalHeadXml() {}

/**
 * Default implementation for storing the contents of a
 * QuadOutputSignalHead
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return Element containing the complete info
 */
/*public*/ QDomElement QuadOutputSignalHeadXml::store(QObject* o) {
    QuadOutputSignalHead* p = (QuadOutputSignalHead*)o;

    QDomElement element = doc.createElement("signalhead");
    //element.setAttribute("class", this.getClass().getName());
    element.setAttribute("class", "jmri.implementation.configurexml.QuadOutputSignalHead");

    // include contents
    element.setAttribute("systemName", p->getSystemName());
    //element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->getSystemName())));
    QDomElement systemname = doc.createElement("systemName");
    systemname.appendChild(doc.createTextNode(p->getSystemName()));
    element.appendChild(systemname);

    storeCommon(p, element);

    element.appendChild(addTurnoutElement(p->getGreen(), "green"));
    element.appendChild(addTurnoutElement(p->getYellow(), "yellow"));
    element.appendChild(addTurnoutElement(p->getRed(), "red"));
    element.appendChild(addTurnoutElement(p->getLunar(), "lunar"));

    return element;
}

/**
 * Create a QuadOutputSignalHead
 * @param element Top level Element to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool QuadOutputSignalHeadXml::load(QDomElement element) throw (Exception) {
    QDomNodeList l = element.elementsByTagName("turnoutname");
    if (l.size() == 0) l = element.elementsByTagName("turnout");
    NamedBeanHandle<Turnout*>* green = loadTurnout(l.at(0).toElement());
    NamedBeanHandle<Turnout*>* yellow = loadTurnout(l.at(1).toElement());
    NamedBeanHandle<Turnout*>* red = loadTurnout(l.at(2).toElement());
    NamedBeanHandle<Turnout*>* lunar = loadTurnout(l.at(3).toElement());

    // put it together
    QString sys = getSystemName(element);
    QString uname = getUserName(element);
    SignalHead* h;
    if (uname == NULL)
        h = (SignalHead*)new QuadOutputSignalHead(sys, green, yellow, red, lunar);
    else
        h = (SignalHead*)new QuadOutputSignalHead(sys, uname, green, yellow, red, lunar);

    loadCommon(h, element);

    qobject_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->Register(h);
    return true;
}
