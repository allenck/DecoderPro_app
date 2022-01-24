#ifndef FRMTRL_H
#define FRMTRL_H
#include "jframe.h"
#include "jbutton.h"
#include "jlabel.h"
#include "awtwindowproperties.h"
#include "codebuttonhandlerdata.h"
#include "ctcserialdata.h"
#include "frmmainform.h"
#include "topology.h"
#include "frmtrl_rules.h"

class FrmTRL : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmTRL(  AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData,
                  CTCSerialData* ctcSerialData, CheckJMRIObject* checkJMRIObject, QWidget* parent = nullptr);
  /*public*/ bool closedNormally() { return _mClosedNormally; }
  /*public*/ static bool dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData);

 private:
  // Variables declaration - do not modify
  /*private*/ JButton* _mAutoGenerate;
  /*private*/ JLabel* _mAutoGenerateWarning;
  /*private*/ JButton* _mEditLeftTrafficLockingRules;
  /*private*/ JButton* _mEditRightTrafficLockingRules;
  /*private*/ JLabel* _mLeftNumberOfRules;
  /*private*/ JLabel* _mLeftNumberOfRulesPrompt;
  /*private*/ JButton* _mOK;
  /*private*/ JButton* _mReverseLeftRight;
  /*private*/ JLabel* _mRightNumberOfRules;
  /*private*/ JLabel* _mRightNumberOfRulesPrompt;
  /*private*/ JLabel* jLabel10;
  /*private*/ JLabel* jLabel11;
  /*private*/ JLabel* jLabel4;
  // End of variables declaration
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgTRL";     // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ CTCSerialData* _mCTCSerialData;
  /*private*/ /*final*/ CheckJMRIObject* _mCheckJMRIObject;
  /*private*/ /*final*/ FrmMainForm* _mMainForm;
  /*private*/ Topology* _mTopology;
  /*private*/ void initOrig();
  /*private*/ bool dataChanged();
  /*private*/ QList<QString> getListOfExternalSensorsSlaved(   CodeButtonHandlerData* currentCodeButtonHandlerData,
                                                              QList<CodeButtonHandlerData*> codeButtonHandlerDataArrayList);
  /*private*/ void updateRuleCounts();
  /*private*/ static bool valid(CheckJMRIObject* checkJMRIObject, QList<TrafficLockingData*>* trafficLockingRules);
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);

 private slots:
  /*private*/ void _mEditLeftTrafficLockingRulesActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEditRightTrafficLockingRulesActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mOKActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mReverseLeftRightActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mAutoGenerateActionPerformed(/*java.awt.event.ActionEvent evt*/);

  friend class FrmTRL_windowListener;
  friend class FrmTRL_Rules_windowListener;
};

class FrmTRL_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmTRL* dlg;
 public:
  FrmTRL_windowListener(FrmTRL* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

class FrmTRL_Rules_windowListener : public WindowListener
{
  Q_OBJECT
  FrmTRL* frmTRL;
  FrmTRL_Rules* dialog;
 public:
  FrmTRL_Rules_windowListener(FrmTRL_Rules* dialog, FrmTRL* frmTRL)
  {
   this->dialog = dialog;
   this->frmTRL = frmTRL;
  }
  /*public*/ void windowClosing(QCloseEvent *){}
  /*public*/ void windowClosed(QCloseEvent* e) {
      if (dialog->closedNormally()) {
          frmTRL->_mClosedNormally = true;
          frmTRL->updateRuleCounts();
      }
      frmTRL->_mMainForm->_mTRL_RulesFormOpen = false;
  }
  friend class FrmTRL_Rules;
};

#endif // FRMTRL_H
