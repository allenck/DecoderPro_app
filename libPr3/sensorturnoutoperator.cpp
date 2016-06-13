#include "sensorturnoutoperator.h"
#include "abstractturnout.h"
#include <QDateTime>

//SensorTurnoutOperator::SensorTurnoutOperator(QObject *parent) :
//    TurnoutOperator(parent)
//{
//}
///*public*/ class SensorTurnoutOperator extends TurnoutOperator {

/*public*/ SensorTurnoutOperator::SensorTurnoutOperator(AbstractTurnout* t, long i, int mt, QObject *parent) : TurnoutOperator(t,parent)
{
    log = new Logger("SensorTurnoutOperator");
    //super(t);
    interval = i;
    maxTries = mt;
    tries = 0;
}

/**
 * Do the autmation for a turnout with sensor feedback.
 * Keep trying up to maxTries until the sensor tells
 * us the change has actually happened. Note the call to
 * operatorCheck each time we're about to actually do something -
 * if we're no longer the current operator this throws
 * TurnoutOperatorException which just terminates the thread.
 */
/*public*/ void SensorTurnoutOperator::run() {
    //long startTime = System.currentTimeMillis();
//    listener = new PropertyChangeListener() {
//        //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="NN_NAKED_NOTIFY",
//                    justification="notify not naked, outside sensor and turnout is shared state")
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            if (e.getPropertyName().equals("KnownState")) {
//                synchronized(this) {
//                    this.notify();
//                }
//            }
//        }
//    };
    listener = new MyPropertyChangeListener(this);
    myTurnout->addPropertyChangeListener(listener);
    connect(myTurnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
    try {
        operatorCheck();
        myTurnout->forwardCommandChangeToLayout();
        while (++tries < maxTries) {
            qint64 nextTry = QDateTime::currentMSecsSinceEpoch() + interval;
            long remaining;
            while ((remaining = nextTry - QDateTime::currentMSecsSinceEpoch()) > 0) {
                try {
                    /*synchronized(this)*/ {
                        QMutexLocker locker(&mutex);
                        //wait(remaining);
                        msleep(remaining);
                    }
                } catch (InterruptedException e) {
                    QThread::currentThread()->exit(); // retain if needed later
                }
            }
            if (myTurnout->isConsistentState()) {
                break;
            }
            operatorCheck();
            myTurnout->forwardCommandChangeToLayout();
            log->warn("retrying "+myTurnout->getSystemName()+", try #"+QString::number(tries+1));
        }
        if (!myTurnout->isConsistentState()) {
            log->warn("failed to throw "+myTurnout->getSystemName());
        }
    } catch (TurnoutOperatorException e) { }
    myTurnout->removePropertyChangeListener(listener);
    disconnect(myTurnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));

}
