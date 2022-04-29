#include "expressionreferencexml.h"
#include "instancemanager.h"
#include "expressionreference.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class ExpressionReferenceXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  /*public*/  ExpressionReferenceXml::ExpressionReferenceXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ExpressionReferenceXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ExpressionReferenceXml::store(QObject* o) {
        ExpressionReference* p = (ExpressionReference*) o;

        QDomElement element = doc.createElement("ExpressionReference");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.ExpressionReferenceXml");
        QDomElement e1;
        element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1 = doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));

        element.appendChild(e1 = doc.createElement("is_isNot")); e1.appendChild(doc.createTextNode(Is_IsNot_Enum::toString(p->get_Is_IsNot())));
        element.appendChild(e1 = doc.createElement("pointsTo")); e1.appendChild(doc.createTextNode(ExpressionReference::PointsTo::toString(p->getPointsTo())));

        return element;
    }

    //@Override
    /*public*/  bool ExpressionReferenceXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionReference* h = new ExpressionReference(sys, uname);

        loadCommon(h, shared);

        QDomElement reference = shared.firstChildElement("reference");
        if (!reference.isNull()) {
            h->setReference(reference.text().trimmed());
        }

        QDomElement is_IsNot = shared.firstChildElement("is_isNot");
        if (!is_IsNot.isNull()) {
            h->set_Is_IsNot(Is_IsNot_Enum::valueOf(is_IsNot.text().trimmed()));
        }

        QDomElement type = shared.firstChildElement("pointsTo");
        if (!type.isNull()) {
            h->setPointsTo(ExpressionReference::PointsTo::valueOf(type.text().trimmed()));
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
