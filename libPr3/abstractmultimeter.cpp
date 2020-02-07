#include "abstractmultimeter.h"
#include "loggerfactory.h"
#include "multimeter.h"
#include "sleeperthread.h"
/**
 * Abstract base class for current meter objects.
 *
 * @author Mark Underwood (C) 2015
 */
//abstract /*public*/ class AbstractMultiMeter extends Bean implements MultiMeter {


    /*public*/ AbstractMultiMeter::AbstractMultiMeter(int interval,QObject *parent) : Bean(parent)
{
       sleepInterval = interval;
    }

    /*protected*/ void AbstractMultiMeter::initTimer() {
        if(intervalTask!=nullptr) {
           intervalTask->cancel();
           intervalTask = nullptr;
        }
        if(sleepInterval <0){
           return; // don't start or restart the timer.
        }
        intervalTask = new UpdateTask(this);
        // At some point this will be dynamic intervals...
        log->debug("Starting Meter Timer");
//        jmri.util.TimerUtil.scheduleAtFixedRate(intervalTask,
//                sleepInterval, sleepInterval);
        if(timer == nullptr)
        {
         timer = new QTimer();
         timer->setInterval(sleepInterval);
         connect(timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
        }
    }

    void AbstractMultiMeter::on_timeout()
    {
     intervalTask->run();
    }

    /**
     * Request an update from the layout.  Triggered by a timer.
     */
    // /*abstract*/ /*protected*/ void requestUpdateFromLayout();

    // Timer task for periodic updates...
//    /*private*/ class UpdateTask extends TimerTask {

//        private boolean is_enabled = false;

        /*public*/ UpdateTask::UpdateTask(AbstractMultiMeter *amm) : TimerTask() {
            //super();
 this->amm = amm;
        }

        /*public*/ void UpdateTask::enable() {
            is_enabled = true;
        }

        /*public*/ void UpdateTask::disable() {
            is_enabled = false;
        }

        //@Override
        /*public*/ void UpdateTask::run() {
            if (is_enabled) {
                log->debug("Timer Pop");
                amm->requestUpdateFromLayout();
            }
        }
//    }

    // MultiMeter Interface Methods
    //@Override
    /*public*/ void AbstractMultiMeter::enable() {
        log->debug("Enabling meter.");
        intervalTask->enable();
    }

    //@Override
    /*public*/ void AbstractMultiMeter::disable() {
        log->debug("Disabling meter.");
        intervalTask->disable();
    }

    //@Override
    /*public*/ void AbstractMultiMeter::setCurrent(float c) {
        float old = current_float;
        current_float = c;
        this->firePropertyChange(CURRENT, QVariant(old), QVariant(c));
    }

    //@Override
    /*public*/ float AbstractMultiMeter::getCurrent() {
        return current_float;
    }

    //@Override
    /*public*/ MultiMeter::CurrentUnits AbstractMultiMeter::getCurrentUnits() {
        return currentUnits;
    }

    //@Override
    /*public*/ void AbstractMultiMeter::setVoltage(float v) {
        float old = voltage_float;
        voltage_float = v;
        this->firePropertyChange(VOLTAGE, QVariant(old), QVariant(v));
    }

    //@Override
    /*public*/ float AbstractMultiMeter::getVoltage() {
        return voltage_float;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void AbstractMultiMeter::dispose(){
        if(intervalTask!=nullptr) {
           intervalTask->cancel();
           intervalTask = nullptr;
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* AbstractMultiMeter::log = LoggerFactory::getLogger("AbstractMultiMeter");
/*private*/ /*final*/ /*static*/ Logger* UpdateTask::log = LoggerFactory::getLogger("UpdateTask");
