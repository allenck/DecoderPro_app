#ifndef AUTOTRAINACTION_H
#define AUTOTRAINACTION_H

#include <QObject>
#include "propertychangelistener.h"
#include "runnable.h"
#include "sleeperthread.h"
#include "exceptions.h"
#include "transitsectionaction.h"
#include "autoactivetrain.h"

class AllocatedSection;
class Block;
class Logger;
class PropertyChangeListener;
class Sensor;
class TransitSectionAction;
class TransitSection;
class ActiveTrain;
class AutoActiveTrain;
class AutoTrainAction : public QObject
{
 Q_OBJECT
public:
 //explicit AutoTrainAction(QObject *parent = 0);
 /*public*/ AutoTrainAction(AutoActiveTrain* aat, QObject* parent = 0);
 /*public*/ /*synchronized*/ void executeAction(TransitSectionAction* tsa);
 /*public*/ void handleSensorChange(QString sName);


signals:

public slots:

private:
 Logger* log;
 // operational instance variables
 /*private*/ AutoActiveTrain* _autoActiveTrain;// = null;
 /*private*/ ActiveTrain* _activeTrain;// = null;
 /*private*/ QList<TransitSection*>* _activeTransitSectionList;// = new ArrayList<TransitSection>();
 /*private*/ QList<TransitSectionAction*>* _activeActionList;// = new ArrayList<TransitSectionAction>();
 /*private*/ /*synchronized*/ void completedAction(TransitSectionAction* tsa);
 /*private*/ /*synchronized*/ void checkDelay(TransitSectionAction* tsa);
 // this method is called to listen to a Done Sensor if one was provided
 // if Status is WORKING, and sensor goes Active, Status is set to READY
 /*private*/ Sensor* _doneSensor;// = NULL;
 /*private*/ PropertyChangeListener* _doneSensorListener;// = NULL;
 /*private*/ /*synchronized*/ void listenToDoneSensor(TransitSectionAction* tsa);
 /*private*/ bool waitOnSensor(TransitSectionAction* tsa);

protected:
 /*protected*/ /*synchronized*/ void removeTransitSection(TransitSection* ts);
 /*protected*/ /*synchronized*/ void addTransitSection(TransitSection* ts);
 /*protected*/ /*synchronized*/ void clearRemainingActions();
 /*protected*/ /*synchronized*/ void cancelDoneSensor();
 /*protected*/ /*synchronized*/ void handleBlockStateChange(AllocatedSection* as, Block* b);

 friend class AutoActiveTrain;
 friend class ATAPropertyChangeListener;
 friend class MonitorTrain;
 friend class HornExecution;
 friend class MonitorTrainSpeed;
};

class ATAPropertyChangeListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
  AutoTrainAction* ata;
  QString sensorName;

 public:
  ATAPropertyChangeListener(AutoTrainAction* ata, QString sensorName) {this->ata = ata; this->sensorName = sensorName;}
  QObject* pself() override {return (QObject*)this;}

public slots:
  void propertyChange(PropertyChangeEvent* e)override
  {
   if (e->getPropertyName() == ("KnownState")) {
       ata->handleSensorChange(sensorName);
   }
  }
};

class TSActionDelay : public  Runnable {

    /**
     * A runnable that implements delayed execution of a
     * TransitSectionAction
     */
    /*public*/ TSActionDelay(TransitSectionAction* tsa, int delay, AutoTrainAction* ata) {
        _tsa = tsa;
        _delay = delay;
        this->ata  = ata;
    }

    //@Override
    /*public*/ void run() {
        try {
            SleeperThread::msleep(_delay);
            ata->executeAction(_tsa);
        } catch (InterruptedException e) {
            // interrupting this thread will cause it to terminate without executing the action.
        }
    }
    /*private*/ TransitSectionAction* _tsa = NULL;
    /*private*/ int _delay = 0;
  AutoTrainAction* ata;
};

class HornExecution : public  Runnable {
Q_OBJECT

 public:
    /**
     * A runnable to implement horn execution
     */
    /*public*/ HornExecution(TransitSectionAction* tsa, AutoTrainAction* ata) {
        _tsa = tsa;
        this->ata = ata;
    }

