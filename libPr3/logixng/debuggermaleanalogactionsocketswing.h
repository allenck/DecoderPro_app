#ifndef DEBUGGERMALEANALOGACTIONSOCKETSWING_H
#define DEBUGGERMALEANALOGACTIONSOCKETSWING_H

#include "abstractdebuggermalesocketswing.h"

class DebuggerMaleAnalogActionSocketSwing : public AbstractDebuggerMaleSocketSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DebuggerMaleAnalogActionSocketSwing(QObject *parent = nullptr);
    ~DebuggerMaleAnalogActionSocketSwing(){}
    DebuggerMaleAnalogActionSocketSwing(const DebuggerMaleAnalogActionSocketSwing&) : AbstractDebuggerMaleSocketSwing() {}

    QObject* sself() override {return this;}

};
Q_DECLARE_METATYPE(DebuggerMaleAnalogActionSocketSwing)
#endif // DEBUGGERMALEANALOGACTIONSOCKETSWING_H
