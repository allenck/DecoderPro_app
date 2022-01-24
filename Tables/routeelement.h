#ifndef ROUTEELEMENT_H
#define ROUTEELEMENT_H

#include <QObject>
#include "sensor.h"
#include "turnout.h"
#include "route.h"

class RouteElement : public QObject
{
  Q_OBJECT
 public:
  explicit     RouteElement(QString sysName, QString userName, QObject* parent= nullptr);
  QString getSysName();
  QString getUserName();
  bool isIncluded();
  QString getDisplayName();
  void setIncluded(bool include);
  /*abstract*/virtual  QString getSetToState() = 0;

  /*abstract*/ virtual void setSetToState(QString state) = 0;
  int getState();
  void setState(int state);


 signals:

 public slots:

 private:
  /*private*/ /*final*/ QString _sysName;
  /*private*/ /*final*/ QString _userName;
  /*private*/ bool _included;
  int _setToState;

  friend class RouteTurnout;
  friend class RouteSensor;
};

#endif // ROUTEELEMENT_H
