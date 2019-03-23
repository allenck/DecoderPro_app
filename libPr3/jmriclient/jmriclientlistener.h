#ifndef JMRICLIENTLISTENER_H
#define JMRICLIENTLISTENER_H
#include "abstractmrlistener.h"

class JMRIClientMessage;
class JMRIClientReply;
/**
 * Defines the interface for listening to traffic on the JMRIClient
 * communications link.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2004, 2008
  */
/*public*/ /*interface*/class JMRIClientListener : public AbstractMRListener {
 Q_OBJECT
public slots:

 /*public*/ virtual void message(JMRIClientMessage* /*m*/) {}

 /*public*/ virtual void reply(JMRIClientReply* /*m*/) {}
};
Q_DECLARE_INTERFACE(JMRIClientListener, "JMRIClientListener")
#endif // JMRICLIENTLISTENER_H
