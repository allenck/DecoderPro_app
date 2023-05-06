#include "antecedentxml.h"
#include "defaultdigitalexpressionmanager.h"
#include "antecedent.h"
#include "instancemanager.h"
#include "jmriconfigurexmlexception.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
// /*public*/  class AntecedentXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

/*public*/ AntecedentXml::AntecedentXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent) {
}

/**
 * Default implementation for storing the contents of a ActionMany
 *
 * @param o Object to store, of type ActionMany
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/  QDomElement AntecedentXml::store(QObject* o) {
    Antecedent* p = (Antecedent*) o;

    QDomElement element = doc.createElement("Antecedent");
    element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.AntecedentXml");
    QDomElement e1;
    element.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

    storeCommon((NamedBean*)p->bself(), element);

    element.appendChild(e1=doc.createElement("antecedent")); e1.appendChild(doc.createTextNode(p->getAntecedent()));

    QDomElement e = doc.createElement("Expressions");
    for (int i=0; i < p->getChildCount(); i++) {
        QDomElement e2 = doc.createElement("Socket");
        e2.appendChild(e1=doc.createElement("socketName")); e1.appendChild(doc.createTextNode(p->getChild(i)->getName()));
        MaleSocket* socket = p->getChild(i)->getConnectedSocket();
        QString socketSystemName;
        if (socket != nullptr) {
            socketSystemName = socket->getSystemName();
        } else {
            socketSystemName = p->getExpressionSystemName(i);
        }
        if (socketSystemName != nullptr) {
            e2.appendChild(e1=doc.createElement("systemName")); e1.appendChild(doc.createTextNode(socketSystemName));
        }
        e.appendChild(e2);
    }
    element.appendChild(e);

    return element;
}

//@Override
/*public*/  bool AntecedentXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
    QList<QMap<QString, QString>> expressionSystemNames = QList<QMap<QString, QString>>();

    QDomElement actionElement = shared.firstChildElement("Expressions");
    //for (QDomElement socketElement : actionElement.getChildren()) {
    QDomNodeList list = actionElement.childNodes();
    for(int i=0; i < list.count(); i++)
    {
     QDomElement socketElement = list.at(i).toElement();
        QString socketName = socketElement.firstChildElement("socketName").text().trimmed();
        QDomElement systemNameElement = socketElement.firstChildElement("systemName");
        QString systemName = "";
        if (systemNameElement != QDomElement()) {
            systemName = systemNameElement.text().trimmed();
        }
        expressionSystemNames.append(QMap<QString, QString> {{socketName, systemName}});
    }

    // put it together
    QString sys = getSystemName(shared);
    QString uname = getUserName(shared);

    QString antecedent = shared.firstChildElement("antecedent").text();

    Antecedent* h;
    if (uname == "") {
        h = new Antecedent(sys, "", expressionSystemNames);
    } else {
        h = new Antecedent(sys, uname, expressionSystemNames);
    }
    try {
        h->setAntecedent(antecedent);
    } catch (Exception* e) {
        throw new JmriConfigureXmlException("Antecedent.setAntecedent() has thrown exeception", e);
    }

    loadCommon((NamedBean*)h->bself(), shared);

    ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
    return true;
}
