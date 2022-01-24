#include "trafficlockingdata.h"
#include "loggerfactory.h"
#include "frmtrl_rules.h"
#include "topologyinfo.h"
#include "commonsubs.h"
#include "nbhsensor.h"
#include "nbhsignal.h"

/**
 * This describes one traffic locking rule.
 * <p>
 * The TRLSwitch sub-class contains switch, alignment and ID values.
 * <p>
 * The list of traffic locking rules for each OS section are in the
 * _mTRL_LeftTrafficLockingRules and _mTRL_RightTrafficLockingRuless variable
 * in {@link CodeButtonHandlerData}.
 * @author Dave Sand Copyright (C) 2020
 */
// /*public*/ class TrafficLockingData {

    /*public*/ TrafficLockingData::TrafficLockingData(QObject *parent) : QObject(parent)
    {
    }

    /**
     * Constructor to take a TopologyInfo entry and create a properly formed "this".
     *
     * @param ruleNumber    Rule # (just an integer, starting with 1)
     * @param destinationSignalMast String representation of the destination signal mast so user can see on the form.
     * @param topologyInfo  Source of data.
     */
    /*public*/ TrafficLockingData::TrafficLockingData(int ruleNumber, QString destinationSignalMast, TopologyInfo* topologyInfo, QObject *parent ) {
//         Note:  The Topology process needs to updated.  It needs to create this class for each
//         row and update the appropriate instance of CodeButtonHandleData.
        _mUserRuleNumber = FrmTRL_Rules::getRuleNumberString(ruleNumber);
        _mRuleEnabled = FrmTRL_Rules::getRuleEnabledString();
        _mDestinationSignalOrComment = topologyInfo->getDestinationSignalMast();

        _mSwitchAlignments = new QList<TRLSwitch*>();
        for (int i = 0; i < 5; i++) {
            if (topologyInfo->getOSSectionText(i) != "") {
                int intID;
                bool ok;
                    intID = (topologyInfo->getUniqueID(i).toInt(&ok));
                if(ok) {
                    log->warn(tr("TrafficLockingData format exception: id = %1").arg(topologyInfo->getUniqueID(i)));
                    intID = 0;
                }
               _mSwitchAlignments->append(new TRLSwitch(topologyInfo->getOSSectionText(i), topologyInfo->getNormalReversed(i), intID));
            }
        }

        _mOccupancyExternalSensors = new QList<NBHSensor*>();
        for (int i = 0; i < 9; i++) {
            QString sensorName = topologyInfo->getSensorDisplayName(i);
            NBHSensor* sensor = CommonSubs::getNBHSensor(sensorName, false);
            if (sensor != nullptr && sensor->valid()) {
                _mOccupancyExternalSensors->append(sensor);
            }
        }

        _mOptionalExternalSensors = new QList<NBHSensor*>();
    }

    /**
     * Create a list of occupancy sensors with 9 entries. Unused entries will be set to a dummy NBHSensor.
     * @return a list of occupancy sensors.
     */
    /*public*/ QList<NBHSensor*>* TrafficLockingData::getOccupancySensors() {
        NBHSensor* dummy = new NBHSensor("TrafficLockingData", "", "", "", true);  // NOI18N
        QVector<NBHSensor*> occupancyArray = QVector<NBHSensor*>(9,dummy);
        //Arrays.fill(occupancyArray, dummy);
        QList<NBHSensor*>* occupancyList =  new QList<NBHSensor*>((occupancyArray.toList()));
        for (int index = 0; index < _mOccupancyExternalSensors->size(); index++) {
            occupancyList->replace(index, _mOccupancyExternalSensors->at(index));
        }
        return occupancyList;
    }

    /**
     * Create a list of optional sensors with 2 entries. Unused entries will be set to a dummy NBHSensor.
     * @return a list of optional sensors.
     */
    /*public*/ QList<NBHSensor*>* TrafficLockingData::getOptionalSensors() {
        NBHSensor* dummy = new NBHSensor("TrafficLockingData", "", "", "", true);  // NOI18N
        QVector<NBHSensor*> optionalArray = QVector<NBHSensor*>(2, dummy);
        //Arrays.fill(optionalArray, dummy);
        QList<NBHSensor*>* optionalList = new QList<NBHSensor*>(optionalArray.toList());
        for (int index = 0; index < _mOptionalExternalSensors->size(); index++) {
            optionalList->replace(index, _mOptionalExternalSensors->at(index));
        }
        return optionalList;
    }

    /**
     * Create a list of unique ids with 5 entries.  Unused entries are set to -1.
     * @return a list of ids
     */
    /*public*/ QList<int>* TrafficLockingData::getUniqueIDs() {
        QVector<int>* ids = new QVector<int>(5-1);
        //Arrays.fill(ids, -1);
        QList<int>* idList = new QList<int>(ids->toList());
        for (int index = 0; index < _mSwitchAlignments->size(); index++) {
            idList->replace(index, _mSwitchAlignments->at(index)->_mUniqueID);
        }
        return idList;
    }

    /**
     * Create a list of alignments with 5 entries.  Unused entries are to to Normal.
     * @return a list of alignments
     */
    /*public*/ QList<QString> TrafficLockingData::getAlignments() {
        QVector<QString> alignment = QVector<QString>(5, tr("Normal"));
        //Arrays.fill(alignment, Bundle.getMessage("TLE_Normal"));    // NOI18N
        QList<QString> alignmentList = QList<QString>(alignment.toList());
        for (int index = 0; index < _mSwitchAlignments->size(); index++) {
            alignmentList.replace(index, _mSwitchAlignments->at(index)->_mSwitchAlignment);
        }
        return alignmentList;
    }

    //@Override
    /*public*/ QString TrafficLockingData::toString() {
        QString formattedString = QString("%1,%2,%3").arg(
                _mUserRuleNumber != "" ? _mUserRuleNumber : "").arg(
                _mRuleEnabled != "" ? _mRuleEnabled : "").arg(
                _mDestinationSignalOrComment != "" ? _mDestinationSignalOrComment : "");
        QString buildString = formattedString;
        //_mSwitchAlignments.forEach(tlrSw ->
        foreach(TRLSwitch* tlrSw, *_mSwitchAlignments)
        {
            buildString.append(",");
            buildString.append(tlrSw->_mUserText);
            buildString.append(",");
            buildString.append(tlrSw->_mSwitchAlignment);
            buildString.append(",");
            buildString.append(tlrSw->_mUniqueID);
        }//);
        //_mOccupancyExternalSensors.forEach(sw ->
        foreach(NBHSensor* sw, *_mOccupancyExternalSensors)
        {
            buildString.append(",");
            buildString.append(sw->getHandleName());
        }//);
        //_mOptionalExternalSensors.forEach(sw -> {
        foreach(NBHSensor* sw, *_mOptionalExternalSensors)
        {
            buildString.append(",");
            buildString.append(sw->getHandleName());
        }//);
        return buildString/*.toString()*/;
    }

    /*private*/ /*static*/ /*final*/ Logger* TrafficLockingData::log = LoggerFactory::getLogger("TrafficLockingData");
