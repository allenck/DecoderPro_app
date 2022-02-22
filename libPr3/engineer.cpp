#include "engineer.h"
#include "dccthrottle.h"
#include "abstractsensor.h"
#include "instancemanager.h"
#include "oblock.h"
#include "abstractthrottlemanager.h"
#include "rosterspeedprofile.h"
#include "signalspeedmap.h"
#include "throttlesetting.h"
#include "speedutil.h"
#include "warranttableframe.h"
#include "sleeperthread.h"
#include "blockorder.h"
#include "warranttablemodel.h"
#include "loggerfactory.h"
#include "jmriexception.h"

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

Engineer::Engineer(Warrant* warrant, DccThrottle* throttle, QObject *parent) : QObject(parent)
{
 _speedType = "Normal";
  _minSpeed = 1.0/127;
 _abort = false;
 _halt = false;  // halt/resume from user's control
 _waitForClear = false;  // waits for signals/occupancy/allocation to clear
 _waitForSync = false;  // waits for train to catch up to commands
 _waitForSensor = false; // wait for sensor event
 _speedOverride = false; // speed changing due to signal or occupancy
 _commands = new QList<ThrottleSetting*>();

 _warrant = warrant;
 _throttle = throttle;
 _speedUtil = warrant->getSpeedUtil();
 _commands = _warrant->getThrottleCommands();
 _idxCurrentCommand = 0;
 _idxSkipToSpeedCommand = 0;
 _syncIdx = -1;
 _waitForSensor = false;
 setObjectName("Engineer(" + _warrant->getTrainName() +")");
 log->setDebugEnabled(true);
}

