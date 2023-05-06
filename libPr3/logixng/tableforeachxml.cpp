#include "tableforeachxml.h"
#include "instancemanager.h"
#include "jmriconfigurexmlexception.h"
#include "tableforeach.h"
#include "namedbeanaddressing.h"
#include "tableroworcolumn.h"
#include "defaultdigitalactionmanager.h"
#include "parserexception.h"

/**
 * Handle XML configuration for TableForEach objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class TableForEachXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  TableForEachXml::TableForEachXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent) {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleTurnoutSignalHead
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement TableForEachXml::store(QObject* o) {
        TableForEach* p = (TableForEach*) o;

        QDomElement element = doc.createElement("TableForEach");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.TableForEachXml");
        QDomElement e1;
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1=doc.createElement("localVariable")); e1.appendChild(doc.createTextNode(p->getLocalVariableName()));

        if (p->getTable() != nullptr) {
            element.appendChild(doc.createElement("table")); e1.appendChild(doc.createTextNode(p->getTable()->getName()));
        }

        element.appendChild(e1=doc.createElement("tableAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString(p->getAddressing())));
        element.appendChild(e1=doc.createElement("tableReference")); e1.appendChild(doc.createTextNode(p->getTableReference()));
        element.appendChild(e1=doc.createElement("tableLocalVariable")); e1.appendChild(doc.createTextNode(p->getTableLocalVariable()));
        element.appendChild(e1=doc.createElement("tableFormula")); e1.appendChild(doc.createTextNode(p->getTableFormula()));

        element.appendChild(e1=doc.createElement("rowOrColumnAddressing")); e1.appendChild(doc.createTextNode(NamedBeanAddressing::toString( p->getRowOrColumnAddressing())));
        element.appendChild(e1=doc.createElement("rowOrColumnName")); e1.appendChild(doc.createTextNode(p->getRowOrColumnName()));
        element.appendChild(e1=doc.createElement("rowOrColumnReference")); e1.appendChild(doc.createTextNode(p->getRowOrColumnReference()));
        element.appendChild(e1=doc.createElement("rowOrColumnLocalVariable")); e1.appendChild(doc.createTextNode(p->getRowOrColumnLocalVariable()));
        element.appendChild(e1=doc.createElement("rowOrColumnFormula")); e1.appendChild(doc.createTextNode(p->getRowOrColumnFormula()));

        element.appendChild(e1=doc.createElement("tableRowOrColumn")); e1.appendChild(doc.createTextNode(TableRowOrColumn::toString(p->getRowOrColumn())));

        QDomElement e2 = doc.createElement("Socket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        return element;
    }

    //@Override
    /*public*/  bool TableForEachXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        TableForEach* h = new TableForEach(sys, uname);

        loadCommon(h, shared);

        QDomElement tableRowOrColumnElement = shared.firstChildElement("tableRowOrColumn");
        TableRowOrColumn::TYPE tableRowOrColumn =
                TableRowOrColumn::valueOf(tableRowOrColumnElement.text().trimmed());
        h->setRowOrColumn(tableRowOrColumn);

        QDomElement socketName = shared.firstChildElement("Socket").firstChildElement("socketName");
        h->getChild(0)->setName(socketName.text().trimmed());
        QDomElement socketSystemName = shared.firstChildElement("Socket").firstChildElement("systemName");
        if (!socketSystemName.isNull()) {
            h->setSocketSystemName(socketSystemName.text().trimmed());
        }

        QDomElement tableName = shared.firstChildElement("table");
        if (!tableName.isNull()) {
            h->setTable(tableName.text().trimmed());
        }

        try {
            QDomElement elem = shared.firstChildElement("tableAddressing");
            if (!elem.isNull()) {
                h->setAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            elem = shared.firstChildElement("tableReference");
            if (!elem.isNull()) h->setTableReference(elem.text().trimmed());

            elem = shared.firstChildElement("tableLocalVariable");
            if (!elem.isNull()) h->setTableLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("tableFormula");
            if (!elem.isNull()) h->setTableFormula(elem.text().trimmed());


            elem = shared.firstChildElement("rowOrColumnAddressing");
            if (!elem.isNull()) {
                h->setRowOrColumnAddressing(NamedBeanAddressing::valueOf(elem.text().trimmed()));
            }

            QDomElement rowOrColumnName = shared.firstChildElement("rowOrColumnName");
            if (!rowOrColumnName.isNull()) h->setRowOrColumnName(rowOrColumnName.text().trimmed());

            elem = shared.firstChildElement("rowOrColumnReference");
            if (!elem.isNull()) h->setRowOrColumnReference(elem.text().trimmed());

            elem = shared.firstChildElement("rowOrColumnLocalVariable");
            if (!elem.isNull()) h->setRowOrColumnLocalVariable(elem.text().trimmed());

            elem = shared.firstChildElement("rowOrColumnFormula");
            if (!elem.isNull()) h->setRowOrColumnFormula(elem.text().trimmed());

        } catch (ParserException* e) {
            throw new JmriConfigureXmlException(e);
        }

        QDomElement rowOrColumnName = shared.firstChildElement("rowOrColumnName");
        if (!rowOrColumnName.isNull()) {
            h->setRowOrColumnName(rowOrColumnName.text().trimmed());
        }

        QDomElement localVariable = shared.firstChildElement("localVariable");
        if (!localVariable.isNull()) {
            h->setLocalVariableName(localVariable.text().trimmed());
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
