#include "falsexml.h"
#include "false.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class FalseXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  FalseXml::FalseXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent) {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleFalseSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement FalseXml::store(QObject* o) {
        False* p = (False*) o;

        QDomElement element = doc.createElement("False");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.False.xml");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName())));

        storeCommon(p, element);

        return element;
    }

    //@Override
    /*public*/  bool FalseXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        DigitalExpressionBean* h = new False(sys, uname);

        loadCommon(h, shared);

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
