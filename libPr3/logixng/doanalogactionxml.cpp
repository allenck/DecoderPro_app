#include "doanalogactionxml.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/doanalogaction.h"
#include "logixng/femaleanalogactionsocket.h"
#include "logixng/femaleanalogexpressionsocket.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/ class DoAnalogActionXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

DoAnalogActionXml::DoAnalogActionXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML{parent}
{

}

    /**
     * Default implementation for storing the contents of a DoAnalogAction
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement DoAnalogActionXml::store(QObject* o) {
        DoAnalogAction* p = (DoAnalogAction*) o;

        QDomElement element = doc.createElement("DoAnalogAction");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.DoAnalogAction");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e2 = doc.createElement("ExpressionSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getAnalogExpressionSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getAnalogExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("ActionSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(1)->getName()));
        socket = p->getAnalogActionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getAnalogActionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/ bool DoAnalogActionXml::load(QDomElement shared, QDomElement perNode) {

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        DoAnalogAction* h = new DoAnalogAction(sys, uname);

        loadCommon(h, shared);

        QDomElement socketName = shared.firstChildElement("ExpressionSocket").firstChildElement("socketName");
        h->getChild(0)->setName(socketName.text().trimmed());
        QDomElement socketSystemName = shared.firstChildElement("ExpressionSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setAnalogExpressionSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("ActionSocket").firstChildElement("socketName");
        h->getChild(1)->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("ActionSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setAnalogActionSocketSystemName(socketSystemName.text().trimmed());
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
