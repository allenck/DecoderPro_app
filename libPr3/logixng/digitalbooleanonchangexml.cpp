#include "digitalbooleanonchangexml.h"
#include "digitalbooleanonchange.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class DigitalBooleanOnChangeXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

/*public*/  DigitalBooleanOnChangeXml::DigitalBooleanOnChangeXml(QObject* parent) {
}

/**
 * Default implementation for storing the contents of a SE8cSignalHead
 *
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/  QDomElement DigitalBooleanOnChangeXml::store(QObject* o) {
    DigitalBooleanOnChange* p = (DigitalBooleanOnChange*) o;

    QDomElement element = doc.createElement("OnChange");
    QDomElement e1;
    element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.DigitalBooleanOnChangeXml");
    element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

    storeCommon(p, element);

    element.setAttribute("trigger", DigitalBooleanOnChange::Trigger::toString(p->getTrigger()));

    QDomElement e2 = doc.createElement("Socket");
    QDomElement e3;
    e2.appendChild(e3=doc.createElement("socketName")); e3.appendChild(doc.createTextNode(p->getChild(0)->getName()));
    MaleSocket* socket = p->getSocket()->getConnectedSocket();
    QString socketSystemName;
    if (socket != nullptr) {
        socketSystemName = socket->getSystemName();
    } else {
        socketSystemName = p->getSocketSystemName();
    }
    if (socketSystemName != "") {
        e2.appendChild(e3=doc.createElement("systemName")); e3.appendChild(doc.createTextNode(socketSystemName));
    }
    element.appendChild(e2);

    return element;
}

//@Override
/*public*/  bool DigitalBooleanOnChangeXml::load(QDomElement shared, QDomElement perNode) {

    QString triggerAttribute = shared.attribute("trigger");
    DigitalBooleanOnChange::Trigger::TargetAction trigger = DigitalBooleanOnChange::Trigger::toTargetAction(triggerAttribute);

    QString sys = getSystemName(shared);
    QString uname = getUserName(shared);
    DigitalBooleanOnChange* h = new DigitalBooleanOnChange(sys, uname, trigger);

    loadCommon(h, shared);

    QDomElement socketName = shared.firstChildElement("Socket").firstChildElement("socketName");
    h->getChild(0)->setName(socketName.text().trimmed());
    QDomElement socketSystemName = shared.firstChildElement("Socket").firstChildElement("systemName");
    if (!socketSystemName.isNull()) {
        h->setActionSocketSystemName(socketSystemName.text().trimmed());
    }

    ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->registerAction(h);
    return true;
}
