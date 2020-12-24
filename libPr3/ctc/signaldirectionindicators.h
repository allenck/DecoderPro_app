#ifndef SIGNALDIRECTIONINDICATORS_H
#define SIGNALDIRECTIONINDICATORS_H

#include <QObject>
#include "signaldirectionindicatorsinterface.h"
#include "nbhsignal.h"
#include "timer.h"
#include "requesteddirectionobserved.h"
#include "propertychangelistener.h"
#include <QLinkedList>
#include "codebuttonhandlerdata.h"
#include "fleeting.h"
#include "ctcconstants.h"

class SignalDirectionIndicators : public SignalDirectionIndicatorsInterface
{
  Q_OBJECT
  //Q_INTERFACES(SignalDirectionIndicatorsInterface)
 public:
  /*public*/ SignalDirectionIndicators(QString userIdentifier,
                                      NBHSensor* leftSensor,
                                      NBHSensor* normalSensor,
                                      NBHSensor *rightSensor,
                                      int codingTimeInMilliseconds,
                                      int timeLockingTimeInMilliseconds,
                                      CodeButtonHandlerData::TRAFFIC_DIRECTION trafficDirection,
                                      QList<NBHSignal*> signalListLeftRight,
                                      QList<NBHSignal*> signalListRightLeft,
                                      Fleeting* fleetingObject, SignalDirectionIndicatorsInterface* parent);

  /*public*/ static void resetSignalsUsed();// { _mSignalsUsed.clear(); }
  QObject* self() {return (QObject*)this;}
  /*public*/ void setCodeButtonHandler(CodeButtonHandler* codeButtonHandler);
  /*public*/ void removeAllListeners();
  /*public*/ bool isNonfunctionalObject();
  /*public*/ void setPresentSignalDirectionLever(int presentSignalDirectionLever);
  /*public*/ bool isRunningTime();
  /*public*/ void osSectionBecameOccupied();
  /*public*/ void codeButtonPressed(int requestedDirection, bool requestedChangeInSignalDirection);
  /*public*/ void startCodingTime();
  /*public*/ bool signalsNormal();
  /*public*/ bool signalsNormalOrOutOfCorrespondence();
  /*public*/ int getPresentDirection();
  /*public*/ bool inCorrespondence();
  /*public*/ void forceAllSignalsToHeld();
  /*public*/ int getSignalsInTheFieldDirection();
  /*public*/ void setSignalDirectionIndicatorsToOUTOFCORRESPONDENCE();
  /*public*/ void setRequestedDirection(int direction);

 signals:

 public slots:

 private:
  static /*final*/ QSet<NBHSignal*> _mSignalsUsed;// = QSet<NBHSignal*>();
  /*private*/ class SignalHeadPropertyChangeListenerMaintainer {
    //Q_OBJECT
      /*private*/ /*final*/ NBHSignal* _mSignal;
   public:
      ///*private*/ /*final*/ PropertyChangeListener* _mPropertyChangeListener = (PropertyChangeEvent e) -> { handleSignalChange(e); };
      /*public*/ SignalHeadPropertyChangeListenerMaintainer(NBHSignal* signal) {
          _mSignal = signal;
          _mSignal->addPropertyChangeListener(/*_mPropertyChangeListener*/(PropertyChangeListener*)this);
          _mSignalHeadPropertyChangeListenerLinkedList.append(this); // "leaking this in constructor" is OK here, since this is the last thing we do.  And we are NOT multi-threaded when this happens.
      }
      /*public*/ void removePropertyChangeListener() {
          _mSignal->removePropertyChangeListener(/*_mPropertyChangeListener*/(PropertyChangeListener*)this);
      }
   private:
    /*private*/ QLinkedList<SignalHeadPropertyChangeListenerMaintainer*> _mSignalHeadPropertyChangeListenerLinkedList = QLinkedList<SignalHeadPropertyChangeListenerMaintainer*>();

  };

  /*private*/ NBHSensor* _mLeftSensor;
  /*private*/ NBHSensor* _mNormalSensor;
  /*private*/ NBHSensor* _mRightSensor;
  /*private*/ int _mPresentSignalDirectionLever = CTCConstants::SIGNALSNORMAL;             // Default
  /*private*/ /*final*/ QList<NBHSignal*> _mSignalListLeftRight = QList<NBHSignal*>();
  /*private*/ /*final*/ QList<NBHSignal*> _mSignalListRightLeft = QList<NBHSignal*>();
  /*private*/ Fleeting* _mFleetingObject;
  /*private*/ /*final*/ RequestedDirectionObserved* _mRequestedDirectionObserver = new RequestedDirectionObserved();
  /*private*/ /*final*/ Timer* _mTimeLockingTimer;
  /*private*/ /*final*/ ActionListener* _mTimeLockingTimerActionListener;
  /*private*/ /*final*/ Timer* _mCodingTimeTimer;
  /*private*/ /*final*/ ActionListener* _mCodingTimeTimerActionListener;
  /*private*/ int _mPresentDirection;
  /*private*/ CodeButtonHandler* _mCodeButtonHandler = nullptr;
  /*private*/ void setSignalsHeldTo(int direction);
  /*private*/ void setRLSignalsHeldTo(bool held);
  /*private*/ void setLRSignalsHeldTo(bool held);
  /*private*/ void setSignalDirectionIndicatorsToFieldSignalsState();
  /*private*/ void setSignalDirectionIndicatorsToDirection(int direction);
  /*private*/ void timeLockingDone();
  /*private*/ void codingTimeDone();
  /*private*/ void cancelLockedRoute();
  /*private*/ bool allSignalsRedSetThemAllHeld(int requestedDirection);
  /*private*/ void handleSignalChange(PropertyChangeEvent* e);
  /*private*/ bool changedToUniversalRed(PropertyChangeEvent* e);
  /*private*/ void possiblyUpdateSignalIndicationSensors();
  /*private*/ void addSignal(QString userIdentifier, NBHSignal* signal) throw (CTCException);
//  /*private*/ void SensorSensorsetSignalDirectionIndicatorsToFieldSignalsState();
//  /*private*/ void SensorSensorsetSignalDirectionIndicatorsToDirection(int direction);

  friend class CodeButtonHandler;
  friend class TimeLockingTimerActionListener;
  friend class CodingTimeTimerActionListener;
  friend class CallOn;
};

class TimeLockingTimerActionListener : public ActionListener
{
  Q_OBJECT
  SignalDirectionIndicators* sdi;
 public:
  TimeLockingTimerActionListener(SignalDirectionIndicators* sdi) {this->sdi = sdi;}
 public slots:
  void actionPerformed()
  {
   sdi->timeLockingDone();
  }
};

class CodingTimeTimerActionListener: public ActionListener
{
  Q_OBJECT
  SignalDirectionIndicators* sdi;
 public:
  CodingTimeTimerActionListener(SignalDirectionIndicators* sdi) {this->sdi = sdi;}
 public slots:
  void actionPerformed()
  {
   sdi->codingTimeDone();
  }
};
#endif // SIGNALDIRECTIONINDICATORS_H
