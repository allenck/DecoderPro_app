#include "expressionconditionalxml.h"
#include "defaultconditionalmanager.h"
#include "jmriconfigurexmlexception.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionconditional.h"
#include "instancemanager.h"
#include "logixng/parserexception.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/ class ExpressionConditionalXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ExpressionConditionalXml::ExpressionConditionalXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML(parent)
{

}


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ExpressionConditionalXml::store(QObject* o) {
        ExpressionConditional* p = (ExpressionConditional*) o;

//        if (p->getLightName() == null) throw new RuntimeException("aaaaa");

        QDomElement element = doc.createElement("ExpressionConditional");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.expressions.configutexml.ExpressionConditionalXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Conditional*>* conditional = p->getConditional();
        if (conditional != nullptr) {
            element.appendChild(e1=doc.createElement("conditional")); e1.appendChild(doc.createTextNode(conditional->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("is_isNot")); e1.appendChild(doc.createTextNode(Is_IsNot_Enum::toString(p->get_Is_IsNot())));

        element.appendChild(e1=doc.createElement("stateAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getStateAddressing())));
        element.appendChild(e1=doc.createElement("conditionalState")); e1.appendChild(doc.createTextNode(ExpressionConditional::ConditionalState::toString(p->getConditionalState())));
        element.appendChild(e1=doc.createElement("stateReference")); e1.appendChild(doc.createTextNode(p->getStateReference()));
        element.appendChild(e1=doc.createElement("stateLocalVariable")); e1.appendChild(doc.createTextNode(p->getStateLocalVariable()));
        element.appendChild(e1=doc.createElement("stateFormula")); e1.appendChild(doc.createTextNode(p->getStateFormula()));

        return element;
    }

    //@Override
    /*public*/ bool ExpressionConditionalXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionConditional* h = new ExpressionConditional(sys, uname);

        loadCommon(h, shared);

        QDomElement conditionalName = shared.firstChildElement("conditional");
        if (!conditionalName.isNull()) {
            Conditional* t = ((DefaultConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getConditional(conditionalName.text().trimmed());
            if (t != nullptr) h->setConditional(t);
            else h->removeConditional();
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
                h->set_Is_IsNot(Is_IsNot_Enum::valueOf(is_IsNot.text().trimmed()));
            }


            elem = shared.firstChildElement("stateAddressing");
            if (!elem.isNull()) {
                h->setStateAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement conditionalState = shared.firstChildElement("conditionalState");
            if (!conditionalState.isNull()) {
                h->setConditionalState(ExpressionConditional::ConditionalState::valueOf(conditionalState.text().trimmed()));
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
