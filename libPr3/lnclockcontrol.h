#ifndef LNCLOCKCONTROL_H
#define LNCLOCKCONTROL_H
#include "defaultclockcontrol.h"
#include "slotmanager.h"
#include "lntrafficcontroller.h"
#include "instancemanager.h"
#include "propertychangelistener.h"

/**
 * LnClockControl.java
 *
 * Implementation of the Hardware Fast Clock for Loconet
 * <P>
 * This module is based on a GUI module developed by Bob Jacobsen and Alex
 * Shepherd to correct the Loconet fast clock rate and synchronize it with
 * the internal JMRI fast clock Timebase. The methods that actually send, correct,
 * or receive information from the Loconet hardware are repackaged versions of
 * their code.
 * <P>
 * The Loconet Fast Clock is controlled by the user via the Fast Clock Setup GUI
 * that is accessed from the JMRI Tools menu.
 * <P>
 * For this implementation, "synchronize" implies "correct",
 * since the two clocks run
 * at a different rate.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
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
 *
 * @author      Dave Duchamp Copyright (C) 2007
 * @author		Bob Jacobsen, Alex Shepherd
 * @version     $Revision: 17977 $
 */
class SlotManager;
class LIBPR3SHARED_EXPORT LnClockControl : public DefaultClockControl
{
    Q_OBJECT
public:
 explicit LnClockControl(SlotManager* sm, LnTrafficController* tc, QObject *parent = 0);
    /**
     * Accessor routines
     */
    /*public*/ virtual QString getHardwareClockName() ;
    /*public*/ virtual bool canCorrectHardwareClock();
    /*public*/ virtual void setRate(double newRate);
    /*public*/ virtual bool requiresIntegerRate();
    /*public*/ virtual double getRate();
    //@SuppressWarnings("deprecation")
    /*public*/ virtual void setTime(QDateTime now);
    /*public*/ virtual QDateTime getTime();
    /*public*/ virtual void startHardwareClock(QDateTime now);
    /*public*/ virtual void stopHardwareClock();
    /*public*/ virtual void initializeHardwareClock(double rate, QDateTime now, bool getTime);
    /**
     * Requests read of the Loconet fast clock
     */
    /*public*/ void initiateRead();
    /**
     * Handle changed slot contents, due to clock changes.
     * Can get here three ways:
     *			1) clock slot as a result of action by a throttle and
     *			2) clock slot responding to a read from this module
     *			3) a slot not involving the clock changing
     * @param s
     */
    //@SuppressWarnings("deprecation")
    /*public*/ void dispose();

signals:
    
public slots:
    /*public*/ void notifyChangedSlot(LocoNetSlot* s);
    /**
     * Corrects the Loconet Fast Clock
     */
    //@SuppressWarnings("deprecation")
    /*public*/ void newMinute();

private:
    SlotManager* sm;
    LnTrafficController* tc;

    /* Operational variables */
    Timebase* clock;
    PropertyChangeListener* minuteChangeListener;
    /* current values of clock variables */
    int curDays;
    int curHours;
    int curMinutes;
    int curFractionalMinutes;
    int curRate;
    int savedRate;
    /* current options and flags */
    bool  setInternal; // = false;   // true if Loconet Clock is the master
    bool  synchronizeWithInternalClock; // = false;
    bool  inSyncWithInternalFastClock; // = false;
    bool  timebaseErrorReported; // = false;
    bool  correctFastClock; // = false;
    bool  readInProgress; // = false;
    /* constants */
    const static long MSECPERHOUR = 3600000;
    const static long MSECPERMINUTE = 60000;
    const static double CORRECTION;// = 915.0;
  Logger log;
  /**
   * Push current Clock Control parameters out to LocoNet slot.
   */
  /*private*/ void setClock();

};

#endif // LNCLOCKCONTROL_H
