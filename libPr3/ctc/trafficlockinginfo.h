#ifndef TRAFFICLOCKINGINFO_H
#define TRAFFICLOCKINGINFO_H

#include <QObject>
#include "lockedroute.h"

class TrafficLockingInfo : public QObject
{
  Q_OBJECT
 public:
  /*public*/ bool      _mReturnStatus;     // JUST a return status, no relation to:
  /*public*/ LockedRoute*  _mLockedRoute;      // The locked route object or null if not available.
  explicit TrafficLockingInfo(bool returnStatus, QObject *parent = nullptr);

 signals:

 public slots:
};

#endif // TRAFFICLOCKINGINFO_H
