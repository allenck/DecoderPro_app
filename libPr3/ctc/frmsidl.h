#ifndef FRMSIDL_H
#define FRMSIDL_H
#include "jframe.h"
#include "jcombobox.h"
#include "jbutton.h"
#include "jlabel.h"
#include "awtwindowproperties.h"
#include "codebuttonhandlerdata.h"
#include "programproperties.h"
#include "checkjmriobject.h"
#include "windowadapter.h"

class FrmSIDL : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmSIDL( AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData,
                       ProgramProperties* programProperties, CheckJMRIObject* checkJMRIObject, QWidget* parent = nullptr);

  /*public*/ bool closedNormally() { return _mClosedNormally; }

 private:
  // Variables declaration - do not modify
  /*private*/ JComboBox* _mSIDL_LeftInternalSensor;
  /*private*/ JLabel* _mSIDL_LeftInternalSensorPrompt;
  /*private*/ JComboBox* _mSIDL_NormalInternalSensor;
  /*private*/ JLabel* _mSIDL_NormalInternalSensorPrompt;
  /*private*/ JComboBox* _mSIDL_RightInternalSensor;
  /*private*/ JLabel* _mSIDL_RightInternalSensorPrompt;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JButton* jButton2;
  // End of variables declaration
  /*private*/ void formWindowClosing(QCloseEvent* evt);
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgSIDL";    // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ ProgramProperties* _mProgramProperties;
  /*private*/ void initComponents();

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/);

  friend class FrmSIDL_windowListener;
};

class FrmSIDL_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmSIDL* dlg;
 public:
  FrmSIDL_windowListener(FrmSIDL* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

#endif // FRMSIDL_H
