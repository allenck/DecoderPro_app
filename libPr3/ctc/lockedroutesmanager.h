#ifndef LOCKEDROUTESMANAGER_H
#define LOCKEDROUTESMANAGER_H

#include <QObject>
#include "lockedroute.h"

class Logger;
class LockedRoutesManager : public QObject
{
  Q_OBJECT
 public:
  explicit LockedRoutesManager(QObject *parent = nullptr);
  /*public*/ void clearAllLockedRoutes();
  /*public*/ bool checkRoute(QSet<Sensor*> sensors, QString osSectionDescription, QString ruleDescription);
  /*public*/ LockedRoute *checkRouteAndAllocateIfAvailable(QSet<Sensor*> sensors, QString osSectionDescription, QString ruleDescription, bool rightTraffic);
  /*public*/ void cancelLockedRoute(LockedRoute* lockedRoute);
  /*public*/ void removeAllListeners();
  void dumpAllRoutes();

 signals:

 public slots:

 private:
  static Logger* log;
  /*private*/ /*final*/ QList<LockedRoute*> _mArrayListOfLockedRoutes = QList<LockedRoute*>();
  /*private*/ LockedRoute* existingLockedRouteThatHasCommonSensors;
  /*private*/ LockedRoute* /*private*/CheckRoute(QSet<Sensor*> sensors, QString osSectionDescription, QString ruleDescription, bool checkTraffic, bool rightTraffic);
};

#endif // LOCKEDROUTESMANAGER_H
