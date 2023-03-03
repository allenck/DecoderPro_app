#include "actionentryexitxml.h"
#include "defaultdigitalactionmanager.h"
#include "entryexitpairs.h"
#include "logixng/actionentryexit.h"
#include "instancemanager.h"
#include "parserexception.h"

/**
 * Handle XML configuration for EntryExit objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2021
 */
// /*public*/ class ActionEntryExitXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ActionEntryExitXml::ActionEntryExitXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML{parent}
{

}


    /**
     * Default implementation for storing the contents of a EntryExit
     *
     * @param o Object to store, of type TriggerEntryExit
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ActionEntryExitXml::store(QObject* o) {
        ActionEntryExit* p = (ActionEntryExit*) o;

        QDomElement element = doc.createElement("ActionEntryExit");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.ActionEntryExitXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<DestinationPoints*>* entryExit = p->getDestinationPoints();
        if (entryExit != nullptr) {
            element.appendChild(e1=doc.createElement("destinationPoints")); e1.appendChild(doc.createTextNode(entryExit->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("operationAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getOperationAddressing())));
        element.appendChild(e1=doc.createElement("operationDirect")); e1.appendChild(doc.createTextNode(ActionEntryExit::Operation::toString(p->getOperationDirect())));
        element.appendChild(e1=doc.createElement("operationReference")); e1.appendChild(doc.createTextNode(p->getOperationReference()));
        element.appendChild(e1=doc.createElement("operationLocalVariable")); e1.appendChild(doc.createTextNode(p->getOperationLocalVariable()));
        element.appendChild(e1=doc.createElement("operationFormula")); e1.appendChild(doc.createTextNode(p->getLockFormula()));

        return element;
    }

    //@Override
    /*public*/ bool ActionEntryExitXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionEntryExit* h = new ActionEntryExit(sys, uname);

        loadCommon(h, shared);

        QDomElement entryExitName = shared.firstChildElement("destinationPoints");
        if (!entryExitName .isNull()) {
            DestinationPoints* t = (DestinationPoints*)((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->getNamedBean(entryExitName.text().trimmed())->self();
            if (t != nullptr) h->setDestinationPoints(t);
            else h->removeDestinationPoints();
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

            QDomElement entryExitLock = shared.firstChildElement("operationDirect");
            if (!entryExitLock.isNull()) {
                h->setOperationDirect(ActionEntryExit::Operation::valueOf(entryExitLock.text().trimmed()));
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