/*public*/ void Engineer::process() // run in Java
{
 _debug = log->isDebugEnabled();
 if (log->isDebugEnabled())
  log->debug("Engineer started warrant "+_warrant->getDisplayName());

 cmdBlockIdx = 0;
 while (_idxCurrentCommand < _commands->size())
 {
  while (_idxSkipToSpeedCommand > _idxCurrentCommand)
  {
   if (log->isDebugEnabled())
   {
       ThrottleSetting* ts = _commands->value(_idxCurrentCommand);
       log->debug(tr("Skip Cmd #%1: %2 Warrant %3").arg(_idxCurrentCommand+1).arg(ts->toString()).arg(_warrant->getDisplayName()));
       // Note: command indexes biased from 0 to 1 to match Warrant display of commands.
   }
   _idxCurrentCommand++;
  }
  et = QDateTime::currentMSecsSinceEpoch(); //System.currentTimeMillis();
  ThrottleSetting* ts = _commands->value(_idxCurrentCommand);
  long cmdWaitTime = ts->getTime();    // time to wait before executing command
  _currentCommand = ts->getCommand().toUpper();
  _runOnET = _setRunOnET;     // OK to set here
  if ("SET SENSOR"!=(_currentCommand) && "WAIT SENSOR"!=(_currentCommand) &&
          "RUN WARRANT"!=(_currentCommand)) {
      int idx = _warrant->getIndexOfBlock(ts->getBeanDisplayName(), cmdBlockIdx);
      if (idx >= 0) {
          cmdBlockIdx = idx;
      }
  }
  if (cmdBlockIdx < _warrant->getCurrentOrderIndex() ||
          (_currentCommand==("NOOP") && (cmdBlockIdx <= _warrant->getCurrentOrderIndex()))) {
      // Train advancing too fast, need to process commands more quickly,
      // allow some time for whistle toots etc.
      cmdWaitTime = qMin(cmdWaitTime, 200L); // 200ms per command should be enough for toots etc.
      if (log->isDebugEnabled())
          log->debug(tr("Train reached block \"%1\" before script et=%2ms . Warrant %3").arg(
                  _warrant->getCurrentBlockName()).arg(ts->getTime()).arg(_warrant->getDisplayName()));
  }
  if (_abort) {
      break;
  }
  if (log->isDebugEnabled())
      log->debug(tr("Start Cmd #%1 for block \"%2\" currently in \"%3\". wait %4ms to do cmd %5. Warrant %6").arg(
          _idxCurrentCommand+1).arg(ts->getBeanDisplayName()).arg(_warrant->getCurrentBlockName()).arg(
          cmdWaitTime).arg(_currentCommand).arg(_warrant->getDisplayName()));
          // Note: command indexes biased from 0 to 1 to match Warrant display of commands.
  /*synchronized (this)*/ {
   mutex.lock();
      if (Warrant::Normal != (_speedType)) {
          cmdWaitTime = (long)(cmdWaitTime*_timeRatio); // extend et when speed has been modified from scripted speed
      }
      try {
          if (cmdWaitTime > 0) {
              //wait(cmdWaitTime);
           SleeperThread::msleep(cmdWaitTime);
          }
          if (_abort) {
              break;
          }
      } catch (InterruptedException ie) {
          log->error(tr("At time wait %1").arg(ie.toString()));
          _warrant->debugInfo();
          //Thread.currentThread().interrupt();
          emit finished();
          thread()->quit();
      } catch (IllegalArgumentException iae) {
          log->error(tr("At time wait %1").arg(iae.toString()));
      }
      mutex.unlock();
  }

  _syncIdx = cmdBlockIdx;
  // Having waited, time=ts.getTime(), so blocks should agree.  if not,
  // wait for train to arrive at block and send sync notification.
  // note, blind runs cannot detect entrance.
  if (!_runOnET && _syncIdx > _warrant->getCurrentOrderIndex())
  {
   // commands are ahead of current train position
   // When the next block goes active or a control command is made, a clear sync call
   // will test these indexes again and can trigger a notify() to free the wait
   /*synchronized (this)*/
   {
    mutex.lock();
    try
    {
     _waitForSync = true;
     if (log->isDebugEnabled())
         log->debug(tr("Wait for train to enter \"%1\". Warrant %2").arg(
             _warrant->getBlockAt(_syncIdx)->getDisplayName()).arg(_warrant->getDisplayName()));
     _warrant->fireRunStatus("WaitForSync", _idxCurrentCommand - 1, _idxCurrentCommand);
     waitForSync.wait(&mutex);
    }
    catch (InterruptedException ie)
    {
     log->error(tr("At _waitForSync %1").arg(ie.toString()));
     _warrant->debugInfo();
     //Thread.currentThread().interrupt();
     emit finished();
    }
//          finally {
    _waitForSync = false;
//          }
    mutex.unlock();
   }
  }
  if (_abort) {
      break;
  }

  /*synchronized (this)*/ {
   mutex.lock();
   // block position and elapsed time are as expected, but track conditions
   // such as signals or rogue occupancy requires waiting
   if (_waitForClear)
   {
    try
    {
     _atClear = true;
     if (log->isDebugEnabled())
         log->debug(tr("Waiting for clearance. _waitForClear= %1 _halt= $2 \"%3\".  Warrant %4").arg(
             _waitForClear).arg(_halt).arg(_warrant->getBlockAt(cmdBlockIdx)->getDisplayName()).arg(_warrant->getDisplayName()));
     waitForClear.wait(&mutex);
    }
    catch (InterruptedException ie)
    {
     log->error(tr("At _atClear %1").arg(ie.toString()));
     _warrant->debugInfo();
     //Thread.currentThread().interrupt();
     emit finished();
    }
//          finally {
    _waitForClear = false;
    _atClear = false;
//          }

   }
   mutex.unlock();
  }
  if (_abort) {
      break;
  }

  /*synchronized (this)*/ {
   mutex.lock();
   // user's command to halt requires waiting
   if (_halt)
   {
    try
    {
     _atHalt = true;
     if (log->isDebugEnabled())
         log->debug(tr("Waiting to Resume. _halt= %1, _waitForClear= %2, Block \"%3\".  Warrant %4").arg(
                     _waitForClear).arg(_halt).arg(_warrant->getBlockAt(cmdBlockIdx)->getDisplayName()).arg(_warrant->getDisplayName()));
     atHalt.wait(&mutex);
    }
    catch (InterruptedException ie)
    {
     log->error(tr("At _atHalt %1").arg(ie.toString()));
     _warrant->debugInfo();
     //Thread.currentThread().interrupt();
     emit finished();
    }
//          finally {
     _halt = false;
     _atHalt = false;
//          }
   }
   mutex.unlock();
  }
  if (_abort) {
      break;
  }
  if (_currentCommand == ("SPEED"))
  {
   /*synchronized (this)*/
   {
    mutex.lock();
    if (_ramp != nullptr && !_ramp->ready)
    {
     try
     {
      if (log->isDebugEnabled())
       log->debug(tr("Waiting for ramp to finish.  Warrant %1").arg(_warrant->getDisplayName()));
      //wait();
      waitRampReady.wait(&mutex);
     }
     catch (InterruptedException ie)
     {
      _warrant->debugInfo();
      //Thread.currentThread().interrupt();
      emit finished();
      this->thread()->quit();
     }
//              finally {
//              }
    }
    if (_idxCurrentCommand >= _idxSkipToSpeedCommand)
    {
//              try {
//                  _lock.lock();
     float throttle = ts->getValue().toFloat();
     /* attempt to use dynamic speed measuring - too many variables
     // If recording speed is known, get throttle setting for that speed
     float speed = ts.getSpeed();
     if (speed > 0.0f) {
         speed = _speedUtil.getThrottleSetting(speed);
         if (speed > 0.0f) {
             throttle = speed;
         }
     }*/
     _normalSpeed = throttle;
     float speedMod = _speedUtil->modifySpeed(throttle, _speedType);
     if (qAbs(throttle - speedMod) > .0001f) {
         _timeRatio = throttle / speedMod;
     } else {
         _timeRatio = 1.0f;
     }
     setSpeed(speedMod);
//              }
//           finally {
//                  _lock.unlock();
//              }
    }
    mutex.unlock();
   }
  }
  else
  {    // let non-speed commands go before wait
   try
   {
    if (_currentCommand == ("SPEEDSTEP")) {
        SpeedStepMode::SSMODES mode = SpeedStepMode::getByName(ts->getValue());
        _throttle->setSpeedStepMode(mode);
    } else if (_currentCommand == ("FORWARD")) {
        bool isForward = ts->getValue() == "true";
        _throttle->setIsForward(isForward);
        _speedUtil->setIsForward(isForward);
    } else if (_currentCommand.startsWith("F")) {
        int cmdNum = _currentCommand.mid(1).toInt();
        bool isTrue = ts->getValue()== "true";
        setFunction(cmdNum, isTrue);
    } else if (_currentCommand.startsWith("LOCKF")) {
        int cmdNum = _currentCommand.mid(5).toInt();
        bool isTrue = ts->getValue() == "true";
        setLockFunction(cmdNum, isTrue);
    } else if (_currentCommand == ("SET SENSOR")) {
        setSensor(ts->getBeanSystemName(), ts->getValue());
    } else if (_currentCommand == ("WAIT SENSOR")) {
        getSensor(ts->getBeanSystemName(), ts->getValue());
    } else if (_currentCommand == ("START TRACKER")) {
//              ThreadingUtil.runOnLayout(() -> {
            _warrant->startTracker();
//              });
    } else if (_currentCommand == ("RUN WARRANT")) {
        runWarrant(ts);
    } else if (_runOnET && _currentCommand == ("NOOP")) {    // let warrant know engineer expects entry into dark block
//              ThreadingUtil.runOnLayout(() -> {
            _warrant->goingActive(_warrant->getBlockAt(cmdBlockIdx));
//              });
    }
   }
   catch (NumberFormatException* nfe)
   {
       log->error(tr("Command failed! %1 %2").arg(ts->toString()).arg(nfe->toString()));
   }
  }
  et = QDateTime::currentMSecsSinceEpoch()-et; //System.currentTimeMillis() - et;
  _idxCurrentCommand++;
  if (log->isDebugEnabled())
      log->debug(tr("Cmd #%1 done. et=%2. %3 warrant %4").arg(_idxCurrentCommand).arg(et).arg(ts->toString()).arg(_warrant->getDisplayName()));
 }
 // shut down
 setSpeed(0.0f); // for safety to be sure train stops
 _warrant->stopWarrant(_abort);
}

/*public*/ int Engineer::getCurrentCommandIndex() {
    return _idxCurrentCommand;
}
/**
* Delayed ramp has started.
* Currently informational only
* Do non-speed commands only until idx is reached?  maybe not.
* @param idx index
*/
/*private*/ void Engineer::advanceToCommandIndex(int idx) {
_idxSkipToSpeedCommand = idx;
if (log->isTraceEnabled())
    log->debug(tr("advanceToCommandIndex to %1 - %2").arg(_idxSkipToSpeedCommand+1).arg(_commands->value(idx)->toString()));
    // Note: command indexes biased from 0 to 1 to match Warrant display of commands, which are 1-based.
}
#if 0
/*private*/ void Engineer::setStep(int step) {
    setSpeedStepMode(step);
    _throttle->setSpeedStepMode((SpeedStepMode::SSMODES)step);
}
#endif
/**
 * Cannot set _runOnET to true until current NOOP command completes
 * so there is the intermediate flag _setRunOnET
 * @param set true to run on elapsed time calculations only, false to
 *            consider other inputs
 */
