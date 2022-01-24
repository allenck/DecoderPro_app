#ifndef ROUTESENSOR_H
#define ROUTESENSOR_H
#include "routeelement.h"

class RouteSensor : public RouteElement
{
  Q_OBJECT
 public:
  RouteSensor(QString sysName, QString userName, QObject* parent = nullptr);
  QString getSetToState() override;
  void setSetToState(QString state) override;

 private:
  /*private*/ static /*final*/ QString SET_TO_ACTIVE;// =  tr("Set") + " " +  tr("SensorStateActive");
  /*private*/ static /*final*/ QString SET_TO_INACTIVE;// =  tr("Set") + " " +  tr("SensorStateInactive");

  /*private*/ static /*final*/ QString SET_TO_TOGGLE;// =  tr("Set") + " " +  tr("Toggle");
 static Logger* log;

};

#endif // ROUTESENSOR_H
