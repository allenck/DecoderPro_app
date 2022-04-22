#include "digitalbooleanmanyxml.h"
#include "digitalbooleanmany.h"
#include "instancemanager.h"
#include "defaultdigitalbooleanactionmanager.h"

DigitalBooleanManyXml::DigitalBooleanManyXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 setObjectName("DigitalBooleanManyXml");
}
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class DigitalBooleanManyXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /**
     * Default implementation for storing the contents of a Many
     *
     * @param o Object to store, of type Many
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DigitalBooleanManyXml::store(QObject* o) {
        DigitalBooleanMany* p = (DigitalBooleanMany*) o;

        QDomElement element = doc.createElement("DigitalBooleanMany");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configutexml.DigitalBooleanManyXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e = doc.createElement("Actions");
        for (int i=0; i < p->getChildCount(); i++) {
            QDomElement e2 = doc.createElement("Socket");
            e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(i)->getName()));
            MaleSocket* socket = p->getChild(i)->getConnectedSocket();
            QString socketSystemName;
            if (socket != nullptr) {
                socketSystemName = socket->getSystemName();
            } else {
                socketSystemName = p->getActionSystemName(i);
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
    /*public*/  bool DigitalBooleanManyXml::load(QDomElement shared, QDomElement perNode) {

        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();

        QDomElement actionElement = shared.firstChildElement("Actions");
        //for (QDomElement socketElement : actionElement.getChildren()) {
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
            actionSystemNames.append(QMap<QString, QString> {{socketName, systemName}});
        }

        // put it together
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        DigitalBooleanActionBean* h = new DigitalBooleanMany(sys, uname, actionSystemNames);

        loadCommon(h, shared);

        ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->registerAction(h);

//        log.warn("Register action: " + h.getSystemName() + ", " + h.getLongDescription());
        return true;
    }
