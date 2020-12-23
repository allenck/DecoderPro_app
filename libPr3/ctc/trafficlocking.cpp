#include "trafficlocking.h"
#include "loggerfactory.h"
#include "switchindicatorsroute.h"
#include "instancemanager.h"
#include "ctcmain.h"
#include "nbhsensor.h"
#include "switchdirectionindicators.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */

// /*public*/ class TrafficLocking {
    /*private*/ /*final*/ /*static*/ Logger* TrafficLocking::log = LoggerFactory::getLogger("TrafficLocking");




    /*public*/ TrafficLocking::TrafficLocking(QString userIdentifier, QList<TrafficLockingData *>* _mTRL_LeftTrafficLockingRules, QList<TrafficLockingData *> *_mTRL_RightTrafficLockingRules,
                                              LockedRoutesManager* lockedRoutesManager, QObject* parent)
    {
        _mUserIdentifier = userIdentifier;                                      // Squirrel it
        _mLeftTrafficLockingRulesList = _mTRL_LeftTrafficLockingRules;      // away for later
        _mRightTrafficLockingRulesList = _mTRL_RightTrafficLockingRules;    // "fileReadComplete"
        _mLockedRoutesManager = lockedRoutesManager;
    }

    /*public*/ void TrafficLocking::removeAllListeners() {}   // None done.

//  Since the user may specify "forward referenced" O/S sections (i.e. an entry references an O.S. section that hasn't been read in and created yet),
//  we delay processing of everything until after the file has been completely read in.  Here we do the real work:
    /*public*/ void TrafficLocking::fileReadComplete(QMap<int, CodeButtonHandler*> cbHashMap, QMap<int, SwitchDirectionIndicators*> swdiHashMap) {
        addAllTrafficLockingEntries(_mUserIdentifier, _mLeftTrafficLockingRulesList, "leftTrafficLockingRulesList", cbHashMap, swdiHashMap, _mLeftTrafficLockingRulesArrayList);     // NOI18N
        addAllTrafficLockingEntries(_mUserIdentifier, _mRightTrafficLockingRulesList, "rightTrafficLockingRulesList", cbHashMap, swdiHashMap, _mRightTrafficLockingRulesArrayList);  // NOI18N
    }

    /*private*/ void TrafficLocking::addAllTrafficLockingEntries(QString                                                  userIdentifier,
                                                QList<TrafficLockingData *> *trafficLockingRulesList,
                                                QString                                parameter,
                                                QMap<int, CodeButtonHandler*>          cbHashMap,
                                                QMap<int, SwitchDirectionIndicators*>  swdiHashMap,
                                                QList<TrafficLockingRecord*>*           trafficLockingRecordsQList) {  // <- Output
        //trafficLockingRulesList.forEach(row ->
        foreach(TrafficLockingData* row, *trafficLockingRulesList)
        {
            // Convert TrafficLockingData into a set of fixed size QLists
            QList<NBHSensor*>* occupancySensors = row->getOccupancySensors();
            QList<NBHSensor*>* optionalSensors = row->getOptionalSensors();
            QList<int>* ids = row->getUniqueIDs();
            QList<QString> alignments = row->getAlignments();

            int osSection1UniqueID = ids->at(0);
            int osSection2UniqueID = ids->at(1);
            int osSection3UniqueID = ids->at(2);
            int osSection4UniqueID = ids->at(3);
            int osSection5UniqueID = ids->at(4);

            TrafficLockingRecord* trafficLockingRecord
                = new TrafficLockingRecord( userIdentifier,
                                            parameter,
                                            getSwitchDirectionIndicatorSensor(osSection1UniqueID, alignments.at(0), swdiHashMap),
                                            getSwitchDirectionIndicatorSensor(osSection2UniqueID, alignments.at(1), swdiHashMap),
                                            getSwitchDirectionIndicatorSensor(osSection3UniqueID, alignments.at(2), swdiHashMap),
                                            getSwitchDirectionIndicatorSensor(osSection4UniqueID, alignments.at(3), swdiHashMap),
                                            getSwitchDirectionIndicatorSensor(osSection5UniqueID, alignments.at(4), swdiHashMap),
                                            occupancySensors->at(0),
                                            occupancySensors->at(1),
                                            occupancySensors->at(2),
                                            occupancySensors->at(3),
                                            occupancySensors->at(4),
                                            occupancySensors->at(5),
                                            occupancySensors->at(6),
                                            occupancySensors->at(7),
                                            occupancySensors->at(8),
                                            optionalSensors->at(0),
                                            optionalSensors->at(1),
                                            row->_mRuleEnabled);
            if (!trafficLockingRecord->getOccupancySensors().isEmpty()) {
                trafficLockingRecordsQList->append(trafficLockingRecord);
            }
        }//);
    }

    /*public*/ TrafficLockingInfo* TrafficLocking::valid(int presentSignalDirectionLever, bool fleetingEnabled) {
        if (presentSignalDirectionLever == CTCConstants::LEFTTRAFFIC) return validForTraffic(_mLeftTrafficLockingRulesArrayList, false, fleetingEnabled);
        return validForTraffic(_mRightTrafficLockingRulesArrayList, true, fleetingEnabled);
    }

    /*private*/ TrafficLockingInfo* TrafficLocking::validForTraffic(QList<TrafficLockingRecord*>* trafficLockingRecordList, bool rightTraffic, bool fleetingEnabled) {
        TrafficLockingInfo* returnValue = new TrafficLockingInfo(true);          // ASSUME valid return status
        if (trafficLockingRecordList->isEmpty()) return returnValue; // No rules, OK all of the time.
//  If ALL are disabled, then treat as if nothing in there, always allow, otherwise NONE would be valid!
        bool anyEnabled = false;
        for (int index = 0; index < trafficLockingRecordList->size(); index++) {
            if (trafficLockingRecordList->at(index)->isEnabled()) { anyEnabled = true; break; }
        }
        if (!anyEnabled) return returnValue; // None enabled, always allow.

        for (int index = 0; index < trafficLockingRecordList->size(); index++) {
            TrafficLockingRecord* trafficLockingRecord = trafficLockingRecordList->at(index);
            if (trafficLockingRecord->isValid(fleetingEnabled)) {
//  Ah, we found a rule that matches the route.  See if that route
//  is in conflict with any other routes presently in effect:
                QString ruleNumber = QString::number(index+1);
                returnValue->_mLockedRoute = _mLockedRoutesManager->checkRouteAndAllocateIfAvailable(trafficLockingRecord->getOccupancySensors(), _mUserIdentifier, "Rule #" + ruleNumber, rightTraffic);
                if (returnValue->_mLockedRoute != nullptr) { // OK:
                    if (((CTCMain*)InstanceManager::getDefault("CTCMain"))->_mCTCDebug_TrafficLockingRuleTriggeredDisplayLoggingEnabled) log->info(tr("Rule %1 valid").arg(ruleNumber));
                    return returnValue;
                }
            }
        }
        returnValue->_mReturnStatus = false;
        return returnValue;
    }

    /*private*/ NBHSensor* TrafficLocking::getSwitchDirectionIndicatorSensor(int uniqueID, QString switchAlignment, QMap<int, SwitchDirectionIndicators*> swdiHashMap) {
        if (uniqueID < 0) return nullptr;
        bool isNormalAlignment = switchAlignment != (tr("Reverse"));  // NOI18N
        SwitchDirectionIndicators* switchDirectionIndicators = swdiHashMap.value(uniqueID);
        if (switchDirectionIndicators == nullptr) return nullptr;     // Safety, technically shouldn't happen....
        return switchDirectionIndicators->getProperIndicatorSensor(isNormalAlignment);
    }
