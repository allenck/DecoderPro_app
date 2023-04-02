#ifndef DEBUGGERMALEANALOGEXPRESSIONSOCKETSWING_H
#define DEBUGGERMALEANALOGEXPRESSIONSOCKETSWING_H

#include "abstractdebuggermalesocketswing.h"

class DebuggerMaleAnalogExpressionSocketSwing : public AbstractDebuggerMaleSocketSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DebuggerMaleAnalogExpressionSocketSwing(QObject *parent = nullptr);
    ~DebuggerMaleAnalogExpressionSocketSwing() {}
    DebuggerMaleAnalogExpressionSocketSwing(const DebuggerMaleAnalogExpressionSocketSwing&) : AbstractDebuggerMaleSocketSwing() {}

    QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(DebuggerMaleAnalogExpressionSocketSwing)
#endif // DEBUGGERMALEANALOGEXPRESSIONSOCKETSWING_H
