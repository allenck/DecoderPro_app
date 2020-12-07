#ifndef LNMETERINITTASK_H
#define LNMETERINITTASK_H

#include <QObject>
#include "meterupdatetask.h"
#include "slotmanager.h"
#include <QVector>

class UpdateTask01;
class LocoNetSystemConnectionMemo;
class Logger;
class SlotManager;
class LnTrafficController;
class LnMeterInitTask : public QObject
{
  Q_OBJECT
 public:
  explicit LnMeterInitTask(LnTrafficController* tc, int interval, QObject *parent = nullptr);
  ~LnMeterInitTask() { dispose();}
  /*public*/ void initTimer();
  /*public*/ void dispose();

 signals:

 public slots:

 private:
  static Logger* log;
  bool _enabled = false;
  /*private*/ UpdateTask01* _intervalTask = nullptr;
  /*private*/ /*final*/ int _sleepInterval;
  /*private*/ /*final*/ LnTrafficController* tc = nullptr;

 protected:
  /*protected*/ void enable();
  /*protected*/ void disable();

  friend class UpdateTask01;
  friend class LnPredefinedMeters;
};

/**
 * Timer task for periodic updates
 *
 * Task to check status of the LocoNet connection, and, when it is
 * ready, send a LocoNet query message.
 */
/*private*/ class UpdateTask01 : public TimerTask {

    /*private*/ bool _updateTaskIsEnabled = false;
    LnMeterInitTask* task;
public:
    /*public*/ UpdateTask01(LnMeterInitTask* task) {
        //super();
        this->task = task;
        this->_updateTaskIsEnabled = false;
    }

    /**
     * Enable or disable the update task
     * @param val true to enable, false to disable
     */
    /*public*/ void enable(bool val) {
        if (!val) {
            cancel();
        }
        _updateTaskIsEnabled = val;
    }

    /**
     * get the enable/disable state of the update task
     * @return true if enabled, else false
     */
    /*public*/ bool isEnabled() {
        return _updateTaskIsEnabled;
    }

    //@Override
    /*public*/ void run() {
        if (!_updateTaskIsEnabled) {
         if(LnMeterInitTask::log->isDebugEnabled())
            LnMeterInitTask::log->debug("LnMeter initialization timer finds task not enabled.");
            return;
        } else if (!task->tc->status()) {
            if(LnMeterInitTask::log->isDebugEnabled())
             LnMeterInitTask::log->debug("LnMeter initialization timer finds connection not ready.");
            return;
        }
        LnMeterInitTask::log->debug("LnMeter initialization timer is sending query.");
        task->tc->sendLocoNetMessage(new LocoNetMessage(
                QVector<int>() <<LnConstants::OPC_RQ_SL_DATA<< 0x79<< 0x01<< 0x00));
        task->disable();

    }
  friend class LnPredefinedMeters;
};

#endif // LNMETERINITTASK_H
