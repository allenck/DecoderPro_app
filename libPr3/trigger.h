#ifndef TRIGGER_H
#define TRIGGER_H

#include <QObject>

class QDomElement;
class PropertyChangeEvent;
class TriggerListener;
class VSDSound;
class Trigger : public QObject
{
 Q_OBJECT
public:
 //explicit Trigger(QObject *parent = 0);
 /*static*/ /*public*/ enum TriggerType
 {
     BUTTON, BOOLEAN, STRING, NONE, NOTCH, INT, FLOAT, THROTTLE
 };
 Q_ENUMS(TriggerType)

 /*static*/ /*public*/ enum TargetAction
 {
     PLAY=10, LOOP=11, STOP=12, FADEIN=13, FADEOUT=14, NOTCH2=15, CHANGE=16, NOTHING=17
 };
 Q_ENUMS(TargetAction)

 /*static*/ /*public*/ enum CompareType
 {
     EQ, GT, LT, GTE, LTE
 };
 Q_ENUMS(CompareType)

 /*static*/ /*public*/ enum CompareValueType
 {
  INT2, FLOAT2
 };
 Q_ENUMS(CompareValueType)

 /*public*/ Trigger(QString name, QObject*parent);
 /*abstract*/ virtual /*public*/ void propertyChange(PropertyChangeEvent* event);
 /*public*/ void setName(QString tn);
 /*public*/ QString getName() ;
 /*public*/ void setEventName(QString en);
 /*public*/ QString getEventName();
 /*public*/ void setTarget(VSDSound* tgt) ;
 /*public*/ VSDSound* getTarget();
 /*public*/ void setTargetName(QString tn);
 /*public*/ QString getTargetName() ;
 /*public*/ void setTargetAction(TargetAction ta) ;
 /*public*/ TargetAction getTargetAction();
 /*public*/ void setTriggerType(TriggerType ta);
 /*public*/ TriggerType getTriggerType();
 /*public*/ void setCallback(TriggerListener* cb);
 /*public*/ TriggerListener* getCallback();
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);


signals:

public slots:
private:
 QString trigger_name; // Name for the trigger object
 QString event_name;  // event to respond to
 QString target_name; // target to act on

 VSDSound* target;    // sound to work on
 /*private*/ TargetAction target_action; // action to take
 /*private*/ TriggerType trigger_type;
 TriggerListener* callback;
 friend class ButtonTrigger;
 friend class BoolTrigger;
 friend class ThrottleTrigger;
 friend class FloatTrigger;
 friend class NotchTrigger;
 friend class IntTrigger;
};

#endif // TRIGGER_H
