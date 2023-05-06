#ifndef DEBUGGERMALESTRINGACTIONSOCKETXML_H
#define DEBUGGERMALESTRINGACTIONSOCKETXML_H
#include "abstractdebuggermalesocketxml.h"

/**
 * Handle XML configuration for DebuggerMaleDigitalActionSocket objects.
/ *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ class DebuggerMaleStringActionSocketXml : public AbstractDebuggerMaleSocketXml {
    Q_OBJECT
public:
    Q_INVOKABLE DebuggerMaleStringActionSocketXml(QObject* parent=nullptr) : AbstractDebuggerMaleSocketXml(parent) {}
    ~DebuggerMaleStringActionSocketXml() {}
    DebuggerMaleStringActionSocketXml(const DebuggerMaleStringActionSocketXml&) : AbstractDebuggerMaleSocketXml() {}
    QString getClass() override {return "jmri.jmrit.logixng.tools.debugger.configurexml.DebuggerMaleStringActionSocketXml";}
};
Q_DECLARE_METATYPE(DebuggerMaleStringActionSocketXml)

#endif // DEBUGGERMALESTRINGACTIONSOCKETXML_H
