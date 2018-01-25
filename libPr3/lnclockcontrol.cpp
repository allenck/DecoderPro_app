#include "lnclockcontrol.h"
#include "simpletimebase.h"

const double LnClockControl::CORRECTION = 915.0;
LnClockControl::LnClockControl(SlotManager* sm, LnTrafficController* tc, QObject *parent) :
    DefaultClockControl(parent)
{
    setObjectName("LnClockControl");
    this->sm = sm;
    this->tc = tc;
    // listen for updated slot contents
    if (sm!=NULL)
    {
     //sm->addSlotListener((SlotListener*)this);
     connect(sm, SIGNAL(changedSlot(LocoNetSlot*)), this, SLOT(notifyChangedSlot(LocoNetSlot*)));
    }
    else
        log.error("No LocoNet connection available, LnClockControl can't function");
    curDays = 0;
    curHours = 0;
    curMinutes = 0;
    curFractionalMinutes = 900;
    curRate = 1;
    savedRate = 1;
    setInternal = false;   // true if Loconet Clock is the master
    synchronizeWithInternalClock = false;
    inSyncWithInternalFastClock = false;
    timebaseErrorReported = false;
    correctFastClock = false;
    readInProgress = false;

    // Get internal timebase
    clock = (Timebase*)InstanceManager::getDefault("Timebase");
    // Create a Timebase listener for Minute change events from the internal clock
#if 0 // DONE:
    minuteChangeListener = new PropertyChangeListener() {
            /*public*/ void propertyChange(PropertyChangeEvent e) {
                newMinute();
            }
        };
    clock->addMinuteChangeListener(minuteChangeListener);
#else
    SimpleTimebase* st = (SimpleTimebase*)clock;
    connect(st, SIGNAL(minuteTick()), this, SLOT(newMinute()));
#endif
}


/**
 * Accessor routines
 */
/*public*/ QString LnClockControl::getHardwareClockName() {
    return ("Loconet Fast Clock");
}
/*public*/ bool LnClockControl::canCorrectHardwareClock() {return true;}
/*public*/ void LnClockControl::setRate(double newRate) {
    if (curRate==0) {
        savedRate = (int)newRate;      // clock stopped case
    }
    else {
        curRate = (int)newRate;        // clock running case
        savedRate = curRate;
    }
    setClock();
}
/*public*/ bool LnClockControl::requiresIntegerRate() {return true;}
/*public*/ double LnClockControl::getRate() {return curRate;}

//@SuppressWarnings("deprecation")
/*public*/ void LnClockControl::setTime(QDateTime now) {
    curDays = now.date().dayOfYear();
    curHours = now.time().hour();
    curMinutes = now.time().minute();
    setClock();
}

// @SuppressWarnings("deprecation")
/*public*/ QDateTime LnClockControl::getTime() {
    QDateTime tem = clock->getTime();
    int cHours = tem.time().hour();
    long cNumMSec = tem.time().second();
    long nNumMSec = ((cNumMSec/MSECPERHOUR)*MSECPERHOUR) - (cHours*MSECPERHOUR) +
                (curHours*MSECPERHOUR) + (curMinutes*MSECPERMINUTE) ;
    // Work out how far through the current fast minute we are
    // and add that on to the time.
    nNumMSec += (long) ( ( ( CORRECTION - curFractionalMinutes) / CORRECTION * MSECPERMINUTE) ) ;
    return ( QDateTime::currentDateTime()); // TODO:
}
/*public*/ void LnClockControl::startHardwareClock(QDateTime now) {
    curRate = savedRate;
    setTime(now);
}
/*public*/ void LnClockControl::stopHardwareClock() {
    savedRate = curRate;
    curRate = 0;
    setClock();
}

//@SuppressWarnings("deprecation")
/*public*/ void LnClockControl::initializeHardwareClock(double rate, QDateTime now, bool getTime)
{
 synchronizeWithInternalClock= clock->getSynchronize();
    correctFastClock = clock->getCorrectHardware();
    setInternal = !clock->getInternalMaster();
    if (!setInternal && !synchronizeWithInternalClock && !correctFastClock) {
        // No request to interact with hardware fast clock - ignore call
        return;
    }
    if (rate == 0.0) {
        if (curRate!=0) savedRate = curRate;
        curRate = 0;
    }
    else {
        savedRate = (int)rate;
        if (curRate!=0) curRate = savedRate;
    }
    curDays = now.date().day();
    curHours = now.time().hour();
    curMinutes = now.time().minute();
    if (!getTime) {
        setTime(now);
    }
    if (getTime || synchronizeWithInternalClock || correctFastClock) {
        inSyncWithInternalFastClock = false;
        initiateRead();
    }
}

/**
 * Requests read of the Loconet fast clock
 */
/*public*/ void LnClockControl::initiateRead() {
    if (!readInProgress) {
        sm->sendReadSlot(LnConstants::FC_SLOT);
        readInProgress = true;
    }
}

