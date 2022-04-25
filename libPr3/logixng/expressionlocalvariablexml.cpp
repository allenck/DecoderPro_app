#include "expressionlocalvariablexml.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "expressionlocalvariable.h"
#include "defaultmemorymanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class ExpressionLocalVariableXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  ExpressionLocalVariableXml::ExpressionLocalVariableXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ExpressionLocalVariableXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ExpressionLocalVariableXml::store(QObject* o) {
        ExpressionLocalVariable* p = (ExpressionLocalVariable*) o;

        QDomElement element = doc.createElement("ExpressionLocalVariable");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.ExpressionLocalVariableXml");
        QDomElement e1;
        element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QString variableName = p->getLocalVariable();
        if (variableName != "") {
            element.appendChild(e1 = doc.createElement("variable")); e1.appendChild(doc.createTextNode(variableName));
        }
        QString otherVariableName = p->getOtherLocalVariable();
        if (otherVariableName != "") {
            element.appendChild(e1 = doc.createElement("otherVariable")); e1.appendChild(doc.createTextNode(otherVariableName));
        }

        NamedBeanHandle<Memory*>* memoryName = p->getMemory();
        if (memoryName != nullptr) {
            element.appendChild(e1 = doc.createElement("memory")); e1.appendChild(doc.createTextNode(memoryName->getName()));
        }

        element.appendChild(e1 = doc.createElement("compareTo")); e1.appendChild(doc.createTextNode(ExpressionLocalVariable::CompareTo::toString(p->getCompareTo())));
        element.appendChild(e1 = doc.createElement("variableOperation")); e1.appendChild(doc.createTextNode(ExpressionLocalVariable::VariableOperation::toString( p->getVariableOperation())));
        element.appendChild(e1 = doc.createElement("caseInsensitive")); e1.appendChild(doc.createTextNode(p->getCaseInsensitive() ? "yes" : "no"));

        element.appendChild(e1 = doc.createElement("constant")); e1.appendChild(doc.createTextNode(p->getConstantValue()));
        element.appendChild(e1 = doc.createElement("regEx")); e1.appendChild(doc.createTextNode(p->getRegEx()));

        return element;
    }

    //@Override
    /*public*/  bool ExpressionLocalVariableXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionLocalVariable* h = new ExpressionLocalVariable(sys, uname);

        loadCommon(h, shared);

        QDomElement variableName = shared.firstChildElement("variable");
        if (!variableName.isNull()) {
            h->setLocalVariable(variableName.text().trimmed());
        }

        QDomElement otherVariableName = shared.firstChildElement("otherVariable");
        if (!otherVariableName.isNull()) {
            h->setOtherLocalVariable(otherVariableName.text().trimmed());
        }

        QDomElement memoryName = shared.firstChildElement("memory");
        if (!memoryName.isNull()) {
            Memory* t = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName.text().trimmed());
            if (t != nullptr) h->setMemory(t);
            else h->removeMemory();
        }

        QDomElement constant = shared.firstChildElement("constant");
        if (!constant.isNull()) {
            h->setConstantValue(constant.text());
        }

        QDomElement regEx = shared.firstChildElement("regEx");
        if (!regEx.isNull()) {
            h->setRegEx(regEx.text());
        }

        QDomElement compareTo = shared.firstChildElement("compareTo");
        if (!compareTo.isNull()) {
            h->setCompareTo(ExpressionLocalVariable::CompareTo::valueOf(compareTo.text().trimmed()));
        }

        QDomElement variableOperation = shared.firstChildElement("variableOperation");
        if (!variableOperation.isNull()) {
            h->setVariableOperation(ExpressionLocalVariable::VariableOperation::valueOf(variableOperation.text().trimmed()));
        }

        QDomElement caseInsensitive = shared.firstChildElement("caseInsensitive");
        if (!caseInsensitive.isNull()) {
            h->setCaseInsensitive("yes" == (caseInsensitive.text().trimmed()));
        } else {
            h->setCaseInsensitive(false);
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
