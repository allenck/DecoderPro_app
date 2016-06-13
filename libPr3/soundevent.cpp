#include "soundevent.h"
#include "trigger.h"
#include "vsdsound.h"
#include <QAbstractButton>
#include "vsdecoder.h"
#include <QMetaEnum>
#include "logger.h"
#include "booltrigger.h"
#include "floattrigger.h"
#include "inttrigger.h"
#include "notchtrigger.h"
#include "throttletrigger.h"
#include "buttontrigger.h"

//SoundEvent::SoundEvent(QObject *parent) :
//  QObject(parent)
//{
//}
///*public*/ class SoundEvent implements PropertyChangeListener {


    /*public*/ SoundEvent::SoundEvent(QObject *parent) :
    QObject(parent)
{
        //this(NULL, NULL);
 name = "";
 button_label = "";
 trigger_list = QMap<QString, Trigger*>();
 button_trigger_list = QMap<QString, ButtonTrigger*>();
 button = NULL;
 bt = NULL;
 log = new Logger("SoundEvent");
    }

    /*public*/ SoundEvent::SoundEvent(QString n,QObject *parent) :
    QObject(parent)
{
       // this(n, n);
 name = n;
 button_label = n;
 trigger_list = QMap<QString, Trigger*>();
 button_trigger_list = QMap<QString, ButtonTrigger*>();
 button = NULL;
 bt = NULL;
 log = new Logger("SoundEvent");

}

/*public*/ SoundEvent::SoundEvent(QString n,QString bl,QObject *parent) :
QObject(parent)
{
 name = n;
 button_label = bl;
 trigger_list = QMap<QString, Trigger*>();
 button_trigger_list = QMap<QString, ButtonTrigger*>();
 button = NULL;
 bt = NULL;
 log = new Logger("SoundEvent");
}

/*public*/ void SoundEvent::setName(QString n) {
    name = n;
}

/*public*/ QString SoundEvent::getName() {
    return (name);
}

/*public*/ void SoundEvent::setEventName(QString n) {
    event_name = n;
}

/*public*/ QString SoundEvent::getEventName() {
    return (event_name);
}

/*public*/ SoundEvent::ButtonType SoundEvent::getButtonType() {
    return (buttontype);
}

/*public*/ bool SoundEvent::hasButton() {
    if ((buttontype == NONE) || (buttontype == ENGINE) || (button == NULL)) {
        return (false);
    } else {
        return (true);
    }
}

/*public*/ bool SoundEvent::hasEnginePane() {
    if ((buttontype == ENGINE) && (engine_pane != NULL)) {
        return (true);
    } else {
        return (false);
    }
}

/*public*/ void SoundEvent::setButton(QAbstractButton* b) {
    button = b;
}

/*public*/QAbstractButton* SoundEvent::getButton() {
    if ((buttontype == NONE) || (buttontype == ENGINE)) {
        return (NULL);
    } else {
        return (button);
    }
}

/*public*/ EnginePane* SoundEvent::getEnginePane() {
    if (buttontype == ENGINE) {
        return (engine_pane);
    } else {
        return (NULL);
    }
}

/*public*/ void SoundEvent::setEnginePane(EnginePane* e) {
    engine_pane = e;
}

/*public*/ void SoundEvent::setButtonLabel(QString bl) {
    button->setText(bl);
}

/*public*/ QString SoundEvent::getButtonLabel() {
    return (button->text());
}

/*public*/ void SoundEvent::addTrigger(QString s, Trigger* t) {
    trigger_list.insert(s, t);
}

/*public*/ Trigger*SoundEvent:: getTrigger(QString s) {
    return trigger_list.value(s);
}

/*public*/ void SoundEvent::setSound(VSDSound* v) {
    my_sound = v;
}

/*public*/ VSDSound* SoundEvent::getSound() {
    return (my_sound);
}

/*public*/ void SoundEvent::setParent(VSDecoder* v) {
    parent = v;
}

/*public*/ VSDecoder* SoundEvent::getParent() {
    return parent;
}

/*public*/ void SoundEvent::propertyChange(PropertyChangeEvent* event) {
    foreach (Trigger* t, trigger_list.values()) {
        t->propertyChange(event);
    }
}

