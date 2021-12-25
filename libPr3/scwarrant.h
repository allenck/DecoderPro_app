#ifndef SCWARRANT_H
#define SCWARRANT_H
#include "warrant.h"

class SCTrainRunner;
class SCWarrant : public Warrant
{
 Q_OBJECT
public:
 /*public*/ SCWarrant(QString sName, QString uName, long TTP, QObject *parent = nullptr);
 /*public*/ static /*final*/ float SPEED_STOP;// = 0.0f;
 /*public*/ static /*final*/ float SPEED_TO_PLATFORM;// = 0.2f;
 /*public*/ static /*final*/ float SPEED_UNSIGNALLED;// = 0.4f;
 /*public*/ long getTimeToPlatform();
 /*public*/ void setTimeToPlatform(long TTP);
 /*public*/ void setForward(bool set);
 /*public*/ bool getForward();
 /*public*/ void setSpeedFactor(float factor);
 /*public*/ float getSpeedFactor();
 /*public*/ QString setRoute(bool delay, QList<BlockOrder*>* orders) override;
 /*public*/ bool isRouteFree();
 /*public*/ void notifyThrottleFound(DccThrottle* throttle)override;
 /*public*/ void setTrainDirection ();
 /*public*/ bool isNextBlockFreeAndAllocated();
 /*public*/ void getAndGetNotifiedFromNextSignal();
 /*public*/ void setSpeedFromNextSignal ();
  /*synchronized*/ /*public*/ void stopWarrant(bool abort);
  /*public*/ bool equals(QObject *obj)override;
  /*public*/ uint hashCode()override;

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* evt)override;

private:
 static Logger* log;
 /*private*/ NamedBean* _nextSignal = nullptr; // The signal that we are currently looking at to determine speed.
 /*private*/ long timeToPlatform = 500;
 /*private*/ float speedFactor = 0.8f;
 /*private*/ bool forward = true;
 /*private*/ /*final*/ bool _allowShallowAllocation = false;
 /*private*/ DccThrottle* _throttle = nullptr;
 float _maxBlockLength = 0;
 float getMaxBlockLength();
 void setMaxBlockLength();
 /*private*/ QString allocateStartBlock();
 bool allTurnoutsSet();
 bool isRouteAllocated();
 SignalSpeedMap* _speedMap;// = jmri.InstanceManager::getDefault(SignalSpeedMap.class);
 bool inStartBlock();
 bool approchingDestination();
 /*private*/ void emergencyStop();
 static /*LinkedBlockingQueue*/QLinkedList<SCWarrant*> waitToRunQ;// = LinkedBlockingQueue<>();


protected:
 /*synchronized*/ /*protected*/ QString getRunningMessage();
 /*protected*/ void runSignalControlledTrain ();
 /*protected*/ bool isStartBlockOccupied();
 /*synchronized*/ /*protected*/ void waitForStartblockToGetOccupied();
 /*protected*/ void allocateBlocksAndSetTurnouts(int startIndex);
 /*protected*/ void goingActive(OBlock* block);
 /*protected*/ void goingInactive(OBlock* block);
 /*protected*/ void deallocateUpToBlock(int idx);

 friend class SCTrainRunner;
};

/*private*/ class SCTrainRunner : public Runnable {
  Q_OBJECT
    SCWarrant* _warrant = nullptr;
 public:
    SCTrainRunner(SCWarrant* warrant) {
        _warrant = warrant;
    }

    /**
     * When not using shallow allocation, warrants will have to wait until the entire route
     * is free and allocated to that particular warrant, before strting to run the train.
     * This method uses the waitToRunQ to ensure that warrants do not just compete about
     * resources, but waits in line until their route is free and unallocated.
     */
    bool isItOurTurn();
    /*public*/ void run() override;
};

#endif // SCWARRANT_H
