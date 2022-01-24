#ifndef CALLONDATA_H
#define CALLONDATA_H

#include <QObject>
#include "namedbeanhandle.h"

class Block;
class NBHSignal;
class NBHSensor;
class CallOnData : public QObject
{
  Q_OBJECT
 public:
  explicit CallOnData(QObject *parent = nullptr);
  /*public*/ NBHSignal* _mExternalSignal;
  /*public*/ QString _mSignalFacingDirection;
  /*public*/ QString _mSignalAspectToDisplay;
  /*public*/ NBHSensor* _mCalledOnExternalSensor;
  /*public*/ NamedBeanHandle<Block*>* _mExternalBlock;
  /*public*/ QList<NBHSensor*>* _mSwitchIndicators;      // Up to 6 entries
  /*public*/ QList<QString> _mSwitchIndicatorNames;     // Temporary names during XML loading
  /*public*/ QString toString();

 signals:

 public slots:
};

#endif // CALLONDATA_H