/*protected*/ void Engineer::setRunOnET(bool set) {
    if (log->isDebugEnabled())
        log->debug(tr("setRunOnET %1 command #%2 warrant %3").arg(set).arg(_idxCurrentCommand+1).arg(_warrant->getDisplayName()));
        // Note: command indexes biased from 0 to 1 to match Warrant display of commands.
    _setRunOnET = set;
    if (!set) { // OK to be set false immediately
        _runOnET = false;
    }
}

/*protected*/ bool Engineer::getRunOnET() {
    return _setRunOnET;
}
/**
 * If waiting to sync entrance to a block boundary with recorded wait time,
 * or waiting for clearance ahead for rogue occupancy, stop aspect or
 * sharing of turnouts, this call will free the wait.
 */
/*synchronized*/ /*protected*/ void Engineer::clearWaitForSync() {
    if (_waitForSync) {
        if (log->isDebugEnabled())
            log->debug("clearWaitForSync() calls notify()");
        waitForSync.wakeAll();   // if wait is cleared, this sets _waitForSync= false
    } else {
        ThrottleSetting* ts = _commands->value(_idxCurrentCommand);
        OBlock* block = _warrant->getCurrentBlockOrder()->getBlock();
        // block went active. if waiting on cmdWaitTime, clear it
        if (ts->getCommand().toUpper() == ("NOOP") && ts->getBeanDisplayName() == (block->getDisplayName())) {
            if (log->isDebugEnabled())
                log->debug("clearWaitForSync() calls notify()");
            //notifyAll();
            waitForSync.wakeAll();
        }
    }
}
/**
* Occupancy of blocks and aspects of Portal signals may modify normal train speed
* Ramp speed change.
*/
/*protected*/ void Engineer::rampSpeedTo(QString endSpeedType, int endBlockIdx, bool useIndex)
{
 if (!setSpeedRatio(endSpeedType)) {
     if (endSpeedType != (Warrant::Stop) && endSpeedType != (Warrant::EStop)) {
         setWaitforClear(false);
     }
     return;
 }
 /*synchronized (this)*/ {
     if (log->isDebugEnabled())
         log->debug(tr("rampSpeedTo type= %1, throttle from %2 to %3. warrant %4").arg(
             endSpeedType).arg(getSpeedSetting()).arg(
             _speedUtil->modifySpeed(_normalSpeed,endSpeedType)).arg(
             _warrant->getDisplayName()));

     if (_ramp == nullptr)
     {
      _ramp = new ThrottleRamp(this);
      QThread* thread = new QThread();
      connect(thread, SIGNAL(started()), _ramp, SLOT(process()));
      connect(this, SIGNAL(finished()), thread, SLOT(quit()));
      _ramp->moveToThread(thread);
      thread->start();
     } else {
      _ramp->quit(false);
      _ramp->waitRampSpeedTo.notify_all();
     }
     long time = 0;
     int waitTime = _speedUtil->getRampTimeIncrement() + 20;
     while (time < waitTime && !_ramp->ready) {
         // may need a bit of time for quit() or start() to get ready
         try {
             SleeperThread::msleep(20);
             time += 20;
         }
         catch (InterruptedException ie) { // ignore
         }
     }
     if (_ramp->ready) {
         _ramp->setParameters(endSpeedType, endBlockIdx, useIndex);
         /*synchronized (_ramp)*/ {
             _ramp->notifyAll(); // free wait at ThrottleRamp.run()
             log->debug(tr("rampSpeedTo called notify _ramp.ready=%1").arg(_ramp->ready));
         }
     } else {
         log->error(tr("Can't launch ramp for speed %1! _ramp Thread.State= %2. Waited %3ms").arg(
                 endSpeedType).arg(_ramp->getState()).arg(time-20));
         _warrant->debugInfo();
     }
 }
}

/*private*/ void Engineer::cancelRamp(bool die) {
    if (_ramp != nullptr && !_ramp->ready) {
        _ramp->quit(die);
    }
}

//@SuppressFBWarnings(value= "IS2_INCONSISTENT_SYNC", justification="display of _speedType for viewing only")
/*private*/ void Engineer::rampDone(bool stop, QString type) {
    // ignore "IS2_INCONSISTENT_SYNC" warning here
    if (log->isDebugEnabled())
        log->debug(tr("ThrottleRamp done: %1 for \"%2\" at speed= %3. _normalScript=%4, Thread.State= %5 resume index= %6, current Index= %7 on warrant %8").arg(
                (stop?"stopped":"completed")).arg(type).arg(getSpeedSetting()).arg(_normalSpeed).arg((_ramp != nullptr?_ramp->getState():"_ramp is null!")).arg(
                _idxSkipToSpeedCommand+1).arg(_idxCurrentCommand+1).arg(_warrant->getDisplayName()));
                // Note: command indexes biased from 0 to 1 to match Warrant display of commands.
    if (!stop) {
        _warrant->fireRunStatus("RampDone", _halt, type);
     }
    if (!_atHalt && !_atClear) {
        /*synchronized (this)*/ {
            //notifyAll();  // let engineer run script
      waitForClear.wakeAll();
            log->debug("rampDone called notify");
        }
        if (_currentCommand == ("NOOP")) {
            _idxCurrentCommand--;   // notify advances command.  Repeat wait for entry to next block
        }
    }
}
#if 0
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
#endif
/*private*/ void Engineer::setSpeed(float speed) {
    _speed = speed;
    _throttle->setSpeedSetting(_speed);
    if (log->isDebugEnabled()) log->debug("_speedType="+_speedType+", Speed set to "+
                                          QString::number( _speed)+" _waitForClear= "+(_waitForClear?"true":"false")+" warrant "+_warrant->getDisplayName());
}
/*protected*/ float Engineer::getSpeedSetting() {
    return _throttle->getSpeedSetting();
}

/*protected*/ float Engineer::getScriptSpeed() {
    return _normalSpeed;
}

/**
 * Utility for unscripted speed changes.
 * Records current type and sets time ratio.
 * @param speedType name of speed change type
 * @return true to continue, false to skip setting a speed
 */
