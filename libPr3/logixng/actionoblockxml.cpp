#include "actionoblockxml.h"
#include "logixng/actionoblock.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"
#include "oblockmanager.h"
/**
 * Handle XML configuration for OBlock objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright (C) 2021
 */
// /*public*/ class ActionOBlockXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    ActionOBlockXml::ActionOBlockXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {

    }


    /**
     * Default implementation for storing the contents of an OBlock
     *
     * @param o Object to store, of type ActionOBlock
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ActionOBlockXml::store(QObject* o) {
        ActionOBlock* p = (ActionOBlock*) o;

        QDomElement element = doc.createElement("ActionOBlock");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<OBlock*>* oblock = p->getOBlock();
        if (oblock != nullptr) {
            element.appendChild(e1=doc.createElement("oblock")); e1.appendChild(doc.createTextNode(oblock->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("operationAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getOperationAddressing())));
        element.appendChild(e1=doc.createElement("operationDirect")); e1.appendChild(doc.createTextNode(ActionOBlock::DirectOperation::toString(p->getOperationDirect())));
        element.appendChild(e1=doc.createElement("operationReference")); e1.appendChild(doc.createTextNode(p->getOperationReference()));
        element.appendChild(e1=doc.createElement("operationLocalVariable")); e1.appendChild(doc.createTextNode(p->getOperationLocalVariable()));
        element.appendChild(e1=doc.createElement("operationFormula")); e1.appendChild(doc.createTextNode(p->getOperationFormula()));

        element.appendChild(e1=doc.createElement("dataAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getDataAddressing())));
        element.appendChild(e1=doc.createElement("dataReference")); e1.appendChild(doc.createTextNode(p->getDataReference()));
        element.appendChild(e1=doc.createElement("dataLocalVariable")); e1.appendChild(doc.createTextNode(p->getDataLocalVariable()));
        element.appendChild(e1=doc.createElement("dataFormula")); e1.appendChild(doc.createTextNode(p->getDataFormula()));

        element.appendChild(e1=doc.createElement("oblockValue")); e1.appendChild(doc.createTextNode(p->getOBlockValue()));

        return element;
    }

    //@Override
    /*public*/ bool ActionOBlockXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionOBlock* h = new ActionOBlock(sys, uname);

        loadCommon(h, shared);

        QDomElement oblockName = shared.firstChildElement("oblock");
        if (!oblockName .isNull()) {
            OBlock* t = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getNamedBean(oblockName.text().trimmed())->self();
            if (t != nullptr) h->setOBlock(t);
            else h->removeOBlock();
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
                h->setOperationDirect(ActionOBlock::DirectOperation::valueOf(elem.text().trimmed()));
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


            elem = shared.firstChildElement("oblockValue");
            if (!elem.isNull()) h->setOBlockValue(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
