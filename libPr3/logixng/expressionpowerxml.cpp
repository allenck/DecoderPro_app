#include "expressionpowerxml.h"
#include "expressionpower.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Handle XML configuration for ExpressionPower objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2021
 */
///*public*/  class ExpressionPowerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  ExpressionPowerXml::ExpressionPowerXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ExpressionPowerXml");
  }


    /**
     * Default implementation for storing the contents of a ExpressionPower
     *
     * @param o Object to store, of type ExpressionPower
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ExpressionPowerXml::store(QObject* o) {
        ExpressionPower* p = (ExpressionPower*) o;

        QDomElement element = doc.createElement("ExpressionPower");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.ExpressionPowerXml");
        QDomElement e1;
        element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1 = doc.createElement("is_isNot")); e1.appendChild( doc.createTextNode(Is_IsNot_Enum::toString(p->get_Is_IsNot())));

        element.appendChild(e1 = doc.createElement("powerState")); e1.appendChild(doc.createTextNode(ExpressionPower::PowerState::toString(p->getBeanState())));

        return element;
    }

    //@Override
    /*public*/  bool ExpressionPowerXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException */{
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionPower* h = new ExpressionPower(sys, uname);

        loadCommon(h, shared);

        QDomElement is_IsNot = shared.firstChildElement("is_isNot");
        if (!is_IsNot.isNull()) {
            h->set_Is_IsNot(Is_IsNot_Enum::valueOf(is_IsNot.text().trimmed()));
        }

        QDomElement powerState = shared.firstChildElement("powerState");
        if (!powerState.isNull()) {
            h->setBeanState(ExpressionPower::PowerState::valueOf(powerState.text().trimmed()));
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
