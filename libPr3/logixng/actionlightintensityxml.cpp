#include "actionlightintensityxml.h"
#include "defaultvariablelightmanager.h"
#include "instancemanager.h"
#include "logixng/actionlightintensity.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
  ///*public*/ class ActionLightIntensityXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    ActionLightIntensityXml::ActionLightIntensityXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {

    }


    /**
     * Default implementation for storing the contents of a ActionLightIntensity
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ActionLightIntensityXml::store(QObject* o) {
        ActionLightIntensity* p = (ActionLightIntensity*) o;

        QDomElement element = doc.createElement("ActionLightIntensity");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.ActionLightIntensityXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<VariableLight*>* light = p->getLight();
        if (light != nullptr) {
            element.appendChild(e1=doc.createElement("variableLight")); e1.appendChild(doc.createTextNode(light->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        QDomElement e2 = doc.createElement("IntensitySocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getIntensitySocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getIntensitySocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/ bool ActionLightIntensityXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionLightIntensity* h = new ActionLightIntensity(sys, uname);

        loadCommon(h, shared);

        QDomElement lightName = shared.firstChildElement("variableLight");
        if (!lightName .isNull()) {
            VariableLight* t = (VariableLight*)((DefaultVariableLightManager*)InstanceManager::getDefault("VariableLightManager"))
                    ->getNamedBean(lightName.text().trimmed())->self();
            if (t != nullptr) h->setLight(t);
            else h->removeLight();
        }

        try {
            QDomElement elem = shared.firstChildElement("addressing");
            if (!elem.isNull()) {
                h->setAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("reference");
            if (!elem.isNull()) h->setReference(elem.text().trimmed());

            elem = shared.firstChildElement("localVariable");
            if (!elem.isNull()) h->setLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("formula");
            if (!elem.isNull()) h->setFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        QDomElement socketName = shared.firstChildElement("IntensitySocket").firstChildElement("socketName");
        h->getChild(0)->setName(socketName.text().trimmed());
        QDomElement socketSystemName = shared.firstChildElement("IntensitySocket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setIntensitySystemName(socketSystemName.text().trimmed());
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
