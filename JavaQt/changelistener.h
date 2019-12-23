#ifndef CHANGELISTENER_H
#define CHANGELISTENER_H
#include "eventlistener.h"
#include "changeevent.h"

/*public*/ /*interface*/class  ChangeListener : public QObject, public EventListener {
Q_OBJECT
 Q_INTERFACES(EventListener)
 QObject* self() {return (QObject*)this;}
public slots:

 /*public*/ virtual void stateChanged(ChangeEvent* /*e*/) {}
};
#endif // CHANGELISTENER_H
