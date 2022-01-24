#ifndef SWITCHINDICATORSROUTE_H
#define SWITCHINDICATORSROUTE_H

#include <QObject>
#include "nbhsensor.h"

class SwitchIndicatorsRoute : public QObject
{
  Q_OBJECT
 public:
  /*public*/ SwitchIndicatorsRoute(   QString module, QString userIdentifier, QString parameter,
                                  QString switchIndicator1,
                                  QString switchIndicator2,
                                  QString switchIndicator3,
                                  QString switchIndicator4,
                                  QString switchIndicator5,
                                  QString switchIndicator6, QObject *parent= nullptr);

  /*public*/ SwitchIndicatorsRoute(NBHSensor* switchIndicator1, NBHSensor* switchIndicator2, NBHSensor* switchIndicator3, NBHSensor* switchIndicator4, NBHSensor* switchIndicator5, NBHSensor* switchIndicator6,QObject *parent = nullptr);
  /*public*/ SwitchIndicatorsRoute(QList<NBHSensor*>* switchIndicators,  QObject *parent= nullptr);
  /*public*/ bool isRouteSelected();

 signals:

 public slots:

 private:
  /*private*/ /*final*/ NBHSensor* _mSwitchIndicator1;
  /*private*/ /*final*/ NBHSensor* _mSwitchIndicator2;
  /*private*/ /*final*/ NBHSensor* _mSwitchIndicator3;
  /*private*/ /*final*/ NBHSensor* _mSwitchIndicator4;
  /*private*/ /*final*/ NBHSensor* _mSwitchIndicator5;
  /*private*/ /*final*/ NBHSensor* _mSwitchIndicator6;
  /*private*/ bool isSwitchIndicatorLit(NBHSensor* sensor);

};

#endif // SWITCHINDICATORSROUTE_H