/*private*/ bool Engineer::setSpeedRatio(QString speedType) {
    float newSpeed = _speedUtil->modifySpeed(_normalSpeed, speedType);
    if (log->isTraceEnabled()) {
        float scriptSpeed = _speedUtil->modifySpeed(_normalSpeed, _speedType);
        log->debug(tr("setSpeedRatio: \"%1\" speed setting= %2, calculated current speed = %3,  newSpeed= %4. - %5").arg(
                speedType).arg(getSpeedSetting()).arg(scriptSpeed).arg(newSpeed).arg(_warrant->getDisplayName()));
    }

    if (speedType != (Warrant::Stop) && speedType != (Warrant::EStop)) {
        _speedType = speedType;     // set type regardless of return
        /*synchronized (this)*/ {
            float speedMod = _speedUtil->modifySpeed(1.0f, _speedType);
            if (qAbs(1.0f - speedMod) > .0001f) {
                _timeRatio = 1.0f / speedMod;
            } else {
                _timeRatio = 1.0f;
            }
        }
    }
    if (qAbs(getSpeedSetting() - newSpeed) < .002) {
     setHalt(false);
        return false;
    }
    return true;
}

/*
 * Do immediate speed change.
 */
/*protected*/ void Engineer::setSpeedToType(QString speedType) {
    cancelRamp(false);
    if (speedType == (Warrant::EStop)) {
        setSpeed(-0.1f);        // always do immediate EStop
        _waitForClear = true;
        advanceToCommandIndex(_idxCurrentCommand + 1);  // skip current command
    } else if (speedType == (Warrant::Stop)) {
        setSpeed(0.0f);
        _waitForClear = true;
        advanceToCommandIndex(_idxCurrentCommand + 1);  // skip current command
    } else {
        if (setSpeedRatio(speedType)) {
            setSpeed(_speedUtil->modifySpeed(_normalSpeed, speedType));
        }
    }
    if (log->isDebugEnabled())
        log->debug(tr("setSpeedToType(%1) scriptSpeed= %2").arg(speedType).arg(_normalSpeed));
}

/**
* Flag from user's control
*/
/*synchronized*/ /*public*/ void Engineer::setHalt(bool halt)
{
 if (log->isDebugEnabled())
     log->debug(tr("setHalt(%1): _atHalt= %2, _waitForClear= %3, _waitForSync= %4, warrant %5").arg(
         halt).arg(_atHalt).arg(_waitForClear).arg(_waitForSync).arg(_warrant->getDisplayName()));
 if (!halt) {    // resume normal running
     _halt = false;
     if (_atHalt) {
         if (log->isDebugEnabled())
             log->debug("setHalt calls notify()");
         //notifyAll();   // free wait at _atHalt
         waitForClear.wakeAll();

     }
 } else {
     _halt = true;
 }
}

/*synchronized*/ /*protected*/ void Engineer::setWaitforClear(bool stop)
{
 if (log->isDebugEnabled())
     log->debug(tr("setWaitforClear(%1): _atClear= %2 throttle speed= %3, _halt= %4, _waitForSync= %5, warrant %6").arg(
         stop?"true":"false").arg(_atClear).arg( _throttle->getSpeedSetting()).arg(_halt?"true":"false").arg(_waitForSync?"true":"false").arg(_warrant->getDisplayName()));
 if (!stop) {    // resume normal running
     _waitForClear = false;
     if (_atClear)
     {
      if (log->isDebugEnabled())
          log->debug("setWaitforClear calls notify");
      //notifyAll();   // free wait at _atClear
      waitForClear.wakeAll();
     }
 } else {
     _waitForClear = true;
 }
}

QString Engineer::getFlags() {
    QString buf ="Engineer flags: _waitForClear= ";
    buf.append(_waitForClear);
    buf.append(", _atclear= "); buf.append(_atClear?"true":"false");
    buf.append(", _halt= "); buf.append(_halt?"true":"false");
    buf.append(", _atHalt= "); buf.append(_atHalt?"true":"false");
    buf.append(", _waitForSync= "); buf.append(_waitForSync?"true":"false");
    return buf/*.toString()*/;
}

ThrottleRamp* Engineer::getRamp() {
    return _ramp;
}
/**
 * Immediate stop command from Warrant.controlRunTrain()-user
 * or from Warrant.goingInactive()-train lost
 * or from setMovement()-overrun, possible collision risk.
 * Do not ramp.
 * @param eStop true for emergency stop
 * @param setHalt for user restart needed, otherwise some kind of clear
 */
