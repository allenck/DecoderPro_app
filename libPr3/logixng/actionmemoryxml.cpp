#include "actionmemoryxml.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "actionmemory.h"
#include "namedbeanaddressing.h"
#include "defaultmemorymanager.h"
#include "parserexception.h"
#include "loggerfactory.h"
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class ActionMemoryXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  ActionMemoryXml::ActionMemoryXml(QObject* parent)
     : AbstractNamedBeanManagerConfigXML(parent) {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionMemoryXml::store(QObject* o) {
        ActionMemory* p = (ActionMemory*) o;

        QDomElement element = doc.createElement("ActionMemory");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.ActionMemoryXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Memory*>* memory = p->getMemory();
        if (memory != nullptr) {
            element.appendChild(e1=doc.createElement("memory")); e1.appendChild(doc.createTextNode(memory->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        NamedBeanHandle<Memory*>* otherMemoryName = p->getOtherMemory();
        if (otherMemoryName != nullptr) {
            element.appendChild(e1=doc.createElement("otherMemory")); e1.appendChild(doc.createTextNode(otherMemoryName->getName()));
        }

        element.appendChild(e1=doc.createElement("memoryOperation")); e1.appendChild(doc.createTextNode(ActionMemory::MemoryOperation::toString(p->getMemoryOperation())));

        element.appendChild(e1=doc.createElement("otherConstant")); e1.appendChild(doc.createTextNode(p->getConstantValue()));
        element.appendChild(e1=doc.createElement("otherTableCell")); e1.appendChild(doc.createTextNode(p->getOtherTableCell()));
        element.appendChild(e1=doc.createElement("otherVariable")); e1.appendChild(doc.createTextNode(p->getOtherLocalVariable()));
        element.appendChild(e1=doc.createElement("otherFormula")); e1.appendChild(doc.createTextNode(p->getOtherFormula()));

        return element;
    }

    //@Override
    /*public*/  bool ActionMemoryXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionMemory* h = new ActionMemory(sys, uname);

        loadCommon(h, shared);


        QDomElement memoryName = shared.firstChildElement("memory");
        if (!memoryName.isNull()) {
            Memory* t = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName.text().trimmed());
            if (t != nullptr) h->setMemory(t);
            else h->removeMemory();
        }

        QDomElement otherMemoryName = shared.firstChildElement("otherMemory");
        if (!otherMemoryName.isNull()) {
            Memory* t = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(otherMemoryName.text().trimmed());
            if (t != nullptr) h->setOtherMemory(t);
            else h->removeOtherMemory();
        }

        QDomElement queryType = shared.firstChildElement("memoryOperation");
        if (!queryType.isNull()) {
            try {
                h->setMemoryOperation(ActionMemory::MemoryOperation::valueOf(queryType.text().trimmed()));
            } catch (ParserException* e) {
                log->error("cannot set memory operation: " + queryType.text().trimmed(), e);
            }
        }


        QDomElement elemAddressing = shared.firstChildElement("addressing");

        // Temporary solution for handling change in the xml file.
        // Remove this when JMRI 4.24 is released.
        if (!elemAddressing.isNull()) {
            QDomElement constant = shared.firstChildElement("constant");
            if (!constant .isNull()) {
                h->setOtherConstantValue(constant.text().trimmed());
            }

            QDomElement variable = shared.firstChildElement("variable");
            if (!variable.isNull()) {
                h->setOtherLocalVariable(variable.text().trimmed());
            }

            QDomElement formula = shared.firstChildElement("formula");
            if (!formula.isNull()) {
                try {
                    h->setOtherFormula(formula.text().trimmed());
                } catch (ParserException* e) {
                    log->error("cannot set data: " + formula.text().trimmed(), e);
                }
            }
        } else {
            try {
                h->setAddressing(NamedBeanAddressing::valueOf(elemAddressing.text().trimmed()));

                QDomElement elem = shared.firstChildElement("reference");
                if (!elem.isNull()) h->setReference(elem.text().trimmed());

                elem = shared.firstChildElement("localVariable");
                if (!elem.isNull()) h->setLocalVariable(elem.text().trimmed());

                elem = shared.firstChildElement("formula");
                if (!elem.isNull()) h->setFormula(elem.text().trimmed());

                elem = shared.firstChildElement("otherConstant");
                if (!elem.isNull()) h->setOtherConstantValue(elem.text().trimmed());

                elem = shared.firstChildElement("otherTableCell");
                if (!elem.isNull()) h->setOtherTableCell(elem.text().trimmed());

                elem = shared.firstChildElement("otherVariable");
                if (!elem.isNull()) h->setOtherLocalVariable(elem.text().trimmed());

                elem = shared.firstChildElement("otherFormula");
                if (!elem.isNull()) h->setOtherFormula(elem.text().trimmed());

            } catch (ParserException* e) {
                throw new JmriConfigureXmlException(e);
            }
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionMemoryXml::log = LoggerFactory::getLogger("ActionMemoryXml");
