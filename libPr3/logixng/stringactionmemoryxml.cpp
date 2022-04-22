#include "stringactionmemoryxml.h"
#include "instancemanager.h"
#include "stringactionmemory.h"
#include "defaultstringactionmanager.h"
#include "defaultmemorymanager.h"

/**
 *
 */
///*public*/  class StringActionMemoryXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  StringActionMemoryXml::StringActionMemoryXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("StringActionMemoryXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement StringActionMemoryXml::store(QObject* o) {
        StringActionMemory* p = (StringActionMemory*) o;

        QDomElement element = doc.createElement("StringActionMemory");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.StringActionMemoryXml");

        QDomElement e;
        element.appendChild(e = doc.createElement("systemName"));
        e.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Memory*>* memory = p->getMemory();
        if (memory != nullptr) {
            element.appendChild(e= doc.createElement("memory")); e.appendChild(doc.createTextNode(memory->getName()));
        }

        return element;
    }
/*
    QDomElement addLightElement(NamedBeanHandle<Light> to, String which) {
        QDomElement el = doc.createElement("lightname");
        el.setAttribute("defines", which);
        el.appendChild(to.getName());
        return el;
    }

    QDomElement addLightElement(Light to) {
        String user = to.getUserName();
        String sys = to.getSystemName();

        QDomElement el = doc.createElement("light");
        el.setAttribute("systemName", sys);
        if (user != null) {
            el.setAttribute("userName", user);
        }

        return el;
    }
*/
    //@Override
    /*public*/  bool StringActionMemoryXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
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
        StringActionMemory* h = new StringActionMemory(sys, uname);

        loadCommon(h, shared);

        QDomElement memoryName = shared.firstChildElement("memory");
        if (!memoryName.isNull()) {
            Memory* m = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName.text().trimmed());
            if (m != nullptr) h->setMemory(m);
            else h->removeMemory();
        }

        // this.checkedNamedBeanReference()
        // <T extends NamedBean> T checkedNamedBeanReference(String name, @Nonnull T type, @Nonnull Manager<T> m) {

        ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->registerAction(h);
        return true;
    }
