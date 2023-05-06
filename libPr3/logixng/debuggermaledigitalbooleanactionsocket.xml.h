#ifndef DEBUGGERMALEDIGITALBOOLEANACTIONSOCKET_XML_H
#define DEBUGGERMALEDIGITALBOOLEANACTIONSOCKET_XML_H
#include "abstractdebuggermalesocketxml.h"

/**
 * Handle XML configuration for DebuggerMaleDigitalActionSocket objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ class DebuggerMaleDigitalBooleanActionSocketXml : public AbstractDebuggerMaleSocketXml {
    Q_OBJECT
public:
    Q_INVOKABLE DebuggerMaleDigitalBooleanActionSocketXml(QObject* parent=nullptr) : AbstractDebuggerMaleSocketXml(parent) {}
    ~DebuggerMaleDigitalBooleanActionSocketXml() {}
    DebuggerMaleDigitalBooleanActionSocketXml(const DebuggerMaleDigitalBooleanActionSocketXml&) : AbstractDebuggerMaleSocketXml() {}
    QString getClass() override {return "jmri.jmrit.logixng.tools.debugger.configurexml.DebuggerMaleDigitalBooleanActionSocketXml";}
};
Q_DECLARE_METATYPE(DebuggerMaleDigitalBooleanActionSocketXml)



#endif // DEBUGGERMALEDIGITALBOOLEANACTIONSOCKET_XML_H
