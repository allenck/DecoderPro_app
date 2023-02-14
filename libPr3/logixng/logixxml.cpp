#include "logixxml.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "actions/act_logix.h"
#include "defaultfemaledigitalexpressionsocket.h"
#include "defaultfemaledigitalbooleanactionsocket.h"

LogixXml::LogixXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{

}
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class LogixXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/  QDomElement LogixXml::store(QObject* o) {
        Actions::Logix* p = (Actions::Logix*) o;

        QDomElement element = doc.createElement("Logix");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.LogixXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e2 = doc.createElement("ExpressionSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getExpressionSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("ActionSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(1)->getName()));
        socket = p->getActionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getActionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/  bool LogixXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        Actions::Logix* h = new Actions::Logix(sys, uname);

        loadCommon(h, shared);

        QDomElement socketName = shared.firstChildElement("ExpressionSocket").firstChildElement("socketName");
        h->getChild(0)->setName(socketName.text().trimmed());
        QDomElement socketSystemName = shared.firstChildElement("ExpressionSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setExpressionSocketSystemName(socketSystemName.text().trimmed());
        }

        socketName = shared.firstChildElement("ActionSocket").firstChildElement("socketName");
        h->getChild(1)->setName(socketName.text().trimmed());
        socketSystemName = shared.firstChildElement("ActionSocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setActionSocketSystemName(socketSystemName.text().trimmed());
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
