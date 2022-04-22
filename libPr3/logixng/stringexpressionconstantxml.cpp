#include "stringexpressionconstantxml.h"
#include "stringexpressionconstant.h"
#include "instancemanager.h"
#include "defaultstringexpressionmanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class StringExpressionConstantXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  StringExpressionConstantXml::StringExpressionConstantXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
    {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement StringExpressionConstantXml::store(QObject* o) {
        StringExpressionConstant* p = (StringExpressionConstant*) o;

        QDomElement element = doc.createElement("StringExpressionConstant");
        element.setAttribute("class", "jmri.jmrit.logixng.espressions.configurexml.StringExpressionConstantXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1=doc.createElement("value")); e1.appendChild(doc.createTextNode(p->getValue()));

        return element;
    }

    //@Override
    /*public*/  bool StringExpressionConstantXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        StringExpressionConstant* h;
        h = new StringExpressionConstant(sys, uname);

        loadCommon(h, shared);

        QDomElement valueElement = shared.firstChildElement("value");
        h->setValue(valueElement.text().trimmed());

        ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->registerExpression(h);
        return true;
    }
