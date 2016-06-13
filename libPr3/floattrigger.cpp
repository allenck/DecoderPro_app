#include "floattrigger.h"
#include "logger.h"
#include <QDomElement>
#include "propertychangeevent.h"
#include "vsdsound.h"
#include "triggerlistener.h"
#include <QMetaEnum>

//FloatTrigger::FloatTrigger(QObject *parent) :
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

//class FloatTrigger extends Trigger implements PropertyChangeListener {


    /*public*/ FloatTrigger::FloatTrigger(QString name, float next, Trigger::CompareType ct, QObject *parent) :
  Trigger(name,parent)
{
        //super(name);
        this->setTriggerType(FLOAT);
        match_value = next;
        compare_type = ct;
        log = new Logger("FloatTrigger");
    }

    /*public*/ void FloatTrigger::setMatchValue(float next) {
        match_value = next;
    }

    /*public*/ float FloatTrigger::getMatchValue() {
        return (match_value);
    }

    /*public*/ void FloatTrigger::setCompareType(CompareType ct) {
        compare_type = ct;
    }

    /*public*/ FloatTrigger::CompareType FloatTrigger::getCompareType() {
        return (compare_type);
    }

    /*public*/ void FloatTrigger::propertyChange(PropertyChangeEvent* event) {
        float next;
        bool compare = false;
        int compare_val;

        // Validate
        // If no target, or not a name match, or no trigger, or no action
        // then just return quickly.
        // Careful: Takes advantage of "lazy OR" behavior
        if (target == NULL ) {
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
        next =  event->getNewValue().toFloat(); // HACK!  Needs to be flexible.
        compare_val = next - (match_value);
        switch (compare_type) {
            case GT:
                compare = (compare_val > 0);
                break;
            case LT:
                compare = (compare_val < 0);
                break;
            case GTE:
                compare = (compare_val >= 0);
                break;
            case LTE:
                compare = (compare_val <= 0);
                break;
            case EQ:
            default:
                compare = (compare_val == 0);
                break;
        }

        log->debug("compareTrigger match_value = " + QString::number(match_value) + " next = " + QString::number(next) + " compare_val = " + QString::number(compare_val) + " compare = " + (compare?"true":"false"));

        if (compare) {
            log->debug("compareTrigger taking action");
            this->callback->takeAction();
        }
    }

    //@Override
    /*public*/ QDomElement FloatTrigger::getXml() {
        //QDomElement me = new Element("trigger");
 QDomElement me = QDomElement();
 me.setTagName("trigger");
        me.setAttribute("name", this->getName());
        me.setAttribute("type", "FLOAT");
        log->warn("CompareTrigger.getXml() not implemented");
        return (me);
    }

    //@Override
    /*public*/ void FloatTrigger::setXml(QDomElement e) {
        log->warn("FloatTrigger.setXml()");

        //Get common stuff
        Trigger::setXml(e);

        if (e.attribute("type")==("FLOAT")) {
            match_value = e.firstChildElement("match").text().toFloat() /*+ "f"*/;

            const QMetaObject &mo = Trigger::staticMetaObject;
            int index = mo.indexOfEnumerator("CompareType");
            QMetaEnum metaEnum = mo.enumerator(index);
            //compare_type = Trigger::CompareType.valueOf(e.getChild("compare-type").getValue().toUpperCase());
            compare_type = (CompareType) metaEnum.keyToValue(e.firstChildElement("compare-type").text().toUpper().toLatin1());
        }
    }
