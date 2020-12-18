#ifndef FRMDEFAULTS_H
#define FRMDEFAULTS_H
#include "jframe.h"
#include "otherdata.h"
#include "awtwindowproperties.h"
#include "programproperties.h"
#include "jformattedtextfield.h"
#include "jbutton.h"
#include "jcheckbox.h"
#include "jspinner.h"
#include "jlabel.h"
#include <QRadioButton>
#include "windowadapter.h"

class FrmDefaults : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmDefaults(AwtWindowProperties* awtWindowProperties, ProgramProperties* programProperties, OtherData* otherData, QWidget* parent = nullptr);

  /*public*/ bool closedNormally() { return _mClosedNormally; }

 private:
  // Variables declaration - do not modify
  /*private*/ JFormattedTextField* _mCodeButtonDelayTime;
  /*private*/ JFormattedTextField* _mSIDI_CodingTimeInMilliseconds;
  /*private*/ JFormattedTextField* _mSIDI_TimeLockingTimeInMilliseconds;
  /*private*/ JFormattedTextField* _mSWDI_CodingTimeInMilliseconds;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ QButtonGroup* _mSignalSystemType;
  /*private*/ JCheckBox* _mTUL_EnabledAtStartup;
  /*private*/ JSpinner* _mTUL_SecondsToLockTurnouts;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel17;
  /*private*/ JLabel* jLabel18;
  /*private*/ JLabel* jLabel19;
  /*private*/ JLabel* jLabel2;
  /*private*/ JLabel* jLabel22;
  /*private*/ JLabel* jLabel23;
  /*private*/ JLabel* jLabel27;
  /*private*/ JLabel* jLabel3;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  /*private*/ JLabel* jLabel6;
  /*private*/ JLabel* jLabel7;
  /*private*/ QRadioButton* jRadioButton1;
  /*private*/ QRadioButton* jRadioButton2;
  // End of variables declaration
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgDefaults";    // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ /*final*/ ProgramProperties* _mProgramProperties;
  /*private*/ /*final*/ OtherData* _mOtherData;
  /*private*/ bool _mClosedNormally = false;

  /*private*/ int _mSIDI_CodingTimeInMillisecondsOrig;
  /*private*/ int _mSIDI_TimeLockingTimeInMillisecondsOrig;
  /*private*/ int _mSWDI_CodingTimeInMillisecondsOrig;
  /*private*/ bool _mTUL_EnabledAtStartupOrig;
  /*private*/ int _mCodeButtonDelayTimeOrig;
  /*private*/ OtherData::SIGNAL_SYSTEM_TYPE _mSignalSystemTypeOrig;
  /*private*/ int _mTUL_SecondsToLockTurnoutsOrig;
  /*private*/ void initOrig(ProgramProperties* programProperties, OtherData* otherData);
  /*private*/ bool dataChanged();
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);


 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);

  friend class FrmDefaults_windowListener;
};

class FrmDefaults_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmDefaults* dlg;
 public:
  FrmDefaults_windowListener(FrmDefaults* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};
#endif // FRMDEFAULTS_H
