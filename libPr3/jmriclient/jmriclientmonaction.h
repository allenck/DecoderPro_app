#ifndef JMRICLIENTMONACTION_H
#define JMRICLIENTMONACTION_H
#include "jmriclientmonpane.h"

/**
 * Swing action to create and register a JMRIClientMonFrame object
 *
 * @author Bob Jacobsen Copyright (C) 2008
 * @author Paul Bender Copyright (C) 2018
 */
/*public*/ class JMRIClientMonAction :public JMRIClientMonPane::Default
{
public:
 JMRIClientMonAction(QObject* parent) : JMRIClientMonPane::Default(parent) {}
};
#endif // JMRICLIENTMONACTION_H
