#ifndef JMRICLIENTLISTENER_H
#define JMRICLIENTLISTENER_H
#include "abstractmrlistener.h"
#include "abstractmrmessage.h"

class JMRIClientMessage;
class JMRIClientReply;
/**
 * Defines the interface for listening to traffic on the JMRIClient
 * communications link.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2004, 2008
  */
/*public*/ /*interface*/class JMRIClientListener :  public AbstractMRListener {
 //Q_OBJECT
    Q_INTERFACES(AbstractMRListener)
public:
//public slots:

 /*public*/ void message(AbstractMRMessage* /*m*/, AbstractMRListener* ) {}

 /*public*/ void reply(AbstractMRMessage* /*m*/) {}
};
Q_DECLARE_INTERFACE(JMRIClientListener, "JMRIClientListener")
#endif // JMRICLIENTLISTENER_H
