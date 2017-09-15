#ifndef AUTOACTIVETRAIN_H
#define AUTOACTIVETRAIN_H

#include <QObject>

class RosterEntry;
class LayoutBlockManager;
class AutoEngineer;
class ActiveTrain;
class AutoTrainAction;
class DccThrottle;
class AllocatedSection;
class AutoActiveTrain : public QObject
{
 Q_OBJECT
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

signals:

public slots:

private:
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

protected:
 /*protected*/ /*synchronized*/ void setupNewCurrentSignal(AllocatedSection* as);

 friend class ActiveTrain;
};

#endif // AUTOACTIVETRAIN_H
