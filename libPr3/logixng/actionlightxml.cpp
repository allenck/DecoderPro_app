#include "actionlightxml.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "actionlight.h"
#include "proxylightmanager.h"
#include "parserexception.h"
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class ActionLightXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  ActionLightXml::ActionLightXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ActionLightXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionLightXml::store(QObject* o) {
        ActionLight* p = (ActionLight*) o;

        QDomElement element = doc.createElement("ActionLight");
        element.setAttribute("class", "jmri.jmrit.logixng.configurexml.ActionLightXml");
        QDomElement e1;
        element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Light*>* light = p->getLight();
        if (light != nullptr) {
            element.appendChild(e1 = doc.createElement("light")); e1.appendChild(doc.createTextNode(light->getName()));
        }

        element.appendChild(e1 = doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1 = doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1 = doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1 = doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1 = doc.createElement("stateAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getStateAddressing())));
        element.appendChild(e1 = doc.createElement("lightState")); e1.appendChild(doc.createTextNode(ActionLight::LightState::toString(p->getBeanState())));
        element.appendChild(e1 = doc.createElement("stateReference")); e1.appendChild(doc.createTextNode(p->getStateReference()));
        element.appendChild(e1 = doc.createElement("stateLocalVariable")); e1.appendChild(doc.createTextNode(p->getStateLocalVariable()));
        element.appendChild(e1 = doc.createElement("stateFormula")); e1.appendChild(doc.createTextNode(p->getStateFormula()));

        element.appendChild(e1 = doc.createElement("dataAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getDataAddressing())));
        element.appendChild(e1 = doc.createElement("dataReference")); e1.appendChild(doc.createTextNode(p->getDataReference()));
        element.appendChild(e1 = doc.createElement("dataLocalVariable")); e1.appendChild(doc.createTextNode(p->getDataLocalVariable()));
        element.appendChild(e1 = doc.createElement("dataFormula")); e1.appendChild(doc.createTextNode(p->getDataFormula()));

        if (p->getLightValue() > 0) {
            element.appendChild(e1 = doc.createElement("lightValue")); e1.appendChild(doc.createTextNode(QString::number(p->getLightValue())));
        }

        return element;
    }

    //@Override
    /*public*/  bool ActionLightXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionLight* h = new ActionLight(sys, uname);

        loadCommon(h, shared);

        QDomElement lightName = shared.firstChildElement("light");
        if (!lightName.isNull()) {
            Light* t = ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->getLight(lightName.text().trimmed());
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


            elem = shared.firstChildElement("stateAddressing");
            if (!elem.isNull()) {
                h->setStateAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement lightState = shared.firstChildElement("lightState");
            if (!lightState.isNull()) {
                h->setBeanState(ActionLight::LightState::valueOf(lightState.text().trimmed()));
            }

            elem = shared.firstChildElement("stateReference");
            if (!elem.isNull()) h->setStateReference(elem.text().trimmed());

            elem = shared.firstChildElement("stateLocalVariable");
            if (!elem.isNull()) h->setStateLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("stateFormula");
            if (!elem.isNull()) h->setStateFormula(elem.text().trimmed());


            elem = shared.firstChildElement("dataAddressing");
            if (!elem.isNull()) {
                h->setDataAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("dataReference");
            if (!elem.isNull()) h->setDataReference(elem.text().trimmed());

            elem = shared.firstChildElement("dataLocalVariable");
            if (!elem.isNull()) h->setDataLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("dataFormula");
            if (!elem.isNull()) h->setDataFormula(elem.text().trimmed());


            elem = shared.firstChildElement("lightValue");
            if (!elem.isNull()) {
                try {
              bool ok;
                    h->setLightValue(elem.text().trimmed().toInt(&ok)); if(!ok) throw new NumberFormatException();
                } catch (NumberFormatException* ex) {
                    h->setLightValue(0);
                }
            }

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
