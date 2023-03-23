#include "actionclearslotsxml.h"
#include "instancemanager.h"
#include "loconetsystemconnectionmemo.h"
#include "logixng/actionclearslots.h"
#include "logixng/defaultdigitalactionmanager.h"

/**
 * Handle XML configuration for ExpressionSlotUsage objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
// /*public*/ class ActionClearSlotsXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ActionClearSlotsXml::ActionClearSlotsXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML{parent}
{

}

    /**
     * Default implementation for storing the contents of a ExpressionSlotUsage
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ActionClearSlotsXml::store(QObject* o) {
        ActionClearSlots* p = (ActionClearSlots*) o;

        QDomElement element = doc.createElement("ActionLoconetClearSlots");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.ActionClearSlotsXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        if (p->getMemo() != nullptr) {
            element.appendChild(e1=doc.createElement("systemConnection"));
                                e1.appendChild(doc.createTextNode(p->getMemo()->getSystemPrefix()));
        }

        return element;
    }

    //@Override
    /*public*/ bool ActionClearSlotsXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionClearSlots* h = new ActionClearSlots(sys, uname, nullptr);

        loadCommon(h, shared);

        QDomElement systemConnection = shared.firstChildElement("systemConnection");
        if (!systemConnection.isNull()) {
            QString systemConnectionName = systemConnection.text().trimmed();
            QList<QObject*>* systemConnections =
                    InstanceManager::getList("LocoNetSystemConnectionMemo");

            for (QObject* obj : *systemConnections) {
                LocoNetSystemConnectionMemo* memo = (LocoNetSystemConnectionMemo*)obj;
                if (memo->getSystemPrefix() == (systemConnectionName)) {
                    h->setMemo(memo);
                    break;
                }
            }
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
