#include "actionlocalvariablexml.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "actionlocalvariable.h"
#include "defaultdigitalactionmanager.h"
#include "defaultmemorymanager.h"
#include "parserexception.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class ActionLocalVariableXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ActionLocalVariableXml::ActionLocalVariableXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 setObjectName("ActionLocalVariableXml");
}

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionLocalVariableXml::store(QObject* o) {
        ActionLocalVariable* p = (ActionLocalVariable*) o;

        QDomElement element = doc.createElement("ActionLocalVariable");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.ActionLocalVariableXml");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName())));

        storeCommon(p, element);

        QString variableName = p->getLocalVariable();
        if (variableName != "") {
            element.appendChild(doc.createElement("variable").appendChild(doc.createTextNode(variableName)));
        }

        NamedBeanHandle<Memory*>* memoryName = p->getMemory();
        if (memoryName != nullptr) {
            element.appendChild(doc.createElement("memory").appendChild(doc.createTextNode(memoryName->getName())));
        }

        element.appendChild(doc.createElement("variableOperation").appendChild(doc.createTextNode(ActionLocalVariable::VariableOperation::toString(p->getVariableOperation()))));

        element.appendChild(doc.createElement("constant").appendChild(doc.createTextNode(p->getConstantValue())));
        element.appendChild(doc.createElement("otherTableCell").appendChild(doc.createTextNode(p->getOtherTableCell())));
        element.appendChild(doc.createElement("otherVariable").appendChild(doc.createTextNode(p->getOtherLocalVariable())));
        element.appendChild(doc.createElement("formula").appendChild(doc.createTextNode(p->getFormula())));

        return element;
    }

    //@Override
    /*public*/  bool ActionLocalVariableXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionLocalVariable* h = new ActionLocalVariable(sys, uname);

        loadCommon(h, shared);

        QDomElement variableName = shared.firstChildElement("variable");
        if (!variableName.isNull()) {
            h->setLocalVariable(variableName.text().trimmed());
        }

        QDomElement memoryName = shared.firstChildElement("memory");
        if (!memoryName.isNull()) {
            Memory* t = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName.text().trimmed());
            if (t != nullptr) h->setMemory(t);
            else h->removeMemory();
        }

        QDomElement queryType = shared.firstChildElement("variableOperation");
        if (!queryType.isNull()) {
            try {
                h->setVariableOperation(ActionLocalVariable::VariableOperation::valueOf(queryType.text().trimmed()));
            } catch (ParserException* e) {
                log->error("cannot set variable operation: " + queryType.text().trimmed(), e);
            }
        }

        QDomElement constant = shared.firstChildElement("constant");
        if (!constant.isNull()) {
            h->setConstantValue(constant.text().trimmed());
        }

        QDomElement otherTableCell = shared.firstChildElement("otherTableCell");
        if (!otherTableCell.isNull()) {
            h->setOtherTableCell(otherTableCell.text().trimmed());
        }

        QDomElement otherVariable = shared.firstChildElement("otherVariable");
        if (!otherVariable.isNull()) {
            h->setOtherLocalVariable(otherVariable.text().trimmed());
        }

        QDomElement formula = shared.firstChildElement("formula");
        if (!formula.isNull()) {
            try {
                h->setFormula(formula.text().trimmed());
            } catch (ParserException* e) {
                log->error("cannot set data: " + formula.text().trimmed(), e);
            }
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionLocalVariableXml::log = LoggerFactory::getLogger("ActionLocalVariableXml");