    //@Override
    /*public*/ void run() override
    {
        ata->_autoActiveTrain->incrementHornExecution();
        if (_tsa->getWhatCode() == TransitSectionAction::SOUNDHORN) {
            if (ata->_autoActiveTrain->getAutoEngineer() != NULL) {
                try {
                    ata->_autoActiveTrain->getAutoEngineer()->setFunction(2, true);
                    SleeperThread::msleep(_tsa->getDataWhat1());
                } catch (InterruptedException e) {
                    // interrupting will cause termination after turning horn off
                }
            }
            if (ata->_autoActiveTrain->getAutoEngineer() != NULL) {
                ata->_autoActiveTrain->getAutoEngineer()->setFunction(2, false);
            }
        } else if (_tsa->getWhatCode() == TransitSectionAction::SOUNDHORNPATTERN) {
            QString pattern = _tsa->getStringWhat();
            int index = 0;
            int sleepTime = ((_tsa->getDataWhat1()) * 12) / 10;
            bool keepGoing = true;
            while (keepGoing && (index < pattern.length())) {
                // sound horn
                if (ata->_autoActiveTrain->getAutoEngineer() != NULL) {
                    ata->_autoActiveTrain->getAutoEngineer()->setFunction(2, true);
                    try {
                        if (pattern.at(index) == 's') {
                            SleeperThread::msleep(_tsa->getDataWhat1());
                        } else if (pattern.at(index) == 'l') {
                            SleeperThread::msleep(_tsa->getDataWhat2());
                        }
                    } catch (InterruptedException e) {
                        // interrupting will cause termination after turning horn off
                        keepGoing = false;
                    }
                } else {
                    // loss of an autoEngineer will cause termination
                    keepGoing = false;
                }
                if (ata->_autoActiveTrain->getAutoEngineer() != NULL) {
                    ata->_autoActiveTrain->getAutoEngineer()->setFunction(2, false);
                } else {
                    keepGoing = false;
                }
                index++;
                if (keepGoing && (index < pattern.length())) {
                    try {
                        SleeperThread::msleep(sleepTime);
                    } catch (InterruptedException e) {
                        keepGoing = false;
                    }
                }
            }
        }
        ata->_autoActiveTrain->decrementHornExecution();
        ata->completedAction(_tsa);
    }
 private:
    /*private*/ TransitSectionAction* _tsa = NULL;
  AutoTrainAction* ata;
};

class MonitorTrain : public  Runnable {
Q_OBJECT
 public:
    /**
     * A runnable to monitor whether the autoActiveTrain is moving or
     * stopped Note: If train stops to do work with a manual throttle, this
     * thread will continue to wait until auto operation is resumed.
     */
    /*public*/ MonitorTrain(TransitSectionAction* tsa, AutoTrainAction* ata) {
        _tsa = tsa;
        this->ata = ata;
    }

    //@Override
    /*public*/ void run() {
        if (_tsa != NULL) {
            bool waitingOnTrain = true;
            if (_tsa->getWhenCode() == TransitSectionAction::TRAINSTOP) {
                try {
                    while (waitingOnTrain) {
                        if ((ata->_autoActiveTrain->getAutoEngineer() != NULL)
                                && (ata->_autoActiveTrain->getAutoEngineer()->isStopped())) {
                            waitingOnTrain = false;
                        } else {
                            SleeperThread::msleep(_delay);
                        }
                    }
                    ata->executeAction(_tsa);
                } catch (InterruptedException e) {
                    // interrupting will cause termination without executing the action
                }
            } else if (_tsa->getWhenCode() == TransitSectionAction::TRAINSTART) {
                if ((ata->_autoActiveTrain->getAutoEngineer() != NULL)
                        && (!ata->_autoActiveTrain->getAutoEngineer()->isStopped())) {
                    // if train is not currently stopped, wait for it to stop
                    bool waitingForStop = true;
                    try {
                        while (waitingForStop) {
                            if ((ata->_autoActiveTrain->getAutoEngineer() != NULL)
                                    && (ata->_autoActiveTrain->getAutoEngineer()->isStopped())) {
                                waitingForStop = false;
                            } else {
                                SleeperThread::msleep(_delay);
                            }
                        }
                    } catch (InterruptedException e) {
                        // interrupting will cause termination without executing the action
                    }
                }
                // train is stopped, wait for it to start
                try {
                    while (waitingOnTrain) {
                        if ((ata->_autoActiveTrain->getAutoEngineer() != NULL)
                                && (!ata->_autoActiveTrain->getAutoEngineer()->isStopped())) {
                            waitingOnTrain = false;
                        } else {
                            SleeperThread::msleep(_delay);
                        }
                    }
                    ata->executeAction(_tsa);
                } catch (InterruptedException e) {
                    // interrupting will cause termination without executing the action
                }
            }
        }
    }
    /*private*/ int _delay = 50;
    /*private*/ TransitSectionAction* _tsa = NULL;
  AutoTrainAction* ata;
};

class MonitorTrainSpeed : public Runnable {
Q_OBJECT
  AutoTrainAction* ata;
  public:
    /**
     * A runnable to monitor whether the autoActiveTrain is moving or
     * stopped Note: If train stops to do work with a manual throttle, this
     * thread will continue to wait until auto operation is resumed.
     */
    /*public*/ MonitorTrainSpeed(TransitSectionAction* tsa, AutoTrainAction* ata) {
        _tsa = tsa;
        this->ata = ata;
    }

    //@Override
    /*public*/ void run();
  private:
    /*private*/ int _delay = 51;
    /*private*/ TransitSectionAction* _tsa = NULL;
};
#endif // AUTOTRAINACTION_H
