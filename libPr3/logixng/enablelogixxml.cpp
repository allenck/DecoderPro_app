#include "enablelogixxml.h"
#include "defaultlogixmanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/enablelogix.h"
#include "instancemanager.h"
#include "logixng/parserexception.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2021
 */
///*public*/ class EnableLogixXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    EnableLogixXml::EnableLogixXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {

    }


    /**
     * Default implementation for storing the contents of a EnableLogix
     *
     * @param o Object to store, of type EnableLogix
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement EnableLogixXml::store(QObject* o) {
        EnableLogix* p = (EnableLogix*) o;

        QDomElement element = doc.createElement("EnableLogix");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.EnableLogixXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Logix*>* logix = p-> getLogix();
        if (logix != nullptr) {
            element.appendChild(e1=doc.createElement("logix")); e1.appendChild(doc.createTextNode(logix->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p-> getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p-> getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p-> getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p-> getFormula()));

        element.appendChild(e1=doc.createElement("operationAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p-> getOperationAddressing())));
        element.appendChild(e1=doc.createElement("operationDirect")); e1.appendChild(doc.createTextNode(EnableLogix::Operation::toString(p-> getOperationDirect())));
        element.appendChild(e1=doc.createElement("operationReference")); e1.appendChild(doc.createTextNode(p-> getOperationReference()));
        element.appendChild(e1=doc.createElement("operationLocalVariable")); e1.appendChild(doc.createTextNode(p-> getOperationLocalVariable()));
        element.appendChild(e1=doc.createElement("operationFormula")); e1.appendChild(doc.createTextNode(p-> getLockFormula()));

        return element;
    }

    //@Override
    /*public*/ bool EnableLogixXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        EnableLogix* h = new EnableLogix(sys, uname);

        loadCommon(h, shared);

        QDomElement logixName = shared.firstChildElement("logix");
        if (!logixName.isNull()) {
            Logix* t = ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->getLogix(logixName.text().trimmed());
            if (t != nullptr) h->setLogix(t);
            else h->removeLogix();
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

            QDomElement logixLock = shared.firstChildElement("operationDirect");
            if (!logixLock.isNull()) {
                h->setOperationDirect(EnableLogix::Operation::valueOf(logixLock.text().trimmed()));
            }

            elem = shared.firstChildElement("operationReference");
            if (!elem.isNull()) h->setOperationReference(elem.text().trimmed());

            elem = shared.firstChildElement("operationLocalVariable");
            if (!elem.isNull()) h->setOperationLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("operationFormula");
            if (!elem.isNull()) h->setOperationFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }

//    /*private*/ final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(EnableLogixXml.class);
