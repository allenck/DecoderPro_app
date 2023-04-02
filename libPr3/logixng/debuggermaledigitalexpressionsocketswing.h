#ifndef DEBUGGERMALEDIGITALEXPRESSIONSOCKETSWING_H
#define DEBUGGERMALEDIGITALEXPRESSIONSOCKETSWING_H

#include "abstractdebuggermalesocketswing.h"

class DebuggerMaleDigitalExpressionSocketSwing : public AbstractDebuggerMaleSocketSwing
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit DebuggerMaleDigitalExpressionSocketSwing(QObject *parent = nullptr);
    ~DebuggerMaleDigitalExpressionSocketSwing() {}
    DebuggerMaleDigitalExpressionSocketSwing(const DebuggerMaleDigitalExpressionSocketSwing&) : AbstractDebuggerMaleSocketSwing(){}

    QObject* sself() override {return this;}

};
Q_DECLARE_METATYPE(DebuggerMaleDigitalExpressionSocketSwing)
#endif // DEBUGGERMALEDIGITALEXPRESSIONSOCKETSWING_H
