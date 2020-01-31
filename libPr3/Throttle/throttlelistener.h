#ifndef THROTTLELISTENER_H
#define THROTTLELISTENER_H
#include "eventlistener.h"

class DccThrottle;
class locoAddress;
class DccLocoAddress;
/**
 * A listener interface for a class requesting a DccThrottle from the
 * ThrottleManager.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 * @author Bob Jacobsen Copyright (C) 2007
 */
/*public*/ /*interface*/class  ThrottleListener //: public EventListener
{
 //Q_OBJECT
public:
 /**
      * A decision type requested from ThrottleManager to ThrottleListener,
      * or decision made from ThrottleListener to ThrottleManager
      *
      * @since 4.15.7
      */
     enum DecisionType {
         /**
          * Notification for decision needed, Steal OR Cancel, or wish to Steal
          */
         STEAL,
         /**
          * Notification for decision needed, Share OR Cancel, or wish to Share
          */
         SHARE,
         /**
          * Notification for decision needed, Steal OR Share OR Cancel
          */
         STEAL_OR_SHARE
     };
 //ThrottleListener() : EventListener() {}
public slots:
    /**
     * Get notification that a throttle has been found as you requested.
     *
     * @param t An instantiation of the DccThrottle with the address requested.
     */
    /*public*/ virtual void notifyThrottleFound(DccThrottle* /*t*/) {}

    /**
     * Get notification that an attempt to request a throttle has failed
     *
     * @param address DccLocoAddress of the failed loco request.
     * @param reason  The reason why the throttle request failed.
     */
    /*public*/ virtual void notifyFailedThrottleRequest(locoAddress* /*address*/, QString /*reason*/) {}
    /**
      * Get notification that a throttle request is in use by another
      * device, and a "steal", "share", or "steal/share" decision may be required.
      *
      * @param address The LocoAddress that needs the decision.
      * @param question The question being asked, steal / cancel, share / cancel, steal / share / cancel
      */
    /*public*/ virtual void notifyDecisionRequired(locoAddress* /*address*/, DecisionType /*question*/){}
     /*public*/ virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(ThrottleListener, "ThrottleListener")
#endif // THROTTLELISTENER_H
