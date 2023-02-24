#include "actionsignalmastxml.h"
#include "defaultsignalmastmanager.h"
#include "logixng/actionsignalmast.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "parserexception.h"
#include "loggerfactory.h"
/**
 * Handle XML configuration for ActionSignalMastXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/ class ActionSignalMastXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ActionSignalMastXml::ActionSignalMastXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML(parent){
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalMast
     *
     * @param o Object to store, of type TripleLightSignalMast
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ActionSignalMastXml::store(QObject* o) {
        ActionSignalMast* p = (ActionSignalMast*) o;

        QDomElement element = doc.createElement("ActionSignalMast");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.ActionSignalMastXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<SignalMast*>* signalMast = p->getSignalMast();
        if (signalMast != nullptr) {
            element.appendChild(e1=doc.createElement("signalMast")); e1.appendChild(doc.createTextNode(signalMast->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("operationAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getOperationAddressing())));
        element.appendChild(e1=doc.createElement("operationType")); e1.appendChild(doc.createTextNode(ActionSignalMast::OperationType::toString(p->getOperationType())));
        element.appendChild(e1=doc.createElement("operationReference")); e1.appendChild(doc.createTextNode(p->getOperationReference()));
        element.appendChild(e1=doc.createElement("operationLocalVariable")); e1.appendChild(doc.createTextNode(p->getOperationLocalVariable()));
        element.appendChild(e1=doc.createElement("operationFormula")); e1.appendChild(doc.createTextNode(p->getOperationFormula()));

        element.appendChild(e1=doc.createElement("aspectAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAspectAddressing())));
        element.appendChild(e1=doc.createElement("aspect")); e1.appendChild(doc.createTextNode(p->getAspect()));
        element.appendChild(e1=doc.createElement("aspectReference")); e1.appendChild(doc.createTextNode(p->getAspectReference()));
        element.appendChild(e1=doc.createElement("aspectLocalVariable")); e1.appendChild(doc.createTextNode(p->getAspectLocalVariable()));
        element.appendChild(e1=doc.createElement("aspectFormula")); e1.appendChild(doc.createTextNode(p->getAspectFormula()));

        signalMast = p->getExampleSignalMast();
        if (signalMast != nullptr) {
            element.appendChild(e1=doc.createElement("exampleSignalMast")); e1.appendChild(doc.createTextNode(signalMast->getName()));
        }

        return element;
    }

    //@Override
    /*public*/ bool ActionSignalMastXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionSignalMast* h = new ActionSignalMast(sys, uname);

        loadCommon(h, shared);

        QDomElement signalMastName = shared.firstChildElement("signalMast");
        if (!signalMastName.isNull()) {
            SignalMast* signalMast = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMastName.text().trimmed());
            if (signalMast != nullptr) h->setSignalMast(signalMast);
            else h->removeSignalMast();
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

            QDomElement queryType = shared.firstChildElement("operationType");
            if (!queryType.isNull()) {
                h->setOperationType(ActionSignalMast::OperationType::valueOf(queryType.text().trimmed()));
            }

            elem = shared.firstChildElement("operationReference");
            if (!elem.isNull()) h->setOperationReference(elem.text().trimmed());

            elem = shared.firstChildElement("operationLocalVariable");
            if (!elem.isNull()) h->setOperationLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("operationFormula");
            if (!elem.isNull()) h->setOperationFormula(elem.text().trimmed());


            elem = shared.firstChildElement("aspectAddressing");
            if (!elem.isNull()) {
                h->setAspectAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement aspectElement = shared.firstChildElement("aspect");
            if (!aspectElement.isNull()) {
                try {
                    h->setAspect(aspectElement.text().trimmed());
                } catch (NumberFormatException* e) {
                    log->error("cannot parse aspect: " + aspectElement.text().trimmed(), e);
                }
            }

            elem = shared.firstChildElement("aspectReference");
            if (!elem.isNull()) h->setAspectReference(elem.text().trimmed());

            elem = shared.firstChildElement("aspectLocalVariable");
            if (!elem.isNull()) h->setAspectLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("aspectFormula");
            if (!elem.isNull()) h->setAspectFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        signalMastName = shared.firstChildElement("exampleSignalMast");
        if (!signalMastName.isNull()) {
            SignalMast* signalMast = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMastName.text().trimmed());
            if (signalMast != nullptr) h->setExampleSignalMast(signalMast);
            else h->removeSignalMast();
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionSignalMastXml::log = LoggerFactory::getLogger("ActionSignalMastXml");
