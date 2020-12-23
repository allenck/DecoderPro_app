#ifndef FRMTRL_RULES_H
#define FRMTRL_RULES_H

#include <QObject>
#include "jbutton.h"
#include "jtextfield.h"
#include "jlabel.h"
#include "jcombobox.h"
#include "jcheckbox.h"
#include <QScrollArea>
#include "defaultlistmodel.h"
#include "listselectionevent.h"
#include "trafficlockingdata.h"
#include "windowlistener.h"
#include "jframe.h"
#include "windowadapter.h"
#include "listselectionlistener.h"
#include "jlist.h"

class CheckJMRIObject;
class CTCSerialData;
class CodeButtonHandlerData;
class AwtWindowProperties;
class FrmTRL_Rules : public JFrame
{
  Q_OBJECT
 public:
  explicit FrmTRL_Rules(QWidget *parent = nullptr) {}
  /*public*/ bool closedNormally() { return _mClosedNormally; }
  /*public*/ FrmTRL_Rules(AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData,
                      bool isLeftTraffic,
                      CTCSerialData* ctcSerialData, CheckJMRIObject* checkJMRIObject, QWidget *parent = nullptr);

  /*public*/ static QString getRuleNumberString(int ruleNumber);

  /*public*/ static QString getRuleEnabledString();
  /*public*/ TrafficLockingData::TRLSwitch *getSwitchAllignment(JComboBox* userText, JComboBox* alignment);

 signals:

 public slots:

 private:
  // Variables declaration - do not modify
  /*private*/ JButton* _mAddNew;
  /*private*/ JButton* _mCancel;
  /*private*/ JButton* _mDelete;
  /*private*/ JTextField* _mDestinationSignalOrComment;
  /*private*/ JLabel*  _mDestinationSignalOrCommentPrompt;
  /*private*/ JButton* _mDisableALLRules;
  /*private*/ JButton* _mDupToEnd;
  /*private*/ JButton* _mEditBelow;
  /*private*/ JButton* _mEnableALLRules;
  /*private*/ JButton* _mGroupingListAddReplace;
  /*private*/ JComboBox* _mOS_NumberEntry1;
  /*private*/ JComboBox* _mOS_NumberEntry2;
  /*private*/ JComboBox* _mOS_NumberEntry3;
  /*private*/ JComboBox* _mOS_NumberEntry4;
  /*private*/ JComboBox* _mOS_NumberEntry5;
  /*private*/ JComboBox* _mOccupancyExternalSensor1;
  /*private*/ JComboBox* _mOccupancyExternalSensor2;
  /*private*/ JComboBox* _mOccupancyExternalSensor3;
  /*private*/ JComboBox* _mOccupancyExternalSensor4;
  /*private*/ JComboBox* _mOccupancyExternalSensor5;
  /*private*/ JComboBox* _mOccupancyExternalSensor6;
  /*private*/ JComboBox* _mOccupancyExternalSensor7;
  /*private*/ JComboBox* _mOccupancyExternalSensor8;
  /*private*/ JComboBox* _mOccupancyExternalSensor9;
  /*private*/ JComboBox* _mOptionalExternalSensor1;
  /*private*/ JComboBox* _mOptionalExternalSensor2;
  /*private*/ JCheckBox* _mRuleEnabled;
  /*private*/ JLabel*    _mRulesInfo;
  /*private*/ JButton*   _mSaveAndClose;
  /*private*/ JComboBox* _mSwitchAlignment1;
  /*private*/ JComboBox* _mSwitchAlignment2;
  /*private*/ JComboBox* _mSwitchAlignment3;
  /*private*/ JComboBox* _mSwitchAlignment4;
  /*private*/ JComboBox* _mSwitchAlignment5;
  /*private*/ JList/*<TrafficLockingData*>*/* _mTRL_TrafficLockingRules;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel10;
  /*private*/ JLabel* jLabel2;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  /*private*/ JLabel* jLabel7;
  /*private*/ JLabel* jLabel8;
  /*private*/ QScrollArea* jScrollPane1;
  // End of variables declaration

  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgTRL_Rules";   // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ bool _mIsLeftTraffic;
  /*private*/ /*final*/ CTCSerialData* _mCTCSerialData;
  /*private*/ /*final*/ CheckJMRIObject* _mCheckJMRIObject;
  /*private*/ /*final*/ QList<int> _mArrayListOfSelectableOSSectionUniqueIDs;
  /*private*/ bool _mAddNewPressed;

  /*private*/ /*final*/ DefaultListModel/*<TrafficLockingData*>*/* _mTrafficLockingModel;
  /*private*/ /*final*/ QList<TrafficLockingData*>* _mTrafficLockingRulesOrig = new QList<TrafficLockingData*>();
  /*private*/ void initOrig();
  /*private*/ bool dataChanged();
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(/*java.awt.event.WindowEvent evt*/);
  /*private*/ void _mTRL_TrafficLockingRulesValueChanged(ListSelectionEvent* evt);
  /*private*/ TrafficLockingData* renumberRule(TrafficLockingData* rule, int number);
  /*private*/ void enableTopPart(bool enabled);

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mAddNewActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEditBelowActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mDeleteActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mGroupingListAddReplaceActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mCancelActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEnableALLRulesActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mDisableALLRulesActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mDupToEndActionPerformed(/*java.awt.event.ActionEvent evt*/);

  friend class FTR_WindowListener;
  friend class FTR_ListSelectionListener;
};

class FTR_WindowListener : public WindowAdapter
{
  Q_OBJECT
  FrmTRL_Rules* rules;
 public:
  FTR_WindowListener(FrmTRL_Rules* rules) {this->rules = rules;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent*) {
      rules->formWindowClosing(/*evt*/);
  }
};

class FTR_ListSelectionListener : public ListSelectionListener
{
  Q_OBJECT
  FrmTRL_Rules* rules;
 public:
  FTR_ListSelectionListener(FrmTRL_Rules* rules) {this->rules = rules;}
 public slots:
  //@Override
  /*public*/ void valueChanged(ListSelectionEvent* evt) {
      rules->_mTRL_TrafficLockingRulesValueChanged(evt);
  }
  QObject* self() {return (QObject*)this;}
};
#endif // FRMTRL_RULES_H
