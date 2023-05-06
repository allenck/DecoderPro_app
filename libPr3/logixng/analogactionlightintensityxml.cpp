#include "analogactionlightintensityxml.h"
#include "analogactionlightintensity.h"
#include "defaultvariablelightmanager.h"
#include "jmriconfigurexmlexception.h"
#include "parserexception.h"
#include "defaultanalogactionmanager.h"

/**
 * Handle XML configuration for AnalogActionLightIntensity objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class AnalogActionLightIntensityXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  AnalogActionLightIntensityXml::AnalogActionLightIntensityXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("AnalogActionLightIntensityXml");
  }


    /**
     * Default implementation for storing the contents of a AnalogActionLightIntensity
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement AnalogActionLightIntensityXml::store(QObject* o) {
        AnalogActionLightIntensity* p = (AnalogActionLightIntensity*) o;

        QDomElement element = doc.createElement("AnalogActionLightIntensity");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.AnalogActionLightIntensityXml");
        QDomElement e1;
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

        return element;
    }

    //@Override
    /*public*/  bool AnalogActionLightIntensityXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        AnalogActionLightIntensity* h = new AnalogActionLightIntensity(sys, uname);

        loadCommon(h, shared);

        QDomElement lightName = shared.firstChildElement("variableLight");
        if (!lightName.isNull()) {
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

        ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->registerAction(h);
        return true;
    }
