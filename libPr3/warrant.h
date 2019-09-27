#ifndef WARRANT_H
#define WARRANT_H
#include "abstractnamedbean.h"
#include "exceptions.h"
#include "engineer.h"
#include "libPr3_global.h"

class SpeedUtil;
class CommandDelay;
class BlockSpeedInfo;
//class Calibrater;
class RosterEntry;
class DccThrottle;
class SignalSpeedMap;
class Engineer;
class OBlock;
class LearnThrottleFrame;
class DccLocoAddress;
class ThrottleSetting;
class BlockOrder;
class LIBPR3SHARED_EXPORT Warrant : public AbstractNamedBean
{
    Q_OBJECT
public:
   //explicit Warrant(QObject *parent = 0);
    /*public*/ Warrant(QString sName, QString uName, QObject *parent = 0);
    // Throttle modes
    enum MODES
    {
     MODE_NONE 	= 0,
     MODE_LEARN 	= 1,	// Record command list
     MODE_RUN 	= 2,	// Autorun (playback) command list
     MODE_MANUAL = 3	// block detection/reservation for manually run train
    };
    static QString modeName(int i);
    // control states
    enum STATES
    {
     STOP =0,
     HALT = 1,
     RESUME = 2,
     ABORT = 3,
     RETRY = 4,
     ESTOP = 5,
     RAMP_HALT = 6,
     RUNNING = 7,
     SPEED_RESTRICTED = 8,
     WAIT_FOR_CLEAR = 9,
     WAIT_FOR_SENSOR = 10,
     WAIT_FOR_TRAIN = 11,
     WAIT_FOR_DELAYED_START = 12,
     LEARNING = 13,
     STOP_PENDING = 14,
     RAMPING_UP = 15,
     DEBUG = 7
    };
    enum POSITIONS
    {
     // Estimated positions of the train in the block it occupies
     BEG    = 1,
     MID    = 2,
     END    = 3
    };
    /*public*/ static /*final*/ QString Stop;// = "Stop";   // NOI18N
    /*public*/ static /*final*/ QString EStop;// = "EStop";     // NOI18N
    /*public*/ static /*final*/ QString Normal;// = "Normal";   // NOI18N
    /*public*/ static /*final*/ QString Clear;// = "Clear";     // NOI18N

    /*public*/ /*final*/ static SignalSpeedMap* getSpeedMap();
    /*public*/ int getState() ;
    /*public*/ void setState(int state);
    /*public*/ SpeedUtil* getSpeedUtil();
    /*public*/ void setSpeedUtil(SpeedUtil* su);
    /*public*/ QList<BlockOrder*>* getBlockOrders();
    /*public*/ void addBlockOrder(BlockOrder* order);
    /*public*/ BlockOrder* getfirstOrder();
    /*public*/ BlockOrder* getLastOrder();
    /*public*/ BlockOrder* getViaOrder();
    /*public*/ void setViaOrder(BlockOrder* order);
    /*public*/ BlockOrder* getAvoidOrder();
    /*public*/ void setAvoidOrder(BlockOrder* order);
    /*public*/ BlockOrder* getCurrentBlockOrder();
    /*public*/ int getCurrentOrderIndex();
    /*public*/ QList <ThrottleSetting*>* getThrottleCommands();
    /*public*/ void setThrottleCommands(QList<ThrottleSetting*> list);
    /*public*/ void addThrottleCommand(ThrottleSetting* ts);
    /*public*/ QString getTrainName();
    /*public*/ void setTrainName(QString name) ;
    /*public*/ QString getTrainId();
    /*public*/ bool setTrainId(QString id);
    /*public*/ DccLocoAddress* getDccAddress();
    /*public*/ void setDccAddress(DccLocoAddress* address);
    /*public*/ bool setDccAddress(QString id);
    /*public*/ bool getRunBlind();
    /*public*/ void setRunBlind(bool runBlind);
    /*public*/ QString setThrottleFactor(QString sFactor);
    /******************************** state queries *****************/
    /*public*/ bool isAllocated();
    /*public*/ bool isTotalAllocated();
    /*public*/ bool hasRouteSet();
    /*public*/ bool routeIsFree();
    /*public*/ bool routeIsOccupied();

