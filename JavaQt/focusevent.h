#ifndef FOCUSEVENT_H
#define FOCUSEVENT_H
#include "eventlistener.h"
#include "focusevent.h"


class FocusEvent :  public QObject, public EventListener
{
public:
 FocusEvent(QObject* parent = nullptr) : QObject(parent) {}
 QObject* self() {return (QObject*)this;}
public slots:

 /*public*/ virtual void stateChanged(FocusEvent* /*e*/) {}};

#endif // FOCUSEVENT_H
