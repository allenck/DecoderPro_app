#include "buttontrigger.h"
#include "logger.h"
#include "triggerlistener.h"
#include "QAbstractButton"
#include <QDomElement>
#include "vsdsound.h"

//ButtonTrigger::ButtonTrigger(QObject *parent) :
//  Trigger(parent)
//{
//}
///*public*/ class ButtonTrigger extends Trigger implements PropertyChangeListener, ActionListener, MouseListener {


/*public*/ ButtonTrigger::ButtonTrigger(QString name,QObject *parent) :
Trigger(name,parent) {
    //this(name, false);
 match_value = false;
 log = new Logger("ButtonTrigger");
}

/*public*/ ButtonTrigger::ButtonTrigger(QString name, bool bv,QObject *parent) :
Trigger(name,parent)
{
 //super(name);
 this->setTriggerType(Trigger::BUTTON);
 match_value = bv;
 log = new Logger("ButtonTrigger");
}

/*public*/ void ButtonTrigger::setMatchValue(bool bv) {
    match_value = bv;
}

/*public*/ bool ButtonTrigger::getMatchValue() {
    return (match_value);
}

// Button action functions called directly from the enclosing SoundEvent.
/*public*/ void ButtonTrigger::mouseDown()
{
 log->debug("buttonTrigger " + getName() + " mouseDown() called.");
 if (match_value) {
     this->callback->takeAction();
 }
}

/*public*/ void ButtonTrigger::mouseUp()
{
    log->debug("buttonTrigger " + getName() + " mouseUp() called.");
    if (!match_value) {
        this->callback->takeAction();
    }
}

/*public*/ void ButtonTrigger::click(bool v) {
    log->debug("buttonTrigger " + getName() + " click( " + v + ") called.");
    if (v == match_value) {
        this->callback->takeAction();
    }
}

// PropertyChangeListener functions
/*public*/ void ButtonTrigger::propertyChange(PropertyChangeEvent* event) {
    // Button triggers respond to the button methods above, not to
    // property change events.  Do nothing.
}

// ActionListener function(s)
/*public*/ void ButtonTrigger::actionPerformed(JActionEvent* /*e*/)
{
    log->debug("ButtonTrigger.actionPerformed() " + this->getName());
// TODO:        this->click(((QAbstractButton*) e.getSource()).isSelected());
}

// MouseListener functions
/*public*/ void ButtonTrigger::mousePressed(QMouseEvent* e) {
    log->debug("MouseListener.mousePressed() " + this->getName());
    this->mouseDown();
}

/*public*/ void ButtonTrigger::mouseReleased(QMouseEvent* e) {
    log->debug("MouseListener.mouseReleased() " + this->getName());
    this->mouseUp();
}

/*public*/ void ButtonTrigger::mouseEntered(QMouseEvent* e) {
}

/*public*/ void ButtonTrigger::mouseExited(QMouseEvent* e) {
}

/*public*/ void ButtonTrigger::mouseClicked(QMouseEvent* e) {
}

//@Override
/*public*/ QDomElement ButtonTrigger::getXml()
{
    QDomElement me = QDomElement();
    me.setTagName("Trigger");
    log->debug("Bool Trigger getXml():");
    log->debug("  trigger_name = " + this->getName());
    log->debug("  event_name = " + this->event_name);
    log->debug("  target_name = " + target->getName());
    log->debug("  match = " + (match_value)?"true":"false");
//        log->debug("  action = " + this->getTriggerType().toString());

    me.setAttribute("name", this->getName());
    me.setAttribute("type", "BOOLEAN");

//        me.addContent(new Element("event-name").addContent(event_name));
    QDomElement me1 = QDomElement();
    me1.setTagName("event-name");
    QDomText t1 = QDomText();
    t1.setData(event_name);
    me1.appendChild(t1);
    me.appendChild(me1);
//        me.addContent(new Element("target-name").addContent(target.getName()));
    QDomElement me2 = QDomElement();
    me2.setTagName("target-name");
    QDomText t2 = QDomText();
    t2.setData(target->getName());
    me2.appendChild(t2);
    me.appendChild(me2);
//        me.addContent(new Element("match").addContent(Boolean.valueOf(match_value).toString()));
    QDomElement me3 = QDomElement();
    me3.setTagName("match");
    QDomText t3 = QDomText();
//    t3.setData(match_value.toBool());
    me2.appendChild(t3);
    me.appendChild(me3);
//        me.addContent(new Element("action").addContent(this->getTriggerType().toString()));
    QDomElement me4 = QDomElement();
    me3.setTagName("action");
    QDomText t4 = QDomText();
//    t4.setData(this->getTriggerType().toString());
    me4.appendChild(t4);
    me.appendChild(me4);

    return (me);
}

//@Override
/*public*/ void ButtonTrigger::setXml(QDomElement e) {
    // Get common stuff
    Trigger::setXml(e);
    // Only do this if this is a ButtonTrigger type Element
    if (e.attribute("type")==("BUTTON")) {
     match_value = (e.firstChildElement("match").text()== "true");
    }
}
