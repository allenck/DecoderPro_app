#include "expressionmemoryxml.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
#include "expressionmemory.h"
#include "defaultmemorymanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class ExpressionMemoryXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  /*public*/  ExpressionMemoryXml::ExpressionMemoryXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ExpressionMemoryXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ExpressionMemoryXml::store(QObject* o) {
        ExpressionMemory* p = (ExpressionMemory*) o;

        QDomElement element = doc.createElement("ExpressionMemory");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.ExpressionMemoryXml");
        QDomElement e1;
        element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Memory*>* memory = p->getMemory();
        if (memory != nullptr) {
            element.appendChild(e1 = doc.createElement("memory")); e1.appendChild(doc.createTextNode(memory->getName()));
        }
        NamedBeanHandle<Memory*>* otherMemory = p->getOtherMemory();
        if (otherMemory != nullptr) {
            element.appendChild(e1 = doc.createElement("otherMemory")); e1.appendChild(doc.createTextNode(otherMemory->getName()));
        }

        QString variableName = p->getLocalVariable();
        if (variableName != "") {
            element.appendChild(e1 = doc.createElement("variable")); e1.appendChild(doc.createTextNode(variableName));
        }

        element.appendChild(e1 = doc.createElement("compareTo")); e1.appendChild(doc.createTextNode(ExpressionMemory::CompareTo::toString(p->getCompareTo())));
        element.appendChild(e1 = doc.createElement("memoryOperation")); e1.appendChild(doc.createTextNode(ExpressionMemory::MemoryOperation::toString( p->getMemoryOperation())));
        element.appendChild(e1 = doc.createElement("caseInsensitive")); e1.appendChild(doc.createTextNode(p->getCaseInsensitive() ? "yes" : "no"));

        element.appendChild(e1 = doc.createElement("constant")); e1.appendChild(doc.createTextNode(p->getConstantValue()));
        element.appendChild(e1 = doc.createElement("regEx")); e1.appendChild(doc.createTextNode(p->getRegEx()));

        return element;
    }

    //@Override
    /*public*/  bool ExpressionMemoryXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException */{     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionMemory* h = new ExpressionMemory(sys, uname);

        loadCommon(h, shared);

        QDomElement memoryName = shared.firstChildElement("memory");
        if (!memoryName.isNull()) {
            Memory* m = (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName.text().trimmed());
            if (m != nullptr) h->setMemory(m);
            else h->removeMemory();
        }

        QDomElement otherMemoryName = shared.firstChildElement("otherMemory");
        if (!otherMemoryName.isNull()) {
            Memory* m = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(otherMemoryName.text().trimmed());
            if (m != nullptr) h->setOtherMemory(m);
            else h->removeOtherMemory();
        }

        QDomElement variableName = shared.firstChildElement("variable");
        if (!variableName.isNull()) {
            h->setLocalVariable(variableName.text().trimmed());
        }

        QDomElement constant = shared.firstChildElement("constant");
        if (!constant.isNull()) {
            h->setConstantValue(constant.text());
        }

        QDomElement regEx = shared.firstChildElement("regEx");
        if (!regEx.isNull()) {
            h->setRegEx(regEx.text());
        }

        QDomElement memoryOperation = shared.firstChildElement("memoryOperation");
        if (!memoryOperation.isNull()) {
            h->setMemoryOperation(ExpressionMemory::MemoryOperation::valueOf(memoryOperation.text().trimmed()));
        }

        QDomElement compareTo = shared.firstChildElement("compareTo");
        if (!compareTo.isNull()) {
            h->setCompareTo(ExpressionMemory::CompareTo::valueOf(compareTo.text().trimmed()));
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
