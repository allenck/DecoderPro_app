#ifndef TOGGLESOUNDEVENT_H
#define TOGGLESOUNDEVENT_H
#include "soundevent.h"

class Logger;
class JToggleButton;
class ToggleSoundEvent : public SoundEvent
{
 Q_OBJECT
public:
 explicit ToggleSoundEvent(QObject *parent = 0);
 /*public*/ ToggleSoundEvent(QString n,QObject *parent = 0) ;
 /*public*/ ToggleSoundEvent(QString n, QString bl,QObject *parent =0);
 /*public*/ bool hasButton();
 /*public*/ void setButton(JToggleButton* b);
 /*public*/ QAbstractButton* getButton() ;
 /*public*/ void setButtonLabel(QString bl) ;
 /*public*/ QString getButtonLabel();
 /*protected*/ ButtonTrigger* setupButtonAction(QDomElement te) ;
 /*public*/ QDomElement getXml() ;
 /*public*/ void setXml(QDomElement el);
 /*public*/ void setXml(QDomElement el, VSDFile* vf);
signals:

public slots:
private:
 JToggleButton* button;
 Trigger* t; // used in setXml as a temporary holder for creating the
 // event listener class.
 ButtonTrigger* bt; // used in setupButtonAction() as a temporary holder
 // for creating the button listeners.
 Logger* log;
};

#endif // TOGGLESOUNDEVENT_H
