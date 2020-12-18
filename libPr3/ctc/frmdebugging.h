#ifndef FRMDEBUGGING_H
#define FRMDEBUGGING_H
#include "jframe.h"
#include "awtwindowproperties.h"
#include "windowlistener.h"
#include "otherdata.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "jbutton.h"
#include "windowadapter.h"

class FrmDebugging : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmDebugging(AwtWindowProperties* awtWindowProperties, OtherData* otherData, QWidget* parent=nullptr);
  /*public*/ bool closedNormally() { return _mClosedNormally; }


 private:
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgDebugging";   // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ /*final*/ OtherData* _mOtherData;
  /*private*/ bool _mClosedNormally = false;

  /*private*/ QString _mCTCDebugSystemReloadInternalSensorOrig;
  /*private*/ QString _mCTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensorOrig;
  // Variables declaration - do not modify
  /*private*/ JTextField* _mCTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor;
  /*private*/ JTextField* _mCTCSystemReloadInternalSensor;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel2;
  /*private*/ JLabel* jLabel3;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  // End of variables declaration
  /*private*/ void initOrig(OtherData* otherData);
  /*private*/ bool dataChanged();
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);

  friend class FrmDebugging_windowListener;
};

class FrmDebugging_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmDebugging* dlg;
 public:
  FrmDebugging_windowListener(FrmDebugging* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};
#endif // FRMDEBUGGING_H
