#include "dccsignalheadxml.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "dccsignalhead.h"

#if 1
/**
 * Handle XML configuration for DccSignalHead objects.
 *
 * This file is part of JMRI.
 *
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 *
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2008, 2009
 * @author Petr Koud'a Copyright: Copyright (c) 2007
 */
// /*public*/ class DccSignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

/*public*/ DccSignalHeadXml::DccSignalHeadXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent) {
 setProperty("JavaClassname", "jmri.implementation.configurexml.DccSignalHeadXml");
}

/**
 * Default implementation for storing the contents of a LsDecSignalHead
 *
 * @param o Object to store, of type LsDecSignalHead
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement DccSignalHeadXml::store(QObject* o) {
    DccSignalHead* p = (DccSignalHead*) o;

    QDomElement element = doc.createElement("signalhead");
    element.setAttribute("class", "jmri.implementation.configurexml.DccSignalHeadXml");

    element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->getSystemName())));

    storeCommon(p, element);

    if (p->useAddressOffSet()) {
        element.appendChild(doc.createElement("useAddressOffSet").appendChild(doc.createTextNode("yes")));
    } else {
        element.appendChild(doc.createElement("useAddressOffSet").appendChild(doc.createTextNode("no")));
    }

    for (int i = 0; i < p->getValidStates().length(); i++) {
        QString aspect = p->getValidStateNames()[i];
        //String address = p.getOutputForAppearance(i);
        QDomElement el = doc.createElement("aspect");
        el.setAttribute("defines", aspect);
        el.appendChild(doc.createElement("number").appendChild(doc.createTextNode(QString::number(p->getOutputForAppearance(p->getValidStates()[i])))));
        element.appendChild(el);
    }

    return element;
}

//@Override
/*public*/ bool DccSignalHeadXml::load(QDomElement shared, QDomElement perNode) {
    // put it together
    QString sys = getSystemName(shared);
    QString uname = getUserName(shared);
    DccSignalHead* h;
    if (uname == nullptr) {
        h = new DccSignalHead(sys);
    } else {
        h = new DccSignalHead(sys, uname);
    }

    loadCommon(h, shared);

    if (!shared.firstChildElement("useAddressOffSet").isNull()) {
        if (shared.firstChildElement("useAddressOffSet").text() == ("yes")) {
            h->useAddressOffSet(true);
        }
    }

    QDomNodeList list = shared.elementsByTagName("aspect");
    for (int i =0; i < list.size(); i++) {
     QDomElement e = list.at(i).toElement();
        QString aspect = e.attribute("defines");
        int number = -1;
        bool bok;
            QString value = e.attribute("number");
            number = (value).toInt(&bok);

        if(!bok) {
            log->error("failed to convert DCC number");
        }
        int indexOfAspect = -1;

        for (int i = 0; i < h->getValidStates().length(); i++) {
            if (h->getValidStateNames()[i] == (aspect)) {
                indexOfAspect = i;
                break;
            }
        }
        if (indexOfAspect != -1) {
            h->setOutputForAppearance(h->getValidStates()[indexOfAspect], number);
        }
    }

    static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->Register(h);
    return true;
}

//@Override
/*public*/ void DccSignalHeadXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->error("Invalid method called");
}

/*private*/ /*final*/ /*static*/ Logger* DccSignalHeadXml::log = LoggerFactory::getLogger("DccSignalHeadXml");


#endif
