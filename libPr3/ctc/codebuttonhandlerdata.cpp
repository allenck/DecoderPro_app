#include "codebuttonhandlerdata.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class CodeButtonHandlerData {
    /*public*/ /*static*/ /*final*/ int CodeButtonHandlerData::SWITCH_NOT_SLAVED = -1;
    /*private*/ /*final*/ /*static*/ QMap<int, CodeButtonHandlerData::LOCK_IMPLEMENTATION> CodeButtonHandlerData::LOCK_IMPLEMENTATION::map = QMap<int, CodeButtonHandlerData::LOCK_IMPLEMENTATION>();
    /*private*/ /*final*/ /*static*/ QMap<int, CodeButtonHandlerData::TURNOUT_TYPE> CodeButtonHandlerData::TURNOUT_TYPE::map = QMap<int, CodeButtonHandlerData::TURNOUT_TYPE>();

    /*public*/ /*static*/ CodeButtonHandlerData::LOCK_IMPLEMENTATION getLockImplementation(int radioGroupValue) { return CodeButtonHandlerData::LOCK_IMPLEMENTATION::map.value(radioGroupValue); }
    /*public*/ /*static*/ CodeButtonHandlerData::LOCK_IMPLEMENTATION getLockImplementation(QButtonGroup* buttonGroup) { return CodeButtonHandlerData::LOCK_IMPLEMENTATION::map.value(ProjectsCommonSubs::getButtonSelectedInt(buttonGroup)); }
    /*public*/ /*static*/ CodeButtonHandlerData::TURNOUT_TYPE getTurnoutType(int radioGroupValue) { return CodeButtonHandlerData::TURNOUT_TYPE::map.value(radioGroupValue); }
    /*public*/ /*static*/ CodeButtonHandlerData::TURNOUT_TYPE getTurnoutType(QButtonGroup* buttonGroup) { return CodeButtonHandlerData::TURNOUT_TYPE::map.value(ProjectsCommonSubs::getButtonSelectedInt(buttonGroup)); }

    /*public*/ CodeButtonHandlerData::CodeButtonHandlerData(int uniqueID, int switchNumber, int signalEtcNumber, int guiColumnNumber, QObject* parent) : QObject(parent){
        _mUniqueID = uniqueID;
        _mSwitchNumber = switchNumber;
        _mSignalEtcNumber = signalEtcNumber;
        _mOSSectionSwitchSlavedToUniqueID = SWITCH_NOT_SLAVED;
        _mGUIColumnNumber = guiColumnNumber;
        _mSWDI_GUITurnoutType = CodeButtonHandlerData::TURNOUT_TYPE::TURNOUT;
        _mTUL_LockImplementation = LOCK_IMPLEMENTATION::GREGS;
    }


