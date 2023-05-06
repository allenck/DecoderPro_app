#include "triggerroutexml.h"
#include "abstractroutemanager.h"
#include "instancemanager.h"
#include "jmriconfigurexmlexception.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"
#include "triggerroute.h"
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2021
 */
// /*public*/ class TriggerRouteXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

TriggerRouteXml::TriggerRouteXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML{parent}
{

}

    /**
     * Default implementation for storing the contents of a TriggerRoute
     *
     * @param o Object to store, of type TriggerRoute
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement TriggerRouteXml::store(QObject* o) {
    TriggerRoute* p = (TriggerRoute*) o;

        QDomElement element = doc.createElement("TriggerRoute");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.TriggerRoute");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Route*>* route = p->getRoute();
        if (route != nullptr) {
            element.appendChild(e1=doc.createElement("route")); e1.appendChild(doc.createTextNode(route->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("operationAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getOperationAddressing())));
        element.appendChild(e1=doc.createElement("operationDirect")); e1.appendChild(doc.createTextNode(TriggerRoute::Operation::toString(p->getOperationDirect())));
        element.appendChild(e1=doc.createElement("operationReference")); e1.appendChild(doc.createTextNode(p->getOperationReference()));
        element.appendChild(e1=doc.createElement("operationLocalVariable")); e1.appendChild(doc.createTextNode(p->getOperationLocalVariable()));
        element.appendChild(e1=doc.createElement("operationFormula")); e1.appendChild(doc.createTextNode(p->getLockFormula()));

        return element;
    }

    //@Override
    /*public*/ bool TriggerRouteXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        TriggerRoute* h = new TriggerRoute(sys, uname);

        loadCommon(h, shared);

        QDomElement routeName = shared.firstChildElement("route");
        if (!routeName.isNull()) {
            Route* t = ((AbstractRouteManager*)InstanceManager::getDefault("RouteManager"))->getRoute(routeName.text().trimmed());
            if (t != nullptr) h->setRoute(t);
            else h->removeRoute();
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


            elem = shared.firstChildElement("operationAddressing");
            if (!elem.isNull()) {
                h->setOperationAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement routeLock = shared.firstChildElement("operationDirect");
            if (!routeLock.isNull()) {
                h->setOperationDirect(TriggerRoute::Operation::valueOf(routeLock.text().trimmed()));
            }

            elem = shared.firstChildElement("operationReference");
            if (!elem.isNull()) h->setOperationReference(elem.text().trimmed());

            elem = shared.firstChildElement("operationLocalVariable");
            if (!elem.isNull()) h->setOperationLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("operationFormula");
            if (!elem.isNull()) h->setOperationFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
