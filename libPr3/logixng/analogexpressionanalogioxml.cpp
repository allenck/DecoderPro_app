#include "analogexpressionanalogioxml.h"
#include "instancemanager.h"
#include "analogexpressionanalogio.h"
#include "proxyanalogiomanager.h"
#include "defaultanalogexpressionmanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class AnalogExpressionAnalogIOXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  AnalogExpressionAnalogIOXml::AnalogExpressionAnalogIOXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {

  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement AnalogExpressionAnalogIOXml::store(QObject* o) {
        AnalogExpressionAnalogIO* p = (AnalogExpressionAnalogIO*) o;

        QDomElement element = doc.createElement("AnalogExpressionAnalogIO");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configutexml.AnalogExpressionAnalogIOXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<AnalogIO*>* analogIO = p->getAnalogIO();
        if (analogIO != nullptr) {
            element.appendChild(e1=doc.createElement("analogIO")); e1.appendChild(doc.createTextNode(analogIO->getName()));
        }

        return element;
    }

    //@Override
    /*public*/  bool AnalogExpressionAnalogIOXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        AnalogExpressionAnalogIO* h;
        h = new AnalogExpressionAnalogIO(sys, uname);

        loadCommon(h, shared);

        QDomElement analogIOName = shared.firstChildElement("analogIO");
        if (!analogIOName .isNull()) {
            AnalogIO* m = (AnalogIO*)((ProxyAnalogIOManager*)InstanceManager::getDefault("AnalogIOManager"))->AbstractProxyManager::getNamedBean(analogIOName.text().trimmed());
            if (m != nullptr) h->setAnalogIO(m);
            else h->removeAnalogIO();
        }

        ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(h);
        return true;
    }
