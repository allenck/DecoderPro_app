#ifndef MOMENTARYSOUNDEVENT_H
#define MOMENTARYSOUNDEVENT_H
#include "soundevent.h"
#include <QPushButton>

class MSButton;
class Logger;
class MomentarySoundEvent : public SoundEvent
{
 Q_OBJECT
public:
 explicit MomentarySoundEvent(QObject *parent = 0);
 /*public*/ MomentarySoundEvent(QString n,QObject *parent = 0);
 /*public*/ MomentarySoundEvent(QString n, QString bl,QObject *parent = 0);
 /*public*/ bool hasButton();
 /*public*/ void setButton(MSButton* b) ;
 /*public*/ QAbstractButton* getButton();
 /*public*/ void setButtonLabel(QString bl);
 /*public*/ QString getButtonLabel();
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement el);
 /*public*/ void setXml(QDomElement el, VSDFile* vf);
 /*public*/ void addButtonMouseHandler(ButtonTrigger* bt);
signals:

public slots:
private:
 MSButton* button;
 Trigger* t; // used in setXml as a temporary holder for creating the
 // event listener class.
 ButtonTrigger* bt; // used in setupButtonAction() as a temporary holder
 // for creating the button listeners.
 Logger* log;
protected:
 /*protected*/ ButtonTrigger* setupButtonAction(QDomElement te) ;

};
class MSButton : public QPushButton
{
 Q_OBJECT
 ButtonTrigger* bt;
public:
 MSButton();
 void mousePressEvent(QMouseEvent* e);
 void addMouseListener(ButtonTrigger* bt);
 void mouseReleaseEvent(QMouseEvent *e);

};

#endif // MOMENTARYSOUNDEVENT_H
