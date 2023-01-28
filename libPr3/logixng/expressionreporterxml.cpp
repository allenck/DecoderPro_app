#include "expressionreporterxml.h"
#include "expressionreporter.h"
#include "namedbeanhandlemanager.h"
#include "namedbeanhandle.h"
#include "reporter.h"
#include "abstractreportermanager.h"
#include "instancemanager.h"
#include "abstractmemorymanager.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class ExpressionReporterXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  ExpressionReporterXml::ExpressionReporterXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent){
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return  QDomElement containing the complete info
     */
    //@Override
    /*public*/   QDomElement ExpressionReporterXml::store(QObject* o) {
        ExpressionReporter* p = (ExpressionReporter*) o;

         QDomElement element =  doc.createElement("ExpressionReporter");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.ExpressionReporterXml");
        element.appendChild( doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName())));

        storeCommon(p, element);

        NamedBeanHandle<Reporter*>* reporter = p->getReporter();
        if (reporter != nullptr) {
            element.appendChild( doc.createElement("reporter").appendChild(doc.createTextNode(reporter->getName())));
        }

        element.appendChild( doc.createElement("reporterValue").appendChild(doc.createTextNode(ExpressionReporter::ReporterValue::toString(p->getReporterValue()))));
        element.appendChild( doc.createElement("reporterOperation").appendChild(doc.createTextNode(ExpressionReporter::ReporterOperation::toString(p->getReporterOperation()))));
        element.appendChild( doc.createElement("compareTo").appendChild(doc.createTextNode(ExpressionReporter::CompareTo::toString(p->getCompareTo()))));

        element.appendChild( doc.createElement("caseInsensitive").appendChild(doc.createTextNode(p->getCaseInsensitive() ? "yes" : "no")));

        element.appendChild( doc.createElement("constant").appendChild(doc.createTextNode(p->getConstantValue())));

        NamedBeanHandle<Memory*>* memory = p->getMemory();
        if (memory != nullptr) {
            element.appendChild( doc.createElement("memory").appendChild(doc.createTextNode(memory->getName())));
        }

        QString variableName = p->getLocalVariable();
        if (variableName != "") {
            element.appendChild( doc.createElement("variable").appendChild(doc.createTextNode(variableName)));
        }

        element.appendChild( doc.createElement("regEx").appendChild(doc.createTextNode(p->getRegEx())));

        return element;
    }

    //@Override
    /*public*/  bool ExpressionReporterXml::load( QDomElement shared,  QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ExpressionReporter* h = new ExpressionReporter(sys, uname);

        loadCommon(h, shared);

         QDomElement reporterName = shared.firstChildElement("reporter");
        if (!reporterName.isNull()) {
            Reporter* m = ((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter(reporterName.text().trimmed());
            if (m != nullptr) h->setReporter(m);
            else h->removeReporter();
        }

         QDomElement memoryName = shared.firstChildElement("memory");
        if (!memoryName.isNull()) {
            Memory* m = ((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName.text().trimmed());
            if (m != nullptr) h->setMemory(m);
            else h->removeMemory();
        }

         QDomElement variableName = shared.firstChildElement("variable");
        if (!variableName.isNull()) {
            h->setLocalVariable(variableName.text().trimmed());
        }

         QDomElement constant = shared.firstChildElement("constant");
        if (!constant.isNull()) {
            h->setConstantValue(constant.text());
        }

         QDomElement regEx = shared.firstChildElement("regEx");
        if (!regEx.isNull()) {
            h->setRegEx(regEx.text());
        }

         QDomElement reporterValue = shared.firstChildElement("reporterValue");
        if (!reporterValue.isNull()) {
            h->setReporterValue(ExpressionReporter::ReporterValue::fromString(reporterValue.text().trimmed()));
        }

         QDomElement reporterOperation = shared.firstChildElement("reporterOperation");
        if (!reporterOperation.isNull()) {
            h->setReporterOperation(ExpressionReporter::ReporterOperation::fromString(reporterOperation.text().trimmed()));
        }

         QDomElement compareTo = shared.firstChildElement("compareTo");
        if (!compareTo.isNull()) {
            h->setCompareTo(ExpressionReporter::CompareTo::fromString(compareTo.text().trimmed()));
        }

         QDomElement caseInsensitive = shared.firstChildElement("caseInsensitive");
        if (!caseInsensitive.isNull()) {
            h->setCaseInsensitive("yes" == (caseInsensitive.text().trimmed()));
        } else {
            h->setCaseInsensitive(false);
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }
