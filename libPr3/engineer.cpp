#include "engineer.h"
#include "dccthrottle.h"
#include "warrant.h"
#include "abstractsensor.h"
#include "instancemanager.h"
#include "oblock.h"
#include "abstractthrottlemanager.h"
#include "rosterspeedprofile.h"
#include "signalspeedmap.h"

//Engineer::Engineer(QObject *parent) :
//    QThread(parent)
//{
//}
/**
 * Execute a throttle command script for a warrant
 *
 * @version $Revision: 21526 $
 * @author	Pete Cressman  Copyright (C) 2009, 2010, 2011
 */

    /************************** Thread running the train *****************/

// /*public*/ class Engineer extends Thread implements Runnable, java.beans.PropertyChangeListener {

Engineer::Engineer(Warrant* warrant, DccThrottle* throttle, QObject *parent) : QThread(parent)
{
 _speedType = "Normal";
  _minSpeed = 1.0/127;
 _abort = false;
 _halt = false;  // halt/resume from user's control
 _waitForClear = false;  // waits for signals/occupancy/allocation to clear
 _waitForSync = false;  // waits for train to catch up to commands
 _waitForSensor = false; // wait for sensor event
 _speedOverride = false; // speed changing due to signal or occupancy
 log = new Logger("Engineer");

 _warrant = warrant;
 _idxCurrentCommand = -1;
 _throttle = throttle;
 _syncIdx = 0;
 setSpeedStepMode(_throttle->getSpeedStepMode());
}
#if 0
    /*public*/ void run() {
 _debug = log->isDebugEnabled();
        if (log->isDebugEnabled()) log->debug("Engineer started warrant "+_warrant.getDisplayName());

        while (_idxCurrentCommand+1 < _warrant._commands.size()) {
            long et = System.currentTimeMillis();
            ThrottleSetting ts = _warrant._commands.get(_idxCurrentCommand+1);
            long time = ts.getTime();
            String command = ts.getCommand().toUpperCase();
            // actual playback total elapsed time is "ts.getTime()" before record time.
            // current block at playback may also be before current block at record
            synchronized(this) {
                if (_abort) { break; }
                try {
                    if (time > 0) {
                        wait(time);
                    }
                    if (_abort) { break; }
                    if (!command==("SET SENSOR") && !command==("WAIT SENSOR")
                                && !command==("RUN WARRANT")) {
                        _syncIdx = _warrant.getIndexOfBlock(ts.getBlockName(), _warrant._idxCurrentOrder);
                        // Having waited, time=ts.getTime(), so blocks should agree.  if not,
                        // wait for train to arrive at block and send sync notification.
                        // note, blind runs cannot detect entrance.
                        if (!_warrant._tempRunBlind && _syncIdx > _warrant._idxCurrentOrder) {
                            // commands are ahead of current train position
                            if (log->isDebugEnabled()) log->debug("Command Block \""+ts.getBlockName()+
                                                      "\" wait for train to enter. "+_warrant.getDisplayName());
                            _waitForSync = true;
                            _warrant.fireRunStatus("Command", Integer.valueOf(_idxCurrentCommand), Integer.valueOf(_idxCurrentCommand+1));
                            wait();
                        }
                    }
                } catch (InterruptedException ie) {
                    log->error("InterruptedException "+ie);
                } catch (java.lang.IllegalArgumentException iae) {
                    log->error("IllegalArgumentException "+iae);
                }

                _waitForSensor = false;
                _waitForSync = false;
                if (_abort) { break; }

                _idxCurrentCommand++;
                try {
                    if (_waitForClear || _halt) {
                        wait();
                    }
                } catch (InterruptedException ie) {
                    log->error("InterruptedException "+ie);
                }
                if (_abort) { break; }
            }

            try {
                if (command==("SPEED")) {
                    float speed = Float.parseFloat(ts.getValue());
                    _lock.lock();
                    try {
                        setSpeed(modifySpeed(speed, _speedType));
                    } finally {
                      _lock.unlock();
                    }
                } else if (command==("SPEEDSTEP")) {
                    int step = Integer.parseInt(ts.getValue());
                    setStep(step);
                } else if (command==("FORWARD")) {
                    bool isForward = Boolean.parseBoolean(ts.getValue());
                    _throttle.setIsForward(isForward);
                } else if (command.startsWith("F")) {
                    int cmdNum = Integer.parseInt(command.substring(1));
                    bool isTrue = Boolean.parseBoolean(ts.getValue());
                    setFunction(cmdNum, isTrue);
                } else if (command.startsWith("LOCKF")) {
                    int cmdNum = Integer.parseInt(command.substring(5));
                    bool isTrue = Boolean.parseBoolean(ts.getValue());
                    setLockFunction(cmdNum, isTrue);
                } else if (command==("SET SENSOR")) {
                    setSensor(ts.getBlockName(), ts.getValue());
                } else if (command==("WAIT SENSOR")) {
                    getSensor(ts.getBlockName(), ts.getValue());
                } else if (command==("RUN WARRANT")) {
                    runWarrant(ts);
                }
                _warrant.fireRunStatus("Command", Integer.valueOf(_idxCurrentCommand), Integer.valueOf(_idxCurrentCommand+1));
                et = System.currentTimeMillis()-et;
                if (log->isDebugEnabled()) log->debug("Cmd #"+(_idxCurrentCommand+1)+": "+
                                                    ts.toString()+" et= "+et+" warrant "+_warrant.getDisplayName());
            } catch (NumberFormatException e) {
                  log->error("Command failed! "+ts.toString()+" - "+e);
            }
         }
        // shut down
        abort();
    }

    /*private*/ void setStep(int step) {
        setSpeedStepMode(step);
        _throttle.setSpeedStepMode(step);
    }
#endif
/*private*/ void Engineer::setSpeedStepMode(int step) {
        switch (step) {
            case DccThrottle::SpeedStepMode14:
                _minSpeed = 1.0/15;
                break;
            case DccThrottle::SpeedStepMode27:
                _minSpeed = 1.0/28;
                break;
            case DccThrottle::SpeedStepMode28:
                _minSpeed = 1.0/29;
                break;
            default:
                _minSpeed = 1.0/127;
                break;
        }
    }

    /*public*/ int Engineer::getCurrentCommandIndex() {
        return _idxCurrentCommand;
    }

/*protected*/ void Engineer::setCurrentCommandIndex(int idx) {
    _idxCurrentCommand = idx;
}

    /**
    * If waiting to sync entrance to a block boundary with record time,
    * this call will free the wait.
    * @param  block train has just entered.
    */
    /*synchronized*/ /*public*/ void Engineer::synchNotify(OBlock* block) {
//        if (!_halt && !_wait) {
    QMutexLocker locker(&mutex);
        if (!_halt) {
            if (_syncIdx <= _warrant->_idxCurrentOrder) {
//                this->notify();
            }
        }
        if (log->isDebugEnabled()) {
            if (block!=NULL) log->debug("synchNotify from block "+block->getDisplayName()+
                    " _waitForClear= "+_waitForClear+" for warrant "+_warrant->getDisplayName());
            else  log->debug(tr("synchNotify: _waitForSync= ")+(_waitForSync?"true":"false")+
                             " _waitForClear= "+(_waitForClear?"true":"false")+" for warrant "+_warrant->getDisplayName());
        }
    }
    /**
    * Occupancy of blocks and aspects of Portal signals may modify normal train speed
    * Ramp speed change.
    */
    /*synchronized*/ /*public*/ void Engineer::rampSpeedTo(QString endSpeedType, long /*waitTime*/) {
        if (_speedType==(endSpeedType)) {
            return;
        }
//        ThrottleRamp ramp = new ThrottleRamp(endSpeedType, waitTime);
//        new Thread(ramp).start();
    }
#if 0
    /**
    * Get the last normal speed setting.  Regress through commends, if necessary.
    */
    /*private*/ float getLastSpeedCommand(int currentIndex) {
        float speed = 0.0f;
        if (currentIndex<0) {
            return speed;
        }
        ThrottleSetting ts = _warrant._commands.get(currentIndex);
        String command = ts.getCommand().toUpperCase();
        try {
            if (command==("SPEED")) {
                speed = Float.parseFloat(ts.getValue());
            }
            int idx = currentIndex;
            while (!command==("SPEED") && idx>0) {
                idx--;
                ts = _warrant._commands.get(idx);
                command = ts.getCommand().toUpperCase();
                if (command==("SPEED")) {
                    speed = Float.parseFloat(ts.getValue());
                }
            }
            if (log->isDebugEnabled()) log->debug("getLastSpeedCommand: speed= "+speed+", from Command #"+idx+
                    " warrant "+_warrant.getDisplayName());
        } catch (NumberFormatException nfe) {
              log->warn(ts.toString()+" - "+nfe);
        }
        return speed;
    }
#endif
/*private*/ float Engineer::modifySpeed(float s, QString sType) {
    SignalSpeedMap* map = Warrant::getSpeedMap();
    float speed = map->getSpeed(sType)/100;

    if (map->isRatioOfNormalSpeed()) {
        speed *= s;
    } else { // max speed specified by signal aspect
        // use the minimum of recorded speed and aspect specified speed
        if (s<speed) {
            speed = s;
        }
    }
    speed *= _warrant->_throttleFactor;
    if (0.0f < speed && speed < _minSpeed) {
        speed = 0.0f;
    }
    return speed;
}

/*private*/ void Engineer::setSpeed(float speed) {
        _speed = speed;
        _throttle->setSpeedSetting(_speed);
        if (log->isDebugEnabled()) log->debug("_speedType="+_speedType+", Speed set to "+
                                              QString::number( _speed)+" _waitForClear= "+(_waitForClear?"true":"false")+" warrant "+_warrant->getDisplayName());
    }

    /*synchronized*/ /*public*/ int Engineer::getRunState()
    {
        QMutexLocker locker(&mutex);
        if (_abort) {
            return Warrant::ABORT;
        } else if (_waitForClear) {
            return Warrant::WAIT_FOR_CLEAR;
        } else if (_waitForSync) {
            return Warrant::WAIT_FOR_TRAIN;
        } else if (_waitForSensor) {
            return Warrant::WAIT_FOR_SENSOR;
        } else  if (_halt) {
            return Warrant::HALT;
        } else if (_speedType!=("Normal")) {
            return Warrant::SPEED_RESTRICTED;
        }
        return Warrant::RUNNING;
    }

    /*public*/ QString Engineer::getSpeedRestriction() {
        if (_speedOverride) {
            return "Change to "+_speedType;
        }
        else if (_speed == 0.0f) {
            return "At Stop";
        } else {
            return _speedType;
        }
    }
    /**
    * Flag from user's control
    */
/*synchronized*/ /*public*/ void Engineer::setHalt(bool halt)
{
 QMutexLocker locker(&mutex);
 _halt = halt;
 if (!_halt)
 {
#if 0
  _lock.lock();
  try
  {
   setSpeed(modifySpeed(getLastSpeedCommand(_idxCurrentCommand), _speedType));
            if (!_waitForClear) {
                this.notify();
            }
   }
  catch ()
   {
   finally {
            _lock.unlock();
        }
    } else {
        _throttle->setSpeedSetting(0.0f);
    }
#endif
  if (log->isDebugEnabled()) log->debug(tr("setHalt(")+(halt?"true":"false")+"): throttle speed= "+_throttle->getSpeedSetting()+
                                " _waitForClear= "+(_waitForClear?"true":"false")+" warrant "+_warrant->getDisplayName());\
 }
}
/**
* Flag from user to end run
*/
/*synchronized*/ /*public*/ void Engineer::abort() {
    QMutexLocker locker(&mutex);
    _abort = true;
    if (_throttle != NULL) {
        _throttle->setSpeedSetting(-1.0f);
        _throttle->setSpeedSetting(0.0f);
        try {
            ((AbstractThrottleManager*)InstanceManager::throttleManagerInstance())->releaseThrottle(_throttle, (ThrottleListener*)_warrant);
        } catch (Exception e) {
            // NULL pointer catch and maybe other such.
            log->warn("Throttle release and cancel threw: "+e.getMessage());
        }
    }
    _warrant->setRunMode(Warrant::MODE_NONE, NULL, NULL, NULL, false);
    if (log->isDebugEnabled()) log->debug("Engineer shut down. warrant "+_warrant->getDisplayName());
}
/*protected*/ void Engineer::releaseThrottle() {
        InstanceManager::throttleManagerInstance()->releaseThrottle(_throttle, (ThrottleListener*)_warrant);
    }
#if 0
/*private*/ void setFunction(int cmdNum, bool isSet) {
    switch (cmdNum)
    {
        case 0: _throttle.setF0(isSet); break;
        case 1: _throttle.setF1(isSet); break;
        case 2: _throttle.setF2(isSet); break;
        case 3: _throttle.setF3(isSet); break;
        case 4: _throttle.setF4(isSet); break;
        case 5: _throttle.setF5(isSet); break;
        case 6: _throttle.setF6(isSet); break;
        case 7: _throttle.setF7(isSet); break;
        case 8: _throttle.setF8(isSet); break;
        case 9: _throttle.setF9(isSet); break;
        case 10: _throttle.setF10(isSet); break;
        case 11: _throttle.setF11(isSet); break;
        case 12: _throttle.setF12(isSet); break;
        case 13: _throttle.setF13(isSet); break;
        case 14: _throttle.setF14(isSet); break;
        case 15: _throttle.setF15(isSet); break;
        case 16: _throttle.setF16(isSet); break;
        case 17: _throttle.setF17(isSet); break;
        case 18: _throttle.setF18(isSet); break;
        case 19: _throttle.setF19(isSet); break;
        case 20: _throttle.setF20(isSet); break;
        case 21: _throttle.setF21(isSet); break;
        case 22: _throttle.setF22(isSet); break;
        case 23: _throttle.setF23(isSet); break;
        case 24: _throttle.setF24(isSet); break;
        case 25: _throttle.setF25(isSet); break;
        case 26: _throttle.setF26(isSet); break;
        case 27: _throttle.setF27(isSet); break;
        case 28: _throttle.setF28(isSet); break;
    }
}

/*private*/ void setLockFunction(int cmdNum, bool isTrue) {
    switch (cmdNum)
    {
        case 0: _throttle.setF0Momentary(!isTrue); break;
        case 1: _throttle.setF1Momentary(!isTrue); break;
        case 2: _throttle.setF2Momentary(!isTrue); break;
        case 3: _throttle.setF3Momentary(!isTrue); break;
        case 4: _throttle.setF4Momentary(!isTrue); break;
        case 5: _throttle.setF5Momentary(!isTrue); break;
        case 6: _throttle.setF6Momentary(!isTrue); break;
        case 7: _throttle.setF7Momentary(!isTrue); break;
        case 8: _throttle.setF8Momentary(!isTrue); break;
        case 9: _throttle.setF9Momentary(!isTrue); break;
        case 10: _throttle.setF10Momentary(!isTrue); break;
        case 11: _throttle.setF11Momentary(!isTrue); break;
        case 12: _throttle.setF12Momentary(!isTrue); break;
        case 13: _throttle.setF13Momentary(!isTrue); break;
        case 14: _throttle.setF14Momentary(!isTrue); break;
        case 15: _throttle.setF15Momentary(!isTrue); break;
        case 16: _throttle.setF16Momentary(!isTrue); break;
        case 17: _throttle.setF17Momentary(!isTrue); break;
        case 18: _throttle.setF18Momentary(!isTrue); break;
        case 19: _throttle.setF19Momentary(!isTrue); break;
        case 20: _throttle.setF20Momentary(!isTrue); break;
        case 21: _throttle.setF21Momentary(!isTrue); break;
        case 22: _throttle.setF22Momentary(!isTrue); break;
        case 23: _throttle.setF23Momentary(!isTrue); break;
        case 24: _throttle.setF24Momentary(!isTrue); break;
        case 25: _throttle.setF25Momentary(!isTrue); break;
        case 26: _throttle.setF26Momentary(!isTrue); break;
        case 27: _throttle.setF27Momentary(!isTrue); break;
        case 28: _throttle.setF28Momentary(!isTrue); break;
    }
}

/**
 * Set Sensor state
 * @param sensorName
 * @param action
 */
/*private*/ void setSensor(String sensorName, String action) {
    action = action.toUpperCase();
    jmri.Sensor s = InstanceManager.sensorManagerInstance().getSensor(sensorName);
    if (s != NULL) {
        try {
            if ("ACTIVE"==(action)) {
                s.setKnownState(jmri.Sensor.ACTIVE);
            } else if ("INACTIVE"==(action)) {
                s.setKnownState(jmri.Sensor.INACTIVE);
            }
        } catch (jmri.JmriException e) {
            log->warn("Exception setting sensor "+sensorName+" in action");
        }
    } else {
        log->warn("Sensor "+sensorName+" not found.");
    }
}

/**
 * Wait for Sensor state event
 * @param sensorName
 * @param action
 */
/*private*/ void getSensor(String sensorName, String action) {
    action = action.toUpperCase();
    _waitSensor = InstanceManager.sensorManagerInstance().getSensor(sensorName);
    if (_waitSensor != NULL) {
        int state = _waitSensor.getKnownState();
        if ("ACTIVE"==(action)) {
            _sensorWaitState = Sensor.ACTIVE;
        } else if ("INACTIVE"==(action)) {
            _sensorWaitState = Sensor.INACTIVE;
        }
        if (state==_sensorWaitState) {
            log->warn("Engineer: state of event sensor "+sensorName+" already at state "+action);
            return;
        }
        _waitSensor.addPropertyChangeListener(this);
        if (log->isDebugEnabled()) log->debug("Listen for propertyChange of "+
                _waitSensor.getDisplayName()+", wait for State= "+_sensorWaitState);
        // suspend commands until sensor changes state
        synchronized(this) {
            try {
                _waitForSensor = true;
                wait();
            } catch (InterruptedException ie) {
                log->error("InterruptedException "+ie);
            }
        }
   } else {
        log->warn("Sensor "+sensorName+" not found.");
    }
}
#endif
/*protected*/ Sensor* Engineer::getWaitSensor() {
    return _waitSensor;
}
#if 0
/*public*/ void propertyChange(java.beans.PropertyChangeEvent evt) {
    if (log->isDebugEnabled()) log->debug("propertyChange "+evt.getPropertyName()+
            " new value= "+evt.getNewValue());
    if ((evt.getPropertyName()==("KnownState") &&
            ((Number)evt.getNewValue()).intValue()== _sensorWaitState) ) {
        synchronized(this) {
            if (!_halt) {
                this.notify();
                _waitSensor.removePropertyChangeListener(this);
                _sensorWaitState = 0;
                _waitSensor = NULL;
            }
        }
    }
}

/**
 * Wait for Sensor state event
 * @param sensorName
 * @param action
 */
/*private*/ void runWarrant(ThrottleSetting ts) {
    Warrant w = InstanceManager.warrantManagerInstance().getWarrant(ts.getBlockName());
    if (w==NULL) {
        log->warn("Warrant \""+ts.getBlockName()+"\" not found.");
        return;
    }
    int num = 0;
    try {
        num = Integer.parseInt(ts.getValue());
    } catch (NumberFormatException nfe) {
        log->error("Could not parse \""+ts.getValue()+"\". "+nfe);
    }
    if (num==0) {
        log->info("Warrant \""+_warrant.getDisplayName()+"\" completed last launch of \""+ts.getBlockName()+"\".");
        return;
    }
    if (num>0) {
        num--;
        ts.setValue(Integer.toString(num));
    }
    String msg = NULL;
    if (_warrant==(w)) {
        _idxCurrentCommand = -1;
        w.startupWarrant();
    } else {
        msg = w.setRunMode(Warrant::MODE_RUN, NULL, NULL, NULL, false);
    }
    if (msg!=NULL) {
        log->error("Continuing warrant lanch from \""+_warrant.getDisplayName()+"\": "+msg);
    }
}

class ThrottleRamp implements Runnable {
    String endSpeedType;

    ThrottleRamp(String type, long startWait) {
        endSpeedType = type;
        synchronized(this) {
            if (startWait>0.0) {
                try {
                    wait(startWait);
                } catch (InterruptedException ie) {
                    log->error("InterruptedException "+ie);
                }
            }
        }
        _speedOverride = true;
    }

    /*public*/ void run() {
        _lock.lock();
        try {
            float endSpeed = getLastSpeedCommand(_idxCurrentCommand);
            endSpeed = modifySpeed(endSpeed, endSpeedType);
            String old = _speedType;
            _speedType = endSpeedType;   // transition
            if (log->isDebugEnabled()) log->debug("rampSpeed from \""+old+"\" to \""+endSpeedType+
                                "\" on warrant "+_warrant.getDisplayName());
            float speed = _throttle.getSpeedSetting();
            _warrant.fireRunStatus("SpeedRestriction", old,
                               (endSpeed > speed ? "increasing" : "decreasing"));

            synchronized(this) {
                if (!_speedType==("Stop")) {
                    notify();
                    _waitForClear = false;
                } else {
                    _waitForClear = true;
                }
            }

            float incr = Math.max(_throttle.getSpeedIncrement(), _minSpeed);
            switch (_throttle.getSpeedStepMode()) {
                case DccThrottle.SpeedStepMode14:
                    break;
                case DccThrottle.SpeedStepMode27:
                case DccThrottle.SpeedStepMode28:
                    incr *= 2;
                    break;
                default:    // SpeedStepMode128
                    incr *= 4;
                    break;
            }
            jmri.implementation.SignalSpeedMap map = Warrant::getSpeedMap();
            incr *= map.getNumSteps();
            int delay = map.getStepDelay();

            if (endSpeed > speed) {
                synchronized(this) {
                    while (speed < endSpeed) {
                        speed += incr;
                        if (speed > endSpeed) { // don't overshoot
                            speed = endSpeed;
                        }
                        setSpeed(speed);
                        try {
                            wait(delay);
                        } catch (InterruptedException ie) {
                            log->error("InterruptedException "+ie);
                        }
                    }
                }
            } else {
                synchronized(this) {
                    while (speed > endSpeed) {
                        speed -= incr;
                        if (speed < endSpeed) { // don't undershoot
                            speed = endSpeed;
                        }
                        setSpeed(speed);
                        try {
                            wait(delay);
                        } catch (InterruptedException ie) {
                            log->error("InterruptedException "+ie);
                        }
                    }
                }
            }
            _warrant.fireRunStatus("SpeedRestriction", old, _speedType);
        } finally {
            _speedOverride = false;
            _lock.unlock();
        }
        if (log->isDebugEnabled()) log->debug("rampSpeed complete to \""+endSpeedType+
                "\" on warrant "+_warrant.getDisplayName());
        synchNotify(NULL);
    }
}
#endif
/*synchronized*/ /*protected*/ void Engineer::setWaitforClear(bool set)
{
    bool wasWaitforClear = _waitForClear;
    _waitForClear = set;
    checkHalt();
    if (!_waitForClear && !_halt && wasWaitforClear) {
        if (_debug) log->debug("setWaitforClear calls notify()");
        this->notify();
    }
}
/*private*/ float Engineer::getThrottleFactor(float speedStep)
{
 if (_speedProfile != NULL)
 {
     return _speedProfile->getSpeed(speedStep, _throttle->getIsForward())/(speedStep*1000);
 }
 return _speedMap->getDefaultThrottleFactor();
}
/*protected*/ QString Engineer::minSpeedType(QString speed1, QString speed2)
{
 if (secondGreaterThanFirst(speed1, speed2)) {
     return speed1;
 }
 return speed2;
}
/**
    * If waiting to sync entrance to a block boundary with recorded wait time,
    * or waiting for clearance ahead for rogue occupancy, stop aspect or sharing
    *  of turnouts, this call will free the wait.
    */
    /*synchronized*/ /*protected*/ void Engineer::checkHalt() {
        if (_waitForSync &&!_halt && !_waitForSensor && !_waitForClear) {
            if (_debug) log->debug("checkHalt calls notify()");
            this->notify();
        }
        if (_debug) log->debug(QString("checkHalt _waitForSync= ")+(_waitForSync?"true":"false"));
    }
