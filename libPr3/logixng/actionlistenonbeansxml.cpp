#include "actionlistenonbeansxml.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "actionlistenonbeans.h"
#include "namedbeantype.h"
#include "defaultdigitalactionmanager.h"
#include "loggerfactory.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class ActionListenOnBeansXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  ActionListenOnBeansXml::ActionListenOnBeansXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ActionListenOnBeansXml");
  }


    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionListenOnBeansXml::store(QObject* o) {
        ActionListenOnBeans* p = (ActionListenOnBeans*) o;

        QDomElement element = doc.createElement("ActionListenOnBeans");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.ActionListenOnBeansXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement parameters = doc.createElement("References");
        for (ActionListenOnBeans::NamedBeanReference* ref : p->getReferences()) {
            QDomElement elementParameter = doc.createElement("Reference");
            elementParameter.appendChild(e1=doc.createElement("name")); e1.appendChild(doc.createTextNode(ref->getName()));
            elementParameter.appendChild(e1=doc.createElement("type")); e1.appendChild(doc.createTextNode(NamedBeanType::toString(ref->getType())));
            parameters.appendChild(elementParameter);
        }
        element.appendChild(parameters);

        return element;
    }

    //@Override
    /*public*/  bool ActionListenOnBeansXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionListenOnBeans* h = new ActionListenOnBeans(sys, uname);

        loadCommon(h, shared);

        QDomNodeList parameterList = shared.firstChildElement("References").childNodes();  // NOI18N
        log->debug("Found " + QString::number(parameterList.size()) + " references");  // NOI18N

        //for (QDomElement e : parameterList) {
        for(int i=0; i < parameterList.size(); i++)
        {
         QDomElement e = parameterList.at(i).toElement();
            QDomElement elementName = e.firstChildElement("name");

            NamedBeanType::TYPE type;
            QDomElement elementType = e.firstChildElement("type");
            if (!elementType.isNull()) {
                type = NamedBeanType::valueOf(elementType.text().trimmed());
            }

            if (!elementName.isNull()) throw new IllegalArgumentException("Element 'name' does not exists");
//            if (type == null) throw new IllegalArgumentException("Element 'type' does not exists");

            h->addReference(new ActionListenOnBeans::NamedBeanReference(elementName.text().trimmed(), type));
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionListenOnBeansXml::log = LoggerFactory::getLogger("ActionListenOnBeansXml");
