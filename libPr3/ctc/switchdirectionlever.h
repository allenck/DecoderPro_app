#ifndef SWITCHDIRECTIONLEVER_H
#define SWITCHDIRECTIONLEVER_H

#include <QObject>
#include "nbhsensor.h"
class SwitchDirectionLever : public QObject
{
  Q_OBJECT
 public:
  /*public*/ SwitchDirectionLever(QString userIdentifier,
                              NBHSensor* switchLeverSensor, QObject *parent= nullptr);
  /*public*/ void removeAllListeners();
  /*public*/ NBHSensor* getSwitchLeverSensor();
  /*public*/ int getPresentState();

 signals:

 public slots:

 private:
  /*private*/ NBHSensor* _mSwitchLeverSensor;

};

#endif // SWITCHDIRECTIONLEVER_H
