#ifndef CHANGELISTENER_H
#define CHANGELISTENER_H
#include "eventlistener.h"
#include "changeevent.h"

/*public*/ /*interface*/class  ChangeListener : public QObject, public EventListener
{
 Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 ChangeListener(QObject* parent = nullptr) : QObject(parent) {}
// ~ChangeListener() {}
// ChangeListener(const ChangeListener&) : QObject() {}
 QObject* self() {return (QObject*)this;}
public slots:

 /*public*/ virtual void stateChanged(ChangeEvent* /*e*/) {}
};
//Q_DECLARE_METATYPE(ChangeListener)
#endif // CHANGELISTENER_H
