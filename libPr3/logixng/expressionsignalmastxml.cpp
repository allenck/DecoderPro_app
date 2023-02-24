#include "expressionsignalmastxml.h"
#include "defaultsignalmastmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionsignalmast.h"
#include "signalmast.h"
#include "parserexception.h"

/**
 * Handle XML configuration for ExpressionSignalMastXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/ class ExpressionSignalMastXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    ExpressionSignalMastXml::ExpressionSignalMastXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalMast
     *
     * @param o Object to store, of type TripleLightSignalMast
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement ExpressionSignalMastXml::store(QObject* o) {
        ExpressionSignalMast* p = (ExpressionSignalMast*) o;

        QDomElement element = doc.createElement("ExpressionSignalMast");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<SignalMast*>* signalMast = p->getSignalMast();
        if (signalMast != nullptr) {
            element.appendChild(e1=doc.createElement("signalMast")); e1.appendChild(doc.createTextNode(signalMast->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("queryAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getQueryAddressing())));
        element.appendChild(e1=doc.createElement("queryType")); e1.appendChild(doc.createTextNode(ExpressionSignalMast::QueryType::toString(p->getQueryType())));
        element.appendChild(e1=doc.createElement("queryReference")); e1.appendChild(doc.createTextNode(p->getQueryReference()));
        element.appendChild(e1=doc.createElement("queryLocalVariable")); e1.appendChild(doc.createTextNode(p->getQueryLocalVariable()));
        element.appendChild(e1=doc.createElement("queryFormula")); e1.appendChild(doc.createTextNode(p->getQueryFormula()));

        element.appendChild(e1=doc.createElement("aspectAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAspectAddressing())));
        element.appendChild(e1=doc.createElement("aspect")); e1.appendChild(doc.createTextNode(p->getAspect()));
        element.appendChild(e1=doc.createElement("aspectReference")); e1.appendChild(doc.createTextNode(p->getAspectReference()));
        element.appendChild(e1=doc.createElement("aspectLocalVariable")); e1.appendChild(doc.createTextNode(p->getAspectLocalVariable()));
        element.appendChild(e1=doc.createElement("aspectFormula")); e1.appendChild(doc.createTextNode(p->getAspectFormula()));

        signalMast = p->getExampleSignalMast();
        if (signalMast != nullptr) {
            element.appendChild(e1=doc.createElement("exampleSignalMast")); e1.appendChild(doc.createTextNode(signalMast->getName()));
        }

        return element;
    }

    //@Override
    /*public*/ bool ExpressionSignalMastXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionSignalMast* h = new ExpressionSignalMast(sys, uname);

        loadCommon(h, shared);

        QDomElement signalMastName = shared.firstChildElement("signalMast");
        if (!signalMastName.isNull()) {
            SignalMast* signalMast = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMastName.text().trimmed());
            if (signalMast != nullptr) h->setSignalMast(signalMast);
            else h->removeSignalMast();
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
                h->setQueryType(ExpressionSignalMast::QueryType::valueOf(queryType.text().trimmed()));
            }

            elem = shared.firstChildElement("queryReference");
            if (!elem.isNull()) h->setQueryReference(elem.text().trimmed());

            elem = shared.firstChildElement("queryLocalVariable");
            if (!elem.isNull()) h->setQueryLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("queryFormula");
            if (!elem.isNull()) h->setQueryFormula(elem.text().trimmed());


            elem = shared.firstChildElement("aspectAddressing");
            if (!elem.isNull()) {
                h->setAspectAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement aspectElement = shared.firstChildElement("aspect");
            if (!aspectElement.isNull()) {
                try {
                    h->setAspect(aspectElement.text().trimmed());
                } catch (NumberFormatException* e) {
                    log->error("cannot parse aspect: " + aspectElement.text().trimmed(), e);
                }
            }

            elem = shared.firstChildElement("aspectReference");
            if (!elem.isNull()) h->setAspectReference(elem.text().trimmed());

            elem = shared.firstChildElement("aspectLocalVariable");
            if (!elem.isNull()) h->setAspectLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("aspectFormula");
            if (!elem.isNull()) h->setAspectFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        signalMastName = shared.firstChildElement("exampleSignalMast");
        if (!signalMastName.isNull()) {
            SignalMast* signalMast = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMastName.text().trimmed());
            if (signalMast != nullptr) h->setExampleSignalMast(signalMast);
            else h->removeSignalMast();
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionSignalMastXml::log = LoggerFactory::getLogger("ExpressionSignalMastXml");
