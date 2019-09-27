#ifndef ENGINEER_H
#define ENGINEER_H

#include <QThread>
#include <QMutex>
#include "logger.h"

class SignalSpeedMap;
class RosterSpeedProfile;
class ThrottleRamp;
class OBlock;
class Sensor;
class DccThrottle;
class Warrant;
class Engineer : public QThread
{
    Q_OBJECT
public:
    //explicit Engineer(QObject *parent = 0);
    Engineer(Warrant* warrant, DccThrottle* throttle, QObject *parent = 0);
    /*public*/ int getCurrentCommandIndex();
    /*synchronized*/ /*public*/ int getRunState();
    /*public*/ QString getSpeedRestriction();
    /*synchronized*/ /*public*/ void setHalt(bool halt);
    /*synchronized*/ /*public*/ void abort();
    /*synchronized*/ /*public*/ void rampSpeedTo(QString endSpeedType, long waitTime);
    /*synchronized*/ /*public*/ void synchNotify(OBlock* block);

signals:

public slots:
private:
    /*private*/ int     _idxCurrentCommand;     // current throttle command
    /*private*/ QString _currentCommand;
    /*private*/ float   _speed;
    /*private*/ int _idxSkipToSpeedCommand;   // skip to this index to reset script when ramping
    /*private*/ float _normalSpeed = 0;       // current commanded throttle setting (unmodified)
    /*private*/ QString  _speedType;// = "Normal";
    /*private*/ float   _minSpeed;// = 1.0f/127;
    /*private*/ bool _abort;// = false;
    /*private*/ bool _halt;// = false;  // halt/resume from user's control
    /*private*/ bool _waitForClear;// = false;  // waits for signals/occupancy/allocation to clear
    /*private*/ bool _waitForSync;// = false;  // waits for train to catch up to commands
    /*private*/ bool _waitForSensor;// = false; // wait for sensor event
    /*private*/ bool _speedOverride;// = false; // speed changing due to signal or occupancy
    /*private*/ int     _syncIdx;
    /*private*/ DccThrottle* _throttle;
    /*private*/ Warrant* _warrant;
    /*private*/ Sensor* 	_waitSensor;
    /*private*/ int		_sensorWaitState;
    /*private*/ ThrottleRamp* _ramp;
    SignalSpeedMap*     _speedMap;
    RosterSpeedProfile*  _speedProfile;
//    /*final*/ ReentrantLock _lock = new ReentrantLock();
    bool _debug;

    /*private*/ void setSpeedStepMode(int step);
    QMutex mutex;
    Logger* log;
    /*private*/ float modifySpeed(float s, QString sType);
    /*private*/ void setSpeed(float speed);
    /*private*/ void notify();
    /*private*/ float getThrottleFactor(float speedStep);

protected:
    /*protected*/ Sensor* getWaitSensor();
    /*synchronized*/ /*protected*/ void setWaitforClear(bool set);
    /*protected*/ QString minSpeedType(QString speed1, QString speed2);
    /*protected*/ void rampSpeedTo(QString endSpeedType);
    /*protected*/ float getDistanceTraveled(float speedSetting, QString speedtype, long time);
    /*protected*/ bool secondGreaterThanFirst(QString speed1, QString speed2);
    /*protected*/ DccThrottle* getThrottle();
    /*protected*/ float rampLengthForSpeedChange(float curSpeed, QString curSpeedType, QString toSpeedType);
    /*protected*/ void setCurrentCommandIndex(int idx);
    /*protected*/ long getTimeForDistance(float speed, float distance);
    /*synchronized*/ /*protected*/ void checkHalt();
    /*protected*/ void releaseThrottle();
    /*protected*/ float getSpeedSetting();
    /*protected*/ float getScriptSpeed();

friend class Warrant;
friend class CommandDelay;
};

#endif // ENGINEER_H
