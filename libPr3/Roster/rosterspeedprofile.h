#ifndef ROSTERSPEEDPROFILE_H
#define ROSTERSPEEDPROFILE_H

#include <QObject>
#include <QMap>
#include <QLinkedList>
#include <QtXml>
#include "libPr3_global.h"

class SpeedStep;
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

public:
 //explicit RosterSpeedProfile(QObject *parent = 0);
 /*public*/ RosterSpeedProfile(RosterEntry* re, QObject *parent = 0);
 /*public*/ RosterEntry* getRosterEntry();
 /*public*/ float getOverRunTimeForward();
 /*public*/ void setOverRunTimeForward(float dt);
 /*public*/ float getOverRunTimeReverse();
 /*public*/ void setOverRunTimeReverse(float dt) ;
 /*public*/ void clearCurrentProfile();
 /*public*/ void deleteStep(int step);
 /*public*/ bool hasForwardSpeeds();
 /*public*/ bool hasReverseSpeeds();
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
 /*public*/ QMap<int, SpeedStep*> getProfileSpeeds();
 /*public*/ float getForwardFactor();
 /*public*/ float getReverseFactor();
 /*public*/ float getSpeed(float speedStep, bool isForward);
 static /*public*/ /*final*/ float MMS_TO_MPH;// = 0.00223694f;
 static /*public*/ /*final*/ float MMS_TO_KPH;// = 0.0036f;
 /*public*/ float MMSToScaleSpeed(float mms);
 /*public*/ QString convertMMSToScaleSpeedWithUnits(float mms);
 /*public*/ QString convertThrottleSettingToScaleSpeedWithUnits(float throttleSetting, bool isForward);
 /*public*/ float convertScaleSpeedToMMS(float scaleSpeed);
 /*public*/ float getThrottleSetting(float speed, bool isForward);
 /*public*/ SpeedStep* getSpeedStep(float speed);

signals:

public slots:
private:
 RosterEntry* _re;// = null;

 float overRunTimeReverse;// = 0.0;
 float overRunTimeForward;// = 0.0;
 bool _hasForwardSpeeds = false;
 bool _hasReverseSpeeds = false;
 float distanceRemaining;// = 0;
 float distanceTravelled;// = 0;
 inline bool isEqual(double x, double y)
 {
   const double epsilon = 1e-5/* some small number such as 1e-5 */;
   return std::abs(x - y) <= epsilon * std::abs(x);
   // see Knuth section 4.2.2 pages 217-218
 }

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
 Logger* log;
 int extraTime;// = 0;
 void calculateStepDetails(float speedStep, float distance);
 float calculateInitialOverRun(float distance);
 QLinkedList<SpeedSetting*> stepQueue;// = new LinkedList<SpeedSetting>();

private slots:
 void stopLocoTimeOut(DccThrottle* t);
 /*synchronized*/ void setNextStep();

};
/*static*/ /*public*/ class SpeedStep {

    float forward = 0.0f;
    float reverse = 0.0f;
public:
    /*public*/ SpeedStep() {
    }

    /*public*/ void setForwardSpeed(float speed) {
        forward = speed;
    }

    /*public*/ void setReverseSpeed(float speed) {
        reverse = speed;
    }

    /*public*/ float getForwardSpeed() {
        return forward;
    }

    /*public*/ float getReverseSpeed() {
        return reverse;
    }
};
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

#endif // ROSTERSPEEDPROFILE_H
