#ifndef FUNCTIONLISTENER_H
#define FUNCTIONLISTENER_H
#include "eventlistener.h"

class FunctionListener : /*public QObject,*/ public EventListener
{
//    Q_OBJECT
// Q_INTERFACES(EventListener)
public:
    explicit FunctionListener() : EventListener() {}
public slots:
    /*public*/ virtual void notifyFunctionStateChanged(int /*functionNumber*/, bool /*isOn*/) {}
    QObject* self() {return (QObject*)this;}

    /**
     * Get notification that a function's lockable status has changed.
     * @param functionNumber The function that has changed (0-9).
     * @param isLockable True if the function is now Lockable
     * (continuously active).
     */
    /*public*/ virtual void notifyFunctionLockableChanged(int /*functionNumber*/, bool /*isLockable*/) {}

signals:

public slots:

};
Q_DECLARE_INTERFACE(FunctionListener, "FunctionListener")
#endif // FUNCTIONLISTENER_H
