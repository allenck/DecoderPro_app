#ifndef TRAFFICLOCKING_H
#define TRAFFICLOCKING_H

#include <QObject>
#include "trafficlockingdata.h"
#include "lockedroutesmanager.h"
#include "codebuttonhandler.h"
#include "trafficlockinginfo.h"
#include "switchindicatorsroute.h"

//class TrafficLockingRecord;
class TrafficLocking : public QObject
{
  Q_OBJECT
  /*private*/ /*static*/ class TrafficLockingRecord {

      /*private*/ /*final*/ SwitchIndicatorsRoute* _mSwitchIndicatorsRoute;
      /*private*/ /*final*/ NBHSensor* _mOccupancyExternalSensor1;
      /*private*/ /*final*/ NBHSensor* _mOccupancyExternalSensor2;
      /*private*/ /*final*/ NBHSensor* _mOccupancyExternalSensor3;
      /*private*/ /*final*/ NBHSensor* _mOccupancyExternalSensor4;
      /*private*/ /*final*/ NBHSensor* _mOccupancyExternalSensor5;
      /*private*/ /*final*/ NBHSensor* _mOccupancyExternalSensor6;
      /*private*/ /*final*/ NBHSensor* _mOccupancyExternalSensor7;
      /*private*/ /*final*/ NBHSensor* _mOccupancyExternalSensor8;
      /*private*/ /*final*/ NBHSensor* _mOccupancyExternalSensor9;
      /*private*/ /*final*/ NBHSensor* _mOptionalSensor1;
      /*private*/ /*final*/ NBHSensor* _mOptionalSensor2;
      /*private*/ /*final*/ bool _mRuleEnabled;

      /*public*/ TrafficLockingRecord(QString userIdentifier,
                                  QString parameter,
                                  NBHSensor* switchIndicator1,
                                  NBHSensor* switchIndicator2,
                                  NBHSensor* switchIndicator3,
                                  NBHSensor* switchIndicator4,
                                  NBHSensor* switchIndicator5,
                                  NBHSensor* occupancyExternalSensor1,
                                  NBHSensor* occupancyExternalSensor2,
                                  NBHSensor* occupancyExternalSensor3,
                                  NBHSensor* occupancyExternalSensor4,
                                  NBHSensor* occupancyExternalSensor5,
                                  NBHSensor* occupancyExternalSensor6,
                                  NBHSensor* occupancyExternalSensor7,
                                  NBHSensor* occupancyExternalSensor8,
                                  NBHSensor* occupancyExternalSensor9,
                                  NBHSensor* optionalSensor1,
                                  NBHSensor* optionalSensor2,
                                  QString ruleEnabled) {
          _mSwitchIndicatorsRoute = new SwitchIndicatorsRoute(switchIndicator1, switchIndicator2, switchIndicator3, switchIndicator4, switchIndicator5, nullptr);
          _mOccupancyExternalSensor1 = occupancyExternalSensor1;
          _mOccupancyExternalSensor2 = occupancyExternalSensor2;
          _mOccupancyExternalSensor3 = occupancyExternalSensor3;
          _mOccupancyExternalSensor4 = occupancyExternalSensor4;
          _mOccupancyExternalSensor5 = occupancyExternalSensor5;
          _mOccupancyExternalSensor6 = occupancyExternalSensor6;
          _mOccupancyExternalSensor7 = occupancyExternalSensor7;
          _mOccupancyExternalSensor8 = occupancyExternalSensor8;
          _mOccupancyExternalSensor9 = occupancyExternalSensor9;
          _mOptionalSensor1 = optionalSensor1;
          _mOptionalSensor2 = optionalSensor2;
          _mRuleEnabled = ruleEnabled != (QString("Disabled")); // NOI18N  Any problem, default is ENABLED!
      }

      /*public*/ bool isEnabled() { return _mRuleEnabled; }
      /*public*/ bool isValid(bool fleetingEnabled) {
          if (!_mRuleEnabled) return false;    // If disabled, treat as invalid so we skip this rule and try the next rule.

          if (!_mSwitchIndicatorsRoute->isRouteSelected()
          || !isOptionalSensorActive(_mOptionalSensor1)
          || !isOptionalSensorActive(_mOptionalSensor2)) return false;
          return true;
      }

//  Put all non null and valid OCCUPANCY NBHSensor's in a HashSet and return it (the "ROUTE"!) for use by LockedRoutesManager.
      /*public*/ QSet<Sensor*> getOccupancySensors() {
          QSet<Sensor*> returnValue = QSet<Sensor*>();
          if (_mOccupancyExternalSensor1 != nullptr && _mOccupancyExternalSensor1->valid()) returnValue.insert(_mOccupancyExternalSensor1->getBean());
          if (_mOccupancyExternalSensor2 != nullptr && _mOccupancyExternalSensor2->valid()) returnValue.insert(_mOccupancyExternalSensor2->getBean());
          if (_mOccupancyExternalSensor3 != nullptr && _mOccupancyExternalSensor3->valid()) returnValue.insert(_mOccupancyExternalSensor3->getBean());
          if (_mOccupancyExternalSensor4 != nullptr && _mOccupancyExternalSensor4->valid()) returnValue.insert(_mOccupancyExternalSensor4->getBean());
          if (_mOccupancyExternalSensor5 != nullptr && _mOccupancyExternalSensor5->valid()) returnValue.insert(_mOccupancyExternalSensor5->getBean());
          if (_mOccupancyExternalSensor6 != nullptr && _mOccupancyExternalSensor6->valid()) returnValue.insert(_mOccupancyExternalSensor6->getBean());
          if (_mOccupancyExternalSensor7 != nullptr && _mOccupancyExternalSensor7->valid()) returnValue.insert(_mOccupancyExternalSensor7->getBean());
          if (_mOccupancyExternalSensor8 != nullptr && _mOccupancyExternalSensor8->valid()) returnValue.insert(_mOccupancyExternalSensor8->getBean());
          if (_mOccupancyExternalSensor9 != nullptr && _mOccupancyExternalSensor9->valid()) returnValue.insert(_mOccupancyExternalSensor9->getBean());
          returnValue.remove(nullptr);   // Safety: Remove null entry if it exists (There will ONLY be one in a set!)
          return returnValue;
      }

//  Quick and Dirty Routine: If it doesn't exist, it's lit.  If it exists, ACTIVE = lit.  Can't use CTCMain.getSensorKnownState() because of this.
      /*private*/ bool isOptionalSensorActive(NBHSensor* sensor) {
          if (sensor->valid()) return sensor->getKnownState() == Sensor::ACTIVE;
          return true;    // Doesn't exist.
      }

   friend class TrafficLocking;
  };public:
  /*public*/ TrafficLocking(QString userIdentifier, QList<TrafficLockingData *> *_mTRL_LeftTrafficLockingRules,
                            QList<TrafficLockingData*>* _mTRL_RightTrafficLockingRules,
                            LockedRoutesManager* lockedRoutesManager, QObject *parent=nullptr);
  /*public*/ void removeAllListeners();
  /*public*/ void fileReadComplete(QMap<int, CodeButtonHandler*> cbHashMap,QMap<int, SwitchDirectionIndicators*> swdiHashMap);


 signals:

 public slots:

 private:
  static Logger* log;
  /*private*/ /*final*/ QList<TrafficLockingRecord*>* _mLeftTrafficLockingRulesArrayList = new QList<TrafficLockingRecord*>();
  /*private*/ /*final*/ QList<TrafficLockingRecord*>* _mRightTrafficLockingRulesArrayList = new QList<TrafficLockingRecord*>();
  /*private*/ /*final*/ QString _mUserIdentifier;
  /*private*/ /*final*/ QList<TrafficLockingData*>* _mLeftTrafficLockingRulesList;
  /*private*/ /*final*/ QList<TrafficLockingData*>* _mRightTrafficLockingRulesList;
  /*private*/ /*final*/ LockedRoutesManager* _mLockedRoutesManager;
  /*private*/ bool isOptionalSensorActive(NBHSensor* sensor);
  /*private*/ void addAllTrafficLockingEntries(QString                           userIdentifier,
                                              QList<TrafficLockingData*>*            trafficLockingRulesList,
                                              QString                               parameter,
                                              QMap<int, CodeButtonHandler*>         cbHashMap,
                                              QMap<int, SwitchDirectionIndicators*> swdiHashMap,
                                              QList<TrafficLockingRecord *> *trafficLockingRecordsQList); // <- Output
  /*public*/ TrafficLockingInfo* valid(int presentSignalDirectionLever, bool fleetingEnabled);
  /*private*/ TrafficLockingInfo* validForTraffic(QList<TrafficLockingRecord *> *trafficLockingRecordList, bool rightTraffic, bool fleetingEnabled);
  /*private*/ NBHSensor* getSwitchDirectionIndicatorSensor(int uniqueID, QString switchAlignment, QMap<int, SwitchDirectionIndicators*> swdiHashMap);

  friend class CodeButtonHandler;
};

#endif // TRAFFICLOCKING_H
