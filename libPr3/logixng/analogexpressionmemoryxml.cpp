#include "analogexpressionmemoryxml.h"
#include "instancemanager.h"
#include "analogexpressionmemory.h"
#include "defaultmemorymanager.h"
#include "defaultanalogexpressionmanager.h"
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class AnalogExpressionMemoryXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  AnalogExpressionMemoryXml::AnalogExpressionMemoryXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("AnalogExpressionMemoryXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement AnalogExpressionMemoryXml::store(QObject* o) {
        AnalogExpressionMemory* p = (AnalogExpressionMemory*) o;

        QDomElement element = doc.createElement("AnalogExpressionMemory");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.AnalogExpressionMemoryXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createElement(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Memory*>* memory = p->getMemory();
        if (memory != nullptr) {
            element.appendChild(e1=doc.createElement("memory")); e1.appendChild(doc.createTextNode(memory->getName()));
        }

        return element;
    }

    //@Override
    /*public*/  bool AnalogExpressionMemoryXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        AnalogExpressionMemory* h;
        h = new AnalogExpressionMemory(sys, uname);

        loadCommon(h, shared);

        QDomElement memoryName = shared.firstChildElement("memory");
        if (!memoryName.isNull()) {
            Memory* m = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName.text().trimmed());
            if (m != nullptr) h->setMemory(m);
            else h->removeMemory();
        }

        // this.checkedNamedBeanReference()
        // <T extends NamedBean> T checkedNamedBeanReference(String name, @Nonnull T type, @Nonnull Manager<T> m) {

        ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(h);
        return true;
    }
