#ifndef ROSTERSPEEDPROFILE_H
#define ROSTERSPEEDPROFILE_H

#include <QObject>
#include <QMap>
#include <QLinkedList>
#include <QtXml>
#include "libPr3_global.h"

class SpeedSetting;
class Logger;
class Section;
class Block;
class NamedBean;
class DccThrottle;
//class SpeedStep;
class RosterEntry;
class LIBPR3SHARED_EXPORT RosterSpeedProfile : public QObject
{
 Q_OBJECT
public:
 //explicit RosterSpeedProfile(QObject *parent = 0);
 /*public*/ RosterSpeedProfile(RosterEntry* re, QObject *parent = 0);
 /*public*/ RosterEntry* getRosterEntry();
 /*public*/ float getOverRunTimeForward();
 /*public*/ void setOverRunTimeForward(float dt);
 /*public*/ float getOverRunTimeReverse();
 /*public*/ void setOverRunTimeReverse(float dt) ;
 /*public*/ void clearCurrentProfile();
 /*public*/ void setSpeed(int speedStep, float forward, float reverse);
 /*public*/ void setForwardSpeed(float speedStep, float forward);
 /*public*/ void setReverseSpeed(float speedStep, float reverse);
 /*public*/ float getForwardSpeed(float speedStep);
 /*public*/ float getReverseSpeed(float speedStep);
 /*public*/ float getDurationOfTravelInSeconds(bool isForward, float speedStep, int distance);
 /*public*/ float getDistanceTravelled(bool isForward, float speedStep, float duration);
 /*public*/ void setExtraInitialDelay(float eDelay);
 /*public*/ void changeLocoSpeed(DccThrottle* t, Block* blk, float speed);
 /*public*/ void changeLocoSpeed(DccThrottle* t, Section* sec, float speed);
 /*public*/ void changeLocoSpeed(DccThrottle* t, float distance, float speed);
 /*public*/ void cancelSpeedChange();
 /*public*/ void store(QDomElement e);
 /*public*/ void load(QDomElement e);
 /*public*/ int getProfileSize();
 /*public*/ float getForwardFactor();
 /*public*/ float getReverseFactor();
 /*public*/ float getSpeed(float speedStep, bool isForward);
 static /*public*/ /*final*/ float MMS_TO_MPH;// = 0.00223694f;
 static /*public*/ /*final*/ float MMS_TO_KPH;// = 0.0036f;
 /*public*/ float MMSToScaleSpeed(float mms);
 /*public*/ QString convertMMSToScaleSpeedWithUnits(float mms);
 /*public*/ QString convertThrottleSettingToScaleSpeedWithUnits(float throttleSetting, bool isForward);
 /*public*/ float convertScaleSpeedToMMS(float scaleSpeed);

signals:

public slots:
private:
 RosterEntry* _re;// = null;

 float overRunTimeReverse;// = 0.0;
 float overRunTimeForward;// = 0.0;
 float distanceRemaining;// = 0;
 float distanceTravelled;// = 0;
 /*static*/ class SpeedStep
 {

  float forward;// = 0.0;
  float reverse;// = 0.0;
public:
  SpeedStep()
  {
   forward = 0.0;
   reverse = 0.0;
  }

  void setForwardSpeed(float speed) {
      forward = speed;
  }

  void setReverseSpeed(float speed) {
      reverse = speed;
  }

  float getForwardSpeed() {
      return forward;
  }

  float getReverseSpeed() {
      return reverse;
  }
 };

 QMap<int, SpeedStep*> speeds;// = new TreeMap<Integer, SpeedStep>();
 int higherKey(int key);
 int lowerKey(int key);

 DccThrottle* _throttle;

 float desiredSpeedStep;// = -1;

 float extraDelay;// = 0.0f;

 NamedBean* referenced;// = null;

 QTimer* stopTimer;// = null;

 QElapsedTimer* lastTimeTimerStarted;// = 0l;

 bool increaseSpeed;// = false;
 void finishChange();
 /*static*/ class SpeedSetting
 {
  float step;// = 0.0;
  int duration;// = 0;
public:
  SpeedSetting(float step, int duration) {
      this->step = step;
      this->duration = duration;
  }

  float getSpeedStep() {
      return step;
  }

  int getDuration() {
      return duration;
  }
 };
 Logger* log;
 int extraTime;// = 0;
 void calculateStepDetails(float speedStep, float distance);
 float calculateInitialOverRun(float distance);
 QLinkedList<SpeedSetting*> stepQueue;// = new LinkedList<SpeedSetting>();

private slots:
 void stopLocoTimeOut(DccThrottle* t);
 /*synchronized*/ void setNextStep();

};

#endif // ROSTERSPEEDPROFILE_H
