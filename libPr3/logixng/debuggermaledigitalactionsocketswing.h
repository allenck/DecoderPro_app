#ifndef DEBUGGERMALEDIGITALACTIONSOCKETSWING_H
#define DEBUGGERMALEDIGITALACTIONSOCKETSWING_H

#include "abstractdebuggermalesocketswing.h"

class DebuggerMaleDigitalActionSocketSwing : public AbstractDebuggerMaleSocketSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DebuggerMaleDigitalActionSocketSwing(QObject *parent = nullptr);
    ~DebuggerMaleDigitalActionSocketSwing() {}
    DebuggerMaleDigitalActionSocketSwing(const DebuggerMaleDigitalActionSocketSwing&) : AbstractDebuggerMaleSocketSwing() {}

    QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(DebuggerMaleDigitalActionSocketSwing)
#endif // DEBUGGERMALEDIGITALACTIONSOCKETSWING_H
