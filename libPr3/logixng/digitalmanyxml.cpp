#include "digitalmanyxml.h"
#include "digitalmany.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"

DigitalManyXml::DigitalManyXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 setObjectName("DigitalManyXml");
}
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class DigitalManyXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /**
     * Default implementation for storing the contents of a Many
     *
     * @param o Object to store, of type Many
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DigitalManyXml::store(QObject* o) {
        DigitalMany* p = (DigitalMany*) o;

        QDomElement element = doc.createElement("DigitalMany");
        element.setAttribute("class", "jmri.jmrit.logixng,actions.configurexml.DigitalManyXml");
        QDomElement e1;
        element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e = doc.createElement("Actions");
        for (int i=0; i < p->getChildCount(); i++) {
            QDomElement e2 = doc.createElement("Socket");
            e2.appendChild(e1 = doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(i)->getName()));
            MaleSocket* socket = p->getChild(i)->getConnectedSocket();
            QString socketSystemName;
            if (socket != nullptr) {
                socketSystemName = socket->getSystemName();
            } else {
                socketSystemName = p->getActionSystemName(i);
            }
            if (socketSystemName != "") {
                e2.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
            }
            e.appendChild(e2);
        }
        element.appendChild(e);

        return element;
    }

    //@Override
    /*public*/  bool DigitalManyXml::load(QDomElement shared, QDomElement perNode) {

        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();

        QDomElement actionElement = shared.firstChildElement("Actions");
        //for (QDomElement socketElement : actionElement.firstChildElementren()) {
        QDomNodeList nl = actionElement.childNodes();
        for(int i=0; i < nl.size(); i++)
        {
         QDomElement socketElement = nl.at(i).toElement();
            QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
            QDomElement systemNameElement = socketElement.firstChildElement("systemName");
            QString systemName = "";
            if (!systemNameElement.isNull()) {
                systemName = systemNameElement.text().trimmed();
            }
            actionSystemNames.append(QMap<QString, QString>{{socketName, systemName}});
        }

        // put it together
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        DigitalActionBean* h = new DigitalMany(sys, uname, actionSystemNames);

        loadCommon(h, shared);

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);

//        log.warn("Register action: " + h.getSystemName() + ", " + h.getLongDescription());
        return true;
    }
