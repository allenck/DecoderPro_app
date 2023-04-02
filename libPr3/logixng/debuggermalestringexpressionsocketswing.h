#ifndef DEBUGGERMALESTRINGEXPRESSIONSOCKETSWING_H
#define DEBUGGERMALESTRINGEXPRESSIONSOCKETSWING_H

#include "abstractdebuggermalesocketswing.h"

class DebuggerMaleStringExpressionSocketSwing : public AbstractDebuggerMaleSocketSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DebuggerMaleStringExpressionSocketSwing(QObject *parent = nullptr);
    ~DebuggerMaleStringExpressionSocketSwing() {}
    DebuggerMaleStringExpressionSocketSwing(const DebuggerMaleStringExpressionSocketSwing&) : AbstractDebuggerMaleSocketSwing() {}

    QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(DebuggerMaleStringExpressionSocketSwing)
#endif // DEBUGGERMALESTRINGEXPRESSIONSOCKETSWING_H
