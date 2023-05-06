#include "executedelayedxml.h"
#include "defaultdigitalactionmanager.h"
#include "executedelayed.h"
#include "jmriconfigurexmlexception.h"
#include "parserexception.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ExecuteDelayed objects.
 *
 * @author Bob Jacobsen      Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist  Copyright (C) 2021
 */
// /*public*/  class ExecuteDelayedXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  ExecuteDelayedXml::ExecuteDelayedXml(QObject* parent) {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/  QDomElement ExecuteDelayedXml::store(QObject* o) {
        ExecuteDelayed* p = (ExecuteDelayed*) o;

        QDomElement element = doc.createElement("ExecuteDelayed");
        QDomElement esn;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.ExecuteDelayedXml");
        element.appendChild(esn=doc.createElement("systemName")); esn.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e2 = doc.createElement("Socket");
        e2.appendChild(esn=doc.createElement("socketName")); esn.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(esn=doc.createElement("systemName")); esn.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        QDomElement e3;
        element.appendChild(e3=doc.createElement("delayAddressing")); e3.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getDelayAddressing())));
        element.appendChild(e3=doc.createElement("delay")); e3.appendChild(doc.createTextNode(QString::number(p->getDelay())));
        element.appendChild(e3=doc.createElement("delayReference")); e3.appendChild(doc.createTextNode(p->getDelayReference()));
        element.appendChild(e3=doc.createElement("delayLocalVariable")); e3.appendChild(doc.createTextNode(p->getDelayLocalVariable()));
        element.appendChild(e3=doc.createElement("delayFormula")); e3.appendChild(doc.createTextNode(p->getDelayFormula()));

        element.appendChild(e3=doc.createElement("unit")); e3.appendChild(doc.createTextNode(TimerUnit::toString(p->getUnit())));
        element.appendChild(e3=doc.createElement("resetIfAlreadyStarted")); e3.appendChild(doc.createTextNode(p->getResetIfAlreadyStarted() ? "yes" : "no"));  // NOI18N

        return element;
    }

    //@Override
    /*public*/  bool ExecuteDelayedXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {

        QDomElement socketNameElement = shared.firstChildElement("Socket").firstChildElement("socketName");
        QString socketName = socketNameElement.text().trimmed();
        QDomElement socketSystemNameElement = shared.firstChildElement("Socket").firstChildElement("systemName");
        QString socketSystemName = "";
        if (!socketSystemNameElement.isNull()) {
            socketSystemName = socketSystemNameElement.text().trimmed();
        }

        QDomElement delayElement = shared.firstChildElement("delay");
        int delay = 0;
        if (!delayElement.isNull()) {
            delay = delayElement.text().toInt();
        }

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExecuteDelayed* h = new ExecuteDelayed(sys, uname);

        loadCommon(h, shared);

        h->getChild(0)->setName(socketName);
        h->setSocketSystemName(socketSystemName);
        h->setDelay(delay);

        QDomElement unit = shared.firstChildElement("unit");
        if (!unit.isNull()) {
            h->setUnit(TimerUnit::valueOf(unit.text().trimmed()));
        }

        QString resetIfAlreadyStarted = "no";
        if (!shared.firstChildElement("resetIfAlreadyStarted").isNull()) {  // NOI18N
            resetIfAlreadyStarted = shared.firstChildElement("resetIfAlreadyStarted").text().trimmed();  // NOI18N
        }
        h->setResetIfAlreadyStarted("yes" == (resetIfAlreadyStarted));

        try {
            QDomElement elem = shared.firstChildElement("delayAddressing");
            if (!elem.isNull()) {
                h->setDelayAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("delayReference");
            if (!elem.isNull()) h->setDelayReference(elem.text().trimmed());

            elem = shared.firstChildElement("delayLocalVariable");
            if (!elem.isNull()) h->setDelayLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("delayFormula");
            if (!elem.isNull()) h->setDelayFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }

