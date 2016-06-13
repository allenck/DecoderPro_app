#include "dcclocoaddressxml.h"

DccLocoAddressXml::DccLocoAddressXml(QObject *parent) :
    QObject(parent)
{
}

/**
 * Handle XML configuration for DccLocoAddress objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2005
 * @version $Revision: 17977 $
 */
///*public*/ class DccLocoAddressXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/ DccLocoAddressXml() {}

/**
 * Default implementation for storing the contents of a
 * DccLocoAddress
 * @param o Object to store, of type DccLocoAddress
 * @return Element containing the complete info
 */
/*public*/ QDomElement DccLocoAddressXml::store(QDomDocument doc, QObject* o)
{
 DccLocoAddress* p = (DccLocoAddress*)o;

 QDomElement element = doc.createElement("dcclocoaddress");

 // include contents
 if (p!=NULL)
 {
        element.setAttribute("number", p->getNumber());
        if (p->isLongAddress()) element.setAttribute("longaddress", "yes");
        else element.setAttribute("longaddress", "no");
    } else {
        element.setAttribute("number", "");
        element.setAttribute("longaddress", "no");
    }
    return element;
}

/*public*/ bool DccLocoAddressXml::load(QDomElement element) {
    log.error("Invalid method called");
    return false;
}

/*public*/ DccLocoAddress* DccLocoAddressXml::getAddress(QDomElement element) {
 if (element.attribute("number")=="")
  return NULL;
 int number = element.attribute("number").toInt();
 bool longaddress = false;
 QString a = element.attribute("longaddress");
 if (a!="null""" && a==("yes")) longaddress = true;
 return new DccLocoAddress(number, longaddress);
}

/*public*/ void DccLocoAddressXml::load(QDomElement element, QObject* o)
{
 log.error("Invalid method called");
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DccLocoAddressXml.class.getName());
//}
