#ifndef DEBUGGERMALESTRINGACTIONSOCKETSWING_H
#define DEBUGGERMALESTRINGACTIONSOCKETSWING_H

#include "abstractdebuggermalesocketswing.h"

class DebuggerMaleStringActionSocketSwing : public AbstractDebuggerMaleSocketSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DebuggerMaleStringActionSocketSwing(QObject *parent = nullptr);
    ~DebuggerMaleStringActionSocketSwing() {}
    DebuggerMaleStringActionSocketSwing(const DebuggerMaleStringActionSocketSwing&) : AbstractDebuggerMaleSocketSwing() {}

    QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(DebuggerMaleStringActionSocketSwing)
#endif // DEBUGGERMALESTRINGACTIONSOCKETSWING_H
