#include "enginesoundevent.h"
#include "logger.h"
#include "trigger.h"
#include "buttontrigger.h"
#include "dieselpane.h"
#include "vsdsound.h"
#include "propertychangeevent.h"
#include "vsdecoder.h"
#include "enginesound.h"

//EngineSoundEvent::EngineSoundEvent(QObject *parent) :
//  SoundEvent(parent)
//{
//}
///*public*/ class EngineSoundEvent extends SoundEvent implements PropertyChangeListener {


/*
 Trigger t; // used in setXml as a temporary holder for creating the
 // event listener class.

 ButtonTrigger bt; // used in setupButtonAction() as a temporary holder
 // for creating the button listeners.
 */
/*public*/ EngineSoundEvent::EngineSoundEvent(QObject *parent) :
  SoundEvent("","", parent) {
    //this(NULL , NULL );
 engine_pane = NULL;
 log = new Logger("EngineSoundEvent");
}

/*public*/ EngineSoundEvent::EngineSoundEvent(QString n, QObject *parent) :
  SoundEvent(n,n, parent) {
    //this(n, n);
 engine_pane = NULL;
 log = new Logger("EngineSoundEvent");
}

/*public*/ EngineSoundEvent::EngineSoundEvent(QString n, QString bl, QObject *parent) :
  SoundEvent(n,bl, parent) {
    //super(n, bl);
    engine_pane = NULL;
    log = new Logger("EngineSoundEvent");
}

//@Override
/*public*/ bool EngineSoundEvent::hasButton() {
    if ((buttontype == NONE) || (buttontype == ENGINE) || (button == NULL)) {
        return (false);
    } else {
        return (true);
    }
}

//@Override
/*public*/ bool EngineSoundEvent::hasEnginePane() {
    if ((buttontype == ENGINE) && (engine_pane != NULL )) {
        return (true);
    } else {
        return (false);
    }
}

//@Override
/*public*/ QAbstractButton* EngineSoundEvent::getButton() {
    log->debug("engine getButton() called.");
    //return (engine_pane);
    return NULL;
}

//@Override
/*public*/ EnginePane* EngineSoundEvent::getEnginePane() {
    return (engine_pane);
}

//@Override
/*public*/ void EngineSoundEvent::setEnginePane(EnginePane* e) {
    engine_pane = e;
}

//@Override
/*public*/ void EngineSoundEvent::setButtonLabel(QString bl) {
    // can't do this.  Yet.
}

//@Override
/*public*/ QString EngineSoundEvent::getButtonLabel() {
    // can't do this. Yet.
    //return(engine_pane.getText());
    return ("Text");
}

//@Override
/*protected*/ ButtonTrigger* EngineSoundEvent::setupButtonAction(QDomElement te) {
    /*
     MouseListener ml;
     bt = new ButtonTrigger(te.getAttributeValue("name"));
     button_trigger_list.put(bt->getName(), bt);
     log->debug("new ButtonTrigger " + bt->getName() + " type " + btype.toString());
     switch(btype) {
     case TOGGLE:
     this.getButton().addActionListener(bt);
     break;
     case MOMENTARY:
     default:
     this.getButton().addMouseListener(bt);
     // Just send the trigger a click.
     }
     return(bt);  // cast OK since we just instantiated it up above.
     */
    return (NULL );  // cast OK since we just instantiated it up above.
}

/*public*/ void EngineSoundEvent::guiAction(PropertyChangeEvent* evt) {
    if (evt->getPropertyName()==("throttle")) {
        log->debug("GUI throttle changed.  New value = " + evt->getNewValue().toString());
    } else if (evt->getPropertyName()==("start")) {
        log->debug("GUI Start button changed. New value = " + evt->getNewValue().toString());
        if ( evt->getNewValue().toBool() == true) {
            ((EngineSound*) parent->getSound("ENGINE"))->startEngine();
        } else {
            ((EngineSound*) parent->getSound("ENGINE"))->stopEngine();
        }
    }
}

//@Override
/*public*/ void EngineSoundEvent::propertyChange(PropertyChangeEvent* event) {
    SoundEvent::propertyChange(event);
    if (event->getPropertyName()==("SpeedSetting")) {
        ((EngineSound*) parent->getSound("ENGINE"))->handleSpeedChange( event->getNewValue().toFloat(), engine_pane);
    }
    //engine_pane.setThrottle(EngineSound.calcEngineNotch((Float)event.getNewValue()));
}

//@Override
/*public*/ QDomElement EngineSoundEvent::getXml() {
    //QDomElement me = new Element("SoundEvent");
QDomElement me = QDomElement();
me.setTagName("SoundEvent");
    me.setAttribute("name", name);
    me.setAttribute("label", me.text());
    foreach (Trigger* t, trigger_list.values()) {
        me.appendChild(t->getXml());
    }

    return (me);
}

//@Override
/*public*/ void EngineSoundEvent::setXml(QDomElement el) {
    this->setXml(el, NULL );
}

// @Override
/*public*/ void EngineSoundEvent::setXml(QDomElement el, VSDFile* vf) {

    // Create the "button"  (should this be in constructor)
    log->debug("Creating DieselPane");
    engine_pane = new DieselPane("Engine");
    engine_pane->setVisible(true);

    // Handle common stuff
    SoundEvent::setXml(el, vf);

    // Get the SoundEvent's button type and create it.
//        engine_pane.addPropertyChangeListener(new PropertyChangeListener() {
//            /*public*/ void propertyChange(PropertyChangeEvent evt) {
//                guiAction(evt);
//            }
//        });
    connect(engine_pane, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    foreach (ButtonTrigger* bt, button_trigger_list.values()) {
        log->debug("Button Trigger: " + bt->getName());
        log->debug("  Target: " + bt->getTarget()->getName());
// TODO:           log->debug("  Action: " + bt->getTargetAction().toString());
    }

    foreach (Trigger* bt, trigger_list.values()) {
        log->debug("Trigger: " + bt->getName());
        log->debug("  Target: " + bt->getTarget()->getName());
// TODO:           log->debug("  Action: " + bt->getTargetAction().toString());
    }
}  // end setXml()
