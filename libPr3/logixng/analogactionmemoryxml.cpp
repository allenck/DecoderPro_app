#include "analogactionmemoryxml.h"
#include "analogactionmemory.h"
#include "instancemanager.h"
#include "defaultmemorymanager.h"
#include "defaultanalogactionmanager.h"
#include "namedbeanhandle.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class AnalogActionMemoryXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  AnalogActionMemoryXml::AnalogActionMemoryXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent) {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement AnalogActionMemoryXml::store(QObject* o) {
        AnalogActionMemory* p = (AnalogActionMemory*) o;

        QDomElement element = doc.createElement("AnalogActionMemory");
        element.setAttribute("class", ".jmri.jmrit.actions.configurexml.AnalogActionMemoryXml");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName())));

        storeCommon(p, element);

        NamedBeanHandle<Memory*>* memory = p->getMemory();
        if (memory != nullptr) {
            element.appendChild(doc.createElement("memory").appendChild(doc.createTextNode(memory->getName())));
        }

        return element;
    }

    //@Override
    /*public*/  bool AnalogActionMemoryXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        AnalogActionMemory* h;
        h = new AnalogActionMemory(sys, uname);

        loadCommon(h, shared);

        QDomElement memoryName = shared.firstChildElement("memory");
        if (!memoryName.isNull()) {
            Memory* m = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName.text().trimmed());
            if (m != nullptr) h->setMemory(m);
            else h->removeMemory();
        }

        // this.checkedNamedBeanReference()
        // <T extends NamedBean> T checkedNamedBeanReference(String name, @Nonnull T type, @Nonnull Manager<T> m) {

        ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->registerAction(h);
        return true;
    }

