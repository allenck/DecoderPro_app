#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <QObject>
#include <QString>
#include "libPr3_global.h"
#include "propertychangelistener.h"
#include "swingpropertychangesupport.h"
#include "namedbean.h"
/**
 * Provide controls for layout power.
 * <p>
 * The PowerManager handles three states:
 * <ul>
 * <li>On/Off which controls electrical power to the track
 * <li>an optional "Idle" state, where track power is alive but track-connected
 *     decoders may be un-controllable
 * </ul>
 * A layout may not have control over these, in which case attempts to change
 * them should return an exception. If the state cannot be sensed, that should
 * also return an exception.
 * <p>
 * Some connections, including some LocoNet-based connections, implement the "Idle"
 * state.  For these LocoNet-based connections, when the Power state is "Idle", the
 * track power is alive and the command station is broadcasting "stop" to all mobile
 * decoders. Other systems may implement different interpretation of the "Idle" state.
 *
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 */
/*public*/ /*interface*/class PowerManager : public PropertyChangeProvider {
  Q_INTERFACES(PropertyChangeProvider)
public:
//    static final int UNKNOWN = NamedBean.UNKNOWN;
//    static final int ON = 0x02;
//    static final int OFF = 0x04;
//    static final int IDLE = 0x08; // not supported by some connection types
    enum STATE {UNKNOWN = NamedBean::UNKNOWN, ON= 0x02, OFF= 0x04, IDLE= 0x08};

    /**
     * {@link java.beans.PropertyChangeEvent}s are fired with this property name
     * to ensure backwards compatibility for scripts.
     * <p>
     * {@value #POWER_OPN}
     *
     * @deprecated since 4.19.7; use {@link #POWER} instead
     */
    //@Deprecated
    QT_DEPRECATED static /*final*/ QString POWER_OPN;// = "Power"; // OPN == "Old Property Name" // NOI18N
    /**
     * {@link java.beans.PropertyChangeEvent}s are fired with this property name.
     * <p>
     * {@value #POWER}
     */
    static /*final*/ QString POWER;// = "power"; // as recommended in JavaBeans Spec // NOI18N

    /*public*/ virtual void setPower(int v) /*throws JmriException*/=0;

    //@CheckReturnValue
    /*public*/ virtual int getPower()=0;

    // to free resources when no longer used
    /*public*/ virtual void dispose() /*throws JmriException*/=0;

    /*public*/ /*default*/ virtual bool implementsIdle() {
        // By default the Power Manager does not implement the IDLE power state
        return false;
    }

    //@CheckReturnValue
    /*@Nonnull*/ virtual/*public*/ QString getUserName()=0;
};
Q_DECLARE_INTERFACE(PowerManager, "PowerManager")
#endif // POWERMANAGER_H
