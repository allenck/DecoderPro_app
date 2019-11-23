#ifndef SCWARRANT_H
#define SCWARRANT_H
#include "warrant.h"

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
 /*public*/ void notifyThrottleFound(DccThrottle* throttle);
 /*public*/ void setTrainDirection ();
 /*public*/ bool isNextBlockFreeAndAllocated();
 /*public*/ void getAndGetNotifiedFromNextSignal();
 /*public*/ void setSpeedFromNextSignal ();

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


protected:
 /*synchronized*/ /*protected*/ QString getRunningMessage();

};

#endif // SCWARRANT_H
