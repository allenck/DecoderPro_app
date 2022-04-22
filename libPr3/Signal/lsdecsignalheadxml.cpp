#include "lsdecsignalheadxml.h"
#include "loggerfactory.h"
#include "lsdecsignalhead.h"
#include "instancemanager.h"
#include "signalheadmanager.h"

/**
 * Handle XML configuration for LsDecSignalHead objects.
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
 * @author Petr Koud'a Copyright: Copyright (c) 2007
 */
///*public*/  class LsDecSignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

/*public*/  LsDecSignalHeadXml::LsDecSignalHeadXml(QObject* parent)
 : AbstractNamedBeanManagerConfigXML(parent){
}

/**
 * Default implementation for storing the contents of a LsDecSignalHead.
 *
 * @param o Object to store, of type LsDecSignalHead
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/  QDomElement LsDecSignalHeadXml::store(QObject* o) {
    LsDecSignalHead* p = (LsDecSignalHead*) o;

    QDomElement element = doc.createElement("signalhead");
    element.setAttribute("class", "jmri.implementation.configurexml.LsDecSignalHeadXml");

    QDomElement e1;
    element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->getSystemName()));

    storeCommon(p, element);

    element.appendChild(addTurnoutElement(p->getGreen()->getName(), p->getGreenState()));
    element.appendChild(addTurnoutElement(p->getYellow()->getName(), p->getYellowState()));
    element.appendChild(addTurnoutElement(p->getRed()->getName(), p->getRedState()));
    element.appendChild(addTurnoutElement(p->getFlashGreen()->getName(), p->getFlashGreenState()));
    element.appendChild(addTurnoutElement(p->getFlashYellow()->getName(), p->getFlashYellowState()));
    element.appendChild(addTurnoutElement(p->getFlashRed()->getName(), p->getFlashRedState()));
    element.appendChild(addTurnoutElement(p->getDark()->getName(), p->getDarkState()));

    return element;
}

QDomElement LsDecSignalHeadXml::addTurnoutElement(QString name, int s) {
    int state = s;

    QDomElement el = doc.createElement("turnout");
    el.setAttribute("systemName", name);
    if (state == Turnout::THROWN) {
        el.setAttribute("state", "THROWN");
    } else {
        el.setAttribute("state", "CLOSED");
    }

    return el;
}

//@Override
/*public*/  bool LsDecSignalHeadXml::load(QDomElement shared, QDomElement perNode) {
    QDomNodeList l = shared.elementsByTagName("turnout");
    NamedBeanHandle<Turnout*>* green = loadTurnout(l.at(0));
    NamedBeanHandle<Turnout*>* yellow = loadTurnout(l.at(1));
    NamedBeanHandle<Turnout*>* red = loadTurnout(l.at(2));
    NamedBeanHandle<Turnout*>* flashgreen = loadTurnout(l.at(3));
    NamedBeanHandle<Turnout*>* flashyellow = loadTurnout(l.at(4));
    NamedBeanHandle<Turnout*>* flashred = loadTurnout(l.at(5));
    NamedBeanHandle<Turnout*>* dark = loadTurnout(l.at(6));
    int greenstatus = loadTurnoutStatus(l.at(0));
    int yellowstatus = loadTurnoutStatus(l.at(1));
    int redstatus = loadTurnoutStatus(l.at(2));
    int flashgreenstatus = loadTurnoutStatus(l.at(3));
    int flashyellowstatus = loadTurnoutStatus(l.at(4));
    int flashredstatus = loadTurnoutStatus(l.at(5));
    int darkstatus = loadTurnoutStatus(l.at(6));

    // put it together
    QString sys = getSystemName(shared);
    QString uname = getUserName(shared);
    SignalHead* h;
    if (uname == nullptr) {
        h = new LsDecSignalHead(sys, green, greenstatus, yellow, yellowstatus, red, redstatus, flashgreen, flashgreenstatus, flashyellow, flashyellowstatus, flashred, flashredstatus, dark, darkstatus);
    } else {
        h = new LsDecSignalHead(sys, uname, green, greenstatus, yellow, yellowstatus, red, redstatus, flashgreen, flashgreenstatus, flashyellow, flashyellowstatus, flashred, flashredstatus, dark, darkstatus);
    }

    loadCommon(h, shared);

    SignalHead* existingBean =
            ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))
                    ->getBySystemName(sys);

    if ((existingBean != nullptr) && (existingBean != h)) {
        log->error(tr("systemName is already registered: %1").arg(sys));
    } else {
        ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(h);
    }

    return true;
}

NamedBeanHandle<Turnout*>* LsDecSignalHeadXml::loadTurnout(QDomNode o) {
    QDomElement e = o.toElement();
    QString name = e.attribute("systemName");
    Turnout* t = InstanceManager::turnoutManagerInstance()->getTurnout(name);
    if (t != nullptr) {
        return ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, t);
    } else {
        log->warn(tr("Failed to find turnout %1. Check connection and configuration").arg(name));
        return nullptr;
    }
}

int LsDecSignalHeadXml::loadTurnoutStatus(QDomNode o) {
    QDomElement e = o.toElement();
    QString rState = e.attribute("state");
    int tSetState = Turnout::CLOSED;
    if (rState == ("THROWN")) {
        tSetState = Turnout::THROWN;
    }
    return tSetState;
}

//@Override
/*public*/  void LsDecSignalHeadXml::load(QDomElement /*element*/, QObject* /*o*/) {
    log->error("Invalid method called");
}

/*private*/ /*final*/ /*static*/ Logger* LsDecSignalHeadXml::log = LoggerFactory::getLogger("LsDecSignalHeadXml");
