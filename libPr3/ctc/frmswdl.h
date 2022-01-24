#ifndef FRMSWDL_H
#define FRMSWDL_H
#include "jframe.h"
#include "windowadapter.h"
#include "awtwindowproperties.h"
#include "programproperties.h"
#include "jbutton.h"
#include "jlabel.h"
#include "jcombobox.h"
#include "codebuttonhandlerdata.h"
#include "checkjmriobject.h"
#include "windowadapter.h"

class FrmSWDL : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmSWDL( AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData,
                  ProgramProperties* programProperties, CheckJMRIObject* checkJMRIObject, QWidget* parent = nullptr);

  /*public*/ bool closedNormally() { return _mClosedNormally; }

 private:
  // Variables declaration - do not modify
  /*private*/ JComboBox* _mSWDL_InternalSensor;
  /*private*/ JLabel* _mSWDL_InternalSensorPrompt;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JButton* jButton2;
  // End of variables declaration
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgSWDL";    // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ ProgramProperties* _mProgramProperties;
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/);


  friend class FrmSWDL_windowListener;
};

class FrmSWDL_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmSWDL* dlg;
 public:
  FrmSWDL_windowListener(FrmSWDL* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};
#endif // FRMSWDL_H
