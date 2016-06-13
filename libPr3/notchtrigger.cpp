#include "notchtrigger.h"
#include <QDomElement>
#include "logger.h"
#include "propertychangeevent.h"
#include "enginesound.h"
#include "triggerlistener.h"

//NotchTrigger::NotchTrigger(QObject *parent) :
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
 * @version			$Revision: 28746 $
 */
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//import org.jdom2.Element;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

//class NotchTrigger extends Trigger implements PropertyChangeListener {


    /*public*/ NotchTrigger::NotchTrigger(QString name, QObject *parent) :
  Trigger(name, parent){
        //this(name, 0, 0);
 prev_notch = 0;
 current_notch = 0;
    }

    /*public*/ NotchTrigger::NotchTrigger(QString name, int prev, int cur, QObject *parent) :
  Trigger(name, parent)
{
        //super(name);
        this->setTriggerType(NOTCH);
        prev_notch = prev;
        current_notch = cur;
    }

    /*public*/ void NotchTrigger::setNotch(int next) {
        current_notch = next;
    }

    /*public*/ int NotchTrigger::getNotch() {
        return (current_notch);
    }

    /*public*/ void NotchTrigger::propertyChange(PropertyChangeEvent* event) {

        // Validate
        // If no target, or not a name match, or no trigger, or no action
        // then just return quickly.
        // Careful: Takes advantage of "lazy OR" behavior
        if (target == NULL) {
            log->debug("Quit.  No target.");
            return;
        }
        if (event->getPropertyName()==(this->getEventName()) != true) {
            //log->debug("Quit. Event name mismatch event = " + event.getPropertyName() + " this = " + this->getEventName());
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

        // Compare
        prev_notch = current_notch;
        current_notch = EngineSound::calcEngineNotch( event->getNewValue().toFloat());

        log->debug("Notch Trigger prev_notch = " + QString::number(prev_notch) + " current_notch = " + QString::number(current_notch));
        this->callback->takeAction(current_notch);
        /*
         if ((prev == prev_notch) && (next == next_notch)) {
         this->callback.takeAction();
         }
         */
    }

   //@Override
    /*public*/ QDomElement NotchTrigger:: getXml() {
        //Element me = new Element("Trigger");
 QDomElement me = QDomElement();
 me.setTagName("Trigger");
        me.setAttribute("name", this->getName());
        me.setAttribute("type", "NOTCH");
        log->warn("CompareTrigger.getXml() not implemented");
        return (me);
    }

    //@Override
    /*public*/ void NotchTrigger::setXml(QDomElement e) {
        //Get common stuff
        Trigger::setXml(e);
        // Only do this if type Notch
        if (e.attribute("type")==("NOTCH")) {
            // Nothing unique to do...
        }
    }
