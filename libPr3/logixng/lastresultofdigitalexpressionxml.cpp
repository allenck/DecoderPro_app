#include "lastresultofdigitalexpressionxml.h"
#include "lastresultofdigitalexpression.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Handle XML configuration for LastResultOfDigitalExpression objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2021
 */
// /*public*/  class LastResultOfDigitalExpressionXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  LastResultOfDigitalExpressionXml::LastResultOfDigitalExpressionXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("LastResultOfDigitalExpressionXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement  LastResultOfDigitalExpressionXml::store(QObject* o) {
        LastResultOfDigitalExpression* p = (LastResultOfDigitalExpression*) o;

        QDomElement  element = doc.createElement("LastResultOfDigitalExpression");
        element.setAttribute("class", "jmri.jmrit.logixng.");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<DigitalExpressionBean*> *handle = p->getDigitalExpression();
        if (handle != nullptr) {
            element.appendChild(e1=doc.createElement("expression")); e1.appendChild(doc.createTextNode(handle->getName()));
        }

        return element;
    }

    //@Override
    /*public*/  bool LastResultOfDigitalExpressionXml::load(QDomElement  shared, QDomElement  perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        LastResultOfDigitalExpression* h = new LastResultOfDigitalExpression(sys, uname);

        loadCommon(h, shared);

        QDomElement  lightName = shared.firstChildElement("expression");
        if (!lightName.isNull()) {
            DigitalExpressionBean* t = (DigitalExpressionBean*)((DigitalExpressionManager*)InstanceManager
                    ::getDefault("DigitalExpressionManager"))
                    ->getNamedBean(lightName.text().trimmed())->self();
            if (t != nullptr) h->setDigitalExpression(t);
            else h->removeDigitalExpression();
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
