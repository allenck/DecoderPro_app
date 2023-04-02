#ifndef DEBUGGERMALEDIGITALBOOLEANACTIONSOCKETSWING_H
#define DEBUGGERMALEDIGITALBOOLEANACTIONSOCKETSWING_H

#include "abstractdebuggermalesocketswing.h"

class DebuggerMaleDigitalBooleanActionSocketSwing : public AbstractDebuggerMaleSocketSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DebuggerMaleDigitalBooleanActionSocketSwing(QObject *parent = nullptr);
    ~DebuggerMaleDigitalBooleanActionSocketSwing() {}
    DebuggerMaleDigitalBooleanActionSocketSwing(const AbstractDebuggerMaleSocketSwing&) : AbstractDebuggerMaleSocketSwing() {}

    QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(DebuggerMaleDigitalBooleanActionSocketSwing)
#endif // DEBUGGERMALEDIGITALBOOLEANACTIONSOCKETSWING_H
