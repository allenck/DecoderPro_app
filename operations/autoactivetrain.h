#ifndef AUTOACTIVETRAIN_H
#define AUTOACTIVETRAIN_H

#include <QObject>
#include "runnable.h"
#include "throttlelistener.h"
#include "propertychangelistener.h"

class JThread;
class AutoEngineer;
class PropertyChangeEvent;
class DccLocoAddress;
class Logger;
class Sensor;
class PropertyChangeListener;
class Block;
class Section;
class SignalHead;
class SignalMast;
class RosterEntry;
class LayoutBlockManager;
class AutoEngineer;
class ActiveTrain;
class AutoTrainAction;
class DccThrottle;
class AllocatedSection;
class AutoActiveTrain : public QObject, public ThrottleListener
{
 Q_OBJECT
    Q_INTERFACES(ThrottleListener)
public:
 explicit AutoActiveTrain(ActiveTrain* at,QObject *parent = 0);

 /* Speed aspects as defined by Douglas A. Kerr - "Rail Signal Aspects and Indications"
  * http://dougkerr.net/Pumpkin/articles/Rail_signal_aspects.pdf (from Pete Cressman)
  */
 //    SPEED_MASK = 0x07;     // least significant 3 bits
 enum SPEEDS
 {
 STOP_SPEED = 0x01,     // No Speed
 RESTRICTED_SPEED = 0x02,    // Train able to stop within 1/2 visual range (10mph)
 SLOW_SPEED = 0x03,     // Typically 15 mph  (25% of NORMAL)
 MEDIUM_SPEED = 0x04,     // Typically 30 mph (40% of NORMAL)
 LIMITED_SPEED = 0x05,     // Typically 40-45 mph  (65% of NORMAL)
 NORMAL_SPEED = 0x06,     // Varies with road and location
 MAXIMUM_SPEED = 0x07     // "full" throttle
};

 enum RAMP
 {
   /* The ramp rates below are in addition to what the decoder itself does
    */
   RAMP_NONE = 0x00,		// No ramping - set speed immediately
   RAMP_FAST = 0x01,     // Fast ramping
   RAMP_MEDIUM = 0x02,		// Medium ramping
   RAMP_MED_SLOW = 0x03,		// Medium/slow ramping
   RAMP_SLOW = 0x04		// Slow ramping
 };

 /* Stop tasks codes
  */
 enum STOPTASKS
 {
  NO_TASK = 0x00,     // No task at stop
  END_REVERSAL = 0x01,     // Handle reversing direction at end for back and forth running
  BEGINNING_RESET = 0x02     // Handle reseting beginning for back and forth running
 };
 /*public*/ ActiveTrain* getActiveTrain();
 /*public*/ AutoEngineer* getAutoEngineer() ;
 /*public*/ AutoTrainAction* getAutoTrainAction();
 /*public*/ bool getForward();
 /*public*/ void setForward(bool set);
 /*public*/ /*synchronized*/ float getTargetSpeed();
 /*public*/ /*synchronized*/ void setTargetSpeed(float speed);
 /*public*/ int getSavedStatus() ;
 /*public*/ void setSavedStatus(int status);
 /*public*/ /*synchronized*/ void setCurrentRampRate(int rate);
 /*public*/ int getRampRate();
 /*public*/ void setRampRate(int rate);
 /*public*/ float getSpeedFactor();
 /*public*/ void setSpeedFactor(float factor);
 /*public*/ float getMaxSpeed();
 /*public*/ void setMaxSpeed(float speed);
 /*public*/ bool getResistanceWheels() ;
 /*public*/ void setResistanceWheels(bool set);
 /*public*/ bool getRunInReverse();
 /*public*/ void setRunInReverse(bool set);
 /*public*/ bool getSoundDecoder();
 /*public*/ void setSoundDecoder(bool set);
 /*public*/ float getMaxTrainLength();
 /*public*/ void setMaxTrainLength(float length);
 /*public*/ static int getRampRateFromName(QString rampRate);
 /*public*/ bool initialize();
 /*public*/QObject* self() {return (QObject*)this;}

