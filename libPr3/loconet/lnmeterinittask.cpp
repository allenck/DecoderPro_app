#include "lnmeterinittask.h"
#include "loggerfactory.h"
#include "lntrafficcontroller.h"
#include "lnmeterinittask.h"
#include "timerutil.h"
/**
 * Provide access to current and voltage meter from some LocoNet command stations
 *
 * @author Steve G           Copyright (C) 2019
 * @author Bob Jacobsen      Copyright (C) 2019
 * @author Egbert Boerse     Copyright (C) 2019
 * @author Daniel Bergqvist  Copyright (C) 2020
 * @author B. Milhaupt       Copyright (C) 2020
 */
// /*public*/ class LnPredefinedMeters implements LocoNetListener {


/**
 * Provides for LocoNet "Meters" discovery query at connection start-up.
 *
 * This class specifically deals with issues sometimes seen
 * at JMRI LocoNet connection start-up.
 *
 * @author B. Milhaupt     (C) 2020
 */
///*public*/ class LnMeterInitTask {


    /**
     * Create a task to perform an initial query of LocoNet for devices
     * which provide data for JMRI Meters.
     *
     * @param tc Traffic Controller used when sending query
     * @param interval - delay between checks of connection's readiness
     */
    /*public*/ LnMeterInitTask::LnMeterInitTask(LnTrafficController* tc, int interval, QObject *parent)
       : QObject(parent)
    {
        this->tc = tc;
       _sleepInterval = interval;

       log->setDebugEnabled(false);
    }

    /**
     * Enable the task to begin
     */
    /*protected*/ void LnMeterInitTask::enable() {
        if (!_enabled) {
            _enabled = true;
            if(_intervalTask != nullptr) {
                _intervalTask->enable(true);
            }
        }
    }

    /**
     * Cancel the task (if it is not already canceled)
     */
    /*protected*/ void LnMeterInitTask::disable() {
        if(_intervalTask != nullptr) {
            _intervalTask->enable(false);
            _intervalTask->quit();
        }
    }

    /**
     * Initializes timer for send of meters query.
     *
     * Cancels any existing task.  Checks delay and
     * exits if delay is negative.  Establishes a
     * new task only if delay is greater than 0.
     */
    /*public*/ void LnMeterInitTask::initTimer() {
        if(_intervalTask != nullptr) {
           _intervalTask->cancel();
           _intervalTask = nullptr;
        }
        if(_sleepInterval < 0){
           return; // don't start or restart the timer.
        }
        _intervalTask = new UpdateTask01(this);
        log->debug("Starting Initialization Timer");
        TimerUtil::scheduleAtFixedRate(_intervalTask,
                _sleepInterval, _sleepInterval);
    }

    /**
     * Remove references to and from this object, so that it can eventually be
     * garbage-collected.
     */
    /*public*/ void LnMeterInitTask::dispose(){
        if ((_intervalTask != nullptr) && (_intervalTask->isEnabled())) {
           _intervalTask->enable(false);
        }
        if (_intervalTask != nullptr) {
            _intervalTask = nullptr;
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* LnMeterInitTask::log = LoggerFactory::getLogger("LnMeterInitTask");
