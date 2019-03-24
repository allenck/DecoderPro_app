#ifndef JMRICLIENTMONACTION_H
#define JMRICLIENTMONACTION_H
#include "jmriclientmonpane.h"

/**
 * Swing action to create and register a JMRIClientMonFrame object
 *
 * @author Bob Jacobsen Copyright (C) 2008
 * @author Paul Bender Copyright (C) 2018
 */
/*public*/ class JMRIClientMonAction :public JmriNamedPaneActionDefault
{
 Q_OBJECT
public:
 JMRIClientMonAction(QObject* parent= 0) : JmriNamedPaneActionDefault(parent) {}
 ~JMRIClientMonAction() {}
 JMRIClientMonAction(const JMRIClientMonAction&) : JmriNamedPaneActionDefault() {}
};
Q_DECLARE_METATYPE(JMRIClientMonAction)
#endif // JMRICLIENTMONACTION_H
