#include "otherdata.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
///*public*/ class OtherData {
    /*public*/ /*final*/ /*static*/ QString OtherData::CTC_VERSION = "v2.0";

/*private*/ /*final*/ /*static*/ QMap<int, OtherData::CTC_PANEL_TYPE> OtherData::CTC_PANEL_TYPE::map = QMap<int, OtherData::CTC_PANEL_TYPE>();
/*private*/ /*final*/ /*static*/ QMap<int, OtherData::SIGNALS_ON_PANEL> OtherData::SIGNALS_ON_PANEL::map = QMap<int, OtherData::SIGNALS_ON_PANEL>();
/*public*/ /*static*/ QString OtherData::SIGNALS_ON_PANEL::toString()
{
 if(_mRadioGroupValue == OtherData::SIGNALS_ON_PANEL::ALL)
  return "ALL";
 else if(_mRadioGroupValue == OtherData::SIGNALS_ON_PANEL::GREEN_OFF)
  return "GREEN_OFF";

 return "NONE";
}
/*public*/ /*static*/ OtherData::SIGNALS_ON_PANEL OtherData::SIGNALS_ON_PANEL::valueOf(QString t)
{
 if(t == "ALL") return OtherData::SIGNALS_ON_PANEL::ALL;
 else if(t == "GREEN_OFF") return OtherData::SIGNALS_ON_PANEL::GREEN_OFF;
 return OtherData::SIGNALS_ON_PANEL::NONE;
}

/*private*/ /*final*/ /*static*/ QMap<int, OtherData::VERTICAL_SIZE> OtherData::VERTICAL_SIZE::map = QMap<int, OtherData::VERTICAL_SIZE>();
/*private*/ /*final*/ /*static*/ QMap<int, OtherData::SIGNAL_SYSTEM_TYPE> OtherData::SIGNAL_SYSTEM_TYPE::map = QMap<int, OtherData::SIGNAL_SYSTEM_TYPE>();
/*public*/ /*static*/ OtherData::CTC_PANEL_TYPE OtherData::CTC_PANEL_TYPE::getRadioGroupValue(int radioGroupValue) { return OtherData::CTC_PANEL_TYPE::map.value(radioGroupValue); }
/*public*/  QString OtherData::CTC_PANEL_TYPE::toString()
{
 if(_mRadioGroupValue == OtherData::CTC_PANEL_TYPE::USS) return "USS";
 else return "OTHER";
}
/*public*/ /*static*/ OtherData::CTC_PANEL_TYPE OtherData::CTC_PANEL_TYPE::valueOf(QString t)
{
 if(t == "USS") return OtherData::CTC_PANEL_TYPE::USS;
 return OtherData::CTC_PANEL_TYPE::OTHER;
}

/*public*/ /*static*/ OtherData::SIGNALS_ON_PANEL OtherData::SIGNALS_ON_PANEL::getRadioGroupValue(int radioGroupValue) { return OtherData::SIGNALS_ON_PANEL::map.value(radioGroupValue); }
/*public*/ /*static*/ OtherData::VERTICAL_SIZE OtherData::VERTICAL_SIZE::getRadioGroupValue(int radioGroupValue) { return OtherData::VERTICAL_SIZE::map.value(radioGroupValue); }
/*public*/  QString OtherData::VERTICAL_SIZE::toString()
{
 if(_mRadioGroupValue == OtherData::VERTICAL_SIZE::SMALL)
  return "SMALL";
 else if(_mRadioGroupValue == OtherData::VERTICAL_SIZE::MEDIUM)
  return "MEDIUM";
 else if(_mRadioGroupValue ==  OtherData::VERTICAL_SIZE::LARGE)
  return "LARGE";
 return "??";
}
/*public*/ /*static*/ OtherData::VERTICAL_SIZE OtherData::VERTICAL_SIZE::valueOf(QString t)
{
 if(t == "SMALL")
  return OtherData::VERTICAL_SIZE::SMALL;
 if(t == "MEDIUM")
  return OtherData::VERTICAL_SIZE::MEDIUM;
 return OtherData::VERTICAL_SIZE::LARGE;
}

/*public*/ /*static*/ OtherData::SIGNAL_SYSTEM_TYPE OtherData::SIGNAL_SYSTEM_TYPE::getSignalSystemType(int radioGroupValue) { return OtherData::SIGNAL_SYSTEM_TYPE::map.value(radioGroupValue); }
/*public*/ /*static*/ OtherData::SIGNAL_SYSTEM_TYPE OtherData::SIGNAL_SYSTEM_TYPE::getSignalSystemType(QButtonGroup* buttonGroup) { return OtherData::SIGNAL_SYSTEM_TYPE::map.value(ProjectsCommonSubs::getButtonSelectedInt(buttonGroup)); }
/*public*/ /*static*/ QString OtherData::SIGNAL_SYSTEM_TYPE::toString()
{
 if(_mRadioGroupValue == OtherData::SIGNAL_SYSTEM_TYPE::SIGNALHEAD)
  return "SIGNALHEAD";
 return "SIGNALMAST";
}
/*public*/ /*static*/ OtherData::SIGNAL_SYSTEM_TYPE OtherData::SIGNAL_SYSTEM_TYPE::valueOf(QString t)
{
 if(t == "SIGNALHEAD")
  return OtherData::SIGNAL_SYSTEM_TYPE::SIGNALHEAD;
 else return OtherData::SIGNAL_SYSTEM_TYPE::SIGNALMAST;
}

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
