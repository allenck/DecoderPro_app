#ifndef DEBUGGERMALEANALOGACTIONSOCKETXML_H
#define DEBUGGERMALEANALOGACTIONSOCKETXML_H
#include "abstractdebuggermalesocketxml.h"

/**
 * Handle XML configuration for DebuggerMaleDigitalActionSocket objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ class DebuggerMaleAnalogActionSocketXml : public AbstractDebuggerMaleSocketXml {
    Q_OBJECT
public:
    Q_INVOKABLE DebuggerMaleAnalogActionSocketXml(QObject* parent = nullptr) : AbstractDebuggerMaleSocketXml(parent) {}
    ~DebuggerMaleAnalogActionSocketXml() {}
    DebuggerMaleAnalogActionSocketXml(const DebuggerMaleAnalogActionSocketXml&) : AbstractDebuggerMaleSocketXml() {}
    QString getClass() override {return "jmri.jmrit.logixng.tools.debugger.configurexml.DebuggerMaleAnalogActionSocketXml";}
};
Q_DECLARE_METATYPE(DebuggerMaleAnalogActionSocketXml)
#endif // DEBUGGERMALEANALOGACTIONSOCKETXML_H
