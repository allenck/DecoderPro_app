#include "actionwarrantxml.h"
#include "instancemanager.h"
#include "jmriconfigurexmlexception.h"
#include "logixng/actionwarrant.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"
#include "warrantmanager.h"
/**
 * Handle XML configuration for Warrant objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright (C) 2021
 */
// /*public*/ class ActionWarrantXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    ActionWarrantXml::ActionWarrantXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {

    }


    /**
     * Default implementation for storing the contents of a Warrant
     *
     * @param o Object to store, of type TriggerWarrant
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ActionWarrantXml::store(QObject* o) {
        ActionWarrant* p = (ActionWarrant*) o;

        QDomElement element = doc.createElement("ActionWarrant");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.congigurexml.ActionWarrantXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Warrant*>* warrant = p->getWarrant();
        if (warrant != nullptr) {
            element.appendChild(doc.createElement("warrant")); e1.appendChild(doc.createTextNode(warrant->getName()));
        }

        element.appendChild(doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(doc.createElement("operationAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getOperationAddressing())));
        element.appendChild(doc.createElement("operationDirect")); e1.appendChild(doc.createTextNode(ActionWarrant::DirectOperation::toString(p->getOperationDirect())));
        element.appendChild(doc.createElement("operationReference")); e1.appendChild(doc.createTextNode(p->getOperationReference()));
        element.appendChild(doc.createElement("operationLocalVariable")); e1.appendChild(doc.createTextNode(p->getOperationLocalVariable()));
        element.appendChild(doc.createElement("operationFormula")); e1.appendChild(doc.createTextNode(p->getOperFormula()));

        element.appendChild(doc.createElement("dataAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getDataAddressing())));
        element.appendChild(doc.createElement("dataReference")); e1.appendChild(doc.createTextNode(p->getDataReference()));
        element.appendChild(doc.createElement("dataLocalVariable")); e1.appendChild(doc.createTextNode(p->getDataLocalVariable()));
        element.appendChild(doc.createElement("dataFormula")); e1.appendChild(doc.createTextNode(p->getDataFormula()));

        element.appendChild(doc.createElement("trainIdName")); e1.appendChild(doc.createTextNode(p->getTrainIdName()));
        element.appendChild(doc.createElement("controlAutoTrain")); e1.appendChild(doc.createTextNode(ActionWarrant::ControlAutoTrain::toString(p->getControlAutoTrain())));

        return element;
    }

    //@Override
    /*public*/ bool ActionWarrantXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionWarrant* h = new ActionWarrant(sys, uname);

        loadCommon(h, shared);

        QDomElement warrantName = shared.firstChildElement("warrant");
        if (!warrantName.isNull()) {
            Warrant* t = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getNamedBean(warrantName.text().trimmed())->self();
            if (t != nullptr) h->setWarrant(t);
            else h->removeWarrant();
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


            elem = shared.firstChildElement("operationAddressing");
            if (!elem.isNull()) {
                h->setOperationAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("operationDirect");
            if (!elem.isNull()) {
                h->setOperationDirect(ActionWarrant::DirectOperation::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("operationReference");
            if (!elem.isNull()) h->setOperationReference(elem.text().trimmed());

            elem = shared.firstChildElement("operationLocalVariable");
            if (!elem.isNull()) h->setOperationLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("operationFormula");
            if (!elem.isNull()) h->setOperationFormula(elem.text().trimmed());


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


            elem = shared.firstChildElement("trainIdName");
            if (!elem.isNull()) h->setTrainIdName(elem.text().trimmed());

            elem = shared.firstChildElement("controlAutoTrain");
            if (!elem.isNull()) {
                h->setControlAutoTrain(ActionWarrant::ControlAutoTrain::valueOf(elem.text().trimmed()));
            }

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
