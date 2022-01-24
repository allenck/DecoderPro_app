#ifndef TIMEOUTRFIDREPORTER_H
#define TIMEOUTRFIDREPORTER_H
#include "rfidreporter.h"
#include <QThread>


class RfidReporterTimeoutThread;
class TimeoutRfidReporter : public RfidReporter
{
public:
 TimeoutRfidReporter(QString systemName, QObject* parent = nullptr);
 /*public*/ TimeoutRfidReporter(QString systemName, QString userName, QObject* parent = nullptr);
 /*public*/ void notify(IdTag *t);

private:
 static Logger* log;
 /**
  * Timeout in ms
  */
 /*private*/ static /*final*/ int TIMEOUT;// = 2000;

 /**
  * Time when something was last reported by this object
  */
 /*private*/ long whenLastReported = 0;

 /**
  * Reference to the timeout thread for this object
  */
 /*private*/ /*transient*/ RfidReporterTimeoutThread* timeoutThread = nullptr;

 /*private*/ /*final*/ bool logDebug;// = log.isDebugEnabled();
 /*private*/ void cleanUpTimeout();
friend class RfidReporterTimeoutThread;
};
/*private*/ class RfidReporterTimeoutThread : public  QThread {
Q_OBJECT
 TimeoutRfidReporter* parent;
public:
    RfidReporterTimeoutThread(TimeoutRfidReporter* parent = nullptr) : QThread(){
        //super();
     this->parent = parent;
        this->setObjectName("Timeout-" + parent->getSystemName());
    }

    //@Override
    //@SuppressWarnings("SleepWhileInLoop")
    /*public*/ void run() {
        while ((parent->whenLastReported + TimeoutRfidReporter::TIMEOUT) > QDateTime::currentMSecsSinceEpoch()) {
            try {
                QThread::msleep(100);
            } catch (InterruptedException ex) {
            }
        }
        parent->TimeoutRfidReporter::notify(nullptr);
        if (parent->logDebug) {
            parent->log->debug("Timeout-" + parent->getSystemName());
        }
        parent->cleanUpTimeout();
    }
};

#endif // TIMEOUTRFIDREPORTER_H
