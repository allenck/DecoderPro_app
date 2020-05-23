#ifndef FOCUSLISTENER_H
#define FOCUSLISTENER_H
#include "eventlistener.h"
#include "focusevent.h"

class FocusListener : public QObject, public EventListener
{
 Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 FocusListener(QObject* parent = nullptr) : QObject(parent) {}
 QObject* self() {return (QObject*)this;}

public slots:

 /*public*/ virtual void focusGained(FocusEvent* /*fe*/) {}

 /*public*/ virtual void focusLost(FocusEvent* /*fe*/) {}
};

#endif // FOCUSLISTENER_H
