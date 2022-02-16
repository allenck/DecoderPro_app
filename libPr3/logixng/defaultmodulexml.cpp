#include "defaultmodulexml.h"
#include "loggerfactory.h"
#include "defaultmodule.h"
#include "module.h"
#include "femalesocketmanager.h"
#include "instancemanager.h"
#include "modulemanager.h"

/**
 * Handle XML configuration for DefaultModule objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
///*public*/  class DefaultModuleXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  DefaultModuleXml::DefaultModuleXml(QObject* parent) :AbstractNamedBeanManagerConfigXML(parent) {
    }

    /**
     * Default implementation for storing the contents of a DefaultModule
     *
     * @param o Object to store, of type DefaultModule
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/  QDomElement DefaultModuleXml::store(QObject* o) {
        DefaultModule* p = (DefaultModule*) o;

        QDomElement element = doc.createElement("Module");
        element.setAttribute("class", "jmri.jmrit.logixng.implementation.configurexml.DefaultModuleXml");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractBase::getSystemName())));

        storeCommon((NamedBean*)p->AbstractBase::self(), element);

        element.appendChild(doc.createElement("rootSocketType").appendChild(doc.createTextNode(p->getRootSocketType()->getName())));

        QDomElement elementParameters = doc.createElement("Parameters");
        for (Module::Parameter* data : p->getParameters()) {
            QDomElement elementParameter = doc.createElement("Parameter");
            elementParameter.appendChild(doc.createElement("name").appendChild(doc.createTextNode(data->getName())));
            elementParameter.appendChild(doc.createElement("isInput").appendChild(doc.createTextNode(data->isInput() ? "yes" : "no")));
            elementParameter.appendChild(doc.createElement("isOutput").appendChild(doc.createTextNode(data->isOutput() ? "yes" : "no")));
            elementParameters.appendChild(elementParameter);
        }
        element.appendChild(elementParameters);

        QDomElement e2 = doc.createElement("RootSocket");
        e2.appendChild(doc.createElement("socketName").appendChild(doc.createTextNode(p->AbstractBase::getChild(0)->getName())));
        MaleSocket* socket = p->getRootSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(socketSystemName)));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/  bool DefaultModuleXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);

        QString rootSocketTypeName = shared.firstChildElement("rootSocketType").text().trimmed();

        FemaleSocketManager::SocketType* socketType =
                ((FemaleSocketManager*)InstanceManager::getDefault("FemaleSocketManager"))
                        ->getSocketTypeByType(rootSocketTypeName);

        DefaultModule* h = (DefaultModule*) ((ModuleManager*)InstanceManager::getDefault("ModuleManager"))
                ->createModule(sys, uname, socketType);

        loadCommon(h, shared);

        QDomNodeList parameterList = shared.firstChildElement("Parameters").childNodes();  // NOI18N
        log->debug("Found " + QString::number(parameterList.size()) + " parameters");  // NOI18N

        for (int i=0; i<  parameterList.size(); i++)
        {
         QDomElement e = parameterList.at(i).toElement();
            QDomElement elementName = e.firstChildElement("name");

            bool isInput = "yes" ==(e.firstChildElement("isInput").text().trimmed());
            bool isOutput = "yes" == (e.firstChildElement("isOutput").text().trimmed());

            h->addParameter(elementName.text().trimmed(), isInput, isOutput);
        }

        QDomElement socketName = shared.firstChildElement("RootSocket").firstChildElement("socketName");
        h->AbstractBase::getChild(0)->setName(socketName.text().trimmed());
        QDomElement socketSystemName = shared.firstChildElement("RootSocket").firstChildElement("systemName");
        if (socketSystemName != QDomElement()) {
            h->setSocketSystemName(socketSystemName.text().trimmed());
        }

        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultModuleXml::log = LoggerFactory::getLogger("DefaultModuleXml");
