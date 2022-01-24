#ifndef FRMFLEETING_H
#define FRMFLEETING_H
#include "jframe.h"
#include "jlabel.h"
#include "jcheckbox.h"
#include "jtextfield.h"
#include "jbutton.h"
#include "windowadapter.h"
#include "awtwindowproperties.h"
#include "otherdata.h"

class FrmFleeting : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmFleeting(AwtWindowProperties* awtWindowProperties, OtherData* otherData, QWidget* parent = nullptr);

  /*public*/ bool closedNormally() { return _mClosedNormally; }

 private:
  // Variables declaration - do not modify
  /*private*/ JCheckBox* _mDefaultFleetingEnabled;
  /*private*/ JTextField* _mFleetingToggleInternalSensor;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JLabel* jLabel21;
  /*private*/ JLabel* jLabel26;
  /*private*/ JLabel* jLabel29;
  // End of variables declaration
  /*private*/ void formWindowClosing(QCloseEvent* evt);
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgFleeting";    // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ /*final*/ OtherData* _mOtherData;
  /*private*/ bool _mClosedNormally = false;

  /*private*/ QString _mFleetingToggleInternalSensorOrig;
  /*private*/ bool _mDefaultFleetingEnabledOrig;
  /*private*/ void initOrig(OtherData* otherData);
  /*private*/ bool dataChanged();
  /*private*/ void initComponents();

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);

  friend class FrmFleeting_windowListener;
};

class FrmFleeting_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmFleeting* dlg;
 public:
  FrmFleeting_windowListener(FrmFleeting* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};
#endif // FRMFLEETING_H
