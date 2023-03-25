#include "webbrowserxml.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/femalestringexpressionsocket.h"
#include "logixng/webbrowser.h"
#include "instancemanager.h"
/**
 * Handle XML configuration for WebBrowser objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
// /*public*/ class WebBrowserXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    WebBrowserXml::WebBrowserXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {

    }

    /**
     * Default implementation for storing the contents of a WebBrowser
     *
     * @param o Object to store, of type WebBrowser
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement WebBrowserXml::store(QObject* o) {
        WebBrowser* p = (WebBrowser*) o;

        QDomElement element = doc.createElement("WebBrowser");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.WebBrowserXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QString systemName;

        FemaleStringExpressionSocket* expressionSocket = p->getStringExpressionSocket();
        if (expressionSocket->isConnected()) {
            systemName = expressionSocket->getConnectedSocket()->getSystemName();
        } else {
            systemName = p->getStringExpressionSocketSystemName();
        }
        if (systemName != "") {
            element.appendChild(e1=doc.createElement("expressionSystemName")); e1.appendChild(doc.createTextNode(systemName));
        }

        return element;
    }

    //@Override
    /*public*/ bool WebBrowserXml::load(QDomElement shared, QDomElement perNode) {

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        WebBrowser* h = new WebBrowser(sys, uname);

        loadCommon(h, shared);

        QDomElement expressionSystemNameElement = shared.firstChildElement("expressionSystemName");
        if (!expressionSystemNameElement.isNull()) {
            h->setStringExpressionSocketSystemName(expressionSystemNameElement.text().trimmed());
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
