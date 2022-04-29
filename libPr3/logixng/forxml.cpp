#include "forxml.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "for.h"
#include "defaultfemaledigitalexpressionsocket.h"

ForXml::ForXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 setObjectName("For");
}
/**
 * Handle XML configuration for For objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
///*public*/  class ForXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /**
     * Default implementation for storing the contents of a For
     *
     * @param o Object to store, of type For
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ForXml::store(QObject* o) {
        For* p = (For*) o;

        QDomElement element = doc.createElement("For");
        element.setAttribute("class", "jmri.jmrit.logixng.actions configurexml.ForXml");
        QDomElement e1;
        element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e2 = doc.createElement("InitSocket");
        e2.appendChild(e1 = doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getInitActionSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getInitActionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("WhileSocket");
        e2.appendChild(e1 = doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(1)->getName()));
        socket = p->getWhileExpressionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getWhileExpressionSocketSystemName();
        }
        if (socketSystemName != nullptr) {
            e2.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("AfterEachSocket");
        e2.appendChild(e1 = doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(2)->getName()));
        socket = p->getAfterEachActionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getAfterEachExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("DoSocket");
        e2.appendChild(e1 = doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(3)->getName()));
        socket = p->getDoActionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getDoExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/  bool ForXml::load(QDomElement shared, QDomElement perNode) {

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        For* h = new For(sys, uname);

        loadCommon(h, shared);

        QDomElement socketName = shared.firstChildElement("InitSocket").firstChildElement("socketName");
        h->getInitActionSocket()->setName(socketName.text().trimmed());
        QDomElement socketSystemName = shared.firstChildElement("InitSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setInitActionSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("WhileSocket").firstChildElement("socketName");
        h->getWhileExpressionSocket()->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("WhileSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setWhileExpressionSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("AfterEachSocket").firstChildElement("socketName");
        h->getAfterEachActionSocket()->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("AfterEachSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setAfterEachActionSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("DoSocket").firstChildElement("socketName");
        h->getDoActionSocket()->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("DoSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setDoActionSocketSystemName(socketSystemName.text().trimmed());
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
