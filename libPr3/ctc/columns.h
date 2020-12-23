#ifndef COLUMNS_H
#define COLUMNS_H

#include <QObject>
#include "trafficlockingdata.h"

class CTCSerialData;
class JButton;
class JCheckBox;
class JLabel;
class CheckJMRIObject;
class DefaultListModel;
class CodeButtonHandlerData;
class Columns : public QObject
{
  Q_OBJECT
 public:
  explicit Columns(QObject *parent = nullptr);
  /*public*/ /*final*/ static QString REFERENCES_PRESENT_INDICATOR;// = " (";
  /*public*/ Columns( CTCSerialData* ctcSerialData, CheckJMRIObject* checkJMRIObject, DefaultListModel/*<String>*/* defaultListModel,
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
                  QObject *parent = nullptr);
  /*public*/ CodeButtonHandlerData* getSelectedCodeButtonHandlerData();
  /*public*/ /*final*/ void updateFrame();
  /*public*/ int getEntrySelectedIndex();
  /*public*/ void fixAllErrors();
  /*public*/ bool anyErrorsPresent();
  /*public*/ void updateCurrentlySelectedColumnErrorStatus();
  /*public*/ void clearCurrentlySelectedColumnErrorStatus();
  /*public*/ void setEntrySelected(int selectedIndex);
  /*public*/ void sidi_EnabledClicked(bool newState);
  /*public*/ void sidl_EnabledClicked(bool newState);
  /*public*/ void swdi_EnabledClicked(bool newState);
  /*public*/ void swdl_EnabledClicked(bool newState);
  /*public*/ void co_EnabledClicked(bool newState) ;
  /*public*/ void trl_EnabledClicked(bool newState);
  /*public*/ void tul_EnabledClicked(bool newState);
  /*public*/ void il_EnabledClicked(bool newState);
  /*public*/ QString checkForDups(int newSwitchNumber, int newGUIColumnNumber, bool isModify, int indexModifying);


 signals:

 public slots:

 private:
  /*private*/ /*final*/ static QString ERROR_STRING;// = " ***ERROR***";

  /*private*/ /*final*/ CTCSerialData* _mCTCSerialData;
  /*private*/ /*final*/ CheckJMRIObject* _mCheckJMRIObject;
  /*private*/ /*final*/ DefaultListModel/*<String>*/* _mDefaultListModel;
  /*private*/ /*final*/ JButton* _mDeleteButton;
  /*private*/ /*final*/ JButton* _mChangeNumbersButton;
  /*private*/ /*final*/ JButton* _mMoveUpButton;
  /*private*/ /*final*/ JButton* _mMoveDownButton;
  /*private*/ /*final*/ JLabel* _mEdit_CB_Prompt;
  /*private*/ /*final*/ JLabel* _mCB_EditAlwaysEnabled;
  /*private*/ /*final*/ JButton* _mEdit_CB;
  /*private*/ /*final*/ JLabel* _mEdit_SIDI_Prompt;
  /*private*/ /*final*/ JCheckBox* _mSIDI_Enabled;
  /*private*/ /*final*/ JButton* _mEdit_SIDI;
  /*private*/ /*final*/ JLabel* _mEdit_SIDL_Prompt;
  /*private*/ /*final*/ JCheckBox* _mSIDL_Enabled;
  /*private*/ /*final*/ JButton* _mEdit_SIDL;
  /*private*/ /*final*/ JLabel* _mEdit_SWDI_Prompt;
  /*private*/ /*final*/ JCheckBox* _mSWDI_Enabled;
  /*private*/ /*final*/ JButton* _mEdit_SWDI;
  /*private*/ /*final*/ JLabel* _mEdit_SWDL_Prompt;
  /*private*/ /*final*/ JCheckBox* _mSWDL_Enabled;
  /*private*/ /*final*/ JButton* _mEdit_SWDL;
  /*private*/ /*final*/ JLabel* _mEdit_CO_Prompt;
  /*private*/ /*final*/ JCheckBox* _mCO_Enabled;
  /*private*/ /*final*/ JButton* _mEdit_CO;
  /*private*/ /*final*/ JLabel* _mEdit_TRL_Prompt;
  /*private*/ /*final*/ JCheckBox* _mTRL_Enabled;
  /*private*/ /*final*/ JButton* _mEdit_TRL;
  /*private*/ /*final*/ JLabel* _mEdit_TUL_Prompt;
  /*private*/ /*final*/ JCheckBox* _mTUL_Enabled;
  /*private*/ /*final*/ JButton* _mEdit_TUL;
  /*private*/ /*final*/ JLabel* _mEdit_IL_Prompt;
  /*private*/ /*final*/ JCheckBox* _mIL_Enabled;
  /*private*/ /*final*/ JButton* _mEdit_IL;
  /*private*/ int _mSelectedCodeButtonHandlerDataIndex;
  /*private*/ CodeButtonHandlerData* _mSelectedCodeButtonHandlerData;
  /*private*/ void specialUpdateEnableCO_and_TRL();
  static /*private*/ void lazy1(JCheckBox* jCheckBox, JButton* jButton, bool enabled, bool value);
  /*private*/ static void lazy1(JLabel* label, QColor foreground);
  /*private*/ void lazy2(JButton* jButton, bool value);

  /*private*/ QString getListOfTrafficLockingRulesOSSectionsReferenced(CodeButtonHandlerData* currentCodeButtonHandlerData,
                                                                  QList <CodeButtonHandlerData*> codeButtonHandlerDataArrayList);
  /*private*/ void checkThisList(int ourUniqueID, int otherUniqueID, QString lr, QList<TrafficLockingData *> *trafficLockingRules, QSet<QString> setOfUniqueIDs);
  /*private*/ void lazy3(int ourUniqueID, int otherUniqueID, QString lr, int uniqueID, QSet<QString> setOfUniqueIDs);
  /*private*/ QString getListOfSwitchSlavedToOSSectionsReferenced( CodeButtonHandlerData* currentCodeButtonHandlerData,
                                                              QList <CodeButtonHandlerData*> codeButtonHandlerDataArrayList);
  /*private*/ static QString generatePossibleErrorString(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* currentCodeButtonHandlerData);
  /*private*/ QString constructSingleColumnDisplayLine(CodeButtonHandlerData* codeButtonHandlerData);
  /*private*/ bool signalDirectionLeverEnabled();

};

#endif // COLUMNS_H
