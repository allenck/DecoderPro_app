#ifndef FLEETING_H
#define FLEETING_H

#include <QObject>
#include "nbhsensor.h"

class Fleeting : public QObject
{
  Q_OBJECT
 public:
  /*public*/ Fleeting (NBHSensor* fleetingToggleInternalSensor, bool defaultFleetingEnabled, QObject *parent= nullptr);
  /*public*/ void removeAllListeners();
  /*public*/ bool isFleetingEnabled();

 signals:

 public slots:

 private:
  /*private*/ /*final*/ NBHSensor* _mFleetingToggleInternalSensor;
  /*private*/ /*final*/ bool _mDefaultFleetingEnabled;

};

#endif // FLEETING_H
