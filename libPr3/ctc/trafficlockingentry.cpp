#include "trafficlockingentry.h"
#include "projectscommonsubs.h"
/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
///*public*/ class TrafficLockingEntry {
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::USER_RULE_NUMBER_INDEX = 0;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::RULE_ENABLED_INDEX = 1;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::DESTINATION_SIGNAL_OR_COMMENT_INDEX = 2;
//  Unused index 3 (was terminating O.S. section info)
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::USER_TEXT1_INDEX = 4;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::SWITCH_ALIGNMENT1_INDEX = 5;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::USER_TEXT2_INDEX = 6;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::SWITCH_ALIGNMENT2_INDEX = 7;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::USER_TEXT3_INDEX = 8;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::SWITCH_ALIGNMENT3_INDEX = 9;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::USER_TEXT4_INDEX = 10;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::SWITCH_ALIGNMENT4_INDEX = 11;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::USER_TEXT5_INDEX = 12;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::SWITCH_ALIGNMENT5_INDEX = 13;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OCCUPANCY_EXTERNAL_SENSOR1_INDEX  = 14;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OCCUPANCY_EXTERNAL_SENSOR2_INDEX  = 15;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OCCUPANCY_EXTERNAL_SENSOR3_INDEX  = 16;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OCCUPANCY_EXTERNAL_SENSOR4_INDEX  = 17;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OCCUPANCY_EXTERNAL_SENSOR5_INDEX  = 18;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OCCUPANCY_EXTERNAL_SENSOR6_INDEX  = 19;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OCCUPANCY_EXTERNAL_SENSOR7_INDEX  = 20;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OCCUPANCY_EXTERNAL_SENSOR8_INDEX  = 21;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OCCUPANCY_EXTERNAL_SENSOR9_INDEX  = 22;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OPTIONAL_EXTERNAL_SENSOR1_INDEX = 23;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::OPTIONAL_EXTERNAL_SENSOR2_INDEX = 24;
//  Computer maintained:
//  Unused index 25 (was terminating O.S. section info)
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::UNIQUE_ID1_INDEX = 26;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::UNIQUE_ID2_INDEX = 27;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::UNIQUE_ID3_INDEX = 28;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::UNIQUE_ID4_INDEX = 29;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::UNIQUE_ID5_INDEX = 30;
/*private*/ /*static*/ /*final*/ int TrafficLockingEntry::ARRAY_SIZE = 31;


    /*public*/ TrafficLockingEntry::TrafficLockingEntry(QString csvString, QObject *parent) : QObject(parent) {
         QList<QString> arrayListOfStrings = ProjectsCommonSubs::getFixedArrayListSizeFromCSV(csvString, ARRAY_SIZE);
        _mUserRuleNumber = arrayListOfStrings.value(USER_RULE_NUMBER_INDEX);
        _mRuleEnabled = arrayListOfStrings.value(RULE_ENABLED_INDEX);
        _mDestinationSignalOrComment = arrayListOfStrings.value(DESTINATION_SIGNAL_OR_COMMENT_INDEX);
        _mUserText1 = arrayListOfStrings.value(USER_TEXT1_INDEX);
        _mSwitchAlignment1 = arrayListOfStrings.value(SWITCH_ALIGNMENT1_INDEX);
        _mUserText2 = arrayListOfStrings.value(USER_TEXT2_INDEX);
        _mSwitchAlignment2 = arrayListOfStrings.value(SWITCH_ALIGNMENT2_INDEX);
        _mUserText3 = arrayListOfStrings.value(USER_TEXT3_INDEX);
        _mSwitchAlignment3 = arrayListOfStrings.value(SWITCH_ALIGNMENT3_INDEX);
        _mUserText4 = arrayListOfStrings.value(USER_TEXT4_INDEX);
        _mSwitchAlignment4 = arrayListOfStrings.value(SWITCH_ALIGNMENT4_INDEX);
        _mUserText5 = arrayListOfStrings.value(USER_TEXT5_INDEX);
        _mSwitchAlignment5 = arrayListOfStrings.value(SWITCH_ALIGNMENT5_INDEX);
        _mOccupancyExternalSensor1 = arrayListOfStrings.value(OCCUPANCY_EXTERNAL_SENSOR1_INDEX);
        _mOccupancyExternalSensor2 = arrayListOfStrings.value(OCCUPANCY_EXTERNAL_SENSOR2_INDEX);
        _mOccupancyExternalSensor3 = arrayListOfStrings.value(OCCUPANCY_EXTERNAL_SENSOR3_INDEX);
        _mOccupancyExternalSensor4 = arrayListOfStrings.value(OCCUPANCY_EXTERNAL_SENSOR4_INDEX);
        _mOccupancyExternalSensor5 = arrayListOfStrings.value(OCCUPANCY_EXTERNAL_SENSOR5_INDEX);
        _mOccupancyExternalSensor6 = arrayListOfStrings.value(OCCUPANCY_EXTERNAL_SENSOR6_INDEX);
        _mOccupancyExternalSensor7 = arrayListOfStrings.value(OCCUPANCY_EXTERNAL_SENSOR7_INDEX);
        _mOccupancyExternalSensor8 = arrayListOfStrings.value(OCCUPANCY_EXTERNAL_SENSOR8_INDEX);
        _mOccupancyExternalSensor9 = arrayListOfStrings.value(OCCUPANCY_EXTERNAL_SENSOR9_INDEX);
        _mOptionalExternalSensor1 = arrayListOfStrings.value(OPTIONAL_EXTERNAL_SENSOR1_INDEX);
        _mOptionalExternalSensor2 = arrayListOfStrings.value(OPTIONAL_EXTERNAL_SENSOR2_INDEX);
        _mUniqueID1 = arrayListOfStrings.value(UNIQUE_ID1_INDEX);
        _mUniqueID2 = arrayListOfStrings.value(UNIQUE_ID2_INDEX);
        _mUniqueID3 = arrayListOfStrings.value(UNIQUE_ID3_INDEX);
        _mUniqueID4 = arrayListOfStrings.value(UNIQUE_ID4_INDEX);
        _mUniqueID5 = arrayListOfStrings.value(UNIQUE_ID5_INDEX);
    }
