#ifndef FRMCO_H
#define FRMCO_H

#include "jframe.h"
#include "codebuttonhandlerdata.h"
#include "awtwindowproperties.h"
#include "programproperties.h"
#include "ctcserialdata.h"
#include "checkjmriobject.h"
#include "defaultlistmodel.h"
#include "callondata.h"
#include "jbutton.h"
#include "jcombobox.h"
#include "jcheckbox.h"
#include "jlabel.h"
#include "jlist.h"
#include "windowadapter.h"
#include "listselectionlistener.h"

class FrmCO_windowListener;
class FrmCO : public JFrame
{
  Q_OBJECT
 public:
      /*public*/ FrmCO(AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData, ProgramProperties *programProperties,
                           CTCSerialData* ctcSerialData, CheckJMRIObject* checkJMRIObject, bool signalHeadSelected, QWidget *parent = nullptr);
  /*public*/ static bool dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData);


 signals:

 public slots:

 private:
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgCO";  // NOI18N
  /*private*/ static /*final*/ QString PREFIX;// = "_mCO_";           // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ bool _mClosedNormally = false;
  /*public*/ bool closedNormally() { return _mClosedNormally; }
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ ProgramProperties* _mProgramProperties;
  /*private*/ /*final*/ CTCSerialData* _mCTCSerialData;
  /*private*/ /*final*/ CheckJMRIObject* _mCheckJMRIObject;
  /*private*/ /*final*/ bool _mSignalHeadSelected;
  /*private*/ /*final*/ DefaultListModel/*<CallOnData> */* _mDefaultListModel;
  /*private*/ bool _mAddNewPressed;
  /*private*/ QList<CallOnData*> _mDefaultListModelOrig = QList<CallOnData*>();

  // Variables declaration - do not modify
  /*private*/ JButton* _mAddNew;
  /*private*/ JComboBox/*<String>*/* _mCO_CallOnToggleInternalSensor;
  /*private*/ JLabel* _mCO_CallOnToggleInternalSensorPrompt;
  /*private*/ JComboBox/*<String>*/* _mCalledOnExternalSensor;
  /*private*/ JButton* _mCancel;
  /*private*/ JButton* _mDelete;
  /*private*/ JButton* _mEditBelow;
  /*private*/ JComboBox/*<String>*/* _mExternalBlock;
  /*private*/ JComboBox/*<String>*/* _mExternalSignal;
  /*private*/ JButton* _mGroupingListAddReplace;
  /*private*/ JList/*<CallOnData>*/* _mGroupingsList;
  /*private*/ JLabel* _mGroupingsListPrompt;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JComboBox/*<String>*/* _mSignalAspectToDisplay;
  /*private*/ JComboBox/*<String>*/* _mSignalFacingDirection;
  /*private*/ JComboBox/*<String>*/* _mSwitchIndicator1;
  /*private*/ JComboBox/*<String>*/* _mSwitchIndicator2;
  /*private*/ JComboBox/*<String>*/* _mSwitchIndicator3;
  /*private*/ JComboBox/*<String>*/* _mSwitchIndicator4;
  /*private*/ JComboBox/*<String>*/* _mSwitchIndicator5;
  /*private*/ JComboBox/*<String>*/* _mSwitchIndicator6;
  /*private*/ JButton* jButton2;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel10;
  /*private*/ JLabel* jLabel11;
  /*private*/ JLabel* jLabel12;
  /*private*/ JLabel* jLabel13;
  /*private*/ JLabel* jLabel14;
  /*private*/ JLabel* jLabel15;
  /*private*/ JLabel* jLabel16;
  /*private*/ JLabel* jLabel17;
  /*private*/ JLabel* jLabel18;
  /*private*/ JLabel* jLabel3;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  /*private*/ JLabel* jLabel6;
  /*private*/ JLabel* jLabel7;
  /*private*/ JLabel* jLabel8;
  /*private*/ JLabel* jLabel9;
  ///*private*/ JScrollPane jScrollPane1;
  // End of variables declaration

  /*private*/ void initOrig();
  /*private*/ bool dataChanged();
  /*private*/ QList<QString> formFieldsValid();
  /*private*/ void initComponents();
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mAddNewActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEditBelowActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mDeleteActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mGroupingListAddReplaceActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void formWindowClosing(QCloseEvent* evt);
  /*private*/ void jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mGroupingsListValueChanged(ListSelectionEvent* evt);
  /*private*/ void _mCancelActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mSwitchIndicator1ActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void enableTopPart(bool enabled);

  friend class FrmCO_listSelectionListener;
  friend class FrmCO_windowListener;
};

class FrmCO_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmCO* dlg;
 public:
  FrmCO_windowListener(FrmCO* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

class FrmCO_listSelectionListener : public ListSelectionListener
{
 Q_OBJECT
 FrmCO* dlg;
public:
 FrmCO_listSelectionListener(FrmCO* dlg) {this->dlg = dlg;}
 QObject* self() {(QObject*)this;}
 public slots:
  //@Override
  /*public*/ void valueChanged(ListSelectionEvent* evt) override{
      dlg->_mGroupingsListValueChanged(evt);
  }
};
#endif // FRMCO_H
