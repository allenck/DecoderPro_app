#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <QObject>
#include "ctcserialdata.h"
#include "topologyinfo.h"
#include "layoutblockmanager.h"

class SignalMastLogicManager;
class LayoutBlockManager;
class Topology : public QObject
{
  Q_OBJECT
 public:
  explicit Topology(QObject *parent = nullptr);
  /*public*/ Topology(CTCSerialData* cTCSerialData, QList<QString> OSSectionOccupiedExternalSensors, QString normal, QString reverse, QObject *parent = nullptr);
  /*public*/ bool isTopologyAvailable();
  /*public*/ QList<TopologyInfo*> getTrafficLockingRules(bool leftTraffic);
 signals:

 public slots:

 private:
  /*private*/ /*final*/ CTCSerialData* _mCTCSerialData;
  /*private*/ /*final*/ QString _mNormal;
  /*private*/ /*final*/ QString _mReverse;
  /*private*/ /*final*/ SignalMastLogicManager* _mSignalMastLogicManager = (SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager");
  /*private*/ /*final*/ LayoutBlockManager* _mLayoutBlockManager = (LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager");
  /*private*/ QList<Block*> _mStartingBlocks = QList<Block*>();
  /*private*/ void processDestinations(QList<TopologyInfo*> topologyInfos, SignalMastLogic* facingSignalMastLogic);
  /*private*/ void createRules(TopologyInfo* topologyInfo, SignalMastLogic* signalMastLogic, SignalMast* signalMast);
  /*private*/ bool isIntermediateSignalMast(SignalMast* signalMast);
  /*private*/ QList<int> getDirectionArrayListFrom(int direction);
  /*private*/ bool inSameDirectionGenerally(QList<int> possibleDirections, int direction);

};

#endif // TOPOLOGY_H
