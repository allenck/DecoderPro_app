#include "tripleoutoutsignalheadxml.h"
#include "loggerfactory.h"
#include "tripleoutputsignalhead.h"
#include "signalheadmanager.h"
#include "instancemanager.h"
/**
 * Handle XML configuration for TripleOutputSignalHead objects.
 *
 * @author Suzie Tall based on work by Bob Jacobson
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2008
 */
// /*public*/ class TripleOutputSignalHeadXml extends DoubleTurnoutSignalHeadXml {

/*public*/ TripleOutputSignalHeadXml::TripleOutputSignalHeadXml(QObject* parent) : DoubleTurnoutSignalHeadXml(parent){
 setProperty("JavaClassName", "jmri.implementation.configurexml.TripleOutoutSignalHeadXml");
}

/**
 * Default implementation for storing the contents of a
 * TripleOutputSignalHead
 *
 * @param o Object to store, of type TripleOutputSignalHead
 * @return Element containing the complete info
 */
//@Override
/*public*/ QDomElement TripleOutputSignalHeadXml::store(QObject* o) {
    TripleOutputSignalHead* p = (TripleOutputSignalHead*) o;

    QDomElement element = doc.createElement("signalhead");
    element.setAttribute("class", "jmri.implementation.configurexml.TripleOutoutSignalHeadXml");

    // include contents
    element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->getSystemName())));

    storeCommon(p, element);

    element.appendChild(addTurnoutElement(p->getGreen(), "green"));
    element.appendChild(addTurnoutElement(p->getBlue(), "blue"));
    element.appendChild(addTurnoutElement(p->getRed(), "red"));

    return element;
}

//@Override
/*public*/ bool TripleOutputSignalHeadXml::load(QDomElement shared, QDomElement /*perNode*/) throw (JmriConfigureXmlException){
    QDomNodeList l = shared.elementsByTagName("turnoutname");
    if (l.size() == 0) {
        l = shared.elementsByTagName("turnout");
    }
    NamedBeanHandle<Turnout*>* green = loadTurnout(l.at(0).toElement());
    NamedBeanHandle<Turnout*>* blue = loadTurnout(l.at(1).toElement());
    NamedBeanHandle<Turnout*>* red = loadTurnout(l.at(2).toElement());

    // put it together
    QString sys = getSystemName(shared);
    QString uname = getUserName(shared);
    SignalHead* h;
    if (uname == nullptr) {
        h = new TripleOutputSignalHead(sys, green, blue, red);
    } else {
        h = new TripleOutputSignalHead(sys, uname, green, blue, red);
    }

    loadCommon(h, shared);

    static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->Register(h);
    return true;
}

//@Override
/*public*/ void TripleOutputSignalHeadXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}

/*private*/ /*final*/ /*static*/ Logger* TripleOutputSignalHeadXml::log = LoggerFactory::getLogger("TripleOutputSignalHeadXml");
