#ifndef TIMEOUTRFIDSENSOR_H
#define TIMEOUTRFIDSENSOR_H
#include "rfidsensor.h"

class DefaultIdTag;
class RfidSensorTimeoutThread;
class TimeoutRfidSensor : public RfidSensor
{
public:
 TimeoutRfidSensor(QString systemName, QString userName, QObject* parent = nullptr);
 TimeoutRfidSensor(QString systemName, QObject* parent = nullptr);
 /*public*/ void notify(DefaultIdTag *t);


private:
 /*private*/ static /*final*/ int TIMEOUT;// = 1000;
 static Logger* log;
 /**
  * Time when something was last sensed by this object
  */
 /*private*/ long whenLastSensed = 0;

 /**
  * Reference to the timeout thread for this object
  */
 /*private*/ /*transient*/ RfidSensorTimeoutThread* timeoutThread = nullptr;
 /*private*/ /*final*/ bool logDebug;// = log.isDebugEnabled();
 /*private*/ void cleanUpTimeout();

 friend class RfidSensorTimeoutThread;
};

/*private*/ class RfidSensorTimeoutThread : public QThread {
 Q_OBJECT
 TimeoutRfidSensor* parent;

    RfidSensorTimeoutThread(TimeoutRfidSensor* parent) {
        //super();
     this->parent = parent;
        this->setObjectName("Timeout-" + parent->mSystemName);
    }

    //@Override
    //@SuppressWarnings("SleepWhileInLoop")
    /*public*/ void run() {
        while ((parent->whenLastSensed + parent->TIMEOUT) > QDateTime::currentMSecsSinceEpoch()) {
            try {
                QThread::msleep(50);
            } catch (InterruptedException ex) {
            }
        }
        parent->RfidSensor::notify(nullptr);
        if (parent->logDebug) {
            parent->log->debug("Timeout-" + parent->mSystemName);
        }
        parent->cleanUpTimeout();
    }
 friend class TimeoutRfidSensor;
};
#endif // TIMEOUTRFIDSENSOR_H
