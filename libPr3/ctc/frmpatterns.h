#ifndef FRMPATTERNS_H
#define FRMPATTERNS_H
#include "jframe.h"
#include "jlabel.h"
#include "jbutton.h"
#include "jtextfield.h"
#include "awtwindowproperties.h"
#include "programproperties.h"
#include "windowadapter.h"

class FrmPatterns : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmPatterns(AwtWindowProperties* awtWindowProperties, ProgramProperties* programProperties, QWidget* parent = nullptr);

  /*public*/ bool closedNormally() { return _mClosedNormally; }

 private:
  // Variables declaration - do not modify
  /*private*/ JTextField* _mCO_CallOnToggleInternalSensorPattern;
  /*private*/ JTextField* _mCodeButtonInternalSensorPattern;
  /*private*/ JTextField* _mSIDI_LeftInternalSensorPattern;
  /*private*/ JTextField* _mSIDI_NormalInternalSensorPattern;
  /*private*/ JTextField* _mSIDI_RightInternalSensorPattern;
  /*private*/ JTextField* _mSIDL_LeftInternalSensorPattern;
  /*private*/ JTextField* _mSIDL_NormalInternalSensorPattern;
  /*private*/ JTextField* _mSIDL_RightInternalSensorPattern;
  /*private*/ JTextField* _mSWDI_NormalInternalSensorPattern;
  /*private*/ JTextField* _mSWDI_ReversedInternalSensorPattern;
  /*private*/ JTextField* _mSWDL_InternalSensorPattern;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JTextField* _mTUL_DispatcherInternalSensorLockTogglePattern;
  /*private*/ JTextField* _mTUL_DispatcherInternalSensorUnlockedIndicatorPattern;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel10;
  /*private*/ JLabel* jLabel11;
  /*private*/ JLabel* jLabel12;
  /*private*/ JLabel* jLabel13;
  /*private*/ JLabel* jLabel14;
  /*private*/ JLabel* jLabel15;
  /*private*/ JLabel* jLabel16;
  /*private*/ JLabel* jLabel20;
  /*private*/ JLabel* jLabel28;
  /*private*/ JLabel* jLabel3;
  /*private*/ JLabel* jLabel30;
  /*private*/ JLabel* jLabel31;
  /*private*/ JLabel* jLabel32;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  /*private*/ JLabel* jLabel6;
  /*private*/ JLabel* jLabel7;
  /*private*/ JLabel* jLabel8;
  /*private*/ JLabel* jLabel9;
  // End of variables declaration
  /*private*/ void formWindowClosing(QCloseEvent* evt) ;
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgPatterns";    // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ /*final*/ ProgramProperties* _mProgramProperties;
  /*private*/ bool _mClosedNormally = false;

  /*private*/ QString _mCodeButtonInternalSensorPatternOrig;
  /*private*/ QString _mSIDI_LeftInternalSensorPatternOrig;
  /*private*/ QString _mSIDI_NormalInternalSensorPatternOrig;
  /*private*/ QString _mSIDI_RightInternalSensorPatternOrig;
  /*private*/ QString _mSIDL_LeftInternalSensorPatternOrig;
  /*private*/ QString _mSIDL_NormalInternalSensorPatternOrig;
  /*private*/ QString _mSIDL_RightInternalSensorPatternOrig;
  /*private*/ QString _mSWDI_NormalInternalSensorPatternOrig;
  /*private*/ QString _mSWDI_ReversedInternalSensorPatternOrig;
  /*private*/ QString _mSWDL_InternalSensorPatternOrig;
  /*private*/ QString _mCO_CallOnToggleInternalSensorPatternOrig;
  /*private*/ QString _mTUL_DispatcherInternalSensorLockTogglePatternOrig;
  /*private*/ QString _mTUL_DispatcherInternalSensorUnlockedIndicatorPatternOrig;
  /*private*/ void initOrig(ProgramProperties* programProperties);
  /*private*/ bool dataChanged();
  /*private*/ void initComponents();

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);

  friend class FrmPatterns_windowListener;
};

class FrmPatterns_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmPatterns* dlg;
 public:
  FrmPatterns_windowListener(FrmPatterns* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};
#endif // FRMPATTERNS_H
