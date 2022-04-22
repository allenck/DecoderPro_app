#include "stringexpressionmemoryxml.h"
#include "instancemanager.h"
#include "stringexpressionmemory.h"
#include "defaultmemorymanager.h"
#include "namedbeanhandle.h"
#include "defaultstringexpressionmanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class StringExpressionMemoryXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  StringExpressionMemoryXml::StringExpressionMemoryXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
    {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement StringExpressionMemoryXml::store(QObject* o) {
        StringExpressionMemory* p = (StringExpressionMemory*) o;

        QDomElement element = doc.createElement("StringExpressionMemory");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.StringExpressionMemoryXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Memory*>* memory = p->getMemory();
        if (memory != nullptr) {
            element.appendChild(e1=doc.createElement("memory")); e1.appendChild(doc.createTextNode(memory->getName()));
        }

        return element;
    }
/*
    Element addLightElement(NamedBeanHandle<Light> to, String which) {
        Element el = new Element("lightname");
        el.setAttribute("defines", which);
        el.addContent(to.getName());
        return el;
    }

    Element addLightElement(Light to) {
        String user = to.getUserName();
        String sys = to.getSystemName();

        Element el = new Element("light");
        el.setAttribute("systemName", sys);
        if (user != null) {
            el.setAttribute("userName", user);
        }

        return el;
    }
*/
    //@Override
    /*public*/  bool StringExpressionMemoryXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
//        List<Element> l = shared.getChildren("lightname");
/*
        if (l.size() == 0) {
            l = shared.getChildren("light");  // older form
        }
        NamedBeanHandle<Light> low = loadLight(l.get(0));
        NamedBeanHandle<Light> high = loadLight(l.get(1));
*/
        // put it together
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        StringExpressionMemory* h;
        h = new StringExpressionMemory(sys, uname);

        loadCommon(h, shared);

        QDomElement memoryName = shared.firstChildElement("memory");
        if (!memoryName.isNull()) {
            Memory* m = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName.text().trimmed());
            if (m != nullptr) h->setMemory(m);
            else h->removeMemory();
        }

        // this.checkedNamedBeanReference()
        // <T extends NamedBean> T checkedNamedBeanReference(String name, @Nonnull T type, @Nonnull Manager<T> m) {

        ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->registerExpression(h);
        return true;
    }

//    private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(StringExpressionMemoryXml.class);

