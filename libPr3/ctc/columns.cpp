#include "columns.h"
#include "defaultlistmodel.h"
#include "jbutton.h"
#include "ctcserialdata.h"
#include "checkjmriobject.h"
#include "jlabel.h"
#include "jcheckbox.h"
#include "codebuttonhandlerdata.h"
#include "frmswdi.h"
#include "frmcb.h"
#include "frmco.h"
#include "frmsidi.h"
#include "frmtrl.h"
#include "frmil.h"
#include "frmtul.h"

Columns::Columns(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019

 This represents all of the codeButtonHandlerData data in a CTC machine relating to the GUI
 interface.  It maintains the state of the screen for the higher level functions.
 */
///*public*/ class Columns {
/*private*/ /*final*/ /*static*/ QString Columns::ERROR_STRING = " ***ERROR***";
/*public*/ /*final*/ /*static*/ QString Columns::REFERENCES_PRESENT_INDICATOR = " (";

/*public*/ Columns::Columns( CTCSerialData* ctcSerialData, CheckJMRIObject* checkJMRIObject, DefaultListModel/*<String>*/* defaultListModel,
                JButton* deleteButton, JButton* changeNumbersButton,
                JButton* moveUpButton, JButton* moveDownButton,
                JLabel* edit_CB_Prompt, JLabel* cb_EditAlwaysEnabled, JButton* edit_CB,
                JLabel* edit_SIDI_Prompt, JCheckBox* sidi_Enabled,  JButton* edit_SIDI,
                JLabel* edit_SIDL_Prompt, JCheckBox* sidl_Enabled,  JButton* edit_SIDL,
                JLabel* edit_SWDI_Prompt, JCheckBox* swdi_Enabled,  JButton* edit_SWDI,
                JLabel* edit_SWDL_Prompt, JCheckBox* swdl_Enabled,  JButton* edit_SWDL,
                JLabel* edit_CO_Prompt, JCheckBox* co_Enabled,  JButton* edit_CO,
                JLabel* edit_TRL_Prompt,  JCheckBox* trl_Enabled,  JButton* edit_TRL,
                JLabel* edit_TUL_Prompt, JCheckBox* tul_Enabled,  JButton* edit_TUL,
                JLabel* edit_IL_Prompt, JCheckBox* il_Enabled,  JButton* edit_IL,
                QObject *parent) : QObject(parent) {
    _mCTCSerialData = ctcSerialData;
    _mCheckJMRIObject = checkJMRIObject;
    _mDefaultListModel = defaultListModel;
    _mDeleteButton = deleteButton;
    _mChangeNumbersButton = changeNumbersButton;
    _mMoveUpButton = moveUpButton;
    _mMoveDownButton = moveDownButton;
    _mEdit_CB_Prompt = edit_CB_Prompt;
    _mCB_EditAlwaysEnabled = cb_EditAlwaysEnabled;
    _mEdit_CB = edit_CB;
    _mEdit_SIDI_Prompt = edit_SIDI_Prompt;
    _mSIDI_Enabled = sidi_Enabled;
    _mEdit_SIDI = edit_SIDI;
    _mEdit_SIDL_Prompt = edit_SIDL_Prompt;
    _mSIDL_Enabled = sidl_Enabled;
    _mEdit_SIDL = edit_SIDL;
    _mEdit_SWDI_Prompt = edit_SWDI_Prompt;
    _mSWDI_Enabled = swdi_Enabled;
    _mEdit_SWDI = edit_SWDI;
    _mEdit_SWDL_Prompt = edit_SWDL_Prompt;
    _mSWDL_Enabled = swdl_Enabled;
    _mEdit_SWDL = edit_SWDL;
    _mEdit_CO_Prompt = edit_CO_Prompt;
    _mCO_Enabled = co_Enabled;
    _mEdit_CO = edit_CO;
    _mEdit_TRL_Prompt = edit_TRL_Prompt;
    _mTRL_Enabled = trl_Enabled;
    _mEdit_TRL = edit_TRL;
    _mTUL_Enabled = tul_Enabled;
    _mEdit_TUL_Prompt = edit_TUL_Prompt;
    _mEdit_TUL = edit_TUL;
    _mEdit_IL_Prompt = edit_IL_Prompt;
    _mIL_Enabled = il_Enabled;
    _mEdit_IL = edit_IL;
    updateFrame();
}

/*public*/ CodeButtonHandlerData* Columns::getSelectedCodeButtonHandlerData() { return _mSelectedCodeButtonHandlerData; }

/*public*/ /*final*/ void Columns::updateFrame() {
    _mDefaultListModel->clear();
    //_mCTCSerialData->getCodeButtonHandlerDataArrayList().forEach((codeButtonHandlerData) ->
    foreach(CodeButtonHandlerData* codeButtonHandlerData, _mCTCSerialData->getCodeButtonHandlerDataArrayList())
    {
     _mDefaultListModel->addElement(constructSingleColumnDisplayLine(codeButtonHandlerData));
    }//);
    _mDeleteButton->setEnabled(false);    // None selected.
    _mChangeNumbersButton->setEnabled(false);
    _mMoveUpButton->setEnabled(false);
    _mMoveDownButton->setEnabled(false);
    _mSIDI_Enabled->setEnabled(false);
    _mCB_EditAlwaysEnabled->setEnabled(false);
    _mEdit_CB->setEnabled(false);
    _mEdit_SIDI->setEnabled(false);
    _mSIDL_Enabled->setEnabled(false);
    _mEdit_SIDL->setEnabled(false);
    _mSWDI_Enabled->setEnabled(false);
    _mEdit_SWDI->setEnabled(false);
    _mSWDL_Enabled->setEnabled(false);
    _mEdit_SWDL->setEnabled(false);
    _mCO_Enabled->setEnabled(false);
    _mEdit_CO->setEnabled(false);
    _mTRL_Enabled->setEnabled(false);
    _mEdit_TRL->setEnabled(false);
    _mTUL_Enabled->setEnabled(false);
    _mEdit_TUL->setEnabled(false);
    _mIL_Enabled->setEnabled(false);
    _mEdit_IL->setEnabled(false);
}

/*public*/ int Columns::getEntrySelectedIndex() { return _mSelectedCodeButtonHandlerDataIndex; }

/*public*/ void Columns::fixAllErrors() {
    for (CodeButtonHandlerData* codeButtonHandlerData : _mCTCSerialData->getCodeButtonHandlerDataArrayList()) {
        if (!FrmSIDI::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, codeButtonHandlerData)) codeButtonHandlerData->_mSIDI_Enabled = false;
        if (!FrmSWDI::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, codeButtonHandlerData)) codeButtonHandlerData->_mSWDI_Enabled = false;
        if (!FrmCO::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, codeButtonHandlerData)) codeButtonHandlerData->_mCO_Enabled = false;
        if (!FrmTRL::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, codeButtonHandlerData)) codeButtonHandlerData->_mTRL_Enabled = false;
        if (!FrmTUL::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, codeButtonHandlerData)) codeButtonHandlerData->_mTUL_Enabled = false;
        if (!FrmIL::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, codeButtonHandlerData)) codeButtonHandlerData->_mIL_Enabled = false;
    }
    updateFrame();
}

