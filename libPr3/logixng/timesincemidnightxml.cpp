#include "timesincemidnightxml.h"
#include "defaultanalogexpressionmanager.h"
#include "timesincemidnight.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class TimeSinceMidnightXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

TimeSinceMidnightXml::TimeSinceMidnightXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{
 setObjectName("TimeSinceMidnightXml");
}

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement TimeSinceMidnightXml::store(QObject* o) {
        TimeSinceMidnight* p = (TimeSinceMidnight*) o;

        QDomElement element = doc.createElement("TimeSinceMidnight");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.TimeSinceMidnightXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1=doc.createElement("type")); e1.appendChild(doc.createTextNode(TimeSinceMidnight::Type::toString(p->getType())));

        return element;
    }

    //@Override
    /*public*/  bool TimeSinceMidnightXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        TimeSinceMidnight* h = new TimeSinceMidnight(sys, uname);

        loadCommon(h, shared);

        QDomElement type = shared.firstChildElement("type");
        if (!type.isNull()) {
            h->setType(TimeSinceMidnight::Type::getType(type.text().trimmed()));
        }

        ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(h);
        return true;
    }
