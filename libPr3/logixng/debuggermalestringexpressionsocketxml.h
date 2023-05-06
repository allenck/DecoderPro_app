#ifndef DEBUGGERMALESTRINGEXPRESSIONSOCKETXML_H
#define DEBUGGERMALESTRINGEXPRESSIONSOCKETXML_H
#include "abstractdebuggermalesocketxml.h"

/**
 * Handle XML configuration for DebuggerMaleDigitalExpressionSocket objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ class DebuggerMaleStringExpressionSocketXml : public AbstractDebuggerMaleSocketXml {

    Q_OBJECT
public:
    Q_INVOKABLE DebuggerMaleStringExpressionSocketXml(QObject* parent=nullptr) : AbstractDebuggerMaleSocketXml(parent) {}
    ~DebuggerMaleStringExpressionSocketXml() {}
    DebuggerMaleStringExpressionSocketXml(const DebuggerMaleStringExpressionSocketXml&) : AbstractDebuggerMaleSocketXml() {}
    QString getClass() override {return "jmri.jmrit.logixng.tools.debugger.configurexml.DebuggerMaleStringExpressionSocketXml";}
};
Q_DECLARE_METATYPE(DebuggerMaleStringExpressionSocketXml)

#endif // DEBUGGERMALESTRINGEXPRESSIONSOCKETXML_H
