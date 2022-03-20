#include "andxml.h"
#include "digitalexpressionbean.h"
#include "and.h"
#include "digitalexpressionmanager.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class AndXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  AndXml::AndXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent){
    }

    /**
     * Default implementation for storing the contents of a ActionMany
     *
     * @param o Object to store, of type ActionMany
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/  QDomElement AndXml::store(QObject* o) {
        And* p = (And*) o;

        QDomElement element = doc.createElement("And");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.And");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(((AbstractNamedBean*)p->bself())->getSystemName())));

        storeCommon((NamedBean*)p->bself(), element);

        QDomElement e = doc.createElement("Expressions");
        for (int i=0; i < p->getChildCount(); i++) {
            QDomElement e2 = doc.createElement("Socket");
            e2.appendChild(doc.createElement("socketName").appendChild(doc.createTextNode(p->getChild(i)->getName())));
            MaleSocket* socket = p->getChild(i)->getConnectedSocket();
            QString socketSystemName;
            if (socket != nullptr) {
                socketSystemName = socket->getSystemName();
            } else {
                socketSystemName = p->getExpressionSystemName(i);
            }
            if (socketSystemName != "") {
                e2.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(socketSystemName)));
            }
            e.appendChild(e2);
        }
        element.appendChild(e);

        return element;
    }

    //@Override
    /*public*/  bool AndXml::load(QDomElement shared, QDomElement perNode) {
        QList<QMap<QString, QString>> expressionSystemNames = QList<QMap<QString, QString>>();

        QDomElement actionElement = shared.firstChildElement("Expressions");
        QDomNodeList list = actionElement.childNodes();
        for (int i=0; i < list.count(); i++)
        {
         QDomElement socketElement = list.at(i).toElement();
            QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
            QDomElement systemNameElement = socketElement.firstChildElement("systemName");
            QString systemName = "";
            if (systemNameElement != QDomElement()) {
                systemName = systemNameElement.text().trimmed();
            }
            //expressionSystemNames.add(new AbstractMap.SimpleEntry<>(socketName, systemName));
            expressionSystemNames.append(QMap<QString, QString> {{socketName, systemName}});
        }

        // put it together
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        DigitalExpressionBean* h = new And(sys, uname, expressionSystemNames);

        loadCommon(h, shared);

        ((DigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
