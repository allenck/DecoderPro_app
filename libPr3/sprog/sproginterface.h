#ifndef SPROGINTERFACE_H
#define SPROGINTERFACE_H
#include "sproglistener.h"
namespace Sprog
{
/**
 * Define interface for sending and receiving messages to the SPROG command
 * station.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 */
/*public*/ /*interface*/class SprogInterface : public QObject{
 Q_OBJECT
public:
 /*public*/ SprogInterface(QObject* parent = 0);

 virtual /*public*/ void addSprogListener(SprogListener* /*l*/) {}

 virtual /*public*/ void removeSprogListener(SprogListener* /*l*/) {}

    /**
     * Test operational status of interface.
     *
     * @return true if interface implementation is operational.
     */
 virtual bool status() {return false;}

    /**
     * Send a message through the interface.
     *
     * @param m Message to be sent.
     * @param l Listener to be notified of reply.
     */
 virtual void sendSprogMessage(SprogMessage* /*m*/, SprogListener* /*l*/) {}
};
}
#endif // SPROGINTERFACE_H
