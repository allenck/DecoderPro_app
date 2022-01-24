#ifndef TRAFFICLOCKINGDATA_H
#define TRAFFICLOCKINGDATA_H

#include <QObject>

class TopologyInfo;
class NBHSensor;
class Logger;
class TrafficLockingData : public QObject
{
  Q_OBJECT
 public:
  /*public*/ /*static*/ class TRLSwitch {
   public:
      /*public*/ QString _mUserText;
      /*public*/ QString _mSwitchAlignment;
      /*public*/ int _mUniqueID;

      /*public*/ TRLSwitch(QString text, QString alignment, int uniqueID) {
          _mUserText = text;
          _mSwitchAlignment = alignment;
          _mUniqueID = uniqueID;
      }
    friend class TrafficLockingData;
  };
  explicit TrafficLockingData(QObject *parent = nullptr);
  ~TrafficLockingData() {}
  TrafficLockingData(const TrafficLockingData&) : QObject() {}
  TrafficLockingData(int ruleNumber, QString destinationSignalMast, TopologyInfo* topologyInfo, QObject *parent = nullptr);
  /*public*/ QString _mUserRuleNumber;
  /*public*/ QString _mRuleEnabled;
  /*public*/ QString _mDestinationSignalOrComment;
  /*public*/ QList<TrafficLockingData::TRLSwitch*>* _mSwitchAlignments;              // Up to 5 entries
  /*public*/ QList<NBHSensor*>* _mOccupancyExternalSensors;      // Up to 9 entries
  /*public*/ QList<NBHSensor*>* _mOptionalExternalSensors;       // Up to 2 entries
  /*public*/ QList<NBHSensor*>* getOccupancySensors();
  /*public*/ QList<NBHSensor*>* getOptionalSensors();
  /*public*/ QList<int>* getUniqueIDs();
  /*public*/ QList<QString> getAlignments();
  /*public*/ QString toString();

 signals:

 public slots:

 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(TrafficLockingData)
#endif // TRAFFICLOCKINGDATA_H
