#include "ctcserialdata.h"
#include "otherdata.h"
#include "codebuttonhandlerdata.h"
#include "trafficlockingdata.h"
#include "nbhturnout.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class CTCSerialData {



/*public*/ CTCSerialData::CTCSerialData(QObject *parent) {
    _mOtherData = new OtherData();
    _mCodeButtonHandlerDataArrayList = QList<CodeButtonHandlerData*>();
}

/*public*/ OtherData* CTCSerialData::getOtherData() {
    return _mOtherData;
}

/*public*/ int CTCSerialData::getUniqueNumber() {
    return _mOtherData->getNextUniqueNumber();
}

/*public*/ CodeButtonHandlerData* CTCSerialData::getCodeButtonHandlerDataViaUniqueID(int uniqueID) {
    for (CodeButtonHandlerData* codeButtonHandlerData : _mCodeButtonHandlerDataArrayList) {
        if (codeButtonHandlerData->_mUniqueID == uniqueID) {
            return codeButtonHandlerData;
        }
    }
    return nullptr;    // In case it's not found.
}

/*public*/ QString CTCSerialData::getMyShortStringNoCommaViaUniqueID(int uniqueID) {
    for (CodeButtonHandlerData* codeButtonHandlerData : _mCodeButtonHandlerDataArrayList) {
        if (codeButtonHandlerData->_mUniqueID == uniqueID) {
            return codeButtonHandlerData->myShortStringNoComma();
        }
    }
    return "UNKNOWN";    // In case it's not found.
}

/*public*/ int CTCSerialData::getIndexOfUniqueID(int uniqueID) {
    for (int index = 0; index < _mCodeButtonHandlerDataArrayList.size(); index++) {
        if (_mCodeButtonHandlerDataArrayList.at(index)->_mUniqueID == uniqueID) {
            return index;    // That's it.
        }
    }
    return -1;  // not found.
}

/*public*/ void CTCSerialData::setOtherData(OtherData* otherData) {
    _mOtherData = otherData;
}

/*public*/ QList<CodeButtonHandlerData*> CTCSerialData::getCodeButtonHandlerDataArrayList() {
    return _mCodeButtonHandlerDataArrayList;
}

/*public*/ void CTCSerialData::addCodeButtonHandlerData(CodeButtonHandlerData* codeButtonHandlerData) {
    _mCodeButtonHandlerDataArrayList.append(codeButtonHandlerData);
}

/*public*/ void CTCSerialData::removeCodeButtonHandlerData(int index) {
    _mCodeButtonHandlerDataArrayList.removeAt(index);
}

/*public*/ CodeButtonHandlerData* CTCSerialData::getCodeButtonHandlerData(int index) {
    return _mCodeButtonHandlerDataArrayList.at(index);
}

/*public*/ int CTCSerialData::getCodeButtonHandlerDataSize() {
    return _mCodeButtonHandlerDataArrayList.size();
}

/*public*/ void CTCSerialData::moveUp(int index) {
    try {
        //Collections.swap(_mCodeButtonHandlerDataArrayList, index, index - 1);
      CodeButtonHandlerData* i0 = _mCodeButtonHandlerDataArrayList.at(index);
      CodeButtonHandlerData* i1 = _mCodeButtonHandlerDataArrayList.at(index -1);
      _mCodeButtonHandlerDataArrayList.replace(index -1, i0);
      _mCodeButtonHandlerDataArrayList.replace(index, i1);
    } catch (IndexOutOfBoundsException e) {
    }    // Do NOTHING in this case!  Technically should never happen, since buttons aren't enabled for such possibilities
}

/*public*/ void CTCSerialData::moveDown(int index) {
    try {
        //Collections.swap(_mCodeButtonHandlerDataArrayList, index, index + 1);
     //_mCodeButtonHandlerDataArrayList.swapItemsAt(index, index + 1);
     CodeButtonHandlerData* i0 = _mCodeButtonHandlerDataArrayList.at(index);
     CodeButtonHandlerData* i1 = _mCodeButtonHandlerDataArrayList.at(index +1);
     _mCodeButtonHandlerDataArrayList.replace(index +1, i0);
     _mCodeButtonHandlerDataArrayList.replace(index, i1);

    } catch (IndexOutOfBoundsException e) {
    }    // Do NOTHING in this case!  Technically should never happen, since buttons aren't enabled for such possibilities
}

/**
 * Change the identifying attributes with the exception of the uniqueID.  The potential
 * primary changes are the switch and signal numbers.
 * @param index The row being changed.
 * @param newSwitchNumber The new switch number which is always odd.
 * @param newSignalEtcNumber The new signal number which is always one more than the switch number.
 * @param newGUIColumnNumber The location on the panel.  Used by the GUI export process.
 * @param newGUIGeneratedAtLeastOnceAlready A flag to indicate whether the GUI export should include this column.
 */
/*public*/ void CTCSerialData::updateSwitchAndSignalEtcNumbersEverywhere(int index, int newSwitchNumber, int newSignalEtcNumber, int newGUIColumnNumber, bool newGUIGeneratedAtLeastOnceAlready) {
    CodeButtonHandlerData* codeButtonHandlerData = _mCodeButtonHandlerDataArrayList.at(index);
    codeButtonHandlerData->_mSwitchNumber = newSwitchNumber;
    codeButtonHandlerData->_mSignalEtcNumber = newSignalEtcNumber;
    codeButtonHandlerData->_mGUIColumnNumber = newGUIColumnNumber;
    codeButtonHandlerData->_mGUIGeneratedAtLeastOnceAlready = newGUIGeneratedAtLeastOnceAlready;
    int UniqueIDBeingModified = codeButtonHandlerData->_mUniqueID;
    QString replacementString = codeButtonHandlerData->myShortStringNoComma();
    for (CodeButtonHandlerData* temp : _mCodeButtonHandlerDataArrayList) {
        updateTrlUserText(temp->_mTRL_LeftTrafficLockingRules, UniqueIDBeingModified, replacementString);
        updateTrlUserText(temp->_mTRL_RightTrafficLockingRules, UniqueIDBeingModified, replacementString);
    }
}

