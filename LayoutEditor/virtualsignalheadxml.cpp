#include "virtualsignalheadxml.h"
#include "virtualsignalhead.h"
#include "instancemanager.h"
#include "abstractsignalheadmanager.h"
#include <QtXml>

VirtualSignalHeadXml::VirtualSignalHeadXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("VirtualSignalHeadXml");
 setObjectName("VirtualSignalHeadXml");
}
/**
 * Handle XML configuration for VirtualSignalHead objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2005, 2008
 * @version $Revision: 17977 $
 */
// /*public*/ class VirtualSignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

//    /*public*/ VirtualSignalHeadXml() {}

/**
 * Default implementation for storing the contents of a
 * VirtualSignalHead
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return Element containing the complete info
 */
/*public*/ QDomElement VirtualSignalHeadXml::store(QObject* o) {
    VirtualSignalHead* p = (VirtualSignalHead*)o;

    QDomElement element = doc.createElement("signalhead");
    element.setAttribute("class", "jmri.implementation.configurexml.VirtualSignalHeadXml");

    // include contents
    element.setAttribute("systemName", p->getSystemName());
    QDomElement e1;
    element.appendChild(e1 = doc.createElement("systemName"));
    e1.appendChild(doc.createTextNode(p->getSystemName()));

    storeCommon(p, element);

    return element;
}

/**
 * Create a VirtualSignalHead
 * @param element Top level Element to unpack.
 * @return true if successful
 */
/*public*/ bool VirtualSignalHeadXml::load(QDomElement shared, QDomElement perNode) {
    // put it together
    QString sys = getSystemName(shared);
    QString uname = getUserName(shared);
    SignalHead* h;
    if (uname == NULL)
        h = (SignalHead*)new VirtualSignalHead(sys);
    else
        h = (SignalHead*)new VirtualSignalHead(sys, uname);

    loadCommon(h, shared);

    static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->Register(h);
    return true;
}

/*public*/ void VirtualSignalHeadXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}
