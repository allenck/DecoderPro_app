#ifndef SPEEDUTIL_H
#define SPEEDUTIL_H

#include <QObject>

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

protected:
 /*protected*/ SpeedUtil(QList<BlockOrder*>* orders, QObject* parent = nullptr);
 /*protected*/ void setOrders(QList<BlockOrder*>*orders);
 /*protected*/ RosterSpeedProfile* getSpeedProfile();
 /*protected*/ void setDccAddress(DccLocoAddress* dccAddr);
 /*protected*/ float getThrottleSpeedStepIncrement();
 /*protected*/ bool profileHasSpeedInfo();
 /*protected*/ void stopRun(bool updateSpeedProfile);
 /*protected*/ void setThrottle( DccThrottle* throttle);
 /*protected*/ bool secondGreaterThanFirst(QString speed1, QString speed2);
 /*protected*/ float modifySpeed(float tSpeed, QString sType, bool isForward);
 /*protected*/ float getTrackSpeed(float throttleSetting, bool isForward);
 /*protected*/ float getThrottleSettingForSpeed(float trackSpeed, bool isForward);
 /*protected*/ float getDistanceTraveled(float speedSetting, QString speedtype, float time, bool isForward);
 /*protected*/ float getTimeForDistance(float throttleSetting, float distance, bool isForward);
 /*protected*/ float rampLengthForRampDown(float curSetting, QString curSpeedType, QString toSpeedType,
         bool isForward);
 /*protected*/ float rampLengthForSpeedChange(float fSpeed, float toSpeed, bool isForward);
 /*protected*/ float getRampThrottleIncrement();
 /*protected*/ int getRampTimeIncrement();
 /*protected*/ float getMomentumTime(float delta, bool increasing);

friend class NXFrame;
friend class Warrant;
friend class WarrantFrame;
};

#endif // SPEEDUTIL_H
