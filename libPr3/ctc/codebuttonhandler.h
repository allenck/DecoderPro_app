#ifndef CODEBUTTONHANDLER_H
#define CODEBUTTONHANDLER_H

#include <QObject>
#include "ctcconstants.h"

class Sensor;
class LockedRoute;
class LockedRoutesManager;
class NBHSensor;
class PropertyChangeListener;
class SignalDirectionIndicatorsInterface;
class SignalDirectionLever;
class SwitchDirectionIndicators;
class SwitchDirectionLever;
class Fleeting;
class CallOn;
class TrafficLocking;
class TurnoutLock;
class IndicationLockingSignals;
class CodeButtonSimulator;
class CodeButtonHandler : public QObject
{
  Q_OBJECT
 public:
  explicit CodeButtonHandler(QObject *parent = nullptr);
  /*public*/ CodeButtonHandler(   bool turnoutLockingOnlyEnabled,                              // If this is NOT an O.S. section, but only a turnout lock, then this is true.
                              LockedRoutesManager* lockedRoutesManager,
                              QString userIdentifier,
                              int uniqueID,
                              NBHSensor* codeButtonInternalSensor,                             // Required
                              int codeButtonDelayInMilliseconds,                              // If 0, REAL code button, if > 0, tower operations (simulated code button).
                              NBHSensor* osSectionOccupiedExternalSensor,                      // Required, if ACTIVE prevents turnout, lock or call on from occuring.
                              NBHSensor* osSectionOccupiedExternalSensor2,                     // Optional, if ACTIVE prevents turnout, lock or call on from occuring.
                              SignalDirectionIndicatorsInterface* signalDirectionIndicators,   // Required
                              SignalDirectionLever* signalDirectionLever,
                              SwitchDirectionIndicators* switchDirectionIndicators,
                              SwitchDirectionLever* switchDirectionLever,
                              Fleeting* fleeting,                                              // If null, then ALWAYS fleeting!
                              CallOn* callOn,
                              TrafficLocking* trafficLocking,
                              TurnoutLock* turnoutLock,
                              IndicationLockingSignals* indicationLockingSignals, QObject *parent);            // Needed for check of adjacent OS Section(s), and optionally turnoutLock.

  /*public*/ void externalLockTurnout();

 signals:

 public slots:

 private:
  /*private*/ /*final*/ bool _mTurnoutLockingOnlyEnabled;
  /*private*/ /*final*/ LockedRoutesManager* _mLockedRoutesManager;
  /*private*/ /*final*/ QString _mUserIdentifier;
  /*private*/ /*final*/ int _mUniqueID;
  /*private*/ /*final*/ NBHSensor* _mCodeButtonInternalSensor;
  /*private*/ /*final*/ PropertyChangeListener* _mCodeButtonInternalSensorPropertyChangeListener;
  /*private*/ /*final*/ NBHSensor* _mOSSectionOccupiedExternalSensor;
  /*private*/ /*final*/ NBHSensor* _mOSSectionOccupiedExternalSensor2;
  /*private*/ /*final*/ PropertyChangeListener* _mOSSectionOccupiedExternalSensorPropertyChangeListener;
  /*private*/ /*final*/ SignalDirectionIndicatorsInterface* _mSignalDirectionIndicators;
  /*private*/ /*final*/ SignalDirectionLever* _mSignalDirectionLever;
  /*private*/ /*final*/ SwitchDirectionIndicators* _mSwitchDirectionIndicators;
  /*private*/ /*final*/ SwitchDirectionLever* _mSwitchDirectionLever;
  /*private*/ /*final*/ Fleeting* _mFleeting;
  /*private*/ /*final*/ CallOn* _mCallOn;
  /*private*/ /*final*/ TrafficLocking* _mTrafficLocking;
  /*private*/ /*final*/ TurnoutLock* _mTurnoutLock;
  /*private*/ /*final*/ IndicationLockingSignals* _mIndicationLockingSignals;
  /*private*/ /*final*/ CodeButtonSimulator* _mCodeButtonSimulator;
  /*private*/ LockedRoute* _mLockedRoute = nullptr;
  /*private*/ /*static*/ Sensor* initializePreconditioningEnabledSensor();
  /*private*/ static /*final*/ Sensor* _mPreconditioningEnabledSensor;// = initializePreconditioningEnabledSensor();
  /*private*/ /*static*/ class PreconditioningData {
   public:
      /*public*/ bool  _mCodeButtonPressed = false;    // If false, values in these don't matter:
      /*public*/ int      _mSignalDirectionLeverWas = CTCConstants::OUTOFCORRESPONDENCE;   // Safety:
      /*public*/ int      _mSwitchDirectionLeverWas = CTCConstants::OUTOFCORRESPONDENCE;
   friend class CodeButtonHandler;
  };
  /*private*/ PreconditioningData* _mPreconditioningData = new PreconditioningData();

};

#endif // CODEBUTTONHANDLER_H
