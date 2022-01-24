#ifndef CALLON_H
#define CALLON_H

#include <QObject>
#include "callondata.h"
#include "otherdata.h"
#include "signaldirectionindicatorsinterface.h"

class SignalDirectionIndicators;
class TrafficLockingInfo;
class LockedRoutesManager;
class NBHSensor;
class GroupingData;
class CallOn : public QObject
{
  Q_OBJECT
 public:
  /*public*/ CallOn(LockedRoutesManager* lockedRoutesManager, QString userIdentifier, NBHSensor* callOnToggleSensor, QList<CallOnData*> groupingsList, OtherData::SIGNAL_SYSTEM_TYPE signalSystemType, QObject* parent);
  /*public*/ void removeAllListeners();
  /*public*/ void resetToggle();
  /*public*/ TrafficLockingInfo* codeButtonPressed(QSet<Sensor*> sensors,
                                              QString userIdentifier,
                                              SignalDirectionIndicators* signalDirectionIndicatorsObject,
                                              int signalDirectionLever);


 signals:

 public slots:

 private:
  /*private*/ /*final*/ LockedRoutesManager* _mLockedRoutesManager;
  /*private*/ /*final*/ bool _mSignalHeadSelected;
  /*private*/ /*final*/ NBHSensor* _mCallOnToggleSensor;
  /*private*/ /*final*/ QList<GroupingData*> _mGroupingDataArrayList = QList<GroupingData*>();
  static /*private*/ int arrayFind(QStringList array, QString aString);
  /*private*/ QString convertFromForeignLanguageColor(QString foreignLanguageColor);

};

#endif // CALLON_H
