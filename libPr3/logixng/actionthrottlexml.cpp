#include "actionthrottlexml.h"
#include "logixng/actionthrottle.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/femaleanalogexpressionsocket.h"
#include "logixng/femaledigitalexpressionsocket.h"
#include "instancemanager.h"
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/ class ActionThrottleXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ActionThrottleXml::ActionThrottleXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML{parent}
{

}

    /**
     * Default implementation for storing the contents of a ActionThrottle
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/ QDomElement ActionThrottleXml::store(QObject* o) {
        ActionThrottle* p = (ActionThrottle*) o;

        QDomElement element = doc.createElement("Throttle");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.ActionThrottleXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e2 = doc.createElement("LocoAddressSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getLocoAddressSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getLocoAddressSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("LocoSpeedSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(1)->getName()));
        socket = p->getLocoSpeedSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getLocoSpeedSocketSystemName();
        }
        if (socketSystemName != nullptr) {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("LocoDirectionSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(2)->getName()));
        socket = p->getLocoDirectionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getLocoDirectionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/ bool ActionThrottleXml::load(QDomElement shared, QDomElement perNode) {

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionThrottle* h = new ActionThrottle(sys, uname);

        loadCommon(h, shared);

        QDomElement socketName = shared.firstChildElement("LocoAddressSocket").firstChildElement("socketName");
        h->getLocoAddressSocket()->setName(socketName.text().trimmed());
        QDomElement socketSystemName = shared.firstChildElement("LocoAddressSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setLocoAddressSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("LocoSpeedSocket").firstChildElement("socketName");
        h->getLocoSpeedSocket()->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("LocoSpeedSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setLocoSpeedSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("LocoDirectionSocket").firstChildElement("socketName");
        h->getLocoDirectionSocket()->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("LocoDirectionSocket").firstChildElement("systemName");
        if (!socketSystemName .isNull()) {
            h->setLocoDirectionSocketSystemName(socketSystemName.text().trimmed());
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
