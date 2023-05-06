#include "actionreporterxml.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "actionreporter.h"
#include "abstractmemorymanager.h"
#include "parserexception.h"
#include "jmriconfigurexmlexception.h"

/**
 * Handle XML configuration for Reporter objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright (C) 2021
 */
///*public*/  class ActionReporterXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.logixng.actions.ActionBundle");

    ActionReporterXml::ActionReporterXml(QObject *parent)
    {

    }

    /**
     * Default implementation for storing the contents of a Reporter
     *
     * @param o Object to store, of type Reporter
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionReporterXml::store(QObject* o) {
        ActionReporter* p = (ActionReporter*) o;

        QDomElement element = doc.createElement("ActionReporter");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.actions.configurexml.ActionReporterXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        NamedBeanHandle<Reporter*>* reporter = p->getReporter();
        if (reporter != nullptr) {
            element.appendChild(e1=doc.createElement("reporter")); e1.appendChild(doc.createTextNode(reporter->getName()));
        }

        element.appendChild(e1=doc.createElement("addressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("reference")); e1.appendChild(doc.createTextNode(p->getReference()));
        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariable()));
        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        element.appendChild(e1=doc.createElement("reporterValue")); e1.appendChild(doc.createTextNode(ActionReporter::ReporterValue::toString(p->getReporterValue())));

        element.appendChild(e1=doc.createElement("dataAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getDataAddressing())));
        element.appendChild(e1=doc.createElement("dataReference")); e1.appendChild(doc.createTextNode(p->getDataReference()));
        element.appendChild(e1=doc.createElement("dataLocalVariable")); e1.appendChild(doc.createTextNode(p->getDataLocalVariable()));
        element.appendChild(e1=doc.createElement("dataFormula")); e1.appendChild(doc.createTextNode(p->getDataFormula()));

        NamedBeanHandle<Memory*>* memory = p->getMemory();
        if (memory != nullptr) {
            element.appendChild(e1=doc.createElement("memory")); e1.appendChild(doc.createTextNode(memory->getName()));
        }

        return element;
    }

    //@Override
    /*public*/  bool ActionReporterXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionReporter* h = new ActionReporter(sys, uname);

        loadCommon(h, shared);

        QDomElement reporterName = shared.firstChildElement("reporter");
        if (!reporterName.isNull()) {
            Reporter* t = (Reporter*)((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))->getNamedBean(reporterName.text().trimmed())->self();
            if (t != nullptr) h->setReporter(t);
            else h->removeReporter();
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


                elem = shared.firstChildElement("reporterValue");
            if (!elem.isNull()) {
                h->setReporterValue(ActionReporter::ReporterValue::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("dataAddressing");
            if (!elem.isNull()) {
                h->setDataAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("dataReference");
            if (!elem.isNull()) h->setDataReference(elem.text().trimmed());

            elem = shared.firstChildElement("dataLocalVariable");
            if (!elem.isNull()) h->setDataLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("dataFormula");
            if (!elem.isNull()) h->setDataFormula(elem.text().trimmed());


            QDomElement memoryName = shared.firstChildElement("memory");
            if (!memoryName.isNull()) {
                Memory* m = (Memory*)((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getNamedBean(memoryName.text().trimmed())->self();
                if (m != nullptr) h->setMemory(m);
                else h->removeMemory();
            }

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
