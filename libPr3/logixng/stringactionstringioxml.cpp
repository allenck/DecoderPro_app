#include "stringactionstringioxml.h"
#include "instancemanager.h"
#include "logixng/defaultstringactionmanager.h"
#include "logixng/stringactionstringio.h"
#include "abstractstringiomanager.h"

/**
 *
 */
// /*public*/ class StringActionStringIOXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

StringActionStringIOXml::StringActionStringIOXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML(parent)
{

}


    /**
     * Default implementation for storing the contents of a StringActionStringIO
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement StringActionStringIOXml::store(QObject* o) {
        StringActionStringIO* p = (StringActionStringIO*) o;

        QDomElement element = doc.createElement("StringActionStringIO");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.StringActionStringIOXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<StringIO*>* memory = p->getStringIO();
        if (memory != nullptr) {
            element.appendChild(e1=doc.createElement("stringIO")); e1.appendChild(doc.createTextNode(memory->getName()));
        }

        return element;
    }

    //@Override
    /*public*/ bool StringActionStringIOXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        StringActionStringIO* h = new StringActionStringIO(sys, uname);

        loadCommon(h, shared);

        QDomElement stringIOName = shared.firstChildElement("stringIO");
        if (!stringIOName.isNull()) {
            StringIO* m = (StringIO*)((AbstractStringIOManager*)InstanceManager::getDefault("StringIOManager"))->getNamedBean(stringIOName.text().trimmed())->self();
            if (m != nullptr) h->setStringIO(m);
            else h->removeStringIO();
        }

        ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->registerAction(h);
        return true;
    }

//    private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(StringActionStringIOXml.class);

