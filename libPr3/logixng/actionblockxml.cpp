#include "actionblockxml.h"
#include "actionblock.h"
#include "instancemanager.h"
#include "abstractblockmanager.h"
#include "joptionpane.h"
#include "parserexception.h"
#include "defaultdigitalactionmanager.h"

/**
 * Handle XML configuration for Block objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright (C) 2021
 */
///*public*/  class ActionBlockXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    //static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.logixng.actions.ActionBundle");

  ActionBlockXml::ActionBlockXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ActionBlockXml");
  }


    /**
     * Default implementation for storing the contents of a Block
     *
     * @param o Object to store, of type TriggerBlock
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionBlockXml::store(QObject* o) {
        ActionBlock* p = (ActionBlock*) o;

        QDomElement element = doc.createElement("ActionBlock");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.ActionBlockXml");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName())));

        storeCommon(p, element);

        NamedBeanHandle<Block*>* block = p->getBlock();
        if (block != nullptr) {
            element.appendChild(doc.createElement("block").appendChild(doc.createTextNode(block->getName())));
        }

        element.appendChild(doc.createElement("addressing").appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing()))));
        element.appendChild(doc.createElement("reference").appendChild(doc.createTextNode(p->getReference())));
        element.appendChild(doc.createElement("localVariable").appendChild(doc.createTextNode(p->getLocalVariable())));
        element.appendChild(doc.createElement("formula").appendChild(doc.createTextNode(p->getFormula())));

        element.appendChild(doc.createElement("operationAddressing").appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getOperationAddressing()))));
        element.appendChild(doc.createElement("operationDirect").appendChild(doc.createTextNode(ActionBlock::DirectOperation::toString(p->getOperationDirect()))));
        element.appendChild(doc.createElement("operationReference").appendChild(doc.createTextNode(p->getOperationReference())));
        element.appendChild(doc.createElement("operationLocalVariable").appendChild(doc.createTextNode(p->getOperationLocalVariable())));
        element.appendChild(doc.createElement("operationFormula").appendChild(doc.createTextNode(p->getOperationFormula())));

        element.appendChild(doc.createElement("dataAddressing").appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getDataAddressing()))));
        element.appendChild(doc.createElement("dataReference").appendChild(doc.createTextNode(p->getDataReference())));
        element.appendChild(doc.createElement("dataLocalVariable").appendChild(doc.createTextNode(p->getDataLocalVariable())));
        element.appendChild(doc.createElement("dataFormula").appendChild(doc.createTextNode(p->getDataFormula())));

        element.appendChild(doc.createElement("blockValue").appendChild(doc.createTextNode(p->getBlockValue())));

        return element;
    }

    //@Override
    /*public*/  bool ActionBlockXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionBlock* h = new ActionBlock(sys, uname);

        loadCommon(h, shared);

        QDomElement blockName = shared.firstChildElement("block");
        if (!blockName.isNull()) {
            Block* t = (Block*)((AbstractBlockManager*)InstanceManager::getDefault("BlockManager"))->getNamedBean(blockName.text().trimmed())->self();
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


            elem = shared.firstChildElement("operationAddressing");
            if (!elem.isNull()) {
                h->setOperationAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("operationDirect");
            if (!elem.isNull()) {
                QString oper = elem.text().trimmed();
                // deprecated 4.23.5 remove 4.25.1
                if (oper==("SetToConstant") || oper == ("CopyFromMemory") || oper ==("CopyToMemory")) {
                    oper = "SetValue";
                }
                h->setOperationDirect(ActionBlock::DirectOperation::valueOf(oper));
            }

            elem = shared.firstChildElement("operationReference");
            if (!elem.isNull()) h->setOperationReference(elem.text().trimmed());

            elem = shared.firstChildElement("operationLocalVariable");
            if (!elem.isNull()) h->setOperationLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("operationFormula");
            if (!elem.isNull()) h->setOperationFormula(elem.text().trimmed());


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
            if (!elem.isNull()) {
                QString memoryName = elem.text().trimmed();
                h->setBlockValue(">>> " + elem.text().trimmed() + " <<<");
//                if (/*!GraphicsEnvironment.isHeadless() &&*/ !Boolean.getBoolean("jmri.test.no-dialogs")) {
                    JOptionPane::showMessageDialog(nullptr,
                            tr("The copy from memory is replaced by the Reference tab. \nThe old memory reference is now a value enclosd in >>> and <<<."),
                            tr("Block to/from Memory Change Notification:") + " " + memoryName,
                            JOptionPane::WARNING_MESSAGE);
//                }
            }

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
