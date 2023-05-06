#include "expressionoblockxml.h"
#include "jmriconfigurexmlexception.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionoblock.h"
#include "instancemanager.h"
#include "logixng/parserexception.h"
#include "oblockmanager.h"
/**
 * Handle XML configuration for ExpressionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/ class ExpressionOBlockXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ExpressionOBlockXml::ExpressionOBlockXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML{parent}
{

}


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleOBlockSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ExpressionOBlockXml::store(QObject* o) {
        ExpressionOBlock* p = (ExpressionOBlock*) o;

        QDomElement element = doc.createElement("ExpressionOBlock");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit/logixng/expressions.configurexml.ExpressionOBlockXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<OBlock*>* oblock = p->getOBlock();
        if (oblock != nullptr) {
            element.appendChild(e1=doc.createElement("oblock")); e1.appendChild(doc.createTextNode(oblock->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("is_isNot")); e1.appendChild(doc.createTextNode(Is_IsNot_Enum::toString(p->get_Is_IsNot())));

        element.appendChild(e1=doc.createElement("stateAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getStateAddressing())));
        element.appendChild(e1=doc.createElement("oblockStatus")); e1.appendChild(doc.createTextNode(OBlock::OBlockStatus::toString(p->getBeanState())));
        element.appendChild(e1=doc.createElement("stateReference")); e1.appendChild(doc.createTextNode(p->getStateReference()));
        element.appendChild(e1=doc.createElement("stateLocalVariable")); e1.appendChild(doc.createTextNode(p->getStateLocalVariable()));
        element.appendChild(e1=doc.createElement("stateFormula")); e1.appendChild(doc.createTextNode(p->getStateFormula()));

        return element;
    }

    //@Override
    /*public*/ bool ExpressionOBlockXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionOBlock* h = new ExpressionOBlock(sys, uname);

        loadCommon(h, shared);

        QDomElement oblockName = shared.firstChildElement("oblock");
        if (!oblockName.isNull()) {
            OBlock* t = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(oblockName.text().trimmed());
            if (t != nullptr) h->setOBlock(t);
            else h->removeOBlock();
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

            QDomElement oblockState = shared.firstChildElement("oblockStatus");
            if (!oblockState.isNull()) {
                h->setBeanState(OBlock::OBlockStatus::valueOf(oblockState.text().trimmed()));
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
