#include "sequencexml.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "sequence.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
// public  class SequenceXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

    /*public*/  SequenceXml::SequenceXml(QObject* parent)
     : AbstractNamedBeanManagerConfigXML(parent) {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return QDomElement containing the complete info
     */
    /*@Override*/
    /*public*/  QDomElement SequenceXml::store(QObject* o) {
        Sequence* p = (Sequence*) o;

        QDomElement element = doc.createElement("Sequence");
        QDomElement e1;
        element.setAttribute("class", /*this.getClass().getName()*/"jmri,jmrit.logixnh.actions.configurexml.SequenceXml");
        element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        QDomElement e2 = doc.createElement("StartSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(0)->getName()));
        MaleSocket* socket = p->getStartExpressionSocket()->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getStartExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("StopSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(1)->getName()));
        socket = p->getStopExpressionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getStopExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        e2 = doc.createElement("ResetSocket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(2)->getName()));
        socket = p->getResetExpressionSocket()->getConnectedSocket();
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getResetExpressionSocketSystemName();
        }
        if (socketSystemName != "") {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        element.appendChild(e2);

        QDomElement e = doc.createElement("Expressions");
        for (int i=0; i < p->getNumExpressions(); i++) {
            e2 = doc.createElement("Socket");
            e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode((p->getExpressionSocket(i)->getName())));
            socket = p->getExpressionSocket(i)->getConnectedSocket();
            if (socket != nullptr) {
                socketSystemName = socket->getSystemName();
            } else {
                socketSystemName = p->getExpressionSocketSystemName(i);
            }
            if (socketSystemName != "") {
                e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
            }
            e.appendChild(e2);
        }
        element.appendChild(e);

        e = doc.createElement("Actions");
        for (int i=0; i < p->getNumActions(); i++) {
            e2 = doc.createElement("Socket");
            e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getActionSocket(i)->getName()));
            socket = p->getActionSocket(i)->getConnectedSocket();
            if (socket != nullptr) {
                socketSystemName = socket->getSystemName();
            } else {
                socketSystemName = p->getActionSocketSystemName(i);
            }
            if (socketSystemName != "") {
                e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
            }
            e.appendChild(e2);
        }
        element.appendChild(e);

        element.appendChild(e1=doc.createElement("startImmediately")); e1.appendChild(doc.createTextNode(p->getStartImmediately() ? "yes" : "no"));
        element.appendChild(e1=doc.createElement("runContinuously")); e1.appendChild(doc.createTextNode(p->getRunContinuously() ? "yes" : "no"));

        return element;
    }

    /*@Override*/
    /*public*/  bool SequenceXml::load(QDomElement shared, QDomElement perNode) {
        QList<QMap<QString, QString>>* expressionSystemNames = new QList<QMap<QString, QString>>();

        QDomElement socketNameElement = shared.firstChildElement("StartSocket").firstChildElement("socketName");
        QString startSocketName = socketNameElement.text().trimmed();
        QDomElement socketSystemNameElement = shared.firstChildElement("StartSocket").firstChildElement("systemName");
        QString startSocketSystemName = "";
        if (!socketSystemNameElement.isNull()) {
            startSocketSystemName = socketSystemNameElement.text().trimmed();
        }

        socketNameElement = shared.firstChildElement("StopSocket").firstChildElement("socketName");
        QString stopSocketName = socketNameElement.text().trimmed();
        socketSystemNameElement = shared.firstChildElement("StopSocket").firstChildElement("systemName");
        QString stopSocketSystemName = "";
        if (!socketSystemNameElement.isNull()) {
            stopSocketSystemName = socketSystemNameElement.text().trimmed();
        }

        socketNameElement = shared.firstChildElement("ResetSocket").firstChildElement("socketName");
        QString resetSocketName = socketNameElement.text().trimmed();
        socketSystemNameElement = shared.firstChildElement("ResetSocket").firstChildElement("systemName");
        QString resetSocketSystemName = "";
        if (!socketSystemNameElement.isNull()) {
            resetSocketSystemName = socketSystemNameElement.text().trimmed();
        }

        QDomElement expressionElement = shared.firstChildElement("Expressions");
        QDomNodeList nl = expressionElement.childNodes();
        for (int i=0; i < nl.size(); i++) {
         QDomElement socketElement = nl.at(i).toElement();
            QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
            QDomElement systemNameElement = socketElement.firstChildElement("systemName");
            QString systemName = "";
            if (!systemNameElement.isNull()) {
                systemName = systemNameElement.text().trimmed();
            }
            expressionSystemNames->append(QMap<QString, QString>{{socketName, systemName}});
        }

        QList<QMap<QString, QString>>* actionSystemNames = new QList<QMap<QString, QString>>();

        QDomElement actionElement = shared.firstChildElement("Actions");
        QDomNodeList nl2 = actionElement.childNodes();
        for (int i=0; i < nl2.size(); i++) {
         QDomElement socketElement = nl2.at(i).toElement();
            QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
            QDomElement systemNameElement = socketElement.firstChildElement("systemName");
            QString systemName = "";
            if (!systemNameElement.isNull()) {
                systemName = systemNameElement.text().trimmed();
            }
            actionSystemNames->append(QMap<QString, QString>{{socketName, systemName}});
        }

        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        Sequence* h = new Sequence(sys, uname, expressionSystemNames, actionSystemNames);

        loadCommon(h, shared);

        h->getChild(0)->setName(startSocketName);
        h->setStartExpressionSocketSystemName(startSocketSystemName);

        h->getChild(1)->setName(stopSocketName);
        h->setStopExpressionSocketSystemName(stopSocketSystemName);

        h->getChild(2)->setName(resetSocketName);
        h->setResetExpressionSocketSystemName(resetSocketSystemName);

        QDomElement startImmediately = shared.firstChildElement("startImmediately");
        if (!startImmediately.isNull()) {
            h->setStartImmediately("yes"==(startImmediately.text().trimmed()));
        } else {
            h->setStartImmediately(false);
        }

        QDomElement runContinuously = shared.firstChildElement("runContinuously");
        if (!runContinuously.isNull()) {
            h->setRunContinuously("yes" == (runContinuously.text().trimmed()));
        } else {
            h->setRunContinuously(false);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