 /*public*/ Thread *pauseTrain(int fastMinutes);
 /*public*/ void terminate();
 /*public*/ void dispose();

signals:

public slots:
 /*public*/ void notifyThrottleFound(DccThrottle* t);
 /*public*/ void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason);
 /*public*/ void on_sensorChange(PropertyChangeEvent* e);
 /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
 Logger * log;
 // operational instance variables
 /*private*/ ActiveTrain* _activeTrain;// = null;
 /*private*/ AutoTrainAction* _autoTrainAction;// = null;
 /*private*/ DccThrottle* _throttle;// = null;
 /*private*/ AutoEngineer* _autoEngineer;// = null;
 /*private*/ int _address;// = -1;
 /*private*/ bool _forward;// = true;
 /*private*/ float _targetSpeed;// = 0.0;
 /*private*/ int _savedStatus;// = ActiveTrain::RUNNING;
 /*private*/ int _currentRampRate;// = RAMP_NONE;     // current Ramp Rate
 /*private*/ bool _pausingActive;// = false;		// true if train pausing thread is active

 // persistent instance variables (saved with train info)
 /*private*/ int _rampRate;// = RAMP_NONE;     // default Ramp Rate
 /*private*/ float _speedFactor;// = 1.0f;		// default speed factor
 /*private*/ float _maxSpeed;// = 0.6f;			// default maximum train speed
 /*private*/ bool _resistanceWheels;// = true;  // true if all train cars show occupancy
 /*private*/ bool _runInReverse;// = false;  // true if the locomotive should run through Transit in reverse
 /*private*/ bool _soundDecoder;// = false;  // true if locomotive has a sound decoder
 /*private*/ /*volatile*/ float _maxTrainLength;// = 200.0f;  // default train length (scale feet/meters)

 // more operational variables
 /*private*/ QList<AllocatedSection*>* _allocatedSectionList;// = new ArrayList<AllocatedSection>();
 /*private*/ LayoutBlockManager* _lbManager;// = NULL;
 /*private*/ AllocatedSection* _lastAllocatedSection;// = NULL;

 /*private*/ QList<float> _speedRatio;// = {-1.0, 0.0, 0.25, 0.35, 0.50, 0.65, 0.8, 1.15};
  RosterEntry* re;// = NULL;
  bool useSpeedProfile;// = false;

  /*private*/ bool _initialized; // =  false;
  /*private*/ Section* _nextSection; // =  NULL;	                     // train has not reached this Section yet
  /*private*/ /*volatile*/ AllocatedSection* _currentAllocatedSection; // =  NULL;    // head of the train is in this Section
  /*private*/ /*volatile*/ AllocatedSection* _previousAllocatedSection; // =  NULL;   // previous Section - part of train could still be in this section
  /*private*/ SignalHead* _controllingSignal; // =  NULL;
  /*private*/ SignalMast* _controllingSignalMast; // =  NULL;
  /*private*/ PropertyChangeListener* _conSignalListener; // =  NULL;
  /*private*/ PropertyChangeListener* _conSignalMastListener; // =  NULL;
  /*private*/ Block* _conSignalProtectedBlock; // =  NULL;
  /*private*/ /*volatile*/ Block* _currentBlock; // =  NULL;
  /*private*/ Block* _nextBlock; // =  NULL;
  /*private*/ /*volatile*/ Block* _previousBlock; // =  NULL;
  /*private*/ bool _stoppingBySensor; // =  false;
  /*private*/ Sensor* _stopSensor; // =  NULL;
  /*private*/ PropertyChangeListener* _stopSensorListener; // =  NULL;
  /*private*/ bool _stoppingForStopSignal; // =  false;		  // if true, stopping because of signal appearance
  /*private*/ bool _stoppingByBlockOccupancy; // =  false;    // if true, stop when _stoppingBlock goes UNOCCUPIED
  /*private*/ bool _stoppingUsingSpeedProfile; // =  false;     // if true, using the speed profile against the roster entry to bring the loco to a stop in a specific distance
  /*private*/ /*volatile*/ Block* _stoppingBlock; // =  NULL;
  /*private*/ bool _resumingAutomatic; // =  false;  // if true, resuming automatic mode after WORKING session
  /*private*/ bool _needSetSpeed; // =  false;  // if true, train will set speed according to signal instead of stopping

  // keeps track of and restores previous speed
  /*private*/ float _savedSpeed; // =  0.0f;
  // keeps track of number of horn execution threads that are active
  /*private*/ int _activeHornThreads;// = 0;
  float prevSpeed;// = -1.0f;
  /*private*/ bool isInAllocatedList(AllocatedSection* as);
  /*private*/ void addAllocatedSection(AllocatedSection* as);
  /*private*/ void setNewCurrentSection(AllocatedSection* as);
  /*private*/ Block* getNextBlock(Block* b, AllocatedSection* as);
  /*private*/ bool isStopping();
  /*private*/ bool isSectionInAllocatedList(Section* s);
  /*private*/ void removeCurrentSignal();
  /*private*/ /*synchronized*/ void stopInCurrentSection(int task);
  /*private*/ /*synchronized*/ void setTargetSpeedState(int speedState);
  /*private*/ /*synchronized*/ void setTargetSpeedValue(float speed);
  /*private*/ int getBlockLength(Block* b);
  /*private*/ /*synchronized*/ void setStopNow();
  /*private*/ void setStopByBlockOccupancy();
  /*private*/ /*synchronized*/ void cancelStopInCurrentSection();

