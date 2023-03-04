#include "loglocalvariablesxml.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/loglocalvariables.h"
#include "instancemanager.h"
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/ class LogLocalVariablesXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

LogLocalVariablesXml::LogLocalVariablesXml(QObject *parent)
    : AbstractNamedBeanManagerConfigXML{parent}
{

}


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleSensorSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement LogLocalVariablesXml::store(QObject* o) {
        LogLocalVariables* p = (LogLocalVariables*) o;

        QDomElement element = doc.createElement("LogLocalVariables");
        QDomElement e1;
        element.setAttribute("class", /*this->getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.LogLocalVariablesXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        return element;
    }

    //@Override
    /*public*/ bool LogLocalVariablesXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);

        LogLocalVariables* h = new LogLocalVariables(sys, uname);

        loadCommon(h, shared);

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
