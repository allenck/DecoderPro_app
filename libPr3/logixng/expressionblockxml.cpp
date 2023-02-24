#include "expressionblockxml.h"
#include "blockmanager.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionblock.h"
#include "instancemanager.h"
#include "joptionpane.h"
#include "parserexception.h"


/**
 * Handle XML configuration for ExpressionBlockXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright (C) 2021
 */
// /*public*/ class ExpressionBlockXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

//    /*static*/ /*final*/ ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.logixng.actions.ActionBundle");

    ExpressionBlockXml::ExpressionBlockXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {
    }

    /**
     * Default implementation for storing the contents of a ExpressionBlock
     *
     * @param o Object to store, of type ExpressionBlock
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ExpressionBlockXml::store(QObject* o) {
        ExpressionBlock* p = (ExpressionBlock*) o;

        QDomElement element = doc.createElement("ExpressionBlock");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName(*/"jmri.jmrit.logixng.expressions.configurexml.ExpressionBlockXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Block*>* block = p->getBlock();
        if (block != nullptr) {
            element.appendChild(e1=doc.createElement("block")); e1.appendChild(doc.createTextNode(block->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("is_isNot")); e1.appendChild(doc.createTextNode(Is_IsNot_Enum::toString( p->get_Is_IsNot())));

        element.appendChild(e1=doc.createElement("stateAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getStateAddressing())));
        element.appendChild(e1=doc.createElement("blockState")); e1.appendChild(doc.createTextNode(ExpressionBlock::BlockState::toString(p->getBeanState())));
        element.appendChild(e1=doc.createElement("stateReference")); e1.appendChild(doc.createTextNode(p->getStateReference()));
        element.appendChild(e1=doc.createElement("stateLocalVariable")); e1.appendChild(doc.createTextNode(p->getStateLocalVariable()));
        element.appendChild(e1=doc.createElement("stateFormula")); e1.appendChild(doc.createTextNode(p->getStateFormula()));

        element.appendChild(e1=doc.createElement("dataAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getDataAddressing())));
        element.appendChild(e1=doc.createElement("dataReference")); e1.appendChild(doc.createTextNode(p->getDataReference()));
        element.appendChild(e1=doc.createElement("dataLocalVariable")); e1.appendChild(doc.createTextNode(p->getDataLocalVariable()));
        element.appendChild(e1=doc.createElement("dataFormula")); e1.appendChild(doc.createTextNode(p->getDataFormula()));

        element.appendChild(e1=doc.createElement("blockValue")); e1.appendChild(doc.createTextNode(p->getBlockValue()));

        return element;
    }

    //@Override
    /*public*/ bool ExpressionBlockXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionBlock* h = new ExpressionBlock(sys, uname);

        loadCommon(h, shared);

        QDomElement blockName = shared.firstChildElement("block");
        if (!blockName.isNull()) {
            Block* t = (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))
                    ->getNamedBean(blockName.text().trimmed())->self();
            if (t != nullptr) h->setBlock(t);
            else h->removeBlock();
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

            QDomElement blockState = shared.firstChildElement("blockState");
            if (!blockState.isNull()) {

                QString state = blockState.text().trimmed();
                // deprecated 4.23.5 remove 4.25.1
                if (state == ("MemoryMatches")) {
                    state = "ValueMatches";
                }
                h->setBeanState(ExpressionBlock::BlockState::valueOf(state));
            }

            elem = shared.firstChildElement("stateReference");
            if (!elem.isNull()) h->setStateReference(elem.text().trimmed());

            elem = shared.firstChildElement("stateLocalVariable");
            if (!elem.isNull()) h->setStateLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("stateFormula");
            if (!elem.isNull()) h->setStateFormula(elem.text().trimmed());


            elem = shared.firstChildElement("dataAddressing");
            if (!elem.isNull()) {
                h->setDataAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("dataReference");
            if (!elem.isNull()) h->setDataReference(elem.text().trimmed());

            elem = shared.firstChildElement("dataLocalVariable");
            if (!elem.isNull()) h->setDataLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("dataFormula");
            if (!elem.isNull()) h->setDataFormula(elem.text().trimmed());

            elem = shared.firstChildElement("blockValue");
            if (!elem.isNull()) h->setBlockValue(elem.text().trimmed());

            // deprecated 4.23.5 remove 4.25.1
            elem = shared.firstChildElement("blockConstant");
            if (!elem.isNull()) h->setBlockValue(elem.text().trimmed());

            // deprecated 4.23.5 remove 4.25.1
            elem = shared.firstChildElement("blockMemory");
//             if (!elem.isNull()) h->setBlockMemory(elem.text().trimmed());
            if (!elem.isNull()) {
                QString memoryName = elem.text().trimmed();
                h->setBlockValue(">>> " + elem.text().trimmed() + " <<<");
//                if (!GraphicsEnvironment.isHeadless() && !Boolean.getBoolean("jmri.test.no-dialogs")) {
                    JOptionPane::showMessageDialog(nullptr,
                            tr("The block copy memory options have been removed.\n\nThe copy to memory is obsolete. \nThe copy from memory is replaced by the Reference tab. \nThe old memory reference is now a value enclosd in >>> and <<<."),
                            tr("Block to/from Memory Change Notification:") + " " + memoryName,
                            JOptionPane::WARNING_MESSAGE);
//                }
            }

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
