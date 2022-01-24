#ifndef ROUTETURNOUT_H
#define ROUTETURNOUT_H
#include "routeelement.h"

class RouteTurnout : public RouteElement
{
  Q_OBJECT
 public:
  RouteTurnout(QString sysName, QString userName, QObject* parent = nullptr);
  QString getSetToState() override;
  void setSetToState(QString state) override;
 private:

};

#endif // ROUTETURNOUT_H
