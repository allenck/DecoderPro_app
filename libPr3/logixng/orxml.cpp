#include "orxml.h"
#include "or.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class OrXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  OrXml::OrXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent) {
     setObjectName("OrXml");
    }

    /**
     * Default implementation for storing the contents of a ActionMany
     *
     * @param o Object to store, of type ActionMany
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement OrXml::store(QObject* o) {
        Or* p = (Or*) o;

        QDomElement element = doc.createElement("Or");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.Or.Xml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e = doc.createElement("Expressions");
        for (int i=0; i < p->getChildCount(); i++) {
            QDomElement e2 = doc.createElement("Socket");
            e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(i)->getName()));
            MaleSocket* socket = p->getChild(i)->getConnectedSocket();
            QString socketSystemName;
            if (socket != nullptr) {
                socketSystemName = socket->getSystemName();
            } else {
                socketSystemName = p->getExpressionSystemName(i);
            }
            if (socketSystemName != "") {
                e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
            }
            e.appendChild(e2);
        }
        element.appendChild(e);

        return element;
    }

    //@Override
    /*public*/  bool OrXml::load(QDomElement shared, QDomElement perNode) {
        QList<QMap<QString, QString>> expressionSystemNames = QList<QMap<QString, QString>>();

        QDomElement actionElement = shared.firstChildElement("Expressions");
        QDomNodeList nl = actionElement.childNodes();
        for (int i=0; i < nl.size(); i++) {
         QDomElement socketElement = nl.at(i).toElement();
            QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
            QDomElement systemNameElement = socketElement.firstChildElement("systemName");
            QString systemName = "";
            if (!systemNameElement.isNull()) {
                systemName = systemNameElement.text().trimmed();
            }
            expressionSystemNames.append(QMap<QString, QString> {{socketName, systemName}});
        }

        // put it together
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        DigitalExpressionBean* h = new Or(sys, uname, expressionSystemNames);

        loadCommon(h, shared);

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
