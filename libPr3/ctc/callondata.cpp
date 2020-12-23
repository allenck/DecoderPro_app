#include "callondata.h"
#include "nbhsensor.h"
#include "nbhsignal.h"

/**
 * This describes a single line of Call On data.  The list of call on rules
 * for each OS section are in the _mCO_GroupingsList variable in {@link CodeButtonHandlerData}.
 *
 * During panel loading, the switch indicator names are saved as strings.  Once all of the
 * data is loaded, the NBHSensors are copied from the related CodeButtonHandlerData.
 * @author Dave Sand Copyright (C) 2020
 */
///*public*/ class CallOnData {

    /*public*/ CallOnData::CallOnData(QObject *parent) : QObject(parent){
    }

    //@Override
    /*public*/ QString CallOnData::toString() {
        QString formattedString = QString("%1,%2,%3,%4,%5").arg(
                _mExternalSignal != nullptr ? _mExternalSignal->getHandleName() : "").arg(
                _mSignalFacingDirection != "" ? _mSignalFacingDirection : "").arg(
                _mSignalAspectToDisplay != "" ? _mSignalAspectToDisplay : "").arg(
                _mCalledOnExternalSensor != nullptr ? _mCalledOnExternalSensor->getHandleName() : "").arg(
                _mExternalBlock != nullptr ? _mExternalBlock->getName() : "");
        QString buildString = /*new StringBuilder*/(formattedString);
        //_mSwitchIndicators.forEach(sw ->
        foreach(NBHSensor* sw, *_mSwitchIndicators)
        {
            buildString.append(",");
            buildString.append(sw->getHandleName());
        }//);
        return buildString/*.toString()*/;
    }
