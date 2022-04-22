#include "analogexpressionconstantxml.h"
#include "analogexpressionconstant.h"
#include "defaultanalogexpressionmanager.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class AnalogExpressionConstantXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  AnalogExpressionConstantXml::AnalogExpressionConstantXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("AnalogExpressionConstantXml");
  }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement AnalogExpressionConstantXml::store(QObject* o) {
        AnalogExpressionConstant* p = (AnalogExpressionConstant*) o;

        QDomElement element = doc.createElement("AnalogExpressionConstant");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.AnalogExpressionConstantXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1=doc.createElement("value")); e1.appendChild(doc.createTextNode(QString::number(p->getValue())));

        return element;
    }

    //@Override
    /*public*/  bool AnalogExpressionConstantXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException */{     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        AnalogExpressionConstant* h;
        h = new AnalogExpressionConstant(sys, uname);

        loadCommon(h, shared);

        QDomElement valueElement = shared.firstChildElement("value");
        h->setValue(valueElement.text().trimmed().toDouble());

        ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(h);
        return true;
    }