/*public*/ bool Columns::anyErrorsPresent() {
#if 1
    QListIterator<QVariant> enumerationOfStrings = _mDefaultListModel->elements();
    while (enumerationOfStrings.hasNext()) {
        //if (enumerationOfStrings.next().contains(ERROR_STRING)) return true;
     QVariant var = enumerationOfStrings.next();
     if(var.toString().contains(ERROR_STRING))
      return true;
    }
#endif
    return false;
}

/*public*/ void Columns::updateCurrentlySelectedColumnErrorStatus() {
#if 1
    lazy1(_mEdit_CB_Prompt, FrmCB::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, _mSelectedCodeButtonHandlerData) ? Qt::black : Qt::red);
    lazy1(_mEdit_SIDI_Prompt, FrmSIDI::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, _mSelectedCodeButtonHandlerData) ? Qt::black : Qt::red);
    lazy1(_mEdit_SWDI_Prompt, FrmSWDI::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, _mSelectedCodeButtonHandlerData) ? Qt::black : Qt::red);
    lazy1(_mEdit_CO_Prompt, FrmCO::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, _mSelectedCodeButtonHandlerData) ? Qt::black : Qt::red);
    lazy1(_mEdit_TRL_Prompt, FrmTRL::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, _mSelectedCodeButtonHandlerData) ? Qt::black : Qt::red);
    lazy1(_mEdit_TUL_Prompt, FrmTUL::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, _mSelectedCodeButtonHandlerData) ? Qt::black : Qt::red);
    lazy1(_mEdit_IL_Prompt, FrmIL::dialogCodeButtonHandlerDataValid(_mCheckJMRIObject, _mSelectedCodeButtonHandlerData) ? Qt::black : Qt::red);
    _mDefaultListModel->set(_mSelectedCodeButtonHandlerDataIndex, constructSingleColumnDisplayLine(_mSelectedCodeButtonHandlerData));
