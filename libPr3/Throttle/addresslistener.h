#ifndef ADDRESSLISTENER_H
#define ADDRESSLISTENER_H

#include "eventlistener.h"
/**
 * Interface for classes that wish to get notification that a new
 * decoder address has been selected.
 *
 * @author     glen   Copyright (C) 2002
 * @version    $Revision: 21621 $
 */
class DccThrottle;
class LocoAddress;
/*public*/ /*interface*/class  AddressListener : public EventListener
{
    Q_OBJECT
public:
    AddressListener(QObject* parent = 0) : EventListener(/*parent*/) {}
    /**
     * Receive notification that a new address has been selected.
     * @param address The address that is now selected.
     */
    /*public*/ virtual void notifyAddressChosen(LocoAddress* /*address*/) {}

    /**
     * Receive notification that an address has been released/dispatched
     * @param address The address released/dispatched
     */
    /*public*/ virtual void notifyAddressReleased(LocoAddress* /*address*/) {}

    /**
     * Receive notification that a throttle has been found
     * @param throttle The throttle
     */
    /*public*/ virtual void notifyAddressThrottleFound(DccThrottle* /*throttle*/) {}

        /**
         * Receive notification that a new Consist address has been selected.
         * @param newAddress The address that is now selected.
         */
        /*public*/ virtual void notifyConsistAddressChosen(int /*newAddress*/, bool /*isLong*/) {}

    /**
     * Receive notification that a consist address has been
         * released/dispatched
     * @param address The address released/dispatched
     */
    /*public*/ virtual void notifyConsistAddressReleased(int /*address*/, bool /*isLong*/) {}

    /**
     * Receive notification that a throttle has been found
     * @param throttle The throttle
     */
    /*public*/ virtual void notifyConsistAddressThrottleFound(DccThrottle* /*throttle*/) {}
};
#endif // ADDRESSLISTENER_H
