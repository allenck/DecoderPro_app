#include "locoaddressxml.h"
#include "loggerfactory.h"
#include "locoaddress.h"
#include "dcclocoaddressxml.h"

/**
 * Handle XML configuration for LocoAddress objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2005
 */
// /*public*/ class LocoAddressXml extends jmri.configurexml.AbstractXmlAdapter {

/*public*/ LocoAddressXml::LocoAddressXml(QObject* parent) : AbstractXmlAdapter(parent) {
}

/**
 * Default implementation for storing the contents of a LocoAddress
 *
 * @param o Object to store, of type LocoAddress
 * @return Element containing the complete info
 */
//@Override
/*public*/ QDomElement LocoAddressXml::store(QObject* o) {
    locoAddress* p = (locoAddress*) o;

    QDomElement element = doc.createElement("locoaddress");

    // include contents, we shall also store the old format for backward compatability
    DccLocoAddressXml* adapter = new DccLocoAddressXml();

    element.appendChild(adapter->store(p));

    if (p != NULL)
    {
     QDomElement elem;
        element.appendChild(elem = doc.createElement("number"));
        elem.appendChild(doc.createTextNode(QString::number(p->getNumber())));
        element.appendChild(elem=doc.createElement("protocol"));
        elem.appendChild(doc.createTextNode(p->getShortName(p->getProtocol())));
    } else {
        element.appendChild(doc.createElement("number")/*.addContent("")*/);
        element.appendChild(doc.createElement("protocol")/*.addContent("")*/);
    }

    return element;
}

//@Override
/*public*/ bool LocoAddressXml::load(QDomElement shared, QDomElement perNode) {
    log->error("Invalid method called");
    return false;
}

/*public*/ locoAddress* LocoAddressXml::getAddress(QDomElement element) {
    if (element.firstChildElement("number") == QDomElement()) {
        DccLocoAddressXml* adapter = new DccLocoAddressXml();
        return adapter->getAddress(element.firstChildElement("dcclocoaddress"));
    }
    int addr = 0;
    try {
     bool bok;
        addr = element.firstChildElement("number").text().toInt(&bok);
        if(!bok) throw NumberFormatException();
    } catch (NumberFormatException e) {
        return NULL;
    }
    QString protocol = element.firstChildElement("protocol").text();
    locoAddress::Protocol prot = locoAddress::getByShortName(protocol);
    return new DccLocoAddress(addr, prot);
}

//@Override
/*public*/ void LocoAddressXml::load(QDomElement element, QObject* o) throw (Exception){
    log->error("Invalid method called");
}

/*private*/ /*final*/ /*static*/ Logger* LocoAddressXml::log = LoggerFactory::getLogger("DccLocoAddressXml");
