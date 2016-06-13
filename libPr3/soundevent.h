#ifndef SOUNDEVENT_H
#define SOUNDEVENT_H

#include <QObject>
#include <QMap>
#include "triggerlistener.h"


class Logger;
class VSDFile;
class QDomElement;
class PropertyChangeEvent;
class VSDSound;
class VSDecoder;
class ButtonTrigger;
class Trigger;
class QAbstractButton;
class EnginePane;
class SoundEvent : public QObject
{
 Q_OBJECT
public:
 //explicit SoundEvent(QObject *parent = 0);
 /*public*/ enum ButtonType {

     MOMENTARY, TOGGLE, ENGINE, NONE
 };
 Q_ENUMS(ButtonType)

 /*public*/ SoundEvent(QObject *parent = 0) ;
 /*public*/ SoundEvent(QString n,QObject *parent = 0);
 /*public*/ SoundEvent(QString n,QString bl,QObject *parent = 0);
 /*public*/ void setName(QString n);
 /*public*/ QString getName();
 /*public*/ void setEventName(QString n);
 /*public*/ QString getEventName();
 /*public*/ ButtonType getButtonType() ;
 /*public*/ virtual bool hasButton();
 /*public*/ virtual bool hasEnginePane();
 /*public*/ virtual void setButton(QAbstractButton* b) ;
 /*public*/ virtual QAbstractButton* getButton();
 /*public*/ virtual EnginePane* getEnginePane() ;
 /*public*/ virtual void setEnginePane(EnginePane* e);
 /*public*/ virtual void setButtonLabel(QString bl);
 /*public*/ virtual QString getButtonLabel() ;
 /*public*/ void addTrigger(QString s, Trigger* t);
 /*public*/ Trigger* getTrigger(QString s) ;
 /*public*/ void setSound(VSDSound* v) ;
 /*public*/ VSDSound* getSound() ;
 /*public*/ void setParent(VSDecoder* v);
 /*public*/ VSDecoder* getParent();
 /*public*/ virtual QDomElement getXml() ;
 /*public*/ virtual void setXml(QDomElement el) ;
 /*public*/ virtual void setXml(QDomElement el, VSDFile* vf);
 virtual void addButtonMouseHandler(ButtonTrigger* bt);

signals:

public slots:
 /*public*/ virtual void propertyChange(PropertyChangeEvent* event) ;

private:
 QString name;
 QString button_label;
 QString event_name;
 ButtonType buttontype;

 QAbstractButton* button;
 EnginePane* engine_pane;

 Trigger* t; // used in setXml as a temporary holder for creating the
 // event listener class.
 ButtonTrigger* bt; // used in setupButtonAction() as a temporary holder
 // for creating the button listeners.
 VSDecoder* parent;

 VSDSound* my_sound;
 Logger* log;

protected:
 /*protected*/ QMap<QString, ButtonTrigger*> button_trigger_list;

 /*protected*/ QMap<QString, Trigger*> trigger_list;
 // What's wrong here:
 // the anonymous MouseListeners are storing a reference to BT, which keeps getting replaced
 // each time the function is called.
 // what we need to do is (maybe) make the ButtonTrigger itself a MouseListener (and ActionListener)
 //
 /*protected*/ virtual ButtonTrigger* setupButtonAction(QDomElement te);
 /*protected*/ void addXmlTrigger(QDomElement te, VSDFile* vf);
friend class MomentarySoundEvent;
friend class ToggleSoundEvent;
friend class EngineSoundEvent;
};
class PlayCallback : public TriggerListener
{
 Q_OBJECT
 Trigger* t;
 public:
 PlayCallback(Trigger* t);
 /*public*/ void takeAction();
 /*public*/ void takeAction(int i) ;
 /*public*/ void takeAction(float f);
};
class LoopCallback : public TriggerListener
{
 Q_OBJECT
 Trigger* t;
 public:
 LoopCallback(Trigger* t);
 /*public*/ void takeAction();
 /*public*/ void takeAction(int i) ;
 /*public*/ void takeAction(float f);
};
class StopCallback : public TriggerListener
{
 Q_OBJECT
 Trigger* t;
 public:
 StopCallback(Trigger* t);
 /*public*/ void takeAction();
 /*public*/ void takeAction(int i) ;
 /*public*/ void takeAction(float f);
};
class NothingCallback : public TriggerListener
{
 Q_OBJECT
 Trigger* t;
 public:
 NothingCallback(Trigger* t);
 /*public*/ void takeAction();
 /*public*/ void takeAction(int i) ;
 /*public*/ void takeAction(float f);
};
class ChangeCallback : public TriggerListener
{
 Q_OBJECT
 Trigger* t;
 public:
 ChangeCallback(Trigger*t);
 /*public*/ void takeAction();
 /*public*/ void takeAction(int i);
 /*public*/ void takeAction(float f) ;
};
class NotchCallback : public TriggerListener
{
 Q_OBJECT
 Trigger* t;
 public:

NotchCallback(Trigger* t) ;
/*public*/ void takeAction(int i);
/*public*/ void takeAction();
/*public*/ void takeAction(float f) ;
};
#endif // SOUNDEVENT_H
