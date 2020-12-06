#include "meterupdatetask.h"
#include <QMap>
#include "exceptions.h"
#include "timerutil.h"
#include "loggerfactory.h"
/**
 * Handles updates of meters. Several meters may share the update task.
 *
 * @author Mark Underwood    (C) 2015
 * @author Daniel Bergqvist  (C) 2020
 */
//public abstract class MeterUpdateTask {


    /*public*/ MeterUpdateTask::MeterUpdateTask(QObject *parent) : QObject(parent) {
       _sleepInterval = 10000;
    }

    /*public*/ MeterUpdateTask::MeterUpdateTask(int interval, QObject *parent) : QObject(parent) {
       _sleepInterval = interval;
    }

    /*public*/ void MeterUpdateTask::addMeter(Meter* m) {
        meters.insert(m, false);
    }

    /*public*/ void MeterUpdateTask::removeMeter(Meter* m) {
        meters.remove(m);
    }

    /*protected*/ void MeterUpdateTask::enable() {
        if(_intervalTask != nullptr) {
            _intervalTask->enable();
        }
    }

    /*public*/ void MeterUpdateTask::enable(Meter* m) {
        if (!meters.contains(m)) {
            throw  IllegalArgumentException("Meter is not registered");
        }

        if (!meters.value(m)) {
            meters.insert(m, true);
            if (!_enabled) {
                _enabled = true;
                enable();
            }
        }
    }

    /*protected*/ void MeterUpdateTask::disable() {
        if(_intervalTask != nullptr) {
            _intervalTask->disable();
        }
    }

    /*public*/ void MeterUpdateTask::disable(Meter* m) {
        if (!meters.contains(m)) return;

        if (meters.value(m)) {
            meters.insert(m, false);
            if (_enabled) {
                // Is there any more meters that are active?
                bool found = false;
                for (bool b : meters.values()) {
                    found |= b;
                }
                if (! found) {
                    _enabled = false;
                    disable();
                }
            }
        }
    }

    /*public*/ void MeterUpdateTask::initTimer() {
        if(_intervalTask != nullptr) {
           _intervalTask->cancel();
           _intervalTask = nullptr;
        }
        if(_sleepInterval < 0){
           return; // don't start or restart the timer.
        }
        _intervalTask = new UpdateTask02(this);
        // At some point this will be dynamic intervals...
        log->debug("Starting Meter Timer");
        TimerUtil::scheduleAtFixedRate(_intervalTask,
                _sleepInterval, _sleepInterval);
    }

    ///*public*/ abstract void requestUpdateFromLayout();

    /**
     * Remove references to and from this object, so that it can eventually be
     * garbage-collected.
     * @param m the meter that is calling dispose
     */
    /*public*/ void MeterUpdateTask::dispose(Meter* m){
        removeMeter(m);
        if (meters.isEmpty() && (_intervalTask != nullptr)) {
           _intervalTask->cancel();
           _intervalTask = nullptr;
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* MeterUpdateTask::log = LoggerFactory::getLogger("MeterUpdateTask");
