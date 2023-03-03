#include "shutdowncomputerxml.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/shutdowncomputer.h"
#include "instancemanager.h"
/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/ class ShutdownComputerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

ShutdownComputerXml::ShutdownComputerXml(QObject *parent)
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
    /*public*/ QDomElement ShutdownComputerXml::store(QObject* o) {
        ShutdownComputer* p = (ShutdownComputer*) o;

        QDomElement element = doc.createElement("ShutdownComputer");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.ShutdownComputerXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1=doc.createElement("operation")); e1.appendChild(doc.createTextNode(ShutdownComputer::Operation::toString(p->getOperation())));

        return element;
    }

    //@Override
    /*public*/ bool ShutdownComputerXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);

        ShutdownComputer* h = new ShutdownComputer(sys, uname);

        loadCommon(h, shared);

        QDomElement operation = shared.firstChildElement("operation");
        if (!operation.isNull()) {
            h->setOperation(ShutdownComputer::Operation::valueOf(operation.text().trimmed()));
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
