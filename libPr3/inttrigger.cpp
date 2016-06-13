#include "inttrigger.h"
#include "propertychangeevent.h"
#include <QDomElement>
#include <QMetaEnum>
#include "logger.h"
#include "triggerlistener.h"

//IntTrigger::IntTrigger()
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

//class IntTrigger extends Trigger implements PropertyChangeListener {


    /*public*/ IntTrigger::IntTrigger(QString name, QObject *parent) :
  Trigger(name, parent) {
        //this(name, 0, CompareType.EQ);
 notch = 0;
 compare_type = EQ;
 log = new Logger("IntTrigger");
    }

    /*public*/ IntTrigger::IntTrigger(QString name, int next, Trigger::CompareType ct, QObject *parent) :
  Trigger(name, parent) {
        //super(name);
        this->setTriggerType(INT);
        notch = next;
        compare_type = ct;
        log = new Logger("IntTrigger");
    }

    /*public*/ void IntTrigger::setMatchValue(int next) {
        notch = next;
    }

    /*public*/ int IntTrigger::getMatchValue() {
        return (notch);
    }

    /*public*/ void IntTrigger::setCompareType(IntTrigger::CompareType ct) {
        compare_type = ct;
    }

    /*public*/ Trigger::CompareType IntTrigger::getCompareType() {
        return (compare_type);
    }

    /*public*/ void IntTrigger::propertyChange(PropertyChangeEvent* event) {
        int next;
        bool compare = false;

        // Validate
        // If no target, or not a name match, or no trigger, or no action
        // then just return quickly.
        // Careful: Takes advantage of "lazy OR" behavior
        if (target == NULL) {
            log->debug("Quit.  No target.");
            return;
        }
        if (event->getPropertyName()==(this->getEventName()) != true) {
            log->debug("Quit. Event name mismatch event = " + event->getPropertyName() + " this = " + this->getEventName());
            return;
        }
        if (this->getTriggerType() == NONE) {
            log->debug("Quit.  TriggerType = NONE");
            return;
        }
        if (this->getTargetAction() == NOTHING) {
            log->debug("Quit.  TargetAction = NOTHING");
            return;
        }

        // Compare
        next =  event->getNewValue().toInt();
        switch (compare_type) {
            case GT:
                compare = (next > notch);
                break;
            case LT:
                compare = (next < notch);
                break;
            case GTE:
                compare = (next >= notch);
                break;
            case LTE:
                compare = (next <= notch);
                break;
            case EQ:
            default:
                compare = (next == notch);
                break;
        }

        if (compare) {
            this->callback->takeAction();
        }
    }

    //@Override
    /*public*/ void IntTrigger::setXml(QDomElement e) {
        // Grab common stuff.
        Trigger::setXml(e);
        // Only do this if this is a BoolTrigger type Element
        if (e.attribute("type")==("INT")) {
            notch = e.firstChildElement("match").text().toInt();

            const QMetaObject &mo = Trigger::staticMetaObject;
            int index = mo.indexOfEnumerator("CompareType");
            QMetaEnum metaEnum = mo.enumerator(index);
            //compare_type = Trigger.CompareType.valueOf(e.getChild("compare-type").getValue().toUpperCase());
            compare_type = (CompareType)metaEnum.keyToValue(e.firstChildElement("compare-type").text().toUpper().toLatin1());
        }
    }
