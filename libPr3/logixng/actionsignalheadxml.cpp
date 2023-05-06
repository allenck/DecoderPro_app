#include "actionsignalheadxml.h"
#include "instancemanager.h"
#include "jmriconfigurexmlexception.h"
#include "loggerfactory.h"
#include "actionsignalhead.h"
#include "abstractsignalheadmanager.h"
#include "parserexception.h"
#include "defaultdigitalactionmanager.h"

/**
 * Handle XML configuration for ActionSignalHeadXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class ActionSignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  ActionSignalHeadXml::ActionSignalHeadXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ActionSignalHeadXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionSignalHeadXml::store(QObject* o) {
        ActionSignalHead* p = (ActionSignalHead*) o;

        QDomElement element = doc.createElement("ActionSignalHead");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.ActionSignalHeadXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<SignalHead*>* signalHead = p->getSignalHead();
        if (signalHead != nullptr) {
            element.appendChild(e1=doc.createElement("signalHead")); e1.appendChild(doc.createTextNode(signalHead->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("operationAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getOperationAddressing())));
        element.appendChild(e1=doc.createElement("operationType")); e1.appendChild(doc.createTextNode(ActionSignalHead::OperationType::toString(p->getOperationType())));
        element.appendChild(e1=doc.createElement("operationReference")); e1.appendChild(doc.createTextNode(p->getOperationReference()));
        element.appendChild(e1=doc.createElement("operationLocalVariable")); e1.appendChild(doc.createTextNode(p->getOperationLocalVariable()));
        element.appendChild(e1=doc.createElement("operationFormula")); e1.appendChild(doc.createTextNode(p->getOperationFormula()));

        element.appendChild(e1=doc.createElement("appearanceAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAppearanceAddressing())));
        element.appendChild(e1=doc.createElement("appearance")); e1.appendChild(doc.createTextNode(QString::number(p->getAppearance())));
        element.appendChild(e1=doc.createElement("appearanceReference")); e1.appendChild(doc.createTextNode(p->getAppearanceReference()));
        element.appendChild(e1=doc.createElement("appearanceLocalVariable")); e1.appendChild(doc.createTextNode(p->getAppearanceLocalVariable()));
        element.appendChild(e1=doc.createElement("appearanceFormula")); e1.appendChild(doc.createTextNode(p->getAppearanceFormula()));

        signalHead = p->getExampleSignalHead();
        if (signalHead != nullptr) {
            element.appendChild(e1=doc.createElement("exampleSignalHead")); e1.appendChild(doc.createTextNode(signalHead->getName()));
        }

        return element;
    }

    //@Override
    /*public*/  bool ActionSignalHeadXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionSignalHead* h = new ActionSignalHead(sys, uname);

        loadCommon(h, shared);

        QDomElement signalHeadName = shared.firstChildElement("signalHead");
        if (!signalHeadName.isNull()) {
            SignalHead* signalHead = ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName.text().trimmed());
            if (signalHead != nullptr) h->setSignalHead(signalHead);
            else h->removeSignalHead();
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
                h->setOperationType(ActionSignalHead::OperationType::valueOf(queryType.text().trimmed()));
            }

            elem = shared.firstChildElement("operationReference");
            if (!elem.isNull()) h->setOperationReference(elem.text().trimmed());

            elem = shared.firstChildElement("operationLocalVariable");
            if (!elem.isNull()) h->setOperationLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("operationFormula");
            if (!elem.isNull()) h->setOperationFormula(elem.text().trimmed());


            elem = shared.firstChildElement("appearanceAddressing");
            if (!elem.isNull()) {
                h->setAppearanceAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement appearanceElement = shared.firstChildElement("appearance");
            if (!appearanceElement.isNull()) {
                try {
                    int appearance = appearanceElement.text().trimmed().toInt();
                    h->setAppearance(appearance);
                } catch (NumberFormatException* e) {
                    log->error("cannot parse apperance: " + appearanceElement.text().trimmed(), e);
                }
            }

            elem = shared.firstChildElement("appearanceReference");
            if (!elem.isNull()) h->setAppearanceReference(elem.text().trimmed());

            elem = shared.firstChildElement("appearanceLocalVariable");
            if (!elem.isNull()) h->setAppearanceLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("appearanceFormula");
            if (!elem.isNull()) h->setAppearanceFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        signalHeadName = shared.firstChildElement("exampleSignalHead");
        if (!signalHeadName.isNull()) {
            SignalHead* signalHead = ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName.text().trimmed());
            if (signalHead != nullptr) h->setExampleSignalHead(signalHead);
            else h->removeSignalHead();
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionSignalHeadXml::log = LoggerFactory::getLogger("ActionSignalHeadXml");
