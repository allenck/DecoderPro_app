#include "dostringactionxml.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/dostringaction.h"
#include "instancemanager.h"
#include "logixng/femalestringactionsocket.h"
#include "logixng/femalestringexpressionsocket.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/ class DoStringActionXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    DoStringActionXml::DoStringActionXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {
     setObjectName("DoStringActionXml");
    }

    /**
     * Default implementation for storing the contents of a DoStringAction
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement DoStringActionXml::store(QObject* o) {
        DoStringAction* p = (DoStringAction*) o;

        QDomElement element = doc.createElement("DoStringAction");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.DoStringActionXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e2 = doc.createElement("ExpressionSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getStringExpressionSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getStringExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("ActionSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(1)->getName()));
        socket = p->getStringActionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getStringActionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/ bool DoStringActionXml::load(QDomElement shared, QDomElement perNode) {

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        DoStringAction* h = new DoStringAction(sys, uname);

        loadCommon(h, shared);

        QDomElement socketName = shared.firstChildElement("ExpressionSocket").firstChildElement("socketName");
        h->getChild(0)->setName(socketName.text().trimmed());
        QDomElement socketSystemName = shared.firstChildElement("ExpressionSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setStringExpressionSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("ActionSocket").firstChildElement("socketName");
        h->getChild(1)->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("ActionSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setStringActionSocketSystemName(socketSystemName.text().trimmed());
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
