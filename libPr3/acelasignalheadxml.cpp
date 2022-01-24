#include "acelasignalheadxml.h"
#include "instancemanager.h"
#include "acelasignalhead.h"
#include "acelanode.h"
#include "acelaaddress.h"
#include "signalheadmanager.h"

/**
 * Handle XML configuration for AcelaSignalHead objects. based upon example of
 * Grapevine by Bob Jacobsen
 *
 * @author Bob Coleman Copyright: Copyright (c) 2009
 */
//*public*/  class AcelaSignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {


/*public*/  AcelaSignalHeadXml::AcelaSignalHeadXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent){
   _memo = (AcelaSystemConnectionMemo*)InstanceManager::getDefault("AcelaSystemConnectionMemo");
}

/**
 * Default implementation for storing the contents of an Acela
 * AcelaSignalHead
 *
 * @param o Object to store, of type AcelaSignalHead
 * @return Element containing the complete info
 */
//@Override
/*public*/  QDomElement AcelaSignalHeadXml::store(QObject* o) {
    AcelaSignalHead* p = (AcelaSignalHead*) o;

    QDomElement element = doc.createElement("signalhead");
    element.setAttribute("class", "jmri.jmrix.acela.configurexml.AcelaSignalHeadXml");

    // include contents
    element.setAttribute("systemName", p->getSystemName());
    QString tu;
    tu = p->getUserName();
    if (tu != "") {
        element.setAttribute("userName", tu);
    }
    AcelaNode* sh = AcelaAddress::getNodeFromSystemName(p->getSystemName(), _memo);
    int rawaddr = AcelaAddress::getBitFromSystemName(p->getSystemName(), _memo->getSystemPrefix());
    QString shtype = sh->getOutputSignalHeadTypeString(rawaddr);
    element.setAttribute("signalheadType", shtype);

    storeCommon(p, element);

    return element;
}

//@Override
/*public*/  bool AcelaSignalHeadXml::load(QDomElement shared, QDomElement perNode) {
    QString sys = shared.attribute("systemName");
    QString a = shared.attribute("userName");
    SignalHead* h;
    if (a == nullptr) {
        h = new AcelaSignalHead(sys, _memo);
    } else {
        h = new AcelaSignalHead(sys, a, _memo);
    }

    QString t = shared.attribute("signalheadType");
    QString shtype;
    if (t.isEmpty()) {
        shtype = "UKNOWN";
    } else {
        shtype = t;
    }

    loadCommon(h, shared);

    ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(h);

    AcelaNode* sh = AcelaAddress::getNodeFromSystemName(sys, _memo);
    int rawaddr = AcelaAddress::getBitFromSystemName(sys, _memo->getSystemPrefix());
    sh->setOutputSignalHeadTypeString(rawaddr, shtype);

    return true;
}
