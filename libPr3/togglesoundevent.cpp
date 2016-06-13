#include "togglesoundevent.h"
#include "jtogglebutton.h"
#include "trigger.h"
#include <QDomElement>
#include "buttontrigger.h"
#include "logger.h"
#include <QMetaEnum>

///*ToggleSoundEvent::*/ToggleSoundEvent(QObject *parent) :
//  SoundEvent(parent)
//{
//}
///*public*/ class ToggleSoundEvent extends SoundEvent implements PropertyChangeListener {



    /*public*/ ToggleSoundEvent::ToggleSoundEvent(QObject *parent) :
  SoundEvent("", "", parent)
{
        //his(null, null);
 log = new Logger("ToggleSoundEvent");
    }

    /*public*/ ToggleSoundEvent::ToggleSoundEvent(QString n,QObject *parent) :
  SoundEvent(n,n,parent)
{
        //this(n, n);
 log = new Logger("ToggleSoundEvent");
    }

    /*public*/ ToggleSoundEvent::ToggleSoundEvent(QString n, QString bl,QObject *parent) :
  SoundEvent(n,bl,parent)
{
    //super(n, bl);
    button = NULL;
    log = new Logger("ToggleSoundEvent");
}

//@Override
/*public*/ bool ToggleSoundEvent::hasButton() {
    if ((buttontype == NONE) || (buttontype == ENGINE) || (button == NULL)) {
        return (false);
    } else {
        return (true);
    }
}

/*public*/ void ToggleSoundEvent::setButton(JToggleButton* b) {
    button = b;
}

//@Override
/*public*/ QAbstractButton* ToggleSoundEvent::getButton() {
    return (button);
}

//@Override
/*public*/ void ToggleSoundEvent::setButtonLabel(QString bl) {
    button->setText(bl);
}

//@Override
/*public*/ QString ToggleSoundEvent::getButtonLabel() {
    return (button->text());
}

//@Override
/*protected*/ ButtonTrigger* ToggleSoundEvent::setupButtonAction(QDomElement te) {
    bt = new ButtonTrigger(te.attribute("name"));
    button_trigger_list.insert(bt->getName(), bt);
    log->debug(tr("new ButtonTrigger ") + bt->metaObject()->className() + " name " + bt->getName() + " type " + this->getButtonType());
    if (bt != NULL) {
     const QMetaObject &mo = SoundEvent::staticMetaObject;
     int index = mo.indexOfEnumerator("ButtonType");
     QMetaEnum metaEnum = mo.enumerator(index);

        log->debug("name " + bt->getName() + " type " + metaEnum.valueToKey( this->getButtonType()));
    }
    if (button == NULL) {
        log->error("BUTTON SHOULD NOT BE NULL");
        return bt;
    }
// TODO:        button->addActionListener(bt);
    return (bt);
}

//@Override
/*public*/ QDomElement ToggleSoundEvent::getXml() {
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
/*public*/ void ToggleSoundEvent::setXml(QDomElement el) {
this->setXml(el,NULL);
}
//@Override
/*public*/ void ToggleSoundEvent::setXml(QDomElement el, VSDFile* vf) {

    // Create the button first... (put this in constructor?)
    button = new JToggleButton();
    button->setVisible(true);

    // Handle common stuff
    SoundEvent::setXml(el, vf);

    // Get the SoundEvent's button type and create it.
    button->setText(el.attribute("label"));

    /*
     for (ButtonTrigger bt : button_trigger_list.values()) {
     log->debug("Button Trigger: " + bt.getName());
     log->debug("  Target: " + bt.getTarget().getName());
     log->debug("  Action: " + bt.getTargetAction().toString());
     }

     MouseListener [] listeners = button.getListeners(MouseListener.class);
     for (MouseListener l : listeners) {
     log->debug("Listener: " + l.toString());
     }
     */
}  // end setXml()