/*synchronized*/ /*public*/ void Engineer::setStop(bool eStop, bool setHalt) {
    cancelRamp(false);
    if (setHalt) {
        _halt = true;
    } else {
        _waitForClear = true;
    }
    if (eStop) {
        setSpeed(-0.1f);
    } else {
        setSpeed(0.0f);
    }
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

/*public*/ void Engineer::stopRun(bool abort, bool turnOffFunctions) {
    if (abort) {
        _abort =true;
    }
    if (_waitSensor != nullptr) {
        _waitSensor->removePropertyChangeListener((PropertyChangeListener*)this);
    }
    cancelRamp(true);

    if (_throttle != nullptr) {
        if (_throttle->getSpeedSetting() > 0.0f) {
            _throttle->setSpeedSetting(-1.0f);
            setSpeed(0.0f);     // prevent creep after EStop - according to Jim Betz
        }
        if (abort && turnOffFunctions) {
            _throttle->setF0(false);
            _throttle->setF1(false);
            _throttle->setF2(false);
            _throttle->setF3(false);
        }
        _warrant->releaseThrottle(_throttle);
    }
}

/**
 * Wait for Sensor state event
 */
/*private*/ void Engineer::getSensor(QString sensorName, QString act) {
    QString action = act.toUpper();
    if (_waitSensor != nullptr) {
        _waitSensor->removePropertyChangeListener((PropertyChangeListener*)this);
    }
    _waitSensor = InstanceManager::sensorManagerInstance()->getSensor(sensorName);
    if (_waitSensor != nullptr) {
        if ("ACTIVE" == (action)) {
            _sensorWaitState = Sensor::ACTIVE;
        } else if ("INACTIVE" == (action)) {
            _sensorWaitState = Sensor::INACTIVE;
        } else {
            log->error("Bad Sensor command \"" + action + "\"+ for sensor " + sensorName);
            return;
        }
        int state = _waitSensor->getKnownState();
        if (state == _sensorWaitState) {
            log->info("Engineer: state of event sensor " + sensorName + " already at state " + action);
            return;
        }
        _waitSensor->addPropertyChangeListener((PropertyChangeListener*)this);
        if (log->isDebugEnabled())
            log->debug(tr("Listen for propertyChange of %1, wait for State= %2").arg(_waitSensor->getDisplayName()).arg(_sensorWaitState));
        // suspend commands until sensor changes state
        /*synchronized (this)*/ {
         mutex.lock();
            _waitForSensor = true;
            while (_waitForSensor) {
                try {
                    _warrant->fireRunStatus("SensorWaitCommand", act, _waitSensor->getDisplayName());
                    //wait();
                    waitForClear.notify_all();
                    QString name =  _waitSensor->getDisplayName();    // save name, _waitSensor will be null 'eventually'
                    _warrant->fireRunStatus("SensorWaitCommand", "", name);
                } catch (InterruptedException* ie) {
                    log->error("Engineer interrupted at _waitForSensor " + ie->getMessage());
                    _warrant->debugInfo();
                    //Thread.currentThread().interrupt();
                    thread()->quit();
                }
//                    finally {
                    clearSensor();
//                }
            }
            mutex.unlock();
        }
    } else {
        log->warn("Sensor " + sensorName + " not found.");
    }
}

/*private*/ void Engineer::clearSensor() {
    if (_waitSensor != nullptr) {
        _waitSensor->removePropertyChangeListener((PropertyChangeListener*)this);
    }
    _sensorWaitState = 0;
    _waitForSensor = false;
    _waitSensor = nullptr;
}

/*protected*/ Sensor* Engineer::getWaitSensor() {
    return _waitSensor;
}

//@Override
//@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "NN_NAKED_NOTIFY", justification="Notify passing event, not state")
/*public*/ void Engineer::propertyChange(PropertyChangeEvent* evt) {
    if (log->isDebugEnabled())
        log->debug(tr("propertyChange %1 new value= %2").arg(evt->getPropertyName()).arg(evt->getNewValue().toString()));
    if ((evt->getPropertyName()==("KnownState")
            && ( evt->getNewValue()).toInt() == _sensorWaitState)) {
        /*synchronized (this)*/ {
//                if (!_halt && !_waitForClear) {
                //this->notifyAll();  // free sensor wait
      waitForClear.wakeAll();
//                }
        }
    }
}

/*private*/ void Engineer::runWarrant(ThrottleSetting* ts) {
    NamedBean* bean = ts->getNamedBeanHandle()->getBean();
    if (!(static_cast<Warrant*>(bean->self()))) {
        log->error(tr("runWarrant: %1 not a warrant!").arg(bean->getDisplayName()));
        return;
    }
    Warrant* warrant =  (Warrant*)bean->self();
    QString msg = "";
    int num = 0;
    bool bok;
        num = ts->getValue().toInt(&bok);
    if(!bok) {
        msg = tr("%1 is not a valid number for this parameter.").arg(ts->getValue());
    }
    if (num > 0) {
        num--;
    }
    ts->setValue(QString::number(num));
    QColor color = QColor(Qt::red);

    if (msg == nullptr) {
        if (_warrant->getSpeedUtil()->getDccAddress()==(warrant->getSpeedUtil()->getDccAddress())) {
            cmdBlockIdx = 0;    // reset block command number

//            Thread checker = new CheckForTermination(_warrant, warrant, num);
//            checker.start();
            CheckForTermination* checker = new CheckForTermination(_warrant, warrant, num, this);
            QThread* thread = new QThread();
            checker->moveToThread(thread);
            connect(thread, SIGNAL(started()), checker, SLOT(process()));
            connect(checker, SIGNAL(finished()), thread, SLOT(quit()));
            connect(checker, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->start();

            if (log->isDebugEnabled()) log->debug("Exit runWarrant");
            return;
        } else {
            msg = WarrantTableFrame::getDefault()->runTrain(warrant, Warrant::MODE_RUN);
            if (msg != "") {
                msg = tr("CannoCannot run warrant \"%1\". %2tRun").arg(warrant->getDisplayName()).arg(msg);
            } else {
                msg = tr("Launching warrant \"%1\" at block %3 from warrant \"%2\" at block %4.").arg(
                        warrant->getDisplayName()).arg(_warrant->getDisplayName()).arg(
                        warrant->getfirstOrder()->getBlock()->getDisplayName()).arg(
                        _warrant->getfirstOrder()->getBlock()->getDisplayName());
                color = WarrantTableModel::myGreen;
           }
        }
    } else {
        msg = tr("CannoCannot run warrant \"%1\". %2tRun").arg(warrant->getDisplayName()).arg(msg);
    }
    /*final*/ QString m = msg;
    QColor c = color;
//    ThreadingUtil.runOnLayout(()->{
        WarrantTableFrame::getDefault()->setStatusText(m, c, true);
//    });
    if (log->isDebugEnabled()) log->debug("Exit runWarrant - " + msg);
}

//static private class CheckForTermination extends Thread {

//    Warrant oldWarrant;
//    Warrant newWarrant;
//    int num;

    CheckForTermination::CheckForTermination(Warrant* oldWar, Warrant* newWar, int n, Engineer* engineer) {
     oldWarrant = oldWar;
     newWarrant = newWar;
     num = n;
     this->engineer = engineer;
     if (engineer->log->isDebugEnabled()) engineer->log->debug(tr("checkForTermination(%1, %2, %3)").arg(
             oldWarrant->getDisplayName()).arg(newWarrant->getDisplayName()).arg(num));
  }

    //@Override
    //@SuppressFBWarnings(value = "UW_UNCOND_WAIT", justification="false postive, guarded by while statement")
    /*public*/ void CheckForTermination::process() {
        OBlock* endBlock = oldWarrant->getLastOrder()->getBlock();
        long time = 0;
        QString msg = "";
        try {
            while (time < 10000) {
                if (oldWarrant->getRunMode() == Warrant::MODE_NONE) {
                    break;
                }
                /*synchronized (this)*/ {
                    //wait(200);
                 SleeperThread::msleep(200);
                    time += 200;
                }
            }
            if (time >= 10000) {
                msg = tr("Cannot launch \"%1\". \"%2\" has not released its allocation of \"%3\".").arg(
                        newWarrant->getDisplayName()).arg(oldWarrant->getDisplayName()).arg(endBlock->getDisplayName());
            }
        } catch (InterruptedException ie) {
            engineer->log->warn(tr("Warrant \"%1\" InterruptedException message= \"%2\" time= %3").arg(
                    oldWarrant->getDisplayName()).arg(ie.toString()).arg(time));
            //Thread.currentThread().interrupt();
            thread()->quit();
        }
        if (engineer->log->isDebugEnabled()) engineer->log->debug(tr("CheckForTermination waited %1ms. runMode=%2 ").arg(time).arg(oldWarrant->getRunMode()));

        QColor color = QColor(Qt::red);
        msg = newWarrant->setRoute(false, nullptr);
        if (msg == "") {
            msg = newWarrant->setRunMode(Warrant::MODE_RUN, nullptr, nullptr, nullptr, false);
        }
        if (msg != "") {
            msg = tr("Cannot run warrant \"%1\". %2").arg(newWarrant->getDisplayName()).arg(msg);
        } else {
            if (oldWarrant->equals(newWarrant)) {
                msg = tr("Warrant \"%1\" launched. %2 launches remaining.").arg(oldWarrant->getDisplayName()).arg((num<0 ? "unlimited" : QString::number(num)));
            } else {
                msg = tr("Launching warrant \"%1\" at block %4 from warrant \"%2\" at block %3.").arg(
                        newWarrant->getDisplayName()).arg(oldWarrant->getDisplayName()).arg(
                        newWarrant->getfirstOrder()->getBlock()->getDisplayName()).arg(
                        endBlock->getDisplayName());
            }
            color = WarrantTableModel::myGreen;
        }
        QString m = msg;
        QColor c = color;
//        ThreadingUtil.runOnLayoutEventually(() -> { // delay until current warrant can complete
            //WarrantTableFrame::getDefault()->setStatusText(m, c, true);
        if(!QMetaObject::invokeMethod(WarrantTableFrame::getDefault(), "setStatusTest", Qt::AutoConnection, Q_ARG(QString, m), Q_ARG(QColor, c), Q_ARG(bool, true)))
         throw new InvocationTargetException();
//        });
        emit finished();
    }
//}


//class ThrottleRamp implements Runnable {
//    String endSpeedType;

    ThrottleRamp::ThrottleRamp(Engineer *_engineer) {
     setObjectName("Ramp(" + _engineer->_warrant->getTrainName() +")");
     this->_engineer = _engineer;
    }

    void ThrottleRamp::quit(bool die)
    {
      _engineer->log->debug(tr("ThrottleRamp.quit die=%1)").arg(die));
      stop = true;
      if (die) { // once set to true, do not allow resetting to false
          _die = die;
      }
      /*synchronized (_ramp)*/ {
          _engineer->log->debug("ThrottleRamp.quit calls notify)");
          //_engineer->_ramp->notifyAll(); // free waits at ramp time interval
          _engineer->_ramp->waitRampSpeedTo.wakeAll();
      }
    }

    void ThrottleRamp::setParameters(QString endSpeedType, int endBlockIdx, bool useIndex) {
        _endSpeedType = endSpeedType;
        _endBlockIdx = endBlockIdx;
        _useIndex = useIndex;
        /*private*/ bool _stopPending = false;   // ramp slow down in progress
        _engineer->_stopPending = endSpeedType ==(Warrant::Stop);
    }

    RampData* ThrottleRamp::getRampData () {
        return _rampData;
    }

    //@Override
    //@SuppressFBWarnings(value="UW_UNCOND_WAIT", justification="waits may be indefinite until satisfied or thread aborted")
    /*public*/ void ThrottleRamp::process()
    {
     ready = true;
     while (!_die) {
      mutex.lock();
         /*synchronized (this)*/ {
             try {
                 //wait(); // wait until notified by rampSpeedTo() calls quit()
        waitRampSpeedTo.wait(&mutex);
             } catch (InterruptedException ie) {
                 _engineer->log->debug(tr("As expected %1").arg(ie.toString()));
             }
         }
         doRamp();
         mutex.unlock();
     }
    }
    /*public*/ void ThrottleRamp::doRamp() {
                // the time 'right now' is at having done _idxCurrentCommand-1 and is waiting
                // to do the _idxCurrentCommand.  A non-scripted speed change is to begin now.
                // current speed at _idxCurrentCommand is (should be) _normalSpeed modified by _speedType
                // Note on ramp down the _normalSpeed value may be modified.
                // "idxSkipToSpeedCommand" may be used rather than "_idxCurrentCommand".
                // Note on ramp up endSpeed should match scripted speed modified by endSpeedType
                ready = false;
                stop = false;
                float endSpeed = _engineer->_speedUtil->modifySpeed(_engineer->_normalSpeed, _endSpeedType);   // requested end speed
                float speed = _engineer->_throttle->getSpeedSetting();  // current speed setting
                if (speed < 0.0f) {
                    speed = 0.0f;
                }
                _rampData = _engineer->_speedUtil->getRampForSpeedChange(speed, endSpeed);
                int timeIncrement = _rampData->getRampTimeIncrement();

                /*synchronized (this)*/ {
//                    try {
                  _lock.lock();
                         if (_engineer->log->isDebugEnabled())
                             _engineer->log->debug(tr("ThrottleRamp for \"%1\". Ramp %2 to %3. normalSpeed= %4. on warrant %5").arg(
                                _endSpeedType).arg(speed).arg(endSpeed).arg(_engineer->_normalSpeed).arg(_engineer->_warrant->getDisplayName()));
                         // _normalSpeed typically is the last setThrottleSetting done. However it also
                         // may be reset after a down ramp to be the setting expected to be resumed at the
                         // point skipped to by the down ramp.

                        if (_rampData->isUpRamp()) {
                            _engineer->_resumePending = true;
                            // The ramp up will take time and the script may have other speed commands while
                            // ramping up. So 'scriptSpeed' may not be actual script speed when ramp up distance
                            // is traveled.  Adjust 'endSpeed' to match that 'scriptSpeed'.
                            // Up rampDist is distance from current throttle speed to endSpeed.
                            float rampDist = _rampData->getRampLength();
                            long scriptTime = 0;
                            float scriptDist = 0;   // distance traveled at speed 'scriptSpeed' to next speed command
                            float scriptSpeed = _engineer->_normalSpeed;
                            bool hasSpeed = (scriptSpeed > 0);
                            int idx = qMax(_engineer->_idxSkipToSpeedCommand, _engineer->_idxCurrentCommand);
                            // look ahead for point in script where ramp will finish and match the settings
                            while (idx < _engineer->_commands->size()) {
                                ThrottleSetting* ts = _engineer->_commands->value(idx);
                                scriptTime = ts->getTime();
                                QString cmd = ts->getCommand().toUpper();
                                if (hasSpeed) {
                                    scriptDist += _engineer->_speedUtil->getDistanceTraveled(scriptSpeed, _endSpeedType, scriptTime);
                                    if (scriptDist >= rampDist) {   // up ramp will be complete within this distance
                                        _engineer->advanceToCommandIndex(idx); // don't let script set speeds up to here
                                        break;
                                    }
                                }
                                if ("SPEED" == (cmd)) {
                                    scriptSpeed = ts->getValue().toFloat();
                                    hasSpeed = (scriptSpeed > 0);
                                    endSpeed = _engineer->_speedUtil->modifySpeed(scriptSpeed, _endSpeedType);
                                    _rampData = _engineer->_speedUtil->getRampForSpeedChange(speed, endSpeed);
                                    rampDist = _rampData->getRampLength();
                                    _engineer->advanceToCommandIndex(idx); // don't let script set speeds up to here
                                }
                                idx++;
                            }
                            _engineer->_normalSpeed = scriptSpeed;

                            if (_engineer->log->isDebugEnabled())
                                _engineer->log->debug(tr("Ramp up for \"%1\". speedType= %2, endSpeed= %3, scriptDist= %4, resumeIndex= %5, nextSpeedIdx= %6, rampDist= %7").arg(
                                        _endSpeedType).arg(speed).arg(endSpeed).arg(scriptSpeed).arg(_engineer->_idxSkipToSpeedCommand+1).arg(_engineer->_idxCurrentCommand+1).arg(rampDist));
                                    // Note: command indexes biased from 0 to 1 to match Warrant display of commands.

                            QListIterator<float> iter = _rampData->speedIterator(true);
                            if (iter.hasNext()) {
                                speed = iter.next();   // current setting
                            }
                            while (iter.hasNext()) { // do ramp up
                                if (stop) {
                                    break;
                                }
                                speed = iter.next();
                                _engineer->setSpeed(speed);

                                try {
                                    //wait(timeIncrement);
                                 SleeperThread::msleep(timeIncrement);
                                } catch (InterruptedException ie) {
                                    _lock.unlock();
                                    stop = true;
                                }
                            }
                        } else {     // decreasing, ramp down to a modified speed
                            if (_engineer->log->isDebugEnabled())
                                _engineer->log->debug(tr("Ramp down for \"%1\". curSpeed= %2, endSpeed= %3, startIdx=%4 BlockOrderIdx= %5").arg(
                                        _endSpeedType).arg(speed).arg(endSpeed).arg(_engineer->_idxCurrentCommand+1).arg(_endBlockIdx));
                            // Note: command indexes biased from 0 to 1 to match Warrant display of commands.
                            QListIterator<float> iter = _rampData->speedIterator(false);
                            if (iter.hasPrevious()) {
                                speed = iter.previous();   // current setting
                            }
                            while (iter.hasPrevious()) {
                                if (stop) {
                                    break;
                                }
                                speed = iter.previous();
                                if (_useIndex) {
                                    if (_engineer->_warrant->_idxCurrentOrder > _endBlockIdx) { // loco overran end block
                                        speed = endSpeed;
                                    } else if ( _engineer->_warrant->_idxCurrentOrder < _endBlockIdx &&
                                            _endSpeedType == (Warrant::Stop) && qAbs(speed - endSpeed) <.001f) {
                                        // at last speed change. let loco creep to end block
                                        if (_engineer->log->isDebugEnabled())
                                            _engineer->log->debug(tr("Extending ramp to reach block %1. speed= %2").arg(
                                                    _engineer->_warrant->getBlockAt(_endBlockIdx)->getDisplayName()).arg(speed));
                                        while (_endBlockIdx - _engineer->_warrant->_idxCurrentOrder > 0) {
                                            // Until loco reaches end block, continue current speed
                                            try {
                                                //wait(timeIncrement);
                                            } catch (InterruptedException ie) {
                                                _lock.unlock();
                                                stop = true;
                                            }
                                        }
                                    }
                                }
                                _engineer->setSpeed(speed);

                                try {
                                    //wait(timeIncrement);
                                 SleeperThread::msleep(timeIncrement);
                                } catch (InterruptedException ie) {
                                    _lock.unlock();
                                    stop = true;
                                }
                            }
                            _engineer->_stopPending = false;

                            // Down ramp may advance the train beyond the point where the script is paused.
                            // Any down ramp requested with _useIndex==true is expected to end at the end of
                            // a block i.e. the block of BlockOrder indexed by _endBlockIdx.
                            // Therefore script should resume at the exit to this block.
                            // advanceToCommandIndex() sets the resume point of script.
                            if (_useIndex) {
                                int idx = _engineer->_idxCurrentCommand;
                                while (idx < _engineer->_commands->size()) {
                                    ThrottleSetting* ts = _engineer->_commands->value(idx);
                                    NamedBean* bean = ts->getNamedBeanHandle()->getBean();
                                    if (static_cast<OBlock*>(bean->self())) {
                                        OBlock* blk = (OBlock*)bean->self();
                                        if (_endBlockIdx < _engineer->_warrant->getIndexOfBlock(blk, _endBlockIdx)) {
                                            // script is past end point, command should be NOOP
                                            break;
                                        }
                                    }
                                    if (ts->getCommand().toUpper()==("SPEED")) {
                                        _engineer->_normalSpeed =ts->getValue().toFloat(); // modify 'resume' speed to be last speed
                                    }
                                    idx++;
                                }
                                _engineer->advanceToCommandIndex(idx); // skip up to this command

                                if (_engineer->log->isDebugEnabled())
                                    _engineer->log->debug(tr("endBlkName= %1, cmdBlkName= %2, _idxCurrentCommand=%3, skipToBlkName= %4, skipToIdx= %5, _normalSpeed= %6").arg(
                                            _engineer->_warrant->getBlockAt(_endBlockIdx)->getDisplayName()).arg(
                                            _engineer->_commands->value(_engineer->_idxCurrentCommand)->getNamedBeanHandle()->getBean()->getDisplayName()).arg(_engineer->_idxCurrentCommand+1).arg(
                                            _engineer->_commands->value(idx)->getNamedBeanHandle()->getBean()->getDisplayName()).arg(idx+1).arg(
                                            _engineer->_normalSpeed)); // Note: command indexes biased from 0 to 1 to match Warrant display of commands.
                           }
                        }

//                    }
                 /*finally*/ {
                        _lock.unlock();
                        if (_endSpeedType != (Warrant::Stop) &&
                                _endSpeedType !=(Warrant::EStop)) {
                            // speed restored, clear any stop waits
                            // If flags already off, OK to repeat setting false
                            _engineer->setWaitforClear(false);
                            _engineer->setHalt(false);
                        }
                        _engineer->_resumePending = false;
                    }
                }
                _engineer->rampDone(stop, _endSpeedType);
                ready = true;
                stop = false;
            }
//}


#if 0
/*private*/ float Engineer::getThrottleFactor(float speedStep)
{
 if (_speedProfile != NULL)
 {
     return _speedProfile->getSpeed(speedStep, _throttle->getIsForward())/(speedStep*1000);
 }
 return _speedMap->getDefaultThrottleFactor();
}
///*protected*/ QString Engineer::minSpeedType(QString speed1, QString speed2)
//{
// if (secondGreaterThanFirst(speed1, speed2)) {
//     return speed1;
// }
// return speed2;
//}
/**
 * If waiting to sync entrance to a block boundary with recorded wait time,
 * or waiting for clearance ahead for rogue occupancy, stop aspect or sharing
 *  of turnouts, this call will free the wait.
 */
/*synchronized*/ /*protected*/ void Engineer::checkHalt() {
    if (_waitForSync &&!_halt && !_waitForSensor && !_waitForClear) {
        if (_debug) log->debug("checkHalt calls notify()");
        //this->notify();
        waitForSync.notify_all();
    }
    if (_debug) log->debug(QString("checkHalt _waitForSync= ")+(_waitForSync?"true":"false"));
}
#endif
/*private*/ void Engineer::setFunction(int cmdNum, bool isSet) {
    switch (cmdNum) {
        case 0:
            _throttle->setF0(isSet);
            break;
        case 1:
            _throttle->setF1(isSet);
            break;
        case 2:
            _throttle->setF2(isSet);
            break;
        case 3:
            _throttle->setF3(isSet);
            break;
        case 4:
            _throttle->setF4(isSet);
            break;
        case 5:
            _throttle->setF5(isSet);
            break;
        case 6:
            _throttle->setF6(isSet);
            break;
        case 7:
            _throttle->setF7(isSet);
            break;
        case 8:
            _throttle->setF8(isSet);
            break;
        case 9:
            _throttle->setF9(isSet);
            break;
       case 10:
            _throttle->setF10(isSet);
            break;
        case 11:
            _throttle->setF11(isSet);
            break;
        case 12:
            _throttle->setF12(isSet);
            break;
        case 13:
            _throttle->setF13(isSet);
            break;
        case 14:
            _throttle->setF14(isSet);
            break;
        case 15:
            _throttle->setF15(isSet);
            break;
        case 16:
            _throttle->setF16(isSet);
            break;
        case 17:
            _throttle->setF17(isSet);
            break;
        case 18:
            _throttle->setF18(isSet);
            break;
        case 19:
            _throttle->setF19(isSet);
            break;
        case 20:
            _throttle->setF20(isSet);
            break;
        case 21:
            _throttle->setF21(isSet);
            break;
        case 22:
            _throttle->setF22(isSet);
            break;
        case 23:
            _throttle->setF23(isSet);
            break;
        case 24:
            _throttle->setF24(isSet);
            break;
        case 25:
            _throttle->setF25(isSet);
            break;
        case 26:
            _throttle->setF26(isSet);
            break;
        case 27:
            _throttle->setF27(isSet);
            break;
        case 28:
            _throttle->setF28(isSet);
            break;
        default:
            log->error("Function value " + QString::number(cmdNum )+ " out of range");
            throw new IllegalArgumentException("Function Value " + QString::number(cmdNum) + " out of range");
    }
}

/*private*/ void Engineer::setLockFunction(int cmdNum, bool isTrue) {
    switch (cmdNum) {
        case 0:
            _throttle->setF0Momentary(!isTrue);
            break;
        case 1:
            _throttle->setF1Momentary(!isTrue);
            break;
        case 2:
            _throttle->setF2Momentary(!isTrue);
            break;
        case 3:
            _throttle->setF3Momentary(!isTrue);
            break;
        case 4:
            _throttle->setF4Momentary(!isTrue);
            break;
        case 5:
            _throttle->setF5Momentary(!isTrue);
            break;
        case 6:
            _throttle->setF6Momentary(!isTrue);
            break;
        case 7:
            _throttle->setF7Momentary(!isTrue);
            break;
        case 8:
            _throttle->setF8Momentary(!isTrue);
            break;
        case 9:
            _throttle->setF9Momentary(!isTrue);
            break;
        case 10:
            _throttle->setF10Momentary(!isTrue);
            break;
        case 11:
            _throttle->setF11Momentary(!isTrue);
            break;
        case 12:
            _throttle->setF12Momentary(!isTrue);
            break;
        case 13:
            _throttle->setF13Momentary(!isTrue);
            break;
        case 14:
            _throttle->setF14Momentary(!isTrue);
            break;
        case 15:
            _throttle->setF15Momentary(!isTrue);
            break;
        case 16:
            _throttle->setF16Momentary(!isTrue);
            break;
        case 17:
            _throttle->setF17Momentary(!isTrue);
            break;
        case 18:
            _throttle->setF18Momentary(!isTrue);
            break;
        case 19:
            _throttle->setF19Momentary(!isTrue);
            break;
        case 20:
            _throttle->setF20Momentary(!isTrue);
            break;
        case 21:
            _throttle->setF21Momentary(!isTrue);
            break;
        case 22:
            _throttle->setF22Momentary(!isTrue);
            break;
        case 23:
            _throttle->setF23Momentary(!isTrue);
            break;
        case 24:
            _throttle->setF24Momentary(!isTrue);
            break;
        case 25:
            _throttle->setF25Momentary(!isTrue);
            break;
        case 26:
            _throttle->setF26Momentary(!isTrue);
            break;
        case 27:
            _throttle->setF27Momentary(!isTrue);
            break;
        case 28:
            _throttle->setF28Momentary(!isTrue);
            break;
        default:
            log->error("Function value " + QString::number(cmdNum) + " out of range");
            throw new IllegalArgumentException("Function Value " + QString::number(cmdNum) + " out of range");
    }
}

/**
 * Set Sensor state
 */
/*private*/ void Engineer::setSensor(QString sensorName, QString act) {
    QString action = act.toUpper();
    Sensor* s = InstanceManager::sensorManagerInstance()->getSensor(sensorName);
    if (s != nullptr) {
        try {
            if ("ACTIVE" ==(action)) {
                s->setKnownState(Sensor::ACTIVE);
            } else if ("INACTIVE"==(action)) {
                s->setKnownState(Sensor::INACTIVE);
            }
            _warrant->fireRunStatus("SensorSetCommand", act, s->getDisplayName());
        } catch (JmriException* e) {
            log->warn("Exception setting sensor " + sensorName + " in action");
        }
    } else {
        log->warn("Sensor " + sensorName + " not found.");
    }
}


/*private*/ /*final*/ /*static*/ Logger* Engineer::log = LoggerFactory::getLogger("Engineer");



