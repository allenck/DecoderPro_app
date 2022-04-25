#include "clipboardmanyxml.h"
#include "clipboardmany.h"
#include "instancemanager.h"
#include "basemanager.h"

ClipboardManyXml::ClipboardManyXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 setObjectName("ClipboardManyXml");
}
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class ClipboardManyXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /**
     * Default implementation for storing the contents of a Many
     *
     * @param o Object to store, of type Many
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ClipboardManyXml::store(QObject* o) {
        ClipboardMany* p = (ClipboardMany*) o;

        QDomElement element = doc.createElement("Many");
        element.setAttribute("class", "jmri.jmrit.logixng.ClipboardManyXml");

        for (int i=0; i < p->getChildCount(); i++) {
            QDomElement e2 = doc.createElement("Socket");
            QDomElement e1;
            e2.appendChild(e1 = doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(i)->getName()));
            MaleSocket* socket = p->getChild(i)->getConnectedSocket();

            QString socketSystemName;
            QString socketManager;
            if (socket != nullptr) {
                socketSystemName = socket->getSystemName();
                socketManager = socket->getManager()->getClassName();
                e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
                e2.appendChild(e1=doc.createElement("manager")); e1.appendChild(doc.createTextNode(socketManager));
            }
            element.appendChild(e2);
        }

        return element;
    }

    //@Override
    /*public*/  bool ClipboardManyXml::load(QDomElement shared, QDomElement perNode) {
        throw new UnsupportedOperationException("Not supported");
    }

    /*public*/  ClipboardMany* ClipboardManyXml::loadItem(QDomElement shared) {

        QList<ClipboardMany::ItemData*> systemNamesAndClasses = QList<ClipboardMany::ItemData*>();

        QDomElement actionElement = shared.firstChildElement("Many");
        //for (QDomElement socketElement : actionElement.getChildren()) {
        QDomNodeList nl = actionElement.childNodes();
        for(int i =0; i < nl.size(); i++)
        {
         QDomElement socketElement = nl.at(i).toElement();
            QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
            QDomElement systemNameElement = socketElement.firstChildElement("systemName");
            QString systemName = "";
            if (!systemNameElement.isNull()) {
                systemName = systemNameElement.text().trimmed();
            }
            QDomElement managerElement = socketElement.firstChildElement("manager");
            QString manager = "";
            if (!managerElement.isNull()) {
                manager = managerElement.text().trimmed();
            }
            systemNamesAndClasses.append(new ClipboardMany::ItemData(socketName, systemName, manager));
        }

        ClipboardMany* h = new ClipboardMany("", "", systemNamesAndClasses);

        loadCommon(h, shared);

//        InstanceManager.getDefault(DigitalActionManager.class).registerAction(h);

//        log.warn("Register action: " + h.getSystemName() + ", " + h.getLongDescription());
        return h;
    }
