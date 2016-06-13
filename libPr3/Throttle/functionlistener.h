#ifndef FUNCTIONLISTENER_H
#define FUNCTIONLISTENER_H
#include "eventlistener.h"

class FunctionListener : public EventListener
{
    Q_OBJECT
public:
    explicit FunctionListener(QObject *parent = 0) : EventListener(parent) {}
    /*public*/ virtual void notifyFunctionStateChanged(int /*functionNumber*/, bool /*isOn*/) {}

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

#endif // FUNCTIONLISTENER_H
