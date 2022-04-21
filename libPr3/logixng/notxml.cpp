#include "notxml.h"
#include "not.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Handle XML configuration for Not objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2021
 */
///*public*/  class NotXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

NotXml::NotXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 setObjectName("NotXml");
}

    /**
     * Default implementation for storing the contents of a ActionMany
     *
     * @param o Object to store, of type ActionMany
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement NotXml::store(QObject* o) {
        Not* p = (Not*) o;

        QDomElement element = doc.createElement("Not");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.NotXml");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName())));

        storeCommon(p, element);

        QDomElement e2 = doc.createElement("Socket");
        e2.appendChild(doc.createElement("socketName").appendChild(doc.createTextNode(p->getChild(0)->getName())));
        MaleSocket* socket = p->getChild(0)->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(socketSystemName)));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/  bool NotXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        Not* h = new Not(sys, uname);

        loadCommon(h, shared);

        QDomElement socketElement = shared.firstChildElement("Socket");
        QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
        QDomElement systemNameElement = socketElement.firstChildElement("systemName");
        QString systemName = "";
        if (!systemNameElement.isNull()) {
            systemName = systemNameElement.text().trimmed();
        }
        h->getChild(0)->setName(socketName);
        h->setSocketSystemName(systemName);

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
