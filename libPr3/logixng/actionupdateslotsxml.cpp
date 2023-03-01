#include "actionupdateslotsxml.h"
#include "loconetsystemconnectionmemo.h"
#include "logixng/actionupdateslots.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"

/**
 * Handle XML configuration for ExpressionSlotUsage objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
///*public*/ class ActionUpdateSlotsXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ActionUpdateSlotsXml::ActionUpdateSlotsXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML(parent)
{

}

    /**
     * Default implementation for storing the contents of a ExpressionSlotUsage
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ActionUpdateSlotsXml::store(QObject* o) {
        ActionUpdateSlots* p = (ActionUpdateSlots*) o;

        QDomElement element = doc.createElement("ActionLoconetUpdateSlots");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        if (p->getMemo() != nullptr) {
            element.appendChild(e1=doc.createElement("systemConnection"));
                    e1.appendChild(doc.createTextNode(p->getMemo()->getSystemPrefix()));
        }

        return element;
    }

    //@Override
    /*public*/ bool ActionUpdateSlotsXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionUpdateSlots* h = new ActionUpdateSlots(sys, uname, nullptr);

        loadCommon(h, shared);

        QDomElement systemConnection = shared.firstChildElement("systemConnection");
        if (!systemConnection.isNull()) {
            QString systemConnectionName = systemConnection.text().trimmed();
            QList<QObject*>* systemConnections =
                    InstanceManager::getList("LocoNetSystemConnectionMemo");

            for (QObject* obj : *systemConnections) {
                LocoNetSystemConnectionMemo* memo = (LocoNetSystemConnectionMemo*)obj;
                if (memo->getSystemPrefix() ==(systemConnectionName)) {
                    h->setMemo(memo);
                    break;
                }
            }
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }

