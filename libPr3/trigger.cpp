#include "trigger.h"
#include <QDomElement>
#include <QMetaEnum>

//Trigger::Trigger(QObject *parent) :
//  QObject(parent)
//{
//}
//abstract /*public*/ class Trigger implements PropertyChangeListener {



/*public*/ Trigger::Trigger(QString name,QObject* parent) : QObject(parent)
{
    trigger_name = name;
    event_name = "";
    target = NULL;
    target_action = NOTHING;
    trigger_type = NONE;
    target_name = "";
    callback = NULL;
}

/*abstract*/ /*public*/ void Trigger::propertyChange(PropertyChangeEvent* event) {}

// JavaBean set/get functions
/*public*/ void Trigger::setName(QString tn) {
    trigger_name = tn;
}

/*public*/ QString Trigger::getName() {
    return (trigger_name);
}

/*public*/ void Trigger::setEventName(QString en) {
    event_name = en;
}

/*public*/ QString Trigger::getEventName() {
    return (event_name);
}

/*public*/ void Trigger::setTarget(VSDSound* tgt) {
    target = tgt;
}

/*public*/ VSDSound* Trigger::getTarget() {
    return (target);
}

/*public*/ void Trigger::setTargetName(QString tn) {
    target_name = tn;
}

/*public*/ QString Trigger::getTargetName() {
    return (target_name);
}

/*public*/ void Trigger::setTargetAction(TargetAction ta) {
    target_action = ta;
}

/*public*/ Trigger::TargetAction Trigger::getTargetAction() {
    return (target_action);
}

/*public*/ void Trigger::setTriggerType(TriggerType ta) {
    trigger_type = ta;
}

/*public*/ Trigger::TriggerType Trigger::getTriggerType() {
    return (trigger_type);
}

/*public*/ void Trigger::setCallback(TriggerListener* cb) {
    callback = cb;
}

/*public*/ TriggerListener* Trigger::getCallback() {
    return (callback);
}

/*public*/ QDomElement Trigger::getXml() {
QDomElement me = QDomElement();
me.setTagName("trigger");
    me.setAttribute("name", trigger_name);
    me.setAttribute("type", "empty");
    // do something, eventually...
    return (me);
}

/*public*/ void Trigger::setXml(QDomElement e) {
    // Grab XML content that's common to all Triggers
    trigger_name = e.attribute("name");
    event_name = e.firstChildElement("event-name").text();
    target_name = e.firstChildElement("target-name").text();
    //try {
    //this->setTargetAction(TargetAction::valueOf(e.firstChildElement("action")));
    const QMetaObject &mo = Trigger::staticMetaObject;
    int index = mo.indexOfEnumerator("TargetAction");
    QMetaEnum metaEnum = mo.enumerator(index);
    setTargetAction((TargetAction)metaEnum.keyToValue(e.firstChildElement("action").text().toUpper().toLatin1()));

//        } catch (IllegalArgumentException iea) {
//            this->setTargetAction(NOTHING);
//        } catch (NullPointerException npe) {
//            this->setTargetAction(NOTHING);
//        }
}
