#include "otherdata.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
///*public*/ class OtherData {
    /*public*/ /*final*/ /*static*/ QString OtherData::CTC_VERSION = "v2.0";

/*private*/ /*final*/ /*static*/ QMap<int, OtherData::CTC_PANEL_TYPE> OtherData::CTC_PANEL_TYPE::map = QMap<int, OtherData::CTC_PANEL_TYPE>();
/*private*/ /*final*/ /*static*/ QMap<int, OtherData::SIGNALS_ON_PANEL> OtherData::SIGNALS_ON_PANEL::map = QMap<int, OtherData::SIGNALS_ON_PANEL>();
/*private*/ /*final*/ /*static*/ QMap<int, OtherData::VERTICAL_SIZE> OtherData::VERTICAL_SIZE::map = QMap<int, OtherData::VERTICAL_SIZE>();
/*private*/ /*final*/ /*static*/ QMap<int, OtherData::SIGNAL_SYSTEM_TYPE> OtherData::SIGNAL_SYSTEM_TYPE::map = QMap<int, OtherData::SIGNAL_SYSTEM_TYPE>();
/*public*/ /*static*/ OtherData::CTC_PANEL_TYPE OtherData::CTC_PANEL_TYPE::getRadioGroupValue(int radioGroupValue) { return OtherData::CTC_PANEL_TYPE::map.value(radioGroupValue); }
/*public*/ /*static*/ OtherData::SIGNALS_ON_PANEL OtherData::SIGNALS_ON_PANEL::getRadioGroupValue(int radioGroupValue) { return OtherData::SIGNALS_ON_PANEL::map.value(radioGroupValue); }
/*public*/ /*static*/ OtherData::VERTICAL_SIZE OtherData::VERTICAL_SIZE::getRadioGroupValue(int radioGroupValue) { return OtherData::VERTICAL_SIZE::map.value(radioGroupValue); }
/*public*/ /*static*/ OtherData::SIGNAL_SYSTEM_TYPE OtherData::SIGNAL_SYSTEM_TYPE::getSignalSystemType(int radioGroupValue) { return OtherData::SIGNAL_SYSTEM_TYPE::map.value(radioGroupValue); }
/*public*/ /*static*/ OtherData::SIGNAL_SYSTEM_TYPE OtherData::SIGNAL_SYSTEM_TYPE::getSignalSystemType(QButtonGroup* buttonGroup) { return OtherData::SIGNAL_SYSTEM_TYPE::map.value(ProjectsCommonSubs::getButtonSelectedInt(buttonGroup)); }


    OtherData::OtherData(QObject *parent) : QObject(parent)
    {
        _mFleetingToggleInternalSensor = new NBHSensor("OtherData", "fleeting = ", "IS:FLEETING", "IS:FLEETING");  // NOI18N
        _mDefaultFleetingEnabled = false;
        _mSignalSystemType = SIGNAL_SYSTEM_TYPE::SIGNALMAST;
        _mCTCDebugSystemReloadInternalSensor = new NBHSensor("OtherData", "reload = ", "IS:RELOADCTC", "IS:RELOADCTC");  // NOI18N
        _mCTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor = new NBHSensor("OtherData", "debug = ", "IS:DEBUGCTC", "IS:DEBUGCTC");  // NOI18N
        _mGUIDesign_NumberOfEmptyColumnsAtEnd = 0;
        _mGUIDesign_CTCPanelType = CTC_PANEL_TYPE::USS;
        _mGUIDesign_BuilderPlate = false;
        _mGUIDesign_SignalsOnPanel = SIGNALS_ON_PANEL::ALL;
        _mGUIDesign_FleetingToggleSwitch = true;
        _mGUIDesign_AnalogClockEtc = false;
        _mGUIDesign_ReloadCTCSystemButton = true;
        _mGUIDesign_CTCDebugOnToggle = true;
        _mGUIDesign_CreateTrackPieces = false;
        _mGUIDesign_VerticalSize = VERTICAL_SIZE::SMALL;
        _mGUIDesign_OSSectionUnknownInconsistentRedBlink = false;
        _mGUIDesign_TurnoutsOnPanel = true;
    }

    /*public*/ int OtherData::getNextUniqueNumber() { return _mNextUniqueNumber++; }

    /*public*/ void OtherData::possiblySetToHighest(int value) { if (value + 1 > _mNextUniqueNumber) _mNextUniqueNumber = value + 1; }
