#ifndef FRMADDMODIFYCTCCOLUMN_H
#define FRMADDMODIFYCTCCOLUMN_H
#include "jframe.h"
#include "jspinner.h"
#include "jcheckbox.h"
#include "jlabel.h"
#include "jbutton.h"
#include "awtwindowproperties.h"
#include "columns.h"
#include "commonsubs.h"
#include "windowadapter.h"
#include "swingconstants.h"

class FrmAddModifyCTCColumn : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmAddModifyCTCColumn(AwtWindowProperties* awtWindowProperties,
          Columns* columns,
          bool isModify,
          int existingSwitchNumber,
          int existingGUIColumnNumber,
          bool existingGUIGeneratedAtLeastOnceAlready,
          QObject* parent = nullptr);

  /*public*/ int _mNewSwitchNumber;
  /*public*/ int _mNewSignalEtcNumber;
  /*public*/ int _mNewGUIColumnNumber;
  /*public*/ bool _mNewGUIGeneratedAtLeastOnceAlready;
  /*public*/ bool closedNormally() { return _mClosedNormally; }

 private:
  // Variables declaration - do not modify
  /*private*/ JSpinner* _mGUIColumnNumber;
  /*private*/ JCheckBox* _mGUIGeneratedAtLeastOnceAlready;
  /*private*/ JSpinner* _mGUISwitchNumber;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel2;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  // End of variables declaration

  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgAddModifyCTCColumn";  // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ /*final*/ Columns* _mColumns;
  /*private*/ /*final*/ bool _mIsModify;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);


  friend class FrmAddModify_windowListener;
};


class FrmAddModify_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmAddModifyCTCColumn* dlg;
 public:
  FrmAddModify_windowListener(FrmAddModifyCTCColumn* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

#endif // FRMADDMODIFYCTCCOLUMN_H
