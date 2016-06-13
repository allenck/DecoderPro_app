#ifndef THROTTLELISTENER_H
#define THROTTLELISTENER_H

#include <QObject>
#include "eventlistener.h"
//#include "throttle.h"
//#include "dccthrottle.h"
#include "dcclocoaddress.h"

class DccThrottle;
class ThrottleListener : public EventListener
{
    Q_OBJECT
public:
    //explicit ThrottleListener(QObject *parent = 0);
    /**
     * A listener interface for a class requesting a DccThrottle from
     * the ThrottleManager.
     *
     * <hr>
     * This file is part of JMRI.
     * <P>
     * JMRI is free software; you can redistribute it and/or modify it under
     * the terms of version 2 of the GNU General Public License as published
     * by the Free Software Foundation. See the "COPYING" file for a copy
     * of this license.
     * <P>
     * JMRI is distributed in the hope that it will be useful, but WITHOUT
     * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
     * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
     * for more details.
     * <P>
     * @author Bob Jacobsen  Copyright (C) 2007
     */
    //public interface ThrottleListener extends EventListener
    //{
        /**
         * Get notification that a throttle has been found as you requested.
         * @param t An instantiation of the DccThrottle with the address requested.
         */
        virtual void notifyThrottleFound(DccThrottle* t)=0;

        /**
         * Get notification that an attempt to request a throttle has failed
         * @param address DccLocoAddress of the failed loco request.
         * @param reason The reason why the throttle request failed.
         */
        virtual void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason)=0;

signals:
    
public slots:
    
};

#endif // THROTTLELISTENER_H
