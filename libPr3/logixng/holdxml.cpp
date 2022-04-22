#include "holdxml.h"
#include "hold.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class HoldXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  HoldXml::HoldXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent) {
     setObjectName("HoldXml");
    }

    /**
     * Default implementation for storing the contents of a ActionMany
     *
     * @param o Object to store, of type ActionMany
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement HoldXml::store(QObject* o) {
        Hold* p = (Hold*) o;

        QDomElement element = doc.createElement("Hold");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.HoldXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e2 = doc.createElement("TriggerSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getChild(0)->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getTriggerExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("HoldSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(1)->getName()));
        socket = p->getChild(1)->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getHoldActionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createElement(socketSystemName));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/  bool HoldXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        Hold* h = new Hold(sys, uname);

        loadCommon(h, shared);

        QDomElement socketElement = shared.firstChildElement("TriggerSocket");
        QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
        QDomElement systemNameElement = socketElement.firstChildElement("systemName");
        QString systemName = "";
        if (!systemNameElement.isNull()) {
            systemName = systemNameElement.text().trimmed();
        }
        h->getChild(0)->setName(socketName);
        h->setTriggerExpressionSocketSystemName(systemName);

        socketElement = shared.firstChildElement("HoldSocket");
        socketName = socketElement.firstChildElement("socketName").text().trimmed();
        systemNameElement = socketElement.firstChildElement("systemName");
        systemName = "";
        if (!systemNameElement.isNull()) {
            systemName = systemNameElement.text().trimmed();
        }
        h->getChild(1)->setName(socketName);
        h->setHoldActionSocketSystemName(systemName);

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
