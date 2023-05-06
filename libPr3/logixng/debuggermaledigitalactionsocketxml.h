#ifndef DEBUGGERMALEDIGITALACTIONSOCKETXML_H
#define DEBUGGERMALEDIGITALACTIONSOCKETXML_H
#include "abstractdebuggermalesocketxml.h"

/**
 * Handle XML configuration for DebuggerMaleDigitalActionSocket objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ class DebuggerMaleDigitalActionSocketXml :public AbstractDebuggerMaleSocketXml {
    Q_OBJECT
 public:
    Q_INVOKABLE DebuggerMaleDigitalActionSocketXml(QObject* parent = nullptr) : AbstractDebuggerMaleSocketXml(parent){}
    ~DebuggerMaleDigitalActionSocketXml() {}
    DebuggerMaleDigitalActionSocketXml(const DebuggerMaleDigitalActionSocketXml&) : AbstractDebuggerMaleSocketXml() {}
    QString getClass() override {return "jmri.jmrit.logixng.tools.debugger.configurexml.DebuggerMaleDigitalActionSocketXml";}
};
Q_DECLARE_METATYPE(DebuggerMaleDigitalActionSocketXml)
#endif // DEBUGGERMALEDIGITALACTIONSOCKETXML_H