    /*public*/ int getRunMode();
    /*public*/ int getCurrentCommandIndex();
    /*public*/ QString setRunMode(int mode, DccLocoAddress* address,
                                 LearnThrottleFrame* student,
                                 QList <ThrottleSetting*>* commands, bool runBlind);
    /*public*/ bool controlRunTrain(int idx);
    /*public*/ void notifyThrottleFound(DccThrottle* throttle);
    /*public*/ void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason);
    /*public*/ QString allocateRoute(QList <BlockOrder*>* orders);
    /*public*/ void deAllocate();
    /*public*/ QString setRoute(int delay, QList <BlockOrder*>* orders);
    /*public*/ QString checkRoute();
    /*public*/ QString checkForContinuation();
    /*public*/ QString checkStartBlock(int mode);
    /*public*/ void stopWarrant(bool abort);
    /*public*/ void setBlockOrders(QList<BlockOrder*>* orders);
    /*public*/ QString setRoute(int delay, QList<BlockOrder*> orders);
    /*public*/ QString getCurrentBlockName();

signals:
//    void propertyChange(PropertyChangeEvent*);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
    /*private*/ QList <BlockOrder*>* _savedOrders;// = new ArrayList <BlockOrder>();
    /*private*/ BlockOrder* _viaOrder;
    /*private*/ BlockOrder* _avoidOrder;
    /*private*/ QList <ThrottleSetting*>* _throttleCommands;// = new ArrayList <ThrottleSetting>();
    /*private*/ QString _trainName;      // User train name for icon
    /*private*/ QString _trainId;        // Roster Id
    /*private*/ DccLocoAddress* _dccAddress;
    /*private*/ bool _runBlind;              // don't use block detection
    bool _debug;

    // transient members
    /*private*/ QList <BlockOrder*>* _orders;          // temp orders used in run mode
    /*private*/ LearnThrottleFrame* _student;        // need to callback learning throttle in learn mode
    /*private*/ bool _delayStart;				// allows start block unoccupied and wait for train
    /*private*/ int     _idxCurrentOrder;       // Index of block at head of train (if running)
    /*private*/ int     _idxLastOrder;          // Index of block at tail of train just left
    /*private*/ QString  _curSpeedType;          // name of last moving speed, i.e. never "Stop"
    /*private*/ int     _idxSpeedChange;        // Index of last BlockOrder where slower speed changes were scheduled
    /*private*/ QMap<QString, BlockSpeedInfo*> _speedTimeMap;          // map max speeds and occupation times of each block in route
//    private String _exitSpeed;            // name of speed to exit the "protected" block

    /*private*/ int     _runMode;
    /*private*/ Engineer* _engineer;         // thread that runs the train
    /*private*/ bool _allocated;         // initial Blocks of _orders have been allocated
    /*private*/ bool _totalAllocated;    // All Blocks of _orders have been allocated
    /*private*/ bool _routeSet;          // all allocated Blocks of _orders have paths set for route
    /*private*/ OBlock*  _stoppingBlock;     // Block allocated to another warrant or a rouge train
    /*private*/ NamedBean* _stoppingSignal;  // Signal stopping train movement
    /*private*/ OBlock* _shareTOBlock;       // Block in another warrant that controls a turnout in this block
    /*private*/ QString _message;            // last message returned from an action
//    /*private*/ Calibrater* _calibrater;     // Calibrates throttle speed factor
    RosterEntry*     _train;

    /*private*/ static SignalSpeedMap* _speedMap;
    /*private*/ int getBlockStateAt(int idx);
    /*private*/ QString acquireThrottle(DccLocoAddress* address);
    /*private*/ bool checkStoppingBlock();
    /*private*/ long getSpeedChangeWait(int index);
    /*private*/ QString getCurrentSpeedAt(int index);
    /*private*/ bool allocateNextBlock(OBlock* block);
    /*private*/ QString getNextSpeed();
    /*private*/ void checkShareTOBlock();
    /*private*/ void setStoppingBlock(OBlock* block);
    /*private*/ void restart();
    /*private*/ void getBlockSpeedTimes();
    /*private*/ float getLength(BlockOrder* blkOrder);
    /*private*/ QString getMinSpeedType(BlockOrder* blkOrder, QString nextSpeedType) ;
    /*private*/ bool moveIntoNextBlock(int position);
    /*private*/ QString getPermissibleSpeedAt(BlockOrder* bo);
    /*private*/ bool allocateNextBlock(BlockOrder* bo);
    SpeedUtil* _speedUtil;
    /*private*/ QString getSpeedMessage(QString speedType);

    /*private*/ bool _waitForSignal; // train may not move until false
    /*private*/ bool _waitForBlock; // train may not move until false
    /*private*/ bool _waitForWarrant;
    // Crossovers typically have both switches controlled by one TO, although each switch is in a different block
    // At the origin and destination of warrants, TO's shared between warrants may set conflicting paths
    /*private*/ OBlock* _myShareBlock;   // block belonging to this warrant
    /*private*/ OBlock* _otherShareBlock;   // block belonging to another warrant
