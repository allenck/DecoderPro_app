#ifndef JMRICLIENTINTERFACE_H
#define JMRICLIENTINTERFACE_H
#include "jmriclientlistener.h"

/**
 * Layout interface, similar to command station
 *
 * @author Bob Jacobsen Copyright (C) 2001
  */
/*public*/ /*interface*/class JMRIClientInterface {

 /*public*/ virtual void addJMRIClientListener(JMRIClientListener l) {}

 /*public*/ virtual void removeJMRIClientListener(JMRIClientListener l) {}
private:
 virtual bool status() {return false;}   // true if the implementation is operational

 virtual void sendJMRIClientMessage(JMRIClientMessage m, JMRIClientListener l){}  // 2nd arg gets the reply
};
Q_DECLARE_INTERFACE(JMRIClientInterface, "JMRIClientInterface")
#endif // JMRICLIENTINTERFACE_H