#endif
}

/*public*/ void Columns::clearCurrentlySelectedColumnErrorStatus() {
    lazy1(_mEdit_CB_Prompt, Qt::black);
    lazy1(_mEdit_SIDI_Prompt, Qt::black);
    lazy1(_mEdit_SIDL_Prompt, Qt::black);
    lazy1(_mEdit_SWDI_Prompt, Qt::black);
    lazy1(_mEdit_SWDL_Prompt, Qt::black);
    lazy1(_mEdit_CO_Prompt, Qt::black);
    lazy1(_mEdit_TRL_Prompt, Qt::black);
    lazy1(_mEdit_TUL_Prompt, Qt::black);
    lazy1(_mEdit_IL_Prompt, Qt::black);
}

/*private*/ /*static*/ void Columns::lazy1(JLabel* label, QColor foreground) {
    label->setForeground(foreground);
}

/*public*/ void Columns::setEntrySelected(int selectedIndex) {
    if (selectedIndex >= 0) {
        _mDeleteButton->setEnabled(true);
        _mChangeNumbersButton->setEnabled(true);
        _mMoveUpButton->setEnabled(selectedIndex > 0);
        _mMoveDownButton->setEnabled(selectedIndex < _mCTCSerialData->getCodeButtonHandlerDataSize() - 1);
        _mSelectedCodeButtonHandlerDataIndex = selectedIndex;
        _mSelectedCodeButtonHandlerData = _mCTCSerialData->getCodeButtonHandlerData(selectedIndex);
        _mCB_EditAlwaysEnabled->setEnabled(true);
        updateCurrentlySelectedColumnErrorStatus();
        _mEdit_CB->setEnabled(true);
        lazy1(_mSIDI_Enabled, _mEdit_SIDI, true, _mSelectedCodeButtonHandlerData->_mSIDI_Enabled);
        lazy1(_mSIDL_Enabled, _mEdit_SIDL, true, _mSelectedCodeButtonHandlerData->_mSIDL_Enabled);
        lazy1(_mSWDI_Enabled, _mEdit_SWDI, true, _mSelectedCodeButtonHandlerData->_mSWDI_Enabled);
        lazy1(_mSWDL_Enabled, _mEdit_SWDL, true, _mSelectedCodeButtonHandlerData->_mSWDL_Enabled);
        specialUpdateEnableCO_and_TRL();
        lazy1(_mTUL_Enabled, _mEdit_TUL, true, _mSelectedCodeButtonHandlerData->_mTUL_Enabled);
        lazy1(_mIL_Enabled, _mEdit_IL, true, _mSelectedCodeButtonHandlerData->_mIL_Enabled);
    } else {
        clearCurrentlySelectedColumnErrorStatus();
    }
}

/*private*/ void Columns::specialUpdateEnableCO_and_TRL() {
    bool _signalDirectionLeverEnabled = signalDirectionLeverEnabled();
    if (!signalDirectionLeverEnabled()) {   // Force these, until user fixes it.
        _mSelectedCodeButtonHandlerData->_mCO_Enabled = false;
        _mSelectedCodeButtonHandlerData->_mTRL_Enabled = false;
    }
    lazy1(_mCO_Enabled, _mEdit_CO, _signalDirectionLeverEnabled, _mSelectedCodeButtonHandlerData->_mCO_Enabled);
    lazy1(_mTRL_Enabled, _mEdit_TRL, _signalDirectionLeverEnabled, _mSelectedCodeButtonHandlerData->_mTRL_Enabled);
}

/*static*/ /*private*/ void Columns::lazy1(JCheckBox* jCheckBox, JButton* jButton, bool enabled, bool value) {
    jCheckBox->setEnabled(enabled);
    jCheckBox->setChecked(value);
    jButton->setEnabled(value);
}

/*public*/ void Columns::sidi_EnabledClicked(bool newState) {
    _mSelectedCodeButtonHandlerData->_mSIDI_Enabled = newState;
    lazy2(_mEdit_SIDI, newState);
}

/*public*/ void Columns::sidl_EnabledClicked(bool newState) {
    _mSelectedCodeButtonHandlerData->_mSIDL_Enabled = newState;
    lazy2(_mEdit_SIDL, newState);
    specialUpdateEnableCO_and_TRL();
}

/*public*/ void Columns::swdi_EnabledClicked(bool newState) {
    _mSelectedCodeButtonHandlerData->_mSWDI_Enabled = newState;
    lazy2(_mEdit_SWDI, newState);
}