/**
 * Update the text description of entries in the traffic locking rules located in TrafficLockingData.
 * Each alignment entry in each rule is checked for match on uniqueID.  If so, the text is replaced.
 * @param rulesToFix An array of TrafficLockingData entries.  Each entry is a rule.
 * @param uniqueIDBeingModified The uniqueID being checked.
 * @param replacementString The new sw/sig string.
 */
/*private*/ void CTCSerialData::updateTrlUserText(QList<TrafficLockingData*>* rulesToFix, int uniqueIDBeingModified, QString replacementString) {
    //rulesToFix.forEach(rule ->
    foreach(TrafficLockingData* rule, *rulesToFix)
    {
        //rule->_mSwitchAlignments.forEach(alignment ->
        foreach(TrafficLockingData::TRLSwitch* alignment, *rule->_mSwitchAlignments)
        {
            if (uniqueIDBeingModified == alignment->_mUniqueID) {
                alignment->_mUserText = replacementString;
            }
        }//);
    }//);
}

/*public*/ void CTCSerialData::setCodeButtonHandlerData(int index, CodeButtonHandlerData* codeButtonHandlerData) {
    _mCodeButtonHandlerDataArrayList.insert(index, codeButtonHandlerData);
}

//  If none are found, return -1 (which we'll then increment by 2 to 1, which is a good "add" default starting point):
/*public*/ int CTCSerialData::findHighestSwitchNumberUsedSoFar() {
    int highestSwitchNumber = -1;
    for (CodeButtonHandlerData* codeButtonHandlerData : _mCodeButtonHandlerDataArrayList) {
        if (codeButtonHandlerData->_mSwitchNumber > highestSwitchNumber) {
            highestSwitchNumber = codeButtonHandlerData->_mSwitchNumber;
        }
    }
    return highestSwitchNumber;
}

//  If none are found, return 0 (which we'll then increment by 1 to 1, which is a good "add" default starting point):
/*public*/ int CTCSerialData::findHighestColumnNumberUsedSoFar() {
    int highestColumnNumber = 0;
    for (CodeButtonHandlerData* codeButtonHandlerData : _mCodeButtonHandlerDataArrayList) {
        if (codeButtonHandlerData->_mGUIColumnNumber > highestColumnNumber) {
            highestColumnNumber = codeButtonHandlerData->_mGUIColumnNumber;
        }
    }
    return highestColumnNumber;
}

/**
 * Routine to search our _mCodeButtonHandlerDataArrayList for the O.S. section
 * that contains the passed turnout.
 *
 * @param turnout   The turnout to search for in our table.
 * @return          CTCTurnoutData, else if turnout not found, null.
 */
/*public*/ CTCSerialData::CTCTurnoutData* CTCSerialData::getCTCTurnoutData(Turnout* turnout) {
    for (CodeButtonHandlerData* codeButtonHandlerData : _mCodeButtonHandlerDataArrayList) {
        if (codeButtonHandlerData->_mSWDI_Enabled) { // Only if it has one:
            if (codeButtonHandlerData->_mSWDI_ExternalTurnout->getBean() == (turnout)) { // Ah match, this is us:
                return new CTCTurnoutData(codeButtonHandlerData->myShortStringNoComma(), codeButtonHandlerData->_mUniqueID);
            }
        }
    }
    return nullptr;
}

/**
 * This routine is used to support FrmTUL.java.  It generates a HashSet (which
 * prevents duplicate strings) of all such locked turnouts, EXCLUDING the
 * passed "excludedOne", since that one will be handled locally in the calling
 * code.
 *
 * @param excludedOne The one to NOT include in the returned information.
 * @return All locked turnouts NOT INCLUDING excludedOne.
 */
/*public*/ QSet<QString> CTCSerialData::getHashSetOfAllLockedTurnoutsExcludingPassedOne(CodeButtonHandlerData* excludedOne) {
    QSet<QString> lockedTurnouts = QSet<QString>();
    for (CodeButtonHandlerData* codeButtonHandlerData : _mCodeButtonHandlerDataArrayList) {
        if (codeButtonHandlerData != excludedOne) { // Process this one:
            if (codeButtonHandlerData->_mTUL_ExternalTurnout->valid()) { lockedTurnouts.insert(codeButtonHandlerData->_mTUL_ExternalTurnout->getHandleName()); }
            if (codeButtonHandlerData->_mTUL_AdditionalExternalTurnout1->valid()) { lockedTurnouts.insert(codeButtonHandlerData->_mTUL_AdditionalExternalTurnout1->getHandleName()); }
            if (codeButtonHandlerData->_mTUL_AdditionalExternalTurnout2->valid()) { lockedTurnouts.insert(codeButtonHandlerData->_mTUL_AdditionalExternalTurnout2->getHandleName()); }
            if (codeButtonHandlerData->_mTUL_AdditionalExternalTurnout3->valid()) { lockedTurnouts.insert(codeButtonHandlerData->_mTUL_AdditionalExternalTurnout3->getHandleName()); }
        }
    }
    return lockedTurnouts;
}