/**
 * Corrects the Loconet Fast Clock
 */
//@SuppressWarnings("deprecation")
/*public*/ void LnClockControl::newMinute()
{
    // ignore if waiting on Loconet clock read
    if (!inSyncWithInternalFastClock) return;
    if (correctFastClock || synchronizeWithInternalClock) {
        // get time from the internal clock
        QDateTime now = clock->getTime();
        // skip the correction if minutes is 0 because Logic Rail Clock displays incorrectly
        //		if a correction is sent at zero minutes.
        if (now.time().minute()!=0) {
            // Set the Fast Clock Day to the current Day of the month 1-31
            curDays = now.date().day();
            // Update current time
            curHours = now.time().hour();
            curMinutes = now.time().minute();
            long millis = now.time().msec() ;
            // How many ms are we into the fast minute as we want to sync the
            // Fast Clock Master Frac_Mins to the right 65.535 ms tick
            long elapsedMS = millis % MSECPERMINUTE ;
            double frac_min = elapsedMS / (double)MSECPERMINUTE ;
            curFractionalMinutes = (int)CORRECTION - (int)( CORRECTION * frac_min ) ;
            setClock();
        }
    }
    else if (setInternal && !correctFastClock && !synchronizeWithInternalClock) {
        inSyncWithInternalFastClock = false;
        initiateRead();
    }

}

/**
 * Handle changed slot contents, due to clock changes.
 * Can get here three ways:
 *			1) clock slot as a result of action by a throttle and
 *			2) clock slot responding to a read from this module
 *			3) a slot not involving the clock changing
 * @param s
 */
//@SuppressWarnings("deprecation")
/*public*/ void LnClockControl::notifyChangedSlot(LocoNetSlot* s) {
    // only watch the clock slot
    if (s->getSlot()!= LnConstants::FC_SLOT ) return;
    // if don't need to know, simply return
    if (!correctFastClock && !synchronizeWithInternalClock && !setInternal) return;
    if (log.isDebugEnabled()) log.debug("slot update "+QString("%1").arg(s->addr));
    // update current clock variables from the new slot contents
    curDays = s->getFcDays();
    curHours = s->getFcHours();
    curMinutes = s->getFcMinutes();
    int temRate = s->getFcRate();
    // reject the new rate if different and not resetting the internal clock
    if ( (temRate != curRate) && !setInternal) setRate(curRate);
    // keep the new rate if different and resetting the internal clock
    else if ( (temRate != curRate) && setInternal) {
        try {
            clock->userSetRate(temRate);
        }
        catch (TimebaseRateException e) {
            if (!timebaseErrorReported) {
                timebaseErrorReported = true;
                log.warn("Time base exception on setting rate from LocoNet");
            }
        }
    }
    curFractionalMinutes = s->getFcFracMins();
    // we calculate a new msec value for a specific hour/minute
    // in the current day, then set that.
    QDateTime tem = clock->getTime();
    int cHours = tem.time().hour();
    long cNumMSec = tem.time().msec();
    long nNumMSec = ((cNumMSec/MSECPERHOUR)*MSECPERHOUR) - (cHours*MSECPERHOUR) +
                (curHours*MSECPERHOUR) + (curMinutes*MSECPERMINUTE) ;
    // set the internal timebase based on the Loconet clock
    if (readInProgress && !inSyncWithInternalFastClock) {
        // Work out how far through the current fast minute we are
        // and add that on to the time.
        nNumMSec += (long) ( ( ( CORRECTION - curFractionalMinutes) / CORRECTION * MSECPERMINUTE) ) ;
        clock->setTime(QDateTime::fromMSecsSinceEpoch(nNumMSec));
    }
    else if (setInternal) {
        // unsolicited time change from the Loconet
        clock->setTime(QDateTime::fromMSecsSinceEpoch(nNumMSec));
    }
    // Once we have done everything else set the flag to say we are in sync
    inSyncWithInternalFastClock = true;
}

/**
 * Push current Clock Control parameters out to LocoNet slot.
 */
/*private*/ void LnClockControl::setClock() {
    if (setInternal || synchronizeWithInternalClock || correctFastClock) {
        // we are allowed to send commands to the fast clock
        LocoNetSlot* s = sm->slot(LnConstants::FC_SLOT);
        s->setFcDays(curDays);
        s->setFcHours(curHours);
        s->setFcMinutes(curMinutes);
        s->setFcRate(curRate);
        s->setFcFracMins(curFractionalMinutes);
        tc->sendLocoNetMessage(s->writeSlot());
    }
}

/*public*/ void LnClockControl::dispose() {
    // Drop loconet connection
    if (sm!=NULL)
        sm->removeSlotListener((SlotListener*)this);

    // Remove ourselves from the Timebase minute rollover event
    if (minuteChangeListener!=NULL) {
        clock->removeMinuteChangeListener( minuteChangeListener );
        minuteChangeListener = NULL ;
    }
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnClockControl.class.getName());
