#include "digitalformulaxml.h"
#include "digitalformula.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "basemanager.h"
#include "parserexception.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class DigitalFormulaXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  DigitalFormulaXml::DigitalFormulaXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("DigitalFormulaXml");
  }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DigitalFormulaXml::store(QObject* o) {
        DigitalFormula* p = (DigitalFormula*) o;

        QDomElement element = doc.createElement("DigitalFormula");
        element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.DigitalFormulaXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createElement(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e = doc.createElement("Expressions");
        for (int i=0; i < p->getChildCount(); i++) {
            QDomElement e2 = doc.createElement("Socket");
            e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(i)->getName()));
            MaleSocket* socket = p->getChild(i)->getConnectedSocket();

            QString socketSystemName;
            QString socketManager;
            if (socket != nullptr) {
                socketSystemName = socket->getSystemName();
                socketManager = socket->getManager()->getClassName();
            } else {
                socketSystemName = p->getExpressionSystemName(i);
                socketManager = p->getExpressionManager(i);
            }
            if (socketSystemName != "") {
                e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
            }
            if (socketManager != "") {
                e2.appendChild(e1=doc.createElement("manager")); e1.appendChild(doc.createTextNode(socketManager));
            }
            e.appendChild(e2);
        }

        element.appendChild(e);

        element.appendChild(e1=doc.createElement("formula")); e1.appendChild(doc.createTextNode(p->getFormula()));

        return element;
    }

    //@Override
    /*public*/  bool DigitalFormulaXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {     // Test class that inherits this class throws exception
        QList<DigitalFormula::SocketData*> expressionSystemNames = QList<DigitalFormula::SocketData*>();

        QDomElement actionElement = shared.firstChildElement("Expressions");
        //for (QDomElement socketElement : actionElement.childNodes()) {
        QDomNodeList nl = actionElement.childNodes();
        for(int i=0; i < nl.size(); i++)
        {
         QDomElement socketElement = nl.at(i).toElement();
            QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
            QDomElement systemNameElement = socketElement.firstChildElement("systemName");
            QString systemName = "";
            if (!systemNameElement.isNull()) {
                systemName = systemNameElement.text().trimmed();
            }
            QDomElement managerElement = socketElement.firstChildElement("manager");
            QString manager = nullptr;
            if (!managerElement.isNull()) {
                manager = managerElement.text().trimmed();
            }
            expressionSystemNames.append(new DigitalFormula::SocketData(socketName, systemName, manager));
        }

        // put it together
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);

        DigitalFormula* h = new DigitalFormula(sys, uname, expressionSystemNames);

        loadCommon(h, shared);

        QDomElement formula = shared.firstChildElement("formula");
        if (!formula.isNull()) {
            try {
                h->setFormula(formula.text().trimmed());
            } catch (ParserException* e) {
                log->error("cannot set formula: " + formula.text().trimmed(), e);
            }
        }

        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* DigitalFormulaXml::log = LoggerFactory::getLogger("DigitalFormulaXml");
