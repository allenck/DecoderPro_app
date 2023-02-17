#include "mergsd2signalheadxml.h"
#include "loggerfactory.h"
#include "mergsd2signalhead.h"
#include "instancemanager.h"
#include "signalheadmanager.h"

/**
 * Handle XML configuration for MergSD2SignalHead objects.
 *
 * This file is part of JMRI.
 *
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public  License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 *
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public  License for more details.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2008
 * @author Kevin Dickerson Copyright: Copyright (c) 2009
 */
///*public*/  class MergSD2SignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

/*public*/  MergSD2SignalHeadXml::MergSD2SignalHeadXml(QObject* parent)
 : AbstractNamedBeanManagerConfigXML(parent)
{
}

/**
 * Default implementation for storing the contents of a MergSD2SignalHead.
 *
 * @param o Object to store, of type MergSD2SignalHead
 * @return Element containing the complete info
 */
//@Override
/*public*/  QDomElement MergSD2SignalHeadXml::store(QObject* o) {
    MergSD2SignalHead* p = (MergSD2SignalHead*) o;

    QDomElement element = doc.createElement("signalhead");
    element.setAttribute("class", "jmri.implementation.configurexml.MergSD2SignalHeadml");

    QDomElement e1;
    element.appendChild(e1=doc.createElement("systemName"));e1.appendChild(doc.createTextNode(p->getSystemName()));

    element.setAttribute("aspects", p->getAspects());
    if (p->getFeather()) {
        element.setAttribute("feather", "yes");
    }

    storeCommon(p, element);
    int aspects = p->getAspects();
    //@TODO could re-arange this so that it falls through
    switch (aspects) {
        case 2:
            element.appendChild(addTurnoutElement(p->getInput1(), "input1"));
            if (!p->getHome()) {
                element.setAttribute("home", "no");
            }
            break;
        case 3:
            element.appendChild(addTurnoutElement(p->getInput1(), "input1"));
            element.appendChild(addTurnoutElement(p->getInput2(), "input2"));
            break;
        case 4:
            element.appendChild(addTurnoutElement(p->getInput1(), "input1"));
            element.appendChild(addTurnoutElement(p->getInput2(), "input2"));
            element.appendChild(addTurnoutElement(p->getInput3(), "input3"));
            break;
        default:
            log->error(tr("incorrect number of aspects %1 for Signal %2").arg(aspects).arg(p->getDisplayName()));
    }

    return element;
}

QDomElement MergSD2SignalHeadXml::addTurnoutElement(NamedBeanHandle<Turnout*>* to, QString which) {
    QDomElement el = doc.createElement("turnoutname");
    el.setAttribute("defines", which);
    el.appendChild(doc.createTextNode(to->getName()));
    return el;
}

QDomElement MergSD2SignalHeadXml::addSingleTurnoutElement(Turnout* to) {
    QString user = to->getUserName();
    QString sys = to->getSystemName();

    QDomElement el = doc.createElement("turnout");
    el.setAttribute("systemName", sys);
    if (user != "") {
        el.setAttribute("userName", user);
    }
    return el;
}

//@Override
/*public*/  bool MergSD2SignalHeadXml::load(QDomElement shared, QDomElement /*perNode*/) {
    int aspects = 2;
    QDomNodeList l = shared.elementsByTagName("turnoutname");
    if (l.size() == 0) {
        l = shared.elementsByTagName("turnout");
        aspects = l.size() + 1;
    }
    NamedBeanHandle<Turnout*>* input1 = nullptr;
    NamedBeanHandle<Turnout*>* input2 = nullptr;
    NamedBeanHandle<Turnout*>* input3 = nullptr;
    QString yesno = "";
    bool feather = false;
    bool home = true;

    // put it together
    QString sys = getSystemName(shared);
    QString uname = getUserName(shared);

    if (!shared.attribute("feather").isNull() ) {
        yesno = shared.attribute("feather");
    }
    if ((yesno != "") ) {
        if (yesno == ("yes")) {
            feather = true;
        } else if (yesno ==("no")) {
            feather = false;
        }
    }

    if (!shared.attribute("home").isNull()) {
        yesno = shared.attribute("home");
    }
    if ((yesno != "")) {
        if (yesno ==("yes")) {
            home = true;
        } else if (yesno == ("no")) {
            home = false;
        }
    }
    bool ok;
        aspects = shared.attribute("aspects").toInt(&ok);
    if(!ok) {
        log->warn("Could not parse level attribute!");
    }

    SignalHead* h;
    //int aspects = l.size()+1;  //Number of aspects is equal to the number of turnouts used plus 1.
    //@TODO could re-arange this so that it falls through
    switch (aspects) {
        case 2:
            input1 = loadTurnout(l.at(0));
            break;
        case 3:
            input1 = loadTurnout(l.at(0));
            input2 = loadTurnout(l.at(1));
            break;
        case 4:
            input1 = loadTurnout(l.at(0));
            input2 = loadTurnout(l.at(1));
            input3 = loadTurnout(l.at(2));
            break;
        default:
            log->error(tr("incorrect number of aspects %1 when loading Signal %2").arg(aspects).arg(sys));
    }
    if (uname == "") {
        h = new MergSD2SignalHead(sys, aspects, input1, input2, input3, feather, home);
    } else {
        h = new MergSD2SignalHead(sys, uname, aspects, input1, input2, input3, feather, home);
    }

    loadCommon(h, shared);

    SignalHead* existingBean = (SignalHead*)((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))
                    ->getBySystemName(sys)->self();

    if ((existingBean != nullptr) && (existingBean != h)) {
        log->error(tr("systemName is already registered: %1").arg(sys));
    } else {
       ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(h);
    }

    return true;
}

NamedBeanHandle<Turnout*>* MergSD2SignalHeadXml::loadTurnout(QDomNode o) {
    QDomElement e = o.toElement();

    if (e.tagName() == ("turnout")) {
        QString name = e.attribute("systemName");
        Turnout* t;
        if (!e.attribute("userName").isNull()
                && e.attribute("userName")!=("")) {
            name = e.attribute("userName");
            t = InstanceManager::turnoutManagerInstance()->getTurnout(name);
        } else {
            t = (Turnout*)InstanceManager::turnoutManagerInstance()->getBySystemName(name)->self();
        }
        if (t != nullptr) {
            return ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, t);
        } else {
            log->warn(tr("Failed to find turnout %1. Check connection and configuration").arg(name));
            return nullptr;
        }
    } else {
        QString name = e.text();
        try {
            Turnout* t = InstanceManager::turnoutManagerInstance()->provideTurnout(name);
            return ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, t);
        } catch (IllegalArgumentException* ex) {
            log->warn(tr("Failed to provide Turnout \"%1\" in loadTurnout").arg(name));
            return nullptr;
        }
    }
}

//@Override
/*public*/  void MergSD2SignalHeadXml::load(QDomElement /*element*/, QObject* /*o*/) {
    log->error("Invalid method called");
}

/*private*/ /*final*/ /*static*/ Logger* MergSD2SignalHeadXml::log = LoggerFactory::getLogger("MergSD2SignalHeadXml");