// What's wrong here:
// the anonymous MouseListeners are storing a reference to BT, which keeps getting replaced
// each time the function is called.
// what we need to do is (maybe) make the ButtonTrigger itself a MouseListener (and ActionListener)
//
/*protected*/ ButtonTrigger* SoundEvent::setupButtonAction(QDomElement te) {
    /*
     MouseListener ml;
     bt = new ButtonTrigger(te.attribute("name"));
     button_trigger_list.put(bt.getName(), bt);
     log->debug("new ButtonTrigger " + bt.getName() + " type " + btype.toString());
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
    return (NULL);  // cast OK since we just instantiated it up above.
}

/*public*/ QDomElement SoundEvent::getXml() {
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

/*public*/ void SoundEvent::setXml(QDomElement el) {
    this->setXml(el, NULL);
}

    //@SuppressWarnings("cast")
/*protected*/ void SoundEvent::addXmlTrigger(QDomElement te, VSDFile* vf)
{
 QString tts;
 Trigger::TriggerType tt;
 const QMetaObject &mo = Trigger::staticMetaObject;
 int index = mo.indexOfEnumerator("TriggerType");
 QMetaEnum metaEnum = mo.enumerator(index);
 t = NULL;

#if 1
 tts = te.attribute("type");
 if(tts !=  "")
 {
  //tt = Trigger.TriggerType.valueOf(tts.toUpperCase());
  tt = (Trigger::TriggerType)metaEnum.keyToValue(tts.toUpper().toLatin1());
  if(tt < 0)
   log->error(tr("converting enum Trigger::TriggerType '%1").arg(tts));
 }
 else
 {
  tt = Trigger::NONE;
 }

 switch (tt)
 {
     case Trigger::BUTTON:
         if (this->buttontype != SoundEvent::NONE)
         {
          t = new ButtonTrigger(te.attribute("name"));
             //t = (Trigger*)setupButtonAction(te);
          addButtonMouseHandler((ButtonTrigger*)t);
         }
         break;
     case Trigger::BOOLEAN:
         t = (Trigger*)new BoolTrigger(te.attribute("name"));
         break;
     case Trigger::FLOAT:
         t = (Trigger*)new FloatTrigger(te.attribute("name"), 0.0f, Trigger::EQ);
         break;
     case Trigger::NOTCH:
         t = (Trigger*)new NotchTrigger(te.attribute("name"));
         break;
     case Trigger::INT:
         t = (Trigger*)new IntTrigger(te.attribute("name"));
         break;
     case Trigger::STRING:
         //t = new StringTrigger(el.attribute("name"));
         log->warn("Don't have StringTriggers yet...");
         t = NULL;
         return;
     case Trigger::THROTTLE:
         t = (Trigger*)new ThrottleTrigger(te.attribute("name"));
         break;
     case NONE:
     default:
         break;
 }
 if(t!= NULL)
 {

  log->debug("Building trigger " + t->getName());
  t->setXml(te);
  trigger_list.insert(te.attribute("name"), t);
  //log->debug("target name " + t.getTargetName() + " sound " + parent.getSound(t.getTargetName()));
  t->setTarget(parent->getSound(t->getTargetName()));
  //log->debug("target " + t.getTarget());

  if (t->getTarget() == NULL) {
      // If the target is missing, set up a do-nothing operation.
      // Protects against errors in the XML file.
      // Should probably post a warning, though.
      t->setTargetAction(Trigger::NOTHING);
  }
  switch (t->getTargetAction())
  {
     case Trigger::PLAY:
     case Trigger::FADEIN:
         //log->debug("PLAY");
#if 1
         t->setCallback(new PlayCallback(t));
//                {
//                    /*public*/ void takeAction() {
//                        t.getTarget().play();
//                    }

//                    /*public*/ void takeAction(int i) {
//                    }

//                    /*public*/ void takeAction(float f) {
//                    } // do nothing
//                });
#endif
         break;
     case Trigger::LOOP:
         //log->debug("LOOP");

         t->setCallback(new LoopCallback(t));
//         {
//             /*public*/ void takeAction() {
//                 t->getTarget().loop();
//             }

//             /*public*/ void takeAction(int i) {
//             }

//             /*public*/ void takeAction(float f) {
//             } // do nothing
//         });
         break;
     case Trigger::STOP:
     case Trigger::FADEOUT:
         //log->debug("STOP");
         t->setCallback(new StopCallback(t));
//             /*public*/ void takeAction() {
//                 t.getTarget().stop();
//             }

//             /*public*/ void takeAction(int i) {
//             }

//             /*public*/ void takeAction(float f) {
//             } // do nothing
//         });
         break;
     case Trigger::NOTCH:
         //log->debug("NOTCH");
         log->debug("making callback t " + t->getName() + " target " + t->getTarget()->getName());

         t->setCallback(new NotchCallback(t));
//         {
//             /*public*/ void takeAction(int i) {
//                 //log->debug("Notch Trigger Listener. t = " + t + " Target = " + t.getTarget() + " notch = " + i);
//                 t.getTarget().changeNotch(i);
//             }

//             /*public*/ void takeAction() {
//             }

//             /*public*/ void takeAction(float f) {
//             } // do nothing
//         });

         break;
     case Trigger::CHANGE:
         //log->debug("CHANGE");
#endif
         log->debug("making callback t " + t->getName() + " target " + t->getTarget()->getName());

         t->setCallback(new ChangeCallback(t));
//                    {
//             /*public*/ void takeAction() {
//             } // do nothing

//             /*public*/ void takeAction(int i) {
//             } // do nothing

//             /*public*/ void takeAction(float f) {
//                 //log->debug("Throttle Trigger Listener. t = " + t + " Target = " + t.getTarget() + " value = " + f);
//                 t.getTarget().changeThrottle(f);
//             }
//         });

         break;
     case Trigger::NOTHING:
         // Used for when the target sound is missing.
         //log->debug("NOTHING");

         t->setCallback(new NothingCallback(t));
//         {
//             /*public*/ void takeAction() {
//             } // do nothing

//             /*public*/ void takeAction(int i) {
//             } // do nothing

//             /*public*/ void takeAction(float f) {
//             } // do nothing
//         });
         break;
     default:
         // do nothing.
         break;
  } // end switch
 }
} // end function

/*public*/ void SoundEvent::setXml(QDomElement el, VSDFile* vf) {
 QDomElement te;
 QString btv;
 const QMetaObject &mo = SoundEvent::staticMetaObject;
 int index = mo.indexOfEnumerator("ButtonType");
 QMetaEnum metaEnum = mo.enumerator(index);
 // Get the SoundEvent's name.
 name = el.attribute("name");
 if ((btv = el.attribute("buttontype")) != "")
 {
     //buttontype = SoundEvent::ButtonType.valueOf(btv.toUpperCase());
  int value = metaEnum.keyToValue(name.toLatin1());
  buttontype = (ButtonType)value;
 } else {
     buttontype = SoundEvent::NONE;
 }

 // Get the SoundEvent's Triggers and set them up.
 //Iterator<Element> itr = (el.getChildren("trigger")).iterator();
 QDomNodeList l = el.elementsByTagName("trigger");
 //while (itr.hasNext()) {
 for(int i=0; i < l.count(); i++)
 {
     //te = itr.next();
  te = l.at(i).toElement();
     this->addXmlTrigger(te, vf);
 } // end while
}  // end setXml()

PlayCallback::PlayCallback(Trigger *t) { this->t =t;}

/*public*/ void PlayCallback::takeAction() {
    t->getTarget()->play();
}

/*public*/ void PlayCallback::takeAction(int i) {
}

/*public*/ void PlayCallback::takeAction(float f) {
} // do nothing

void SoundEvent::addButtonMouseHandler(ButtonTrigger* bt) {}

LoopCallback::LoopCallback(Trigger *t) {this->t = t;}
/*public*/ void LoopCallback::takeAction() {
    t->getTarget()->loop();
}

/*public*/ void LoopCallback::takeAction(int i) {
}

/*public*/ void LoopCallback::takeAction(float f) {
} // do nothing

StopCallback::StopCallback(Trigger *t) {this->t = t;}
/*public*/ void StopCallback::takeAction() {
    t->getTarget()->stop();
}

/*public*/ void StopCallback::takeAction(int i) {
}

/*public*/ void StopCallback::takeAction(float f) {
} // do nothing

NothingCallback::NothingCallback(Trigger *t) {this->t = t;}
/*public*/ void NothingCallback::takeAction() {
}

/*public*/ void NothingCallback::takeAction(int i) {
}

/*public*/ void NothingCallback::takeAction(float f) {
} // do nothing

ChangeCallback::ChangeCallback(Trigger*t) {this->t = t;}

/*public*/ void ChangeCallback::takeAction() {
} // do nothing

/*public*/ void ChangeCallback::takeAction(int i) {
} // do nothing

/*public*/ void ChangeCallback::takeAction(float f) {
    //log->debug("Throttle Trigger Listener. t = " + t + " Target = " + t.getTarget() + " value = " + f);
    t->getTarget()->changeThrottle(f);
}

NotchCallback::NotchCallback(Trigger* t) {this->t = t;}
/*public*/ void NotchCallback::takeAction(int i) {
    //log->debug("Notch Trigger Listener. t = " + t + " Target = " + t.getTarget() + " notch = " + i);
    t->getTarget()->changeNotch(i);
}

/*public*/ void NotchCallback::takeAction() {
}

/*public*/ void NotchCallback::takeAction(float f) {
} // do nothing
