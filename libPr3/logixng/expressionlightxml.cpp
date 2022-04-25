#include "expressionlightxml.h"
#include "instancemanager.h"
#include "expressionlight.h"
#include "proxylightmanager.h"
#include "parserexception.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Handle XML configuration for ExpressionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class ExpressionLightXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  ExpressionLightXml::ExpressionLightXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent) {
 setObjectName("ExpressionLightXml");
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ExpressionLightXml::store(QObject* o) {
        ExpressionLight* p = (ExpressionLight*) o;

        QDomElement element = doc.createElement("ExpressionLight");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.ExpressionLightXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Light*>* light = p->getLight();
        if (light != nullptr) {
            element.appendChild(e1=doc.createElement("light")); e1.appendChild(doc.createTextNode(light->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("is_isNot")); e1.appendChild(doc.createTextNode(Is_IsNot_Enum::toString( p->get_Is_IsNot())));

        element.appendChild(e1=doc.createElement("stateAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getStateAddressing())));
        element.appendChild(e1=doc.createElement("lightState")); e1.appendChild(doc.createTextNode(ExpressionLight::LightState::toString(p->getBeanState())));
        element.appendChild(e1=doc.createElement("stateReference")); e1.appendChild(doc.createTextNode(p->getStateReference()));
        element.appendChild(e1=doc.createElement("stateLocalVariable")); e1.appendChild(doc.createTextNode(p->getStateLocalVariable()));
        element.appendChild(e1=doc.createElement("stateFormula")); e1.appendChild(doc.createTextNode(p->getStateFormula()));

        return element;
    }

    //@Override
    /*public*/  bool ExpressionLightXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionLight* h = new ExpressionLight(sys, uname);

        loadCommon(h, shared);

        QDomElement lightName = shared.firstChildElement("light");
        if (!lightName.isNull()) {
            Light* t = (Light*)((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->getLight(lightName.text().trimmed());
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


            QDomElement is_IsNot = shared.firstChildElement("is_isNot");
            if (!is_IsNot.isNull()) {
                h->set_Is_IsNot(Is_IsNot_Enum::valueOf(is_IsNot.text().trimmed()));
            }


            elem = shared.firstChildElement("stateAddressing");
            if (!elem.isNull()) {
                h->setStateAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement lightState = shared.firstChildElement("lightState");
            if (!lightState.isNull()) {
                h->setBeanState(ExpressionLight::LightState::valueOf(lightState.text().trimmed()));
            }

            elem = shared.firstChildElement("stateReference");
            if (!elem.isNull()) h->setStateReference(elem.text().trimmed());

            elem = shared.firstChildElement("stateLocalVariable");
            if (!elem.isNull()) h->setStateLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("stateFormula");
            if (!elem.isNull()) h->setStateFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
