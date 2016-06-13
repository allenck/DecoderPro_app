#include "throttletrigger.h"
#include "logger.h"
#include <QDomElement>
#include "propertychangeevent.h"
#include "vsdsound.h"
#include "triggerlistener.h"

//ThrottleTrigger::ThrottleTrigger(QObject *parent) :
//  Trigger(parent)
//{
//}
/*
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2011
 * @version			$Revision: 18245 $
 */
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//import org.jdom2.Element;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

//class ThrottleTrigger extends Trigger implements PropertyChangeListener {


    /*public*/ ThrottleTrigger::ThrottleTrigger(QString name, QObject *parent) :
  Trigger(name,parent) {
        //uper(name);
        this->setTriggerType(Trigger::THROTTLE);
 log = new Logger("ThrottleTrigger");
    }

    /*public*/ void ThrottleTrigger::propertyChange(PropertyChangeEvent* event) {

        // Validate
        // If no target, or not a name match, or no trigger, or no action
        // then just return quickly.
        // Careful: Takes advantage of "lazy OR" behavior
        if (target == NULL ) {
            log->debug("Quit.  No target.");
            return;
        }
        if (event->getPropertyName()==(this->getEventName()) != true) {
            //log->debug("Quit. Event name mismatch event = " + event.getPropertyName() + " this = " + this.getEventName());
            return;
        }
        if (this->getTriggerType() == NONE) {
            //log->debug("Quit.  TriggerType = NONE");
            return;
        }
        if (this->getTargetAction() == NOTHING) {
            //log->debug("Quit.  TargetAction = NOTHING");
            return;
        }

        log->debug("Throttle Trigger old value = " + event->getOldValue().toString() + " new value = " + event->getNewValue().toString());
        this->callback->takeAction( event->getNewValue().toFloat());
    }

    //@Override
    /*public*/ QDomElement ThrottleTrigger::getXml() {
        //QDomElement me = new Element("Trigger");
 QDomElement me = QDomElement();
 me.setTagName("Trigger");
        me.setAttribute("name", this->getName());
        me.setAttribute("type", "THROTTLE");
        log->warn("CompareTrigger.getXml() not implemented");
        return (me);
    }

    //@Override
    /*public*/ void ThrottleTrigger::setXml(QDomElement e) {
        //Get common stuff
        Trigger::setXml(e);
        // Only do this if type Notch
        if (e.attribute("type")==("THROTTLE")) {
            // Nothing unique to do...
        }
    }
