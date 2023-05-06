#ifndef DEBUGGERMALEANALOGEXPRESSIONSOCKETXML_H
#define DEBUGGERMALEANALOGEXPRESSIONSOCKETXML_H
#include "abstractdebuggermalesocketxml.h"

/**
 * Handle XML configuration for DebuggerMaleDigitalExpressionSocket objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ class DebuggerMaleAnalogExpressionSocketXml : public AbstractDebuggerMaleSocketXml {
  Q_OBJECT
public:
  Q_INVOKABLE DebuggerMaleAnalogExpressionSocketXml(QObject* parent=nullptr) : AbstractDebuggerMaleSocketXml(parent) {}
  ~DebuggerMaleAnalogExpressionSocketXml() {}
  DebuggerMaleAnalogExpressionSocketXml(const DebuggerMaleAnalogExpressionSocketXml&) : AbstractDebuggerMaleSocketXml() {}
  QString getClass() override {return "jmri.jmrit.logixng.tools.debugger.configurexml.DebuggerMaleAnalogExpressionSocketXml";}
};
Q_DECLARE_METATYPE(DebuggerMaleAnalogExpressionSocketXml)
#endif // DEBUGGERMALEANALOGEXPRESSIONSOCKETXML_H
