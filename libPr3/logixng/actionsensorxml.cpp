#include "actionsensorxml.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "actionsensor.h"
#include "jmriconfigurexmlexception.h"
#include "namedbeanaddressing.h"
#include "parserexception.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class ActionSensorXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ActionSensorXml::ActionSensorXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{

}

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleSensorSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionSensorXml::store(QObject* o) {
        ActionSensor* p = (ActionSensor*) o;

        QDomElement element = doc.createElement("ActionSensor");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.ActionSensorXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Sensor*>* sensor = p->getSensor();
        if (sensor != nullptr) {
            element.appendChild(e1=doc.createElement("sensor")); e1.appendChild(doc.createTextNode(sensor->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("stateAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getStateAddressing())));
        element.appendChild(e1=doc.createElement("sensorState")); e1.appendChild(doc.createTextNode(ActionSensor::SensorState::toString(p->getBeanState())));
        element.appendChild(e1=doc.createElement("stateReference")); e1.appendChild(doc.createTextNode(p->getStateReference()));
        element.appendChild(e1=doc.createElement("stateLocalVariable")); e1.appendChild(doc.createTextNode(p->getStateLocalVariable()));
        element.appendChild(e1=doc.createElement("stateFormula")); e1.appendChild(doc.createTextNode(p->getStateFormula()));

        return element;
    }

    //@Override
    /*public*/  bool ActionSensorXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException */{
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionSensor* h = new ActionSensor(sys, uname);

        loadCommon(h, shared);

        QDomElement sensorName = shared.firstChildElement("sensor");
        if (!sensorName.isNull()) {
            Sensor* t = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor(sensorName.text().trimmed());
            if (t != nullptr) h->setSensor(t);
            else h->removeSensor();
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

            QDomElement sensorState = shared.firstChildElement("sensorState");
            if (!sensorState.isNull()) {
                h->setBeanState(ActionSensor::SensorState::valueOf(sensorState.text().trimmed()));
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

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
