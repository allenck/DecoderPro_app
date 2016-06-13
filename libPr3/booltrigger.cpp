#include "booltrigger.h"
#include "logger.h"
#include <QDomElement>
#include "propertychangeevent.h"
#include "triggerlistener.h"
#include "vsdsound.h"

//BoolTrigger::BoolTrigger(QObject *parent) :
//  Trigger(parent)
//{
//}
//class BoolTrigger extends Trigger implements PropertyChangeListener {


    /*public*/ BoolTrigger::BoolTrigger(QString name,QObject *parent) :
      Trigger(name, parent) {
        //this(name, false);
 match_value = false;
    }

    /*public*/ BoolTrigger::BoolTrigger(QString name, bool bv,QObject *parent) :
      Trigger(name, parent) {
        //super(name);
        this->setTriggerType(Trigger::BOOLEAN);
        match_value = bv;
    }

    /*public*/ void BoolTrigger::setMatchValue(bool bv) {
        match_value = bv;
    }

    /*public*/ bool BoolTrigger::getMatchValue() {
        return (match_value);
    }

    //@Override
    /*public*/ void BoolTrigger::propertyChange(PropertyChangeEvent* event) {
        // Validate
        // If no target, or not a name match, or no trigger, or no action
        // then just return quickly.
        // Careful: Takes advantage of "lazy OR" behavior
        if (target == NULL) {
            //log->debug("Quit.  No target.");
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
        if (match_value ==  event->getNewValue().toBool()) {
            this->callback->takeAction();
        }
    }

    //@Override
    /*public*/ QDomElement BoolTrigger::getXml() {
        //Element me = new Element("trigger");
     QDomElement me = QDomElement();
     me.setTagName("trigger");

        log->debug("Bool Trigger getXml():");
        log->debug("  trigger_name = " + this->getName());
        log->debug("  event_name = " + this->event_name);
        log->debug("  target_name = " + target->getName());
        log->debug(tr("  match = ") + (match_value?"true":"false"));
// TODO:        log->debug("  action = " + this->getTriggerType().toString());

        me.setAttribute("name", this->getName());
        me.setAttribute("type", "BOOLEAN");
#if 0
        me.addContent(new Element("event-name").addContent(event_name));
        me.addContent(new Element("target-name").addContent(target.getName()));
        me.addContent(new Element("match").addContent(Boolean.valueOf(match_value).toString()));
        me.addContent(new Element("action").addContent(this->getTriggerType().toString()));
#endif
        return (me);
    }

    //@Override
    /*public*/ void BoolTrigger::setXml(QDomElement e) {
        // Get common stuff
        Trigger::setXml(e);
        // Only do this if this is a BoolTrigger type Element
        if (e.attribute("type")==("BOOLEAN")) {
         match_value = e.firstChildElement("match").text()== "true";
        }
    }