Logger* log;
protected:
    /*protected*/ bool _tempRunBlind;            // run mode flag
    /*protected*/ float _throttleFactor;// = 1.0f;
    /*protected*/ QList <ThrottleSetting*>* _commands;   // temp commands used in run mode
    /*protected*/ QString _currentSpeed;			// name of last moving speed, i.e. never "Stop"
    /*protected*/ QString _exitSpeed;			// name of speed to exit the "protected" block
    /*protected*/ QString getRoutePathInBlock(OBlock* block);
    /*protected*/ int getIndexOfBlock(OBlock* block, int startIdx);
    /*protected*/ int getIndexOfBlock(QString name, int startIdx);
    /*protected*/ BlockOrder* getBlockOrderAt(int index);
    /*protected*/ OBlock* getBlockAt(int idx);
    /*protected*/ void fireRunStatus(QString property, QVariant old, QVariant status);
    /*protected*/ QString getRunningMessage();
    /*protected*/ void startupWarrant();
    /*protected*/ QString checkStartBlock();
    /*protected*/ void goingActive(OBlock* block);
    /*protected*/ void goingInactive(OBlock* block);
    /*protected*/ void setShareTOBlock(OBlock* block);
    /*protected*/ QString getRunModeMessage();
    /*protected*/ static /*final*/ QStringList CNTRL_CMDS;// = {"Stop", "Halt", "Resume", "Abort", "Retry"};
    /*protected*/ static /*final*/ QStringList RUN_STATE;// = {"HaltStart", "atHalt", "Resume", "Aborted", "Retry",
//        "Running", "RestrictSpeed", "WaitingForClear", "WaitingForSensor", "RunningLate"};
    /*protected*/ void startTracker();
/*protected*/ void setOrders(QList<BlockOrder*>* orders) ;
/*protected*/ QList<BlockOrder*>* getOrders();
///*protected*/ void setCalibrater(Calibrater* c);
/*protected*/ RosterEntry* getRosterEntry();
/*protected*/ DccThrottle* getThrottle();
/*protected*/ bool isWaitingForSignal();
/*protected*/ bool isWaitingForClear() ;
/*protected*/ bool isWaitingForWarrant();
/*protected*/ Warrant* getBlockingWarrant();


friend class OBlock;
friend class Engineer;
friend class WarrantTableAction;
friend class WarrantTableModel;
friend class CommandDelay;
friend class WarrantTableFrame;
friend class TableFrame;
friend class WarrantFrame;
friend class WarrantManagerXml;
friend class CreateWarrantFrame;
friend class NXFrame;
friend class Calibrater;

};

class BlockSpeedInfo
{
    float entranceSpeed;
    float maxSpeed;
    float exitSpeed;
    long time;
    int firstIdx;
    int lastIdx;
    BlockSpeedInfo(float ens, float ms, float exs, long t, int fi, int li) {
        entranceSpeed = ens;
        maxSpeed = ms;
        exitSpeed = exs;
        time = t;
        firstIdx = fi;
        lastIdx = li;
    }
    float getEntranceSpeed() {
        return entranceSpeed;
    }
    float getMaxSpeed() {
        return maxSpeed;
    }
    float getExitSpeed() {
        return exitSpeed;
    }
    long getTime() {
        return time;
    }
    int getFirstIndex() {
        return firstIdx;
    }
    int getLastIndex() {
        return lastIdx;
    }
    friend class Warrant;
};

class CommandDelay : public QObject
{
Q_OBJECT
 QString nextSpeedType;
 long _startWait;// = 0;
 int _cmdIndex;
 Logger* log;
 Warrant* warrant;
public:
 CommandDelay(QString speedType, long startWait, int cmdIndex, Warrant* warrant);
public slots:
 /*public*/ void process();
signals:
 void finished();
};
#endif // WARRANT_H