/*public*/ void Columns::swdl_EnabledClicked(bool newState) {
    _mSelectedCodeButtonHandlerData->_mSWDL_Enabled = newState;
    lazy2(_mEdit_SWDL, newState);
}

/*public*/ void Columns::co_EnabledClicked(bool newState) {
    _mSelectedCodeButtonHandlerData->_mCO_Enabled = newState;
    lazy2(_mEdit_CO, newState);
}

/*public*/ void Columns::trl_EnabledClicked(bool newState) {
    _mSelectedCodeButtonHandlerData->_mTRL_Enabled = newState;
    lazy2(_mEdit_TRL, newState);
}

/*public*/ void Columns::tul_EnabledClicked(bool newState) {
    _mSelectedCodeButtonHandlerData->_mTUL_Enabled = newState;
    lazy2(_mEdit_TUL, newState);
}

/*public*/ void Columns::il_EnabledClicked(bool newState) {
    _mSelectedCodeButtonHandlerData->_mIL_Enabled = newState;
    lazy2(_mEdit_IL, newState);
}

/*private*/ void Columns::lazy2(JButton* jButton, bool value) {
    jButton->setEnabled(value);
    _mCTCSerialData->setCodeButtonHandlerData(_mSelectedCodeButtonHandlerDataIndex, _mSelectedCodeButtonHandlerData);
    updateCurrentlySelectedColumnErrorStatus();
}

/*public*/ QString Columns::checkForDups(int newSwitchNumber, int newGUIColumnNumber, bool isModify, int indexModifying)
{
    QList <CodeButtonHandlerData*> codeButtonHandlerDataList = _mCTCSerialData->getCodeButtonHandlerDataArrayList();
    int codeButtonHandlerDataListSize = codeButtonHandlerDataList.size();
    for (int index = 0; index < codeButtonHandlerDataListSize; index++)
    {
        if (!isModify || index != indexModifying)
        {  // If add, check all, if modify, check all but indexModifying.
            CodeButtonHandlerData* codeButtonHandlerData = codeButtonHandlerDataList.at(index);
            if (codeButtonHandlerData->_mSwitchNumber == newSwitchNumber)
             return "Switch #" + QString::number(newSwitchNumber) + " already used";
            if (newGUIColumnNumber > 0)
            { // Multiple 0's are allowed here:
                if (codeButtonHandlerData->_mGUIColumnNumber == newGUIColumnNumber)
                 return "GUI Column #" + QString::number(newGUIColumnNumber) + " already used";
            }
        }
    }
    return QString();
}

/*private*/ QString Columns::getListOfTrafficLockingRulesOSSectionsReferenced(CodeButtonHandlerData* currentCodeButtonHandlerData,
                                                                QList <CodeButtonHandlerData*> codeButtonHandlerDataArrayList) {
    QString returnStringBuffer;// = new StringBuffer("");
    QSet<QString> temp = QSet<QString>();
    int currentUniqueID = currentCodeButtonHandlerData->_mUniqueID;
    for (CodeButtonHandlerData* codeButtonHandlerData : codeButtonHandlerDataArrayList) {
        if (currentCodeButtonHandlerData != codeButtonHandlerData) { // Don't check ourselves
            int otherUniqueID = codeButtonHandlerData->_mUniqueID;
            checkThisList(currentUniqueID, otherUniqueID, "L", codeButtonHandlerData->_mTRL_LeftTrafficLockingRules, temp);    // NOI18N
            checkThisList(currentUniqueID, otherUniqueID, "R", codeButtonHandlerData->_mTRL_RightTrafficLockingRules, temp);   // NOI18N
        }
    }
    for (QString result : temp) returnStringBuffer.append(result);
    if (returnStringBuffer.length() > 0) {
        return "TrL: " + returnStringBuffer.mid(0, returnStringBuffer.length() - 2);    // NOI18N
    } else {
        return "";
    }
}

/*private*/ void Columns::checkThisList(int ourUniqueID, int otherUniqueID, QString lr, QList<TrafficLockingData*>* trafficLockingRules, QSet<QString> setOfUniqueIDs) {
    //trafficLockingRules.forEach(rule ->
    foreach(TrafficLockingData* rule, *trafficLockingRules)
    {
        QList<int>* idList = rule->getUniqueIDs();
        lazy3(ourUniqueID, otherUniqueID, lr, idList->at(0), setOfUniqueIDs);
        lazy3(ourUniqueID, otherUniqueID, lr, idList->at(1), setOfUniqueIDs);
        lazy3(ourUniqueID, otherUniqueID, lr, idList->at(2), setOfUniqueIDs);
        lazy3(ourUniqueID, otherUniqueID, lr, idList->at(3), setOfUniqueIDs);
        lazy3(ourUniqueID, otherUniqueID, lr, idList->at(4), setOfUniqueIDs);
    }//);
}

