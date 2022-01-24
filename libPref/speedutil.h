#ifndef SPEEDUTIL_H
#define SPEEDUTIL_H

#include <QObject>

class SpeedStep;
class RampData;
class QDomElement;
class SignalSpeedMap;
class RosterSpeedProfile;
class DccThrottle;
class BlockOrder;
class RosterEntry;
class DccLocoAddress;
class Logger;
class SpeedUtil : public QObject
{
 Q_OBJECT
public:
 explicit SpeedUtil(QObject *parent = nullptr);

 /*public*/ static float SCALE_FACTOR;// = 125; // divided by _scale, gives a rough correction for track speed
 /*public*/ QString getAddress();
 /*public*/ RosterEntry* getRosterEntry();
 /*public*/ bool setDccAddress(QString id);
 /*public*/ QString getRosterId();
 /*public*/ void setRosterId(QString id);
 /*public*/ DccLocoAddress* getDccAddress();
 /*public*/ SpeedStep* getSpeedStep(float speed);
 /*public*/ void setForwardSpeed(float speedStep, float forward);
 /*public*/ void setReverseSpeed(float speedStep, float reverse);
 /*public*/ float getForwardSpeed(float speedStep);
 /*public*/ float getReverseSpeed(float speedStep);
 /*public*/ float getDurationOfTravelInSeconds(bool isForward, float speedStep, int distance);

signals:

public slots:

private:
 static Logger* log;
 /*private*/ DccLocoAddress* _dccAddress;
 /*private*/ QString _rosterId;        // Roster title for train
 /*private*/ RosterEntry* _rosterEntry;
 /*private*/ QList<BlockOrder*>* _orders;

 /*private*/ DccThrottle* _throttle;
 /*private*/ float _stepRampThrottleIncrement;   // user specified throttle increment for ramping
 /*private*/ int _stepRampTimeIncrement; // user specified time for ramp step increment
 /*private*/ RosterSpeedProfile* _mergeProfile; // merge of existing Roster speeedProfile and session speeedProfile
 /*private*/ RosterSpeedProfile* _sessionProfile; // speeds measured in the session
 /*private*/ SignalSpeedMap* _signalSpeedMap;
 /*private*/ float _ma;  // milliseconds needed to increase speed by throttle step amount
 /*private*/ float _md;  // milliseconds needed to decrease speed by throttle step amount
 /*private*/ void makeSpeedTree();
 /*private*/ void makeRampParameters();
 /*private*/ float getMomentumFactor(QDomElement cv);
 /*private*/ float getMomentumAdustment(QDomElement cv);
 long _timeAtSpeed;
 float _distanceTravelled;
 float _settingsTravelled;
 long _changetime;
 int _numchanges;
 /*private*/ void clearStats();
 /*private*/ void makeUpRamp(RampData* ramp);
 /*private*/ void makeDownRamp(RampData* ramp);
 bool _isForward = true;
 /*private*/ float _rampThrottleIncrement;   // user specified throttle increment for ramping
 /*private*/ int _rampTimeIncrement; // user specified time for ramp step increment
 /*private*/ void setSpeed(RosterSpeedProfile* profile, float throttle, float measuredSpeed, bool isForward);

protected:
 /*protected*/ SpeedUtil(QList<BlockOrder *> *orders, QObject* parent = nullptr);
 /*protected*/ void setOrders(QList<BlockOrder*>* orders);
 /*protected*/ void setIsForward(bool forward);
 /*protected*/ RosterSpeedProfile* getSpeedProfile();
 /*protected*/ void setDccAddress(DccLocoAddress* dccAddr);
 /*protected*/ float getThrottleSpeedStepIncrement();
 /*protected*/ bool profileHasSpeedInfo();
 /*protected*/ void stopRun(bool updateSpeedProfile);
 /*protected*/ void setThrottle( DccThrottle* throttle);
 /*protected*/ bool secondGreaterThanFirst(QString speed1, QString speed2);
 /*protected*/ float modifySpeed(float tSpeed, QString sType);
 /*protected*/ float getTrackSpeed(float throttleSetting);
 /*protected*/ float getThrottleSettingForSpeed(float trackSpeed, bool isForward);
 /*protected*/ float getDistanceTraveled(float speedSetting, QString speedtype, float time);
 /*protected*/ float getTimeForDistance(float throttleSetting, float distance);
 /*protected*/ float rampLengthForRampDown(float curSetting, QString curSpeedType, QString toSpeedType);
 /*protected*/ float rampLengthForSpeedChange(float fSpeed, float toSpeed, bool isForward);
 /*protected*/ float getRampThrottleIncrement();
 /*protected*/ int getRampTimeIncrement();
 /*protected*/ float getMomentumTime(float delta, bool increasing);
 /*protected*/ void enteredBlock(int lastIdx, int newIdx);
 /*protected*/ void speedChange();
 /*protected*/ float getDistanceTravelled();
 /*protected*/ void setDistanceTravelled(float dist);
 /*protected*/ RampData* getRampForSpeedChange(float fromSpeed, float toSpeed);
 /*protected*/ float getDistanceOfSpeedChange(float prevSpeed, float currSpeed, long speedTime);

friend class NXFrame;
friend class Warrant;
friend class WarrantFrame;
friend class WarrantTest;
friend class Engineer;
friend class ThrottleRamp;
friend class LearnSpeedPanel;
};

#endif // SPEEDUTIL_H
