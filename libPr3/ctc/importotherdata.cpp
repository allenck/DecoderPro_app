#include "importotherdata.h"
#include <QMap>
/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class ImportOtherData implements Serializable {
/*private*/ /*final*/ /*static*/ int ImportOtherData::FILE_VERSION = 0;
/*private*/ /*final*/ /*static*/ QMap<int, ImportOtherData::CTC_PANEL_TYPE> ImportOtherData::CTC_PANEL_TYPE::map {{0, ImportOtherData::CTC_PANEL_TYPE::USS}, {1, ImportOtherData::CTC_PANEL_TYPE::OTHER}};
/*public*/ QString ImportOtherData::CTC_PANEL_TYPE::toString()
{
 if(_mRadioGroupValue == ImportOtherData::CTC_PANEL_TYPE::USS)
  return "USS";
 return "OTHER";
}
/*public*/ /*static*/ ImportOtherData::CTC_PANEL_TYPE ImportOtherData::CTC_PANEL_TYPE::valueOf(QString t)
{
 if(t == "USS")
  return ImportOtherData::CTC_PANEL_TYPE(0);
 return ImportOtherData::CTC_PANEL_TYPE(1);
}
/*public*/ QString ImportOtherData::SIGNALS_ON_PANEL::toString()
{
 if(_mRadioGroupValue == ALL) return "ALL";
 if(_mRadioGroupValue == GREEN_OFF) return "GREEN_OFF";
 return "NONE";
}

/*public*/ /*static*/ ImportOtherData::SIGNALS_ON_PANEL ImportOtherData::SIGNALS_ON_PANEL::valueOf(QString t)
{
 if(t == "ALL") return ALL;
 if(t == "GREEN_OFF") return GREEN_OFF;
 return NONE;
}

/*private*/ /*final*/ /*static*/ QMap<int, ImportOtherData::SIGNALS_ON_PANEL> ImportOtherData::SIGNALS_ON_PANEL::map {{0, ImportOtherData::SIGNALS_ON_PANEL::ALL}, {1, ImportOtherData::SIGNALS_ON_PANEL::GREEN_OFF}, {2, ImportOtherData::SIGNALS_ON_PANEL::NONE}};
/*private*/ /*final*/ /*static*/ QMap<int, ImportOtherData::VERTICAL_SIZE> ImportOtherData::VERTICAL_SIZE::map {{0, ImportOtherData::VERTICAL_SIZE::SMALL}, {1, ImportOtherData::VERTICAL_SIZE::MEDIUM}, {2, ImportOtherData::VERTICAL_SIZE::LARGE}};
/*public*/ QString ImportOtherData::VERTICAL_SIZE::toString()
{
 if(_mRadioGroupValue == ImportOtherData::VERTICAL_SIZE::SMALL) return "SMALL";
 else if(_mRadioGroupValue == ImportOtherData::VERTICAL_SIZE::MEDIUM) return "MEDIUM";
 else
  return "LARGE";
}

/*public*/ QString ImportOtherData::SIGNAL_SYSTEM_TYPE::toString()
{
 if(_mRadioGroupValue == ImportOtherData::SIGNAL_SYSTEM_TYPE::SIGNALHEAD)
  return "SIGNALHEAD";
 return "SIGNALMAST";
}



/*private*/ /*final*/ /*static*/ QMap<int, ImportOtherData::SIGNAL_SYSTEM_TYPE> ImportOtherData::SIGNAL_SYSTEM_TYPE::map {{0, ImportOtherData::SIGNAL_SYSTEM_TYPE::SIGNALHEAD}, {1, ImportOtherData::SIGNAL_SYSTEM_TYPE::SIGNALMAST}};


/*public*/ ImportOtherData::ImportOtherData(QObject *parent) : QObject(parent){
    _mFleetingToggleInternalSensor = "IS:FLEETING";                                 // NOI18N
    _mDefaultFleetingEnabled = false;
    _mSignalSystemType = SIGNAL_SYSTEM_TYPE::SIGNALMAST;
    _mCTCDebugSystemReloadInternalSensor = "IS:RELOADCTC";                          // NOI18N
    _mCTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor = "IS:DEBUGCTC";    // NOI18N
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

//  Figure out if we need to convert from prior verion(s) (As of 2/20/19, no):
/*public*/ void ImportOtherData::upgradeSelf() {
    if (_mFileVersion == FILE_VERSION) { _mFileVersion = FILE_VERSION; }    // Get around complaints by Travis.
//  I had to get rid of this stub, because SpotBugs complained:
/*
    for (int oldVersion = _mFileVersion; oldVersion < FILE_VERSION; oldVersion++) {
        switch(oldVersion) {
            case 0:
                break;
        }
    }
*/
}
