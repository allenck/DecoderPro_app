#include "expressionturnoutxml.h"
#include "expressionturnout.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
#include "proxyturnoutmanager.h"
#include "parserexception.h"
/**
 * Handle XML configuration for ExpressionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class ExpressionTurnoutXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/ ExpressionTurnoutXml::ExpressionTurnoutXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
    {
     setObjectName("ExpressionTurnoutXml");
    }

    /**
     * Default implementation for storing the contents of a ExpressionTurnout
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ExpressionTurnoutXml::store(QObject* o) {
        ExpressionTurnout* p = (ExpressionTurnout*) o;

        QDomElement element = doc.createElement("ExpressionTurnout");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.ExpressionTurnoutXml");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName())));

        storeCommon(p, element);

        NamedBeanHandle<Turnout*>* turnout = p->getTurnout();
        if (turnout != nullptr) {
            element.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(turnout->getName())));
        }

        element.appendChild(doc.createElement("addressing").appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing()))));
        element.appendChild(doc.createElement("reference").appendChild(doc.createTextNode(p->getReference())));
        element.appendChild(doc.createElement("localVariable").appendChild(doc.createTextNode(p->getLocalVariable())));
        element.appendChild(doc.createElement("formula").appendChild(doc.createTextNode(p->getFormula())));

        element.appendChild(doc.createElement("is_isNot").appendChild(doc.createTextNode(Is_IsNot_Enum::toString(p->get_Is_IsNot()))));

        element.appendChild(doc.createElement("stateAddressing").appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getStateAddressing()))));
        element.appendChild(doc.createElement("turnoutState").appendChild(doc.createTextNode(ExpressionTurnout::TurnoutState::toString(p->getBeanState()))));
        element.appendChild(doc.createElement("stateReference").appendChild(doc.createTextNode(p->getStateReference())));
        element.appendChild(doc.createElement("stateLocalVariable").appendChild(doc.createTextNode(p->getStateLocalVariable())));
        element.appendChild(doc.createElement("stateFormula").appendChild(doc.createTextNode(p->getStateFormula())));

        return element;
    }

    //@Override
    /*public*/  bool ExpressionTurnoutXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionTurnout* h = new ExpressionTurnout(sys, uname);

        loadCommon(h, shared);

        QDomElement turnoutName = shared.firstChildElement("turnout");
        if (!turnoutName.isNull()) {
            Turnout* t = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getTurnout(turnoutName.text().trimmed());
            if (t != nullptr) h->setTurnout(t);
            else h->removeTurnout();
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


            QDomElement is_IsNot = shared.firstChildElement("is_isNot");
            if (!is_IsNot.isNull()) {
                h->set_Is_IsNot(Is_IsNot_Enum::get(is_IsNot.text().trimmed()));
            }


            elem = shared.firstChildElement("stateAddressing");
            if (!elem.isNull()) {
                h->setStateAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement turnoutState = shared.firstChildElement("turnoutState");
            if (!turnoutState.isNull()) {
                h->setBeanState(ExpressionTurnout::TurnoutState::valueOf(turnoutState.text().trimmed()));
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

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
