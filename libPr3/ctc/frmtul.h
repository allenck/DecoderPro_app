#ifndef FRMTUL_H
#define FRMTUL_H
#include "jframe.h"
#include "jframe.h"
#include "jlabel.h"
#include "jbutton.h"
#include "jcombobox.h"
#include "jcheckbox.h"
#include <QRadioButton>
#include "awtwindowproperties.h"
#include "codebuttonhandlerdata.h"
#include "programproperties.h"
#include "ctcserialdata.h"
#include "checkjmriobject.h"
#include "windowadapter.h"

class FrmTUL : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmTUL(AwtWindowProperties* awtWindowProperties,
                  CTCSerialData* ctcSerialData,
                  CodeButtonHandlerData* codeButtonHandlerData,
                  ProgramProperties* programProperties, CheckJMRIObject* checkJMRIObject,
                  QWidget* parent= nullptr);

  /*public*/ bool closedNormally() { return _mClosedNormally; }

 private:
  // Variables declaration - do not modify
  /*private*/ JLabel* _mLabelDlgTULClosed;
  /*private*/ JLabel* _mLabelDlgTULGUIEnable;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JLabel* _mTUL_ActualTurnoutPrompt;
  /*private*/ JComboBox/*<String>*/*_mTUL_AdditionalExternalTurnout1;
  /*private*/ JCheckBox* _mTUL_AdditionalExternalTurnout1FeedbackDifferent;
  /*private*/ JComboBox/*<String>*/*_mTUL_AdditionalExternalTurnout2;
  /*private*/ JCheckBox* _mTUL_AdditionalExternalTurnout2FeedbackDifferent;
  /*private*/ JComboBox/*<String>*/*_mTUL_AdditionalExternalTurnout3;
  /*private*/ JCheckBox* _mTUL_AdditionalExternalTurnout3FeedbackDifferent;
  /*private*/ JComboBox/*<String>*/*_mTUL_DispatcherInternalSensorLockToggle;
  /*private*/ JComboBox/*<String>*/*_mTUL_DispatcherInternalSensorUnlockedIndicator;
  /*private*/ JComboBox/*<String>*/*_mTUL_ExternalTurnout;
  /*private*/ JCheckBox* _mTUL_ExternalTurnoutFeedbackDifferent;
  /*private*/ JCheckBox* _mTUL_GUI_IconsEnabled;
  /*private*/ QButtonGroup* _mTUL_LockImplementation;
  /*private*/ JCheckBox* _mTUL_NoDispatcherControlOfSwitch;
  /*private*/ JCheckBox* _mTUL_ndcos_WhenLockedSwitchStateIsClosed;
  /*private*/ JButton* jButton2;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel11;
  /*private*/ JLabel* jLabel2;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel6;
  /*private*/ JLabel* jLabel7;
  /*private*/ QRadioButton*  jRadioButton1;
  /*private*/ QRadioButton*  jRadioButton2;
  // End of variables declaration
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgTUL";     // NOI18N
  /*private*/ static /*final*/ QString PREFIX;// = "_mTUL_";              // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ /*final*/ CTCSerialData* _mCTCSerialData;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ ProgramProperties* _mProgramProperties;
  /*private*/ /*final*/ CheckJMRIObject* _mCheckJMRIObject;

  //  For support of no dups:
  /*private*/ /*final*/ QSet<QString> _mStartingHashSetOfTurnouts = QSet<QString>();
  /*private*/ /*final*/ QList<QString> _mArrayListOfThisRecordsUsedLockedTurnouts = QList<QString>(); // Should "always" be 4 in length.  See "initializeAll4LockedTurnoutJComboBoxesAndSupportingData"
  /*private*/ bool _mIgnoreActionEvent = false;
  /*private*/ QString _mCurrentExternalTurnout;
  /*private*/ QString _mCurrentAdditionalTurnout1;
  /*private*/ QString _mCurrentAdditionalTurnout2;
  /*private*/ QString _mCurrentAdditionalTurnout3;
  //  End of support of no dups.

  /*private*/ QString _mTUL_ExternalTurnoutOrig;
  /*private*/ bool _mTUL_ExternalTurnoutFeedbackDifferentOrig;
  /*private*/ bool _mTUL_NoDispatcherControlOfSwitchOrig;
  /*private*/ bool _mTUL_ndcos_WhenLockedSwitchStateIsClosedOrig;
  /*private*/ bool _mTUL_GUI_IconsEnabledOrig;
  /*private*/ CodeButtonHandlerData::LOCK_IMPLEMENTATION _mTUL_LockImplementationOrig;
  /*private*/ QString _mTUL_AdditionalExternalTurnout1Orig;
  /*private*/ bool _mTUL_AdditionalExternalTurnout1FeedbackDifferentOrig;
  /*private*/ QString _mTUL_AdditionalExternalTurnout2Orig;
  /*private*/ bool _mTUL_AdditionalExternalTurnout2FeedbackDifferentOrig;
  /*private*/ QString _mTUL_AdditionalExternalTurnout3Orig;
  /*private*/ bool _mTUL_AdditionalExternalTurnout3FeedbackDifferentOrig;
  /*private*/ void initOrig();
  /*private*/ bool dataChanged();
  /*public*/ static bool dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData);
  /*private*/ QList<QString> formFieldsValid();
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);
  /*private*/ void initializeAll4LockedTurnoutJComboBoxesAndSupportingData();
  /*private*/ void update1LockedTurnoutJComboBox(JComboBox/*<String>*/*jComboBox, int index, QString currentSelection);
  /*private*/ QSet<QString> returnHashSetSubset(int indexToLeaveOff);
  /*public*/ void populateJComboBox(JComboBox/*<String>*/*jComboBox, QSet<QString> populateWith, QString currentSelection);
public slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mTUL_ExternalTurnoutActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mTUL_AdditionalExternalTurnout1ActionPerformed(/*java.awt.event.ActionEvent evt*/) ;
  /*private*/ void _mTUL_AdditionalExternalTurnout2ActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mTUL_AdditionalExternalTurnout3ActionPerformed(/*java.awt.event.ActionEvent evt*/) ;
  /*private*/ void _mTUL_NoDispatcherControlOfSwitchActionPerformed(/*java.awt.event.ActionEvent evt*/) ;

  friend class FrmTUL_windowListener;
  friend class Columns;
};

class FrmTUL_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmTUL* dlg;
 public:
  FrmTUL_windowListener(FrmTUL* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

#endif // FRMTUL_H