/*private*/ void Columns::lazy3(int ourUniqueID, int otherUniqueID, QString lr, int uniqueID, QSet<QString> setOfUniqueIDs) {
    if (ourUniqueID == uniqueID) {
        setOfUniqueIDs.insert(_mCTCSerialData->getMyShortStringNoCommaViaUniqueID(otherUniqueID) + lr + ", ");
    }
}

/*private*/ QString Columns::getListOfSwitchSlavedToOSSectionsReferenced( CodeButtonHandlerData* currentCodeButtonHandlerData,
                                                            QList <CodeButtonHandlerData*> codeButtonHandlerDataArrayList) {
    QString returnStringBuffer;// = new StringBuffer("");
    QSet<QString> temp = QSet<QString>();
    int currentUniqueID = currentCodeButtonHandlerData->_mUniqueID;
    for (CodeButtonHandlerData* codeButtonHandlerData : codeButtonHandlerDataArrayList) {
        if (currentCodeButtonHandlerData != codeButtonHandlerData) { // Don't check ourselves
            if (codeButtonHandlerData->_mOSSectionSwitchSlavedToUniqueID != CodeButtonHandlerData::SWITCH_NOT_SLAVED)  { // It's referencing someone else:
                if (currentUniqueID == codeButtonHandlerData->_mOSSectionSwitchSlavedToUniqueID) {
                    temp.insert(_mCTCSerialData->getMyShortStringNoCommaViaUniqueID(codeButtonHandlerData->_mUniqueID) + ", ");
                }
            }
        }
    }
    for (QString result : temp)  returnStringBuffer.append(result);
    if (returnStringBuffer.length() > 0) {
        return "Sw: " + returnStringBuffer.mid(0, returnStringBuffer.length() - 2);   // NOI18N
    } else {
        return "";
    }
}

//  Anything in error, return ERROR_STRING
/*private*/ /*static*/ QString Columns::generatePossibleErrorString(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* currentCodeButtonHandlerData) {
//    if (!FrmCB::dialogCodeButtonHandlerDataValid(checkJMRIObject, currentCodeButtonHandlerData)) return ERROR_STRING;
    if (!FrmSIDI::dialogCodeButtonHandlerDataValid(checkJMRIObject, currentCodeButtonHandlerData)) return ERROR_STRING;
    if (!FrmSWDI::dialogCodeButtonHandlerDataValid(checkJMRIObject, currentCodeButtonHandlerData)) return ERROR_STRING;
    if (!FrmCO::dialogCodeButtonHandlerDataValid(checkJMRIObject, currentCodeButtonHandlerData)) return ERROR_STRING;
    if (!FrmTRL::dialogCodeButtonHandlerDataValid(checkJMRIObject, currentCodeButtonHandlerData)) return ERROR_STRING;
    if (!FrmTUL::dialogCodeButtonHandlerDataValid(checkJMRIObject, currentCodeButtonHandlerData)) return ERROR_STRING;
    if (!FrmIL::dialogCodeButtonHandlerDataValid(checkJMRIObject, currentCodeButtonHandlerData)) return ERROR_STRING;
    return "";                              // No error (string)
}

/*private*/ QString Columns::constructSingleColumnDisplayLine(CodeButtonHandlerData* codeButtonHandlerData) {
    QString referencesString1 = getListOfTrafficLockingRulesOSSectionsReferenced(codeButtonHandlerData, _mCTCSerialData->getCodeButtonHandlerDataArrayList());
    QString referencesString2 = getListOfSwitchSlavedToOSSectionsReferenced(codeButtonHandlerData, _mCTCSerialData->getCodeButtonHandlerDataArrayList());
    QString displayString = codeButtonHandlerData->myString();
    if (!referencesString1.isEmpty() || !referencesString2.isEmpty()) {
        displayString += REFERENCES_PRESENT_INDICATOR + referencesString1 + " " + referencesString2 + ")";
    }
    displayString += generatePossibleErrorString(_mCheckJMRIObject, codeButtonHandlerData);
    return displayString;
}

/*private*/ bool Columns::signalDirectionLeverEnabled() {
    return _mSelectedCodeButtonHandlerData->_mSIDL_Enabled;
}

