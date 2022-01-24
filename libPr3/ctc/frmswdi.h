#ifndef FRMSWDI_H
#define FRMSWDI_H
#include "jframe.h"
#include "codebuttonhandlerdata.h"
#include "windowadapter.h"
#include "jlabel.h"
#include <QRadioButton>
#include "jbutton.h"
#include "awtwindowproperties.h"
#include "jcombobox.h"
#include "jcheckbox.h"
#include "codebuttonhandlerdataroutines.h"

class JFormattedTextField;
class QButtonGroup;
class ProgramProperties;
class CheckJMRIObject;
class FrmSWDI : public JFrame
{
  Q_OBJECT
 public:
  FrmSWDI(QWidget* parent = nullptr);
  /*public*/ bool closedNormally(){ return _mClosedNormally; }
  /*public*/ FrmSWDI( AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData,
                  ProgramProperties* programProperties, CheckJMRIObject* checkJMRIObject, QWidget* parent = nullptr);
  /*public*/ static bool dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData);

 private:
  // Variables declaration - do not modify
  QRadioButton* _mCrossover;
  QRadioButton* _mDoubleCrossover;
  JLabel* _mSWDI_ActualTurnoutPrompt;
  JFormattedTextField* _mSWDI_CodingTimeInMilliseconds;
  JComboBox* _mSWDI_ExternalTurnout;
  JCheckBox*  _mSWDI_FeedbackDifferent;
  JCheckBox*  _mSWDI_GUICrossoverLeftHand;
  JCheckBox*  _mSWDI_GUITurnoutLeftHand;
  QButtonGroup* _mSWDI_GUITurnoutType;
  JComboBox* _mSWDI_NormalInternalSensor;
  JLabel* _mSWDI_NormalInternalSensorPrompt;
  JComboBox* _mSWDI_ReversedInternalSensor;
  JLabel* _mSWDI_ReversedInternalSensorPrompt;
  JButton*  _mSaveAndClose;
  QRadioButton* _mTurnout;
  JButton*  jButton2;
  JLabel* jLabel19;
  JLabel* jLabel2;
  JLabel* jLabel3;
  // End of variables declaration
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgSWDI";    // NOI18N
  /*private*/ static /*final*/ QString PREFIX;// = "_mSWDI_";             // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ ProgramProperties* _mProgramProperties;
  /*private*/ /*final*/ CheckJMRIObject* _mCheckJMRIObject;

  /*private*/ QString _mSWDI_ExternalTurnoutOrig;
  /*private*/ int _mSWDI_CodingTimeInMillisecondsOrig;
  /*private*/ bool _mSWDI_FeedbackDifferentOrig;
  /*private*/ CodeButtonHandlerData::TURNOUT_TYPE _mSWDI_GUITurnoutTypeOrig;
  /*private*/ bool _mSWDI_GUITurnoutLeftHandOrig;
  /*private*/ bool _mSWDI_GUICrossoverLeftHandOrig;
  /*private*/ void initOrig();
  /*private*/ bool dataChanged();
  /*private*/ QList<QString> formFieldsValid();
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mTurnoutActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mCrossoverActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mDoubleCrossoverActionPerformed(/*java.awt.event.ActionEvent evt*/);


  friend class FrmSWDI_windowListener;
};

class FrmSWDI_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmSWDI* dlg;
 public:
  FrmSWDI_windowListener(FrmSWDI* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};
#endif // FRMSWDI_H
