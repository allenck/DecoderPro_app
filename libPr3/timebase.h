#ifndef TIMEBASE_H
#define TIMEBASE_H

#include <QObject>
#include <QDateTime>
#include "propertychangelistener.h"
#include "abstractnamedbean.h"
/**
 * Provide access to clock capabilities in hardware or software.
 * <P>
 * The Rate parameter determines how much faster than real time
 * this timebase runs.  E.g. a value of 2.0 means that the value
 * returned by getTime will advance an hour for every half-hour of
 * wall-clock time elapsed.
 * <P>
 * The Rate and Run parameters are bound, so you can listen for them
 * changing.  The Time parameters is not bound, because it changes
 * continuously.  Ask for its value when needed, or add a
 * a listener for the changes in the "minute" value using {@link #addMinuteChangeListener}
 * <P>
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
 * @author			Bob Jacobsen Copyright (C) 2004, 2007, 2008
 * @version			$Revision: 17977 $
 */

class Timebase :  public AbstractNamedBean
{
    Q_OBJECT
public:
    explicit Timebase(QString name = "", QObject *parent = 0) : AbstractNamedBean(name, parent) {}
    //public interface Timebase extends NamedBean {

    /**
     * Set the current time
     */
virtual void setTime(QDateTime /*d*/){}
    /**
     * Special method for  when the user changes
     * fast clock time in Setup Fast Clock.
     */
    virtual void userSetTime(QDateTime /*d*/) {}

virtual QDateTime getTime() /*const = 0*/{return QDateTime();}

    virtual void setRun(bool /*y*/) {}
    virtual bool getRun() {return false;}

    /**
     * Set fast clock rate factor
     * @throws TimebaseRateException if the implementation can't do the requested rate
     */
    virtual void setRate(double /*factor*/) {} // throws TimebaseRateException;

    /**
     * Used when the user changes fast clock rate in Setup Fast Clock and by
     * hardware ClockControl implementations that fiddle with the fast clock rate to synchronize
     */
virtual void userSetRate(double /*factor*/) {}// throws TimebaseRateException;

    /**
     *  Caution: This method may return a fiddled clock rate if certain hardware clocks
     *  are the Time Source.  Use "userGetRate" if you want the real clock rate instead.
     */
    virtual double getRate() {return 0;}
    /**
     * This method is used by Setup Fast Clock when an external change in fast
     * clock rate occurs because of the peculiar way some hardware clocks attempt to
     * synchronize with the JMRI fast clock. This call will return the "true" rate even if the
     * master Timebase rate has been fiddled by a hardware clock.
     */
    virtual double userGetRate() {return 0;}

    // methods for setting and getting master time source
    virtual void setInternalMaster(bool /*master*/, bool /*update*/) {}
    virtual bool getInternalMaster() {return false;}
    // the following provide for choosing among hardware clocks if hardware master
    virtual void setMasterName(QString /*name*/) {}
virtual QString getMasterName() {return "";}

    // methods for setting and getting synchronize option
    virtual void setSynchronize(bool /*synchronize*/, bool /*update*/) {}
    virtual bool getSynchronize() /*const = 0*/{return false;}

    // methods for setting and getting hardware correction option
    virtual void setCorrectHardware(bool /*correct*/, bool /*update*/) {}
    virtual bool getCorrectHardware() {return false;}

    /**
     * Set 12 or 24 hour display option
     * @param display true if a 12-hour display is requested, false for 24-hour display
     */
    virtual void set12HourDisplay(bool /*display*/, bool /*update*/) {}
    virtual bool use12HourDisplay() {return false;}

    // methods for start up with clock stopped option
    virtual void setStartStopped(bool /*stopped*/) {}
    virtual bool getStartStopped() {return false;}

    // methods to get set time at start up option, and start up time
    virtual void setStartSetTime(bool /*set*/, QDateTime /*time*/) {}
    virtual bool getStartSetTime() {return false;}
virtual QDateTime getStartTime() {return QDateTime();}

    // methods to get set clock start start up option
    virtual void setStartClockOption(int /*option*/) {}
    virtual int getStartClockOption() {return 0;}

    // Note the following method should only be invoked at start up
    virtual void initializeClock() {}

    // clock start options
    const static  int NONE			= 0x00;
    const static  int NIXIE_CLOCK     = 0x01;
    const static  int ANALOG_CLOCK	= 0x02;
    const static  int LCD_CLOCK       = 0x04;

    /**
     * Initialize hardware clock at start up after all options are set up.<p>
     * Note: This method is always called at start up. It should be ignored if there
     *		is no communication with a hardware clock
     */
    virtual void initializeHardwareClock() {}

    /**
     * @return true if call to initialize Hardware Clock has occurred
     */
    virtual bool getIsInitialized() {return false;}

    /**
     * Request a call-back when the bound Rate or Run property changes.
     */
    virtual void addPropertyChangeListener(PropertyChangeListener* /*l*/) {}

    /**
     * Remove a request for a call-back when a bound property changes.
     */
    virtual void removePropertyChangeListener(PropertyChangeListener* /*l*/) {}

    /**
     * Request a call-back when the minutes place of the time changes.
     */
    virtual void addMinuteChangeListener(PropertyChangeListener* /*l*/) {}

    /**
     * Remove a request for call-back when the minutes place of the time changes.
     */
    virtual void removeMinuteChangeListener(PropertyChangeListener* /*l*/) {}
    /**
     * Get the list of minute change listeners. This is the same as calling
     * {@link #getPropertyChangeListeners(String)} with the propertyName
     * {@code minutes}.
     *
     * @return the list of listeners
     */
    //@Nonnull
    virtual /*public*/ QList<PropertyChangeListener*>* getMinuteChangeListeners() =0;

    /**
     * Remove references to and from this object, so that it can
     * eventually be garbage-collected.
     */
    virtual void dispose() {}

signals:
    virtual void minuteTick();
    virtual void propertyChange(PropertyChangeEvent*);
public slots:

};
Q_DECLARE_INTERFACE(Timebase, "Timebase")
#endif // TIMEBASE_H
