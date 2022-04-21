#include "ifthenelsexml.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "ifthenelse.h"
#include "defaultfemaledigitalexpressionsocket.h"

IfThenElseXml::IfThenElseXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 setObjectName("IfThenElseXml");
}
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class IfThenElseXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement IfThenElseXml::store(QObject* o) {
        IfThenElse* p = (IfThenElse*) o;

        QDomElement element = doc.createElement("IfThenElse");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.IfThenElseXml");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName())));

        storeCommon(p, element);

        element.setAttribute("type", IfThenElse::Type::toString(p->getType()));

        QDomElement e2 = doc.createElement("IfSocket");
        e2.appendChild(doc.createElement("socketName").appendChild(doc.createTextNode(p->getChild(0)->getName())));
        MaleSocket* socket = p->getIfExpressionSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getIfExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(socketSystemName)));
        }
        element.appendChild(e2);

        e2 = doc.createElement("ThenSocket");
        e2.appendChild(doc.createElement("socketName").appendChild(doc.createTextNode(p->getChild(1)->getName())));
        socket = p->getThenActionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getThenActionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(socketSystemName)));
        }
        element.appendChild(e2);

        e2 = doc.createElement("ElseSocket");
        e2.appendChild(doc.createElement("socketName").appendChild(doc.createTextNode(p->getChild(2)->getName())));
        socket = p->getElseActionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getElseActionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(socketSystemName)));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/  bool IfThenElseXml::load(QDomElement shared, QDomElement perNode) {

        QString typeStr = shared.attribute("type");

        /*
        To not cause problems during testing, these are accepted
        for now. But they should be removed before the production
        version. These where changed to CamelCase after people
        had started testing LogixNG.
        Remove TRIGGER_ACTION and CONTINOUS_ACTION in if-then-else-4.23.1.xsd
        as well.
        */
        if ("TRIGGER_ACTION" == (typeStr)) typeStr = "ExecuteOnChange";
        if ("CONTINOUS_ACTION" == (typeStr)) typeStr = "AlwaysExecute";
        if ("TriggerAction" == (typeStr)) typeStr = "ExecuteOnChange";
        if ("ContinuousAction" == (typeStr)) typeStr = "AlwaysExecute";

        IfThenElse::Type::ETYPE type = IfThenElse::Type::valueOf(typeStr);

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        IfThenElse* h = new IfThenElse(sys, uname);
         h->setType(type);

        loadCommon(h, shared);

        QDomElement socketName = shared.firstChildElement("IfSocket").firstChildElement("socketName");
         h->getChild(0)->setName(socketName.text().trimmed());
        QDomElement socketSystemName = shared.firstChildElement("IfSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
             h->setIfExpressionSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("ThenSocket").firstChildElement("socketName");
         h->getChild(1)->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("ThenSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
             h->setThenActionSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("ElseSocket").firstChildElement("socketName");
         h->getChild(2)->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("ElseSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
             h->setElseActionSocketSystemName(socketSystemName.text().trimmed());
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
