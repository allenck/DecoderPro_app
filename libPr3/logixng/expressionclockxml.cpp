#include "expressionclockxml.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionclock.h"
#include "loggerfactory.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/ class ExpressionClockXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    ExpressionClockXml::ExpressionClockXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {

    }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ExpressionClockXml::store(QObject* o) {
        ExpressionClock* p = (ExpressionClock*) o;

        QDomElement element = doc.createElement("ExpressionClock");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.expressions/configurexml.ExpressionClockXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1=doc.createElement("is_isNot")); e1.appendChild(doc.createTextNode(Is_IsNot_Enum::toString(p->get_Is_IsNot())));
        element.appendChild(e1=doc.createElement("type")); e1.appendChild(doc.createTextNode(ExpressionClock::Type::toString(p->getType())));
        element.appendChild(e1=doc.createElement("beginTime")); e1.appendChild(doc.createTextNode(QString::number(p->getBeginTime())));
        element.appendChild(e1=doc.createElement("endTime")); e1.appendChild(doc.createTextNode(QString::number(p->getEndTime())));

        return element;
    }

    //@Override
    /*public*/ bool ExpressionClockXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionClock* h = new ExpressionClock(sys, uname);

        loadCommon(h, shared);

        QDomElement is_IsNot = shared.firstChildElement("is_isNot");
        if (!is_IsNot.isNull()) {
            h->set_Is_IsNot(Is_IsNot_Enum::valueOf(is_IsNot.text().trimmed()));
        }

        QDomElement type = shared.firstChildElement("type");
        if (!type.isNull()) {
            h->setType(ExpressionClock::Type::valueOf(type.text().trimmed()));
        }

        int beginTime = 0;
        int endTime = 0;
        QDomElement beginTimeElement = shared.firstChildElement("beginTime");
        QDomElement endTimeElement = shared.firstChildElement("endTime");

        if (!beginTimeElement.isNull()) {
            try {
                bool ok;
                beginTime = beginTimeElement.text().trimmed().toInt(&ok); if(!ok) throw new NumberFormatException();
            } catch (NumberFormatException* e) {
                log->error("cannot parse beginTime: " + beginTimeElement.text().trimmed(), e);
            }
        }
        if (!endTimeElement.isNull()) {
            try {
                bool ok;
                endTime =  endTimeElement.text().trimmed().toInt(&ok); if(!ok) throw new NumberFormatException();
                h->setRange(beginTime, endTime);
            } catch (NumberFormatException* e) {
                log->error("cannot parse endTime: " + endTimeElement.text().trimmed(), e);
            }
        }
        h->setRange(beginTime, endTime);

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionClockXml::log = LoggerFactory::getLogger("ExpressionClockXml");

