#ifndef TRAFFICLOCKINGENTRY_H
#define TRAFFICLOCKINGENTRY_H

#include <QObject>

class TrafficLockingEntry : public QObject
{
  Q_OBJECT
 public:
  /*public*/ TrafficLockingEntry(QString csvString, QObject *parent = nullptr);
  /*public*/ QString _mUserRuleNumber;
  /*public*/ QString _mRuleEnabled;
  /*public*/ /*final*/ QString _mDestinationSignalOrComment;
  /*public*/ QString _mUserText1;
  /*public*/ /*final*/ QString _mSwitchAlignment1;
  /*public*/ QString _mUserText2;
  /*public*/ /*final*/ QString _mSwitchAlignment2;
  /*public*/ QString _mUserText3;
  /*public*/ /*final*/ QString _mSwitchAlignment3;
  /*public*/ QString _mUserText4;
  /*public*/ /*final*/ QString _mSwitchAlignment4;
  /*public*/ QString _mUserText5;
  /*public*/ /*final*/ QString _mSwitchAlignment5;
  /*public*/ /*final*/ QString _mOccupancyExternalSensor1;
  /*public*/ /*final*/ QString _mOccupancyExternalSensor2;
  /*public*/ /*final*/ QString _mOccupancyExternalSensor3;
  /*public*/ /*final*/ QString _mOccupancyExternalSensor4;
  /*public*/ /*final*/ QString _mOccupancyExternalSensor5;
  /*public*/ /*final*/ QString _mOccupancyExternalSensor6;
  /*public*/ /*final*/ QString _mOccupancyExternalSensor7;
  /*public*/ /*final*/ QString _mOccupancyExternalSensor8;
  /*public*/ /*final*/ QString _mOccupancyExternalSensor9;
  /*public*/ /*final*/ QString _mOptionalExternalSensor1;
  /*public*/ /*final*/ QString _mOptionalExternalSensor2;
  /*public*/ QString _mUniqueID1;
  /*public*/ QString _mUniqueID2;
  /*public*/ QString _mUniqueID3;
  /*public*/ QString _mUniqueID4;
  /*public*/ QString _mUniqueID5;

 signals:

 public slots:
 private:
  /*private*/ static /*final*/ int USER_RULE_NUMBER_INDEX;// = 0;
  /*private*/ static /*final*/ int RULE_ENABLED_INDEX;// = 1;
  /*private*/ static /*final*/ int DESTINATION_SIGNAL_OR_COMMENT_INDEX;// = 2;
//  Unused index 3 (was terminating O.S. section info)
  /*private*/ static /*final*/ int USER_TEXT1_INDEX;// = 4;
  /*private*/ static /*final*/ int SWITCH_ALIGNMENT1_INDEX;// = 5;
  /*private*/ static /*final*/ int USER_TEXT2_INDEX;// = 6;
  /*private*/ static /*final*/ int SWITCH_ALIGNMENT2_INDEX;// = 7;
  /*private*/ static /*final*/ int USER_TEXT3_INDEX;// = 8;
  /*private*/ static /*final*/ int SWITCH_ALIGNMENT3_INDEX;// = 9;
  /*private*/ static /*final*/ int USER_TEXT4_INDEX;// = 10;
  /*private*/ static /*final*/ int SWITCH_ALIGNMENT4_INDEX;// = 11;
  /*private*/ static /*final*/ int USER_TEXT5_INDEX;// = 12;
  /*private*/ static /*final*/ int SWITCH_ALIGNMENT5_INDEX;// = 13;
  /*private*/ static /*final*/ int OCCUPANCY_EXTERNAL_SENSOR1_INDEX ;// = 14;
  /*private*/ static /*final*/ int OCCUPANCY_EXTERNAL_SENSOR2_INDEX ;// = 15;
  /*private*/ static /*final*/ int OCCUPANCY_EXTERNAL_SENSOR3_INDEX ;// = 16;
  /*private*/ static /*final*/ int OCCUPANCY_EXTERNAL_SENSOR4_INDEX ;// = 17;
  /*private*/ static /*final*/ int OCCUPANCY_EXTERNAL_SENSOR5_INDEX ;// = 18;
  /*private*/ static /*final*/ int OCCUPANCY_EXTERNAL_SENSOR6_INDEX ;// = 19;
  /*private*/ static /*final*/ int OCCUPANCY_EXTERNAL_SENSOR7_INDEX ;// = 20;
  /*private*/ static /*final*/ int OCCUPANCY_EXTERNAL_SENSOR8_INDEX ;// = 21;
  /*private*/ static /*final*/ int OCCUPANCY_EXTERNAL_SENSOR9_INDEX ;// = 22;
  /*private*/ static /*final*/ int OPTIONAL_EXTERNAL_SENSOR1_INDEX;// = 23;
  /*private*/ static /*final*/ int OPTIONAL_EXTERNAL_SENSOR2_INDEX;// = 24;
//  Computer maintained:
//  Unused index 25 (was terminating O.S. section info)
  /*private*/ static /*final*/ int UNIQUE_ID1_INDEX;// = 26;
  /*private*/ static /*final*/ int UNIQUE_ID2_INDEX;// = 27;
  /*private*/ static /*final*/ int UNIQUE_ID3_INDEX;// = 28;
  /*private*/ static /*final*/ int UNIQUE_ID4_INDEX;// = 29;
  /*private*/ static /*final*/ int UNIQUE_ID5_INDEX;// = 30;
  /*private*/ static /*final*/ int ARRAY_SIZE;// = 31;

};

#endif // TRAFFICLOCKINGENTRY_H