/**
    * Occupancy of blocks and aspects of Portal signals may modify normal train speed
    * Ramp speed change.
    */
    /*protected*/ void Engineer::rampSpeedTo(QString endSpeedType)
{
//        checkHalt();
        if (_speedType==(endSpeedType)) {
            return;
        }
        if (_throttle->getSpeedSetting()<=0 && (endSpeedType==(Warrant::Stop) || endSpeedType==(Warrant::EStop))) {
            _waitForClear = true;
            _speedType = endSpeedType;
            return;
        }
#if 0 // TODO:
        if (_ramp!=NULL) {
            _ramp->quit();
            _ramp = NULL;
        }
        /*synchronized*/(this) {
            if (_debug) log->debug("rampSpeedTo: \""+endSpeedType+"\" from \""+
                    _speedType+"\" setting= "+_throttle->getSpeedSetting()+" for warrant "+_warrant->getDisplayName());
            _ramp = new ThrottleRamp(endSpeedType);
            new Thread(_ramp).start();
        }
#endif
    }
/*protected*/ float Engineer::getDistanceTraveled(float speedSetting, QString speedtype, long time)
{
 float speed =  modifySpeed(speedSetting, speedtype);
 float distance;
 bool isForward = _throttle->getIsForward();
 if (_speedProfile != NULL) {
     distance = _speedProfile->getSpeed(speed, isForward)*time/1000;
 } else {
     distance = (speed*time)/_speedMap->getDefaultThrottleFactor();
 }
 return distance;
}
// return a boolean so minSpeedType() can return a non-null String if possible
/*protected*/ bool Engineer::secondGreaterThanFirst(QString speed1, QString speed2) {
 if (speed1=="") {
        return false;
    }
 if (speed2=="") {
        return true;
    }
    float s1 = modifySpeed(1.0f, speed1);
    float s2 = modifySpeed(1.0f, speed2);
    return (s1<s2);
}
/*protected*/ DccThrottle* Engineer::getThrottle() {
    return _throttle;
}
/*protected*/ float Engineer::rampLengthForSpeedChange(float curSpeed, QString curSpeedType, QString toSpeedType)
{
    if (curSpeedType==(toSpeedType)) {
        return 0.0f;
    }
    float fromSpeed = modifySpeed(curSpeed, curSpeedType);
    float toSpeed = modifySpeed(curSpeed, toSpeedType);
    if (toSpeed>fromSpeed) {
        float tmp = fromSpeed;
        fromSpeed = toSpeed;
        toSpeed = tmp;
    }
    float rampLength = 0.0f;
    float delta = _speedMap->getStepIncrement();
    if (delta<=0.007f) {
        log->error("SignalSpeedMap StepIncrement is not set correctly.  Check Preferences->Warrants.");
        return 1.0f;
    }
    float time = _speedMap->getStepDelay();
    bool isForward = _throttle->getIsForward();
    float speed = fromSpeed;
    while (speed >= toSpeed) {
        float dist;
        if (_speedProfile != NULL) {
            dist = _speedProfile->getSpeed((speed-delta/2), isForward)*time/1000;
        } else {
            dist = (speed-delta/2)*time/_speedMap->getDefaultThrottleFactor();
        }
        if (dist<=0.0f) {
            break;
        }
        speed -= delta;
        if (speed>=toSpeed) {
            rampLength += dist;
        } else {
            rampLength += (delta-(speed-speed))*dist/delta;
        }
    }
    if (_debug) log->debug("rampLengthForSpeedChange()= "+QString::number(rampLength)+
            " for speed= "+QString::number(fromSpeed)+", "+curSpeedType+" to "+toSpeedType+", from "+
            (_speedProfile!=NULL?"SpeedProfile":"Factor="+QString::number(getThrottleFactor(curSpeed))));
    return rampLength;
}
/*protected*/ long Engineer::getTimeForDistance(float speed, float distance)
{
    bool isForward = _throttle->getIsForward();
    float time;
    if (_speedProfile != NULL) {
        time = distance*1000/_speedProfile->getSpeed(speed, isForward);
    } else {
        time = distance*_speedMap->getDefaultThrottleFactor()/speed;
    }
    return (long)time;
}
/*private*/ void Engineer::notify()
{
 // TODO:
}
