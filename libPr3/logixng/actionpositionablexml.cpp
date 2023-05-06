#include "actionpositionablexml.h"
#include "instancemanager.h"
#include "actionpositionable.h"
#include "defaultdigitalactionmanager.h"
#include "jmriconfigurexmlexception.h"
#include "parserexception.h"

/**
 * Handle XML configuration for ActionPositionable objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2021
 */
// /*public*/  class ActionPositionableXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ActionPositionableXml::ActionPositionableXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 setObjectName("ActionPositionableXml");
}

    /**
     * Default implementation for storing the contents of a ActionPositionable
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionPositionableXml::store(QObject* o) {
        ActionPositionable* p = (ActionPositionable*) o;

        QDomElement element = doc.createElement("DisplayActionPositionable");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.ActionPositionableXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QString editorName = p->getEditorName();
        if (editorName != "") {
            element.appendChild(e1=doc.createElement("editorName")); e1.appendChild(doc.createTextNode(editorName));
        }

        QString positionableName = p->getPositionableName();
        if (positionableName != "") {
            element.appendChild(e1=doc.createElement("positionableName")); e1.appendChild(doc.createTextNode(positionableName));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("stateAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getStateAddressing())));
        element.appendChild(e1=doc.createElement("operation")); e1.appendChild(doc.createTextNode(ActionPositionable::Operation::toString(p->getOperation())));
        element.appendChild(e1=doc.createElement("stateReference")); e1.appendChild(doc.createTextNode(p->getStateReference()));
        element.appendChild(e1=doc.createElement("stateLocalVariable")); e1.appendChild(doc.createTextNode(p->getStateLocalVariable()));
        element.appendChild(e1=doc.createElement("stateFormula")); e1.appendChild(doc.createTextNode(p->getStateFormula()));

        return element;
    }

    //@Override
    /*public*/  bool ActionPositionableXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionPositionable* h = new ActionPositionable(sys, uname);

        loadCommon(h, shared);

        QDomElement elem = shared.firstChildElement("editorName");
        if (!elem.isNull()) {
            h->setEditor(elem.text().trimmed());
        }

        elem = shared.firstChildElement("positionableName");
        if (!elem.isNull()) {
            h->setPositionable(elem.text().trimmed());
        }

        try {
            elem = shared.firstChildElement("addressing");
            if (!elem.isNull()) {
                h->setAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("reference");
            if (!elem.isNull()) h->setReference(elem.text().trimmed());

            elem = shared.firstChildElement("localVariable");
            if (!elem.isNull()) h->setLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("formula");
            if (!elem.isNull()) h->setFormula(elem.text().trimmed());


            elem = shared.firstChildElement("stateAddressing");
            if (!elem.isNull()) {
                h->setStateAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement isControlling = shared.firstChildElement("operation");
            if (!isControlling.isNull()) {
                h->setOperation(ActionPositionable::Operation::valueOf(isControlling.text().trimmed()));
            }

            elem = shared.firstChildElement("stateReference");
            if (!elem.isNull()) h->setStateReference(elem.text().trimmed());

            elem = shared.firstChildElement("stateLocalVariable");
            if (!elem.isNull()) h->setStateLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("stateFormula");
            if (!elem.isNull()) h->setStateFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
