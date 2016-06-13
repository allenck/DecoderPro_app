#ifndef CLOCKCONTROL_H
#define CLOCKCONTROL_H

#include <QObject>
#include <QDateTime>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ClockControl : public QObject
{
    Q_OBJECT
public:
    //explicit ClockControl(QObject *parent = 0);
    /**
     * ClockControl defines an interface for control of hardware Fast Clocks
     * <P>
     * Each hardware system that has a hardware Fast Clock implementation must
     * supply a module that implements this interface.  Each ClockControl module
     * must register itself with the Instance Manager at start up.
     * <P>
     * Parameters for fast clocks are set up generically in the Fast Clock Setup,
     * accessed via the JMRI Tools menu. These parameters are saved in the
     * configuration file generically, so no special configxml module is needed
     * for storing parameters.
     * <P>
     * Hardware ClockControl modules should extend DefaultClockControl, which
     * supplies default implementations of methods required by this interface
     * that specific hardware implementations may not need.
     * <P>
     * All Clock Control modules communicate with the internal clock and the
     * master JMRI Timebase, using methods of the Timebase interface.
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
     * @author			Dave Duchamp Copyright (C) 2007
     * @version			$Revision 1.0 $
     */

//    public interface ClockControl {

/**
 * Get status of the fast clock
 */
virtual int getStatus() {return 0;}

/**
 * Get name of hardware clock
 * Note: If there is no hardware clock, DefaultClockControl returns null, so
 *		all hardware clocks must override this method.
 */
    virtual QString getHardwareClockName()/* = 0*/{return "";}

/**
 * Returns true if hardware clock accuracy can be corrected using the
 *		computer clock.
 */
virtual bool canCorrectHardwareClock() {return false;}

/**
 * Returns 'true' if hardware clock can be set to 12 or 24 hour display from
 *              JMRI software.
 */
virtual bool canSet12Or24HourClock() {return false;}

/**
 * Returns true if hardware clock requires an integer rate
 */
virtual bool requiresIntegerRate() {return false;}

/**
 * Get and set the rate of the fast clock
 * Note: The rate is a number that multiplies the wall clock time
 *    For example, a rate of 4 specifies that the fast clock runs 4 times
 *		faster than the wall clock.
 */
virtual void setRate(double /*newRate*/) {}
virtual double getRate()  {return 0;}

/**
 * Set and get the fast clock time
 */
virtual void setTime(QDateTime /*now*/) {}
virtual QDateTime getTime() {return QDateTime();}

/**
 * Start and stop hardware fast clock
 * Some hardware fast clocks continue to run indefinitely. This is provided
 *		for the case where the hardware clock can be stopped and started.
 */
virtual void startHardwareClock(QDateTime /*now*/) {}
virtual void stopHardwareClock() {}

/**
 * Initialize the hardware fast clock
 * Note: When the hardware clock control receives this, it should
 *		initialize those clock settings that are available on the
 *		hardware clock.
 * This method is used when the fast clock is started, and when time source,
 *		synchronize, or correct options are changed.
 * If rate is 0.0, the hardware clock should be initialized "stopped", and the
 *		current rate saved for when the clock is restarted.
 * If getTime is "true" the time from the hardware clock should be used in
 *		place of the supplied time if possible.
 */
virtual void initializeHardwareClock(double /*rate*/, QDateTime /*now*/, bool /*getTime*/) {}

signals:
    
public slots:
    
};

#endif // CLOCKCONTROL_H
