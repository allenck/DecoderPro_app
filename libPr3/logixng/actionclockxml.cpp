#include "actionclockxml.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "actionclock.h"
/**
 * Handle XML configuration for ActionClock objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2021
 * @author Dave Sand Copyright (C) 2021
 */
///*public*/  class ActionClockXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

  ActionClockXml::ActionClockXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
  {
   setObjectName("ActionClockXml");
  }


    /**
     * Default implementation for storing the contents of a clock action.
     *
     * @param o Object to store, of type ActionClock
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement ActionClockXml::store(QObject* o) {
        ActionClock* p = (ActionClock*) o;

        QDomElement element = doc.createElement("ActionClock");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.configurexml.ActionClockXml");
        QDomElement e1;
        element.appendChild(e1 =doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

        storeCommon(p, element);

        element.appendChild(e1 = doc.createElement("clockState")); e1.appendChild(doc.createTextNode(ActionClock::ClockState::toString(p->getBeanState())));

        if (p->getBeanState() == ActionClock::ClockState::SetClock) {
            element.appendChild(e1 =doc.createElement("setTime")); e1.appendChild(doc.createTextNode(QString::number(p->getClockTime())));
        }

        return element;
    }

    //@Override
    /*public*/  bool ActionClockXml::load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        ActionClock* h = new ActionClock(sys, uname);

        loadCommon(h, shared);

        QDomElement clockState = shared.firstChildElement("clockState");
        if (!clockState.isNull()) {
            h->setBeanState(ActionClock::ClockState::valueOf(clockState.text().trimmed()));
        }

        QDomElement setTime = shared.firstChildElement("setTime");
        if (!setTime.isNull()) {
            int time;
            try {
                time = (setTime.text().trimmed()).toInt();
            } catch (NumberFormatException ex) {
                time = 0;
            }
            h->setClockTime(time);
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }
