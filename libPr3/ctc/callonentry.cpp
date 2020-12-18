#include "callonentry.h"
#include "projectscommonsubs.h"

/**
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 *
 * This describes a single line of Call On Data from the GUI screen.
 */
///*public*/ class CallOnEntry {


    /*public*/ CallOnEntry::CallOnEntry(QString csvString, QObject *parent) : QObject(parent) {
        QList<QString> arrayListOfStrings = ProjectsCommonSubs::getFixedArrayListSizeFromCSV(csvString, ARRAY_SIZE);
        _mExternalSignal = arrayListOfStrings.value(EXTERNAL_SIGNAL_INDEX);
        _mSignalFacingDirection = arrayListOfStrings.value(SIGNAL_FACING_DIRECTION_INDEX);
        _mSignalAspectToDisplay = arrayListOfStrings.value(SIGNAL_ASPECT_TO_DISPLAY_INDEX);
        _mCalledOnExternalSensor = arrayListOfStrings.value(CALLED_ON_EXTERNAL_SENSOR_INDEX);
        _mExternalBlock = arrayListOfStrings.value(EXTERNAL_BLOCK_INDEX);
        _mSwitchIndicator1 = arrayListOfStrings.value(SWITCHINDICATOR1_INDEX);
        _mSwitchIndicator2 = arrayListOfStrings.value(SWITCHINDICATOR2_INDEX);
        _mSwitchIndicator3 = arrayListOfStrings.value(SWITCHINDICATOR3_INDEX);
        _mSwitchIndicator4 = arrayListOfStrings.value(SWITCHINDICATOR4_INDEX);
        _mSwitchIndicator5 = arrayListOfStrings.value(SWITCHINDICATOR5_INDEX);
        _mSwitchIndicator6 = arrayListOfStrings.value(SWITCHINDICATOR6_INDEX);
    }
