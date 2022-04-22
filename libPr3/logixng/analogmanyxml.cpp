#include "analogmanyxml.h"
#include "analogmany.h"
#include "defaultanalogactionmanager.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class AnalogManyXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  AnalogManyXml::AnalogManyXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent) {
//        jmri.managers.configurexml.DefaultConditionalManagerXml a;
    }
/*
    @SuppressWarnings("unchecked")  // Reflection does not support generics
    private List<ActionMany.ActionEntry> getActionEntry(Many actionMany)
            throws IllegalAccessException, IllegalArgumentException, NoSuchFieldException {

        Field f = actionMany.getClass().getDeclaredField("actionEntries");
        f.setAccessible(true);
        return (List<ActionMany.ActionEntry>) f.get(actionMany);
    }
*/
    /**
     * Default implementation for storing the contents of a Many
     *
     * @param o Object to store, of type Many
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement AnalogManyXml::store(QObject* o) {
        AnalogMany* p = (AnalogMany*) o;

        QDomElement element = doc.createElement("AnalogMany");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.AnalogManyXml");
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
    /*public*/  bool AnalogManyXml::load(QDomElement shared, QDomElement perNode) {

        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();

        QDomElement actionElement = shared.firstChildElement("Actions");
        //for (Element socketElement : actionElement.getChildren()) {
        QDomNodeList list =  actionElement.childNodes();
        for(int i=0; i < list.count(); i++)
        {
         QDomElement socketElement = list.at(i).toElement();
            QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
            QDomElement systemNameElement = socketElement.firstChildElement("systemName");
            QString systemName = "";
            if (systemNameElement != QDomElement()) {
                systemName = systemNameElement.text().trimmed();
            }
            actionSystemNames.append(QMap<QString, QString> {{socketName, systemName}});
        }

        // put it together
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        AnalogActionBean* h = new AnalogMany(sys, uname, actionSystemNames);

        loadCommon(h, shared);

        ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->registerAction(h);

//        log.warn("Register action: " + h.getSystemName() + ", " + h.getLongDescription());
        return true;
    }
