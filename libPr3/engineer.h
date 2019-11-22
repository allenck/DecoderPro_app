#ifndef ENGINEER_H
#define ENGINEER_H

#include <QThread>
#include <QMutex>
#include "logger.h"
#include "runnable.h"
#include "../libPref/rampdata.h"
#include <QWaitCondition>

class PropertyChangeEvent;
class SpeedUtil;
class ThrottleSetting;
class SignalSpeedMap;
class RosterSpeedProfile;
class ThrottleRamp;
class OBlock;
class Sensor;
class DccThrottle;
class Warrant;
class Engineer : public QObject
{
    Q_OBJECT
public:
    //explicit Engineer(QObject *parent = 0);
    Engineer(Warrant* warrant, DccThrottle* throttle, QObject *parent = 0);
    /*public*/ int getCurrentCommandIndex();
    /*synchronized*/ /*public*/ int getRunState();
    /*synchronized*/ /*public*/ void setHalt(bool halt);
    /*public*/ void stopRun(bool abort, bool turnOffFunctions);
    /*synchronized*/ /*public*/ void setStop(bool eStop, bool setHalt);

signals:
    void finished();
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
    /*public*/ void process();

private:
    int cmdBlockIdx = 0;
    /*private*/ int     _idxCurrentCommand;     // current throttle command
    /*private*/ QString _currentCommand;
    /*private*/ float   _speed;
    /*private*/ int _idxSkipToSpeedCommand;   // skip to this index to reset script when ramping
    /*private*/ float _normalSpeed = 0;       // current commanded throttle setting (unmodified)
    /*private*/ QString  _speedType;// = "Normal";
    /*private*/ qint64 et;    // actual elapsed time while waiting to do current command
    /*private*/ float _timeRatio = 1.0f;     // ratio to extend scripted time when speed is modified
    /*private*/ float   _minSpeed;// = 1.0f/127;
    /*private*/ bool _abort;// = false;
    /*private*/ bool _halt;// = false;  // halt/resume from user's control
    QWaitCondition atHalt;
    /*private*/ bool _stopPending = false;   // ramp slow down in progress
    /*private*/ bool _resumePending = false;   // ramp up to clear flags in progress
    /*private*/ bool _waitForClear;// = false;  // waits for signals/occupancy/allocation to clear
    QWaitCondition waitForClear;
    /*private*/ bool _waitForSync;// = false;  // waits for train to catch up to commands
    QWaitCondition waitForSync;
    QWaitCondition waitRampReady;
    /*private*/ bool _waitForSensor;// = false; // wait for sensor event
    /*private*/ bool _runOnET = false;   // Execute commands on ET only - do not synch
    /*private*/ bool _setRunOnET = false; // Need to delay _runOnET from the block that set it
    /*private*/ bool _speedOverride;// = false; // speed changing due to signal or occupancy
    /*private*/ int     _syncIdx;
    /*private*/ DccThrottle* _throttle = nullptr;
    /*private*/ Warrant* _warrant = nullptr;
    /*private*/ /*final*/ QList<ThrottleSetting*>* _commands = nullptr;
    /*private*/ Sensor* 	_waitSensor = nullptr;
    /*private*/ int		_sensorWaitState;
    /*private*/ ThrottleRamp* _ramp = nullptr;
//    /*final*/ ReentrantLock* _lock = new ReentrantLock(true);    // Ramp needs to block script speeds
    /*private*/ bool _atHalt = false;
    /*private*/ bool _atClear = false;
    /*private*/ /*final*/ SpeedUtil* _speedUtil;
    SignalSpeedMap*     _speedMap = nullptr;
    RosterSpeedProfile*  _speedProfile = nullptr;
//    /*final*/ ReentrantLock _lock = new ReentrantLock();
    bool _debug;

    /*private*/ void setStep(int step);
    /*private*/ void setSpeedStepMode(int step);
    QMutex mutex;
    QMutex _lock;
    static Logger* log;
    /*private*/ void setSpeed(float speed);
    /*private*/ void notify();
    /*private*/ float getThrottleFactor(float speedStep);
    /*private*/ void cancelRamp(bool die);
    /*private*/ void setFunction(int cmdNum, bool isSet);
    /*private*/ void setLockFunction(int cmdNum, bool isTrue);
    /*private*/ void setSensor(QString sensorName, QString act);
    /*private*/ void getSensor(QString sensorName, QString act);
    /*private*/ void clearSensor();
    /*private*/ void runWarrant(ThrottleSetting* ts);
    QString getFlags();
    ThrottleRamp* getRamp();
    /*private*/ void advanceToCommandIndex(int idx);
    /*private*/ void rampDone(bool stop, QString type);
    void notifyAll() {}
    /*private*/ bool setSpeedRatio(QString speedType);


protected:
    /*protected*/ Sensor* getWaitSensor();
    /*synchronized*/ /*protected*/ void setWaitforClear(bool set);
//    /*protected*/ QString minSpeedType(QString speed1, QString speed2);
    /*protected*/ void rampSpeedTo(QString endSpeedType, int endBlockIdx, bool useIndex);
//    /*protected*/ float getDistanceTraveled(float speedSetting, QString speedtype, long time);
//    /*protected*/ bool secondGreaterThanFirst(QString speed1, QString speed2);
//    /*protected*/ DccThrottle* getThrottle();
//    /*protected*/ float rampLengthForSpeedChange(float curSpeed, QString curSpeedType, QString toSpeedType);
//    /*protected*/ long getTimeForDistance(float speed, float distance);
    /*synchronized*/ /*protected*/ void checkHalt();
    /*protected*/ float getSpeedSetting();
    /*protected*/ float getScriptSpeed();
    /*protected*/ void setRunOnET(bool set);
    /*protected*/ bool getRunOnET();
    /*synchronized*/ /*protected*/ void clearWaitForSync();
    /*protected*/ void setSpeedToType(QString speedType);

friend class Warrant;
friend class CommandDelay;
friend class ThrottleRamp;
};

class ThrottleRamp : public QObject {
 Q_OBJECT
    QString endSpeedType;
    Engineer* _engineer;
    /*private*/ RampData* _rampData;
    /*private*/ QString _endSpeedType;
    /*private*/ int _endBlockIdx;   // index of block where down ramp ends - not used for up ramps.
    /*private*/ bool _useIndex;
    /*private*/ bool stop = false;   // aborts ramping
    bool ready = false;   // ready for call doRamp
    /*private*/ bool _die = false;    // kills ramp for good
    QMutex _lock;
public:
    ThrottleRamp(Engineer* _engineer);
    /*public*/ void doRamp();
    void notifyAll() {}
    void quit() {}
public slots:
    /*public*/ void process();
signals:
    void finished();
private:
    void quit(bool die);
    void setParameters(QString endSpeedType, int endBlockIdx, bool useIndex);
    RampData* getRampData ();
    QString getState() {return "??";}
    QMutex mutex;
    QWaitCondition waitRampSpeedTo;

 friend class Warrant;
 friend class Engineer;
};
#endif // ENGINEER_H
