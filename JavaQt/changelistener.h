#ifndef CHANGELISTENER_H
#define CHANGELISTENER_H
#include "eventlistener.h"
#include "changeevent.h"

/*public*/ /*interface*/class  ChangeListener : public EventListener {
Q_OBJECT
public slots:

 /*public*/ virtual void stateChanged(ChangeEvent* e) {}
};

#endif // CHANGELISTENER_H
