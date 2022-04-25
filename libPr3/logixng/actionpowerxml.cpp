#include "actionpowerxml.h"
#include "actionpower.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"


/**
 * Handle XML configuration for ActionPower objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2021
 */
///*public*/  class ActionPowerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  ActionPowerXml::ActionPowerXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
    {
     setObjectName("ActionPowerXml");
    }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TriplePowerSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionPowerXml::store(QObject* o) {
        ActionPower* p = (ActionPower*) o;

        QDomElement element = doc.createElement("ActionPower");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.ActionPowerXml");
        QDomElement e1;
        element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1 = doc.createElement("powerState")); e1.appendChild(doc.createTextNode(ActionPower::PowerState::toString(p->getBeanState())));

        return element;
    }

    //@Override
    /*public*/  bool ActionPowerXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionPower* h = new ActionPower(sys, uname);

        loadCommon(h, shared);

        QDomElement powerState = shared.firstChildElement("powerState");
        if (!powerState.isNull()) {
            h->setBeanState(ActionPower::PowerState::valueOf(powerState.text().trimmed()));
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