private slots:
  /*private*/ /*synchronized*/ void handleStopSensorChange();


protected:
 /*protected*/ /*synchronized*/ void setupNewCurrentSignal(AllocatedSection* as);
  /*protected*/ DccThrottle* getThrottle();
  /*protected*/ Section* getLastAllocatedSection();
  /*protected*/ void saveSpeed() ;
  /*protected*/ void restoreSavedSpeed() ;

  /*protected*/ void decrementHornExecution();
  /*protected*/ void incrementHornExecution() ;
  /*protected*/ void setEngineDirection();
  /*protected*/ AllocatedSection* getCurrentAllocatedSection();
  /*protected*/ void allocateAFresh();
  /*protected*/ /*synchronized*/ void setSpeedBySignal();
  /*protected*/ void waitUntilStopped();
  /*protected*/ void resumeAutomaticRunning();
  /*protected*/ void initiateWorking();
  /*protected*/ void removeAllocatedSection(AllocatedSection* as);
  /*protected*/ void handleBlockStateChange(AllocatedSection* as, Block* b);
  /*protected*/ /*synchronized*/ void executeStopTasks(int task);

protected slots:
  /*protected*/ void handleSectionStateChange(AllocatedSection* as) ;
  /*protected*/ void handleSectionOccupancyChange(AllocatedSection* as);

 friend class ActiveTrain;
 friend class AutoEngineer;
 friend class AutoTrainAction;
 friend class AutoTrainsFrame;
 friend class AllocatedSection;
 friend class HornExecution;
 friend class RespondToBlockStateChange;
 friend class WaitForTrainToStop;
 friend class PauseTrain;
};

// _________________________________________________________________________________________
// This class waits for train stop in a separate thread
class WaitForTrainToStop : public  Runnable {
Q_OBJECT
  AutoActiveTrain* aat;
 public:
    /*public*/ WaitForTrainToStop(int task, AutoActiveTrain* aat) {
        _task = task;
        this->aat = aat;
    }

    //@Override
    /*public*/ void run();
 private:
    /*private*/ int _delay = 91;
    /*private*/ int _task = 0;
};

// _________________________________________________________________________________________
// This class pauses the train in a separate thread
//  Train is stopped, then restarted after specified number of fast Minutes have elapsed
class PauseTrain : public  Runnable , public PropertyChangeListener{
Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
  AutoActiveTrain* aat;
  public:
    /**
     * A runnable that executes a pause train for a specified number of Fast
     * Clock minutes
     */
    /*public*/ PauseTrain(int fastMinutes, AutoActiveTrain* aat) {
        _fastMinutes = fastMinutes;
        this->aat = aat;
    }

    //@Override
    /*public*/ void run();
  QObject* self() override {return (QObject*)this;}
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) {
      _fastMinutes--;
  }

 private:
    /*private*/ int _fastMinutes = 0;
    /*private*/ float _savedTargetSpeed = 0.0f;
    /*private*/ int _savedRampRate = AutoActiveTrain::RAMP_NONE;
};

class AutoEngineer : public  Runnable
{
 Q_OBJECT
  AutoActiveTrain* aat;
public:
    AutoEngineer(AutoActiveTrain* aat);

 private:
    Logger* log;
    // operational instance variables and flags
//        private float _minSpeedStep = 1.0f;
    /*private*/ bool _abort;// = false;
    /*private*/ volatile bool _halt;// = false;  // halt/resume from user's control
    /*private*/ bool _halted;// = false; // true if previously halted
    /*private*/ bool _slowToStop;// = false;
    /*private*/ float _currentSpeed;// = 0.0f;
    /*private*/ Block* _lastBlock;// = NULL;
    /*private*/ float _speedIncrement;// = 0.0f  ; //will be recalculated
public:
    //@Override
    /*public*/ void run();
    /*public*/ /*synchronized*/ void slowToStop(bool toStop);
    /*public*/ /*synchronized*/ void setHalt(bool halt);
    /*public*/ /*synchronized*/ void setSpeedImmediate(float speed);
    /*public*/ /*synchronized*/ bool isStopped();
    /*public*/ /*synchronized*/ bool isAtSpeed();
    /*public*/ void abort();
protected:
    /*protected*/ void setFunction(int cmdNum, bool isSet);
    friend class AutoTrainAction;
    friend class HornExecution;
};

#endif // AUTOACTIVETRAIN_H
