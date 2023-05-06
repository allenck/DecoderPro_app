#include "expressionsignalheadxml.h"
#include "jmriconfigurexmlexception.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "expressionsignalhead.h"
#include "abstractsignalheadmanager.h"
#include "parserexception.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Handle XML configuration for ExpressionSignalHeadXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class ExpressionSignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  /*public*/  ExpressionSignalHeadXml::ExpressionSignalHeadXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ExpressionSignalHeadXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ExpressionSignalHeadXml::store(QObject* o) {
        ExpressionSignalHead* p = (ExpressionSignalHead*) o;

        QDomElement element = doc.createElement("ExpressionSignalHead");
        element.setAttribute("class", "jmri.jmrit.logixng,expressions.configurexml.ExpressionSignalHeadXml");
        QDomElement e1;
        element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<SignalHead*>* signalHead = p->getSignalHead();
        if (signalHead != nullptr) {
            element.appendChild(e1 = doc.createElement("signalHead")); e1.appendChild(doc.createTextNode(signalHead->getName()));
        }

        element.appendChild(e1 = doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1 = doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1 = doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1 = doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1 = doc.createElement("queryAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getQueryAddressing())));
        element.appendChild(e1 = doc.createElement("queryType")); e1.appendChild(doc.createTextNode(ExpressionSignalHead::QueryType::toString(p->getQueryType())));
        element.appendChild(e1 = doc.createElement("queryReference")); e1.appendChild(doc.createTextNode(p->getQueryReference()));
        element.appendChild(e1 = doc.createElement("queryLocalVariable")); e1.appendChild(doc.createTextNode(p->getQueryLocalVariable()));
        element.appendChild(e1 = doc.createElement("queryFormula")); e1.appendChild(doc.createTextNode(p->getQueryFormula()));

        element.appendChild(e1 = doc.createElement("appearanceAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAppearanceAddressing())));
        element.appendChild(e1 = doc.createElement("appearance")); e1.appendChild(doc.createTextNode(QString::number(p->getAppearance())));
        element.appendChild(e1 = doc.createElement("appearanceReference")); e1.appendChild(doc.createTextNode(p->getAppearanceReference()));
        element.appendChild(e1 = doc.createElement("appearanceLocalVariable")); e1.appendChild(doc.createTextNode(p->getAppearanceLocalVariable()));
        element.appendChild(e1 = doc.createElement("appearanceFormula")); e1.appendChild(doc.createTextNode(p->getAppearanceFormula()));

        signalHead = p->getExampleSignalHead();
        if (signalHead != nullptr) {
            element.appendChild(e1 = doc.createElement("exampleSignalHead")); e1.appendChild(doc.createTextNode(signalHead->getName()));
        }

        return element;
    }

    //@Override
    /*public*/  bool ExpressionSignalHeadXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionSignalHead* h = new ExpressionSignalHead(sys, uname);

        loadCommon(h, shared);

        QDomElement signalHeadName = shared.firstChildElement("signalHead");
        if (!signalHeadName.isNull()) {
            SignalHead* signalHead = ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName.text().trimmed());
            if (signalHead != nullptr) h->setSignalHead(signalHead);
            else h->removeSignalHead();
        }

        try {
            QDomElement elem = shared.firstChildElement("addressing");
            if (!elem.isNull()) {
                h->setAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("reference");
            if (!elem.isNull()) h->setReference(elem.text().trimmed());

            elem = shared.firstChildElement("localVariable");
            if (!elem.isNull()) h->setLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("formula");
            if (!elem.isNull()) h->setFormula(elem.text().trimmed());


            elem = shared.firstChildElement("queryAddressing");
            if (!elem.isNull()) {
                h->setQueryAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement queryType = shared.firstChildElement("queryType");
            if (!queryType.isNull()) {
                h->setQueryType(ExpressionSignalHead::QueryType::valueOf(queryType.text().trimmed()));
            }

            elem = shared.firstChildElement("queryReference");
            if (!elem.isNull()) h->setQueryReference(elem.text().trimmed());

            elem = shared.firstChildElement("queryLocalVariable");
            if (!elem.isNull()) h->setQueryLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("queryFormula");
            if (!elem.isNull()) h->setQueryFormula(elem.text().trimmed());


            elem = shared.firstChildElement("appearanceAddressing");
            if (!elem.isNull()) {
                h->setAppearanceAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement appearanceElement = shared.firstChildElement("appearance");
            if (!appearanceElement.isNull()) {
                try {
                    bool ok;
                    int appearance = appearanceElement.text().trimmed().toInt(&ok); if(!ok) throw new NumberFormatException("Illegal appearance");
                    h->setAppearance(appearance);
                } catch (NumberFormatException* e) {
                    log->error("cannot parse apperance: " + appearanceElement.text().trimmed(), e);
                }
            }

            elem = shared.firstChildElement("appearanceReference");
            if (!elem.isNull()) h->setAppearanceReference(elem.text().trimmed());

            elem = shared.firstChildElement("appearanceLocalVariable");
            if (!elem.isNull()) h->setAppearanceLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("appearanceFormula");
            if (!elem.isNull()) h->setAppearanceFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        signalHeadName = shared.firstChildElement("exampleSignalHead");
        if (!signalHeadName.isNull()) {
            SignalHead* signalHead = ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName.text().trimmed());
            if (signalHead != nullptr) h->setExampleSignalHead(signalHead);
            else h->removeSignalHead();
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionSignalHeadXml::log = LoggerFactory::getLogger("ExpressionSignalHeadXml");
