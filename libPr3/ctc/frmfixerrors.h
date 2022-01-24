#ifndef FRMFIXERRORS_H
#define FRMFIXERRORS_H
#include "jframe.h"
#include "jbutton.h"
#include "jlabel.h"
#include "awtwindowproperties.h"
#include "columns.h"
#include "windowadapter.h"

class FrmFixErrors : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmFixErrors(AwtWindowProperties* awtWindowProperties, Columns* columns, QWidget* parent = nullptr);


 private:
  // Variables declaration - do not modify
  /*private*/ JButton* _mCancel;
  /*private*/ JLabel* _mInfo;
  /*private*/ JButton* jButton1;
  // End of variables declaration  /*private*/ void formWindowClosing(QCloseEvent* evt);
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgFixErrors";   // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ /*final*/ Columns* _mColumns;
  /*private*/ void exitDialog();
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);

   private slots:
   /*private*/ void _mCancelActionPerformed(/*java.awt.event.ActionEvent evt*/) ;
   /*private*/ void jButton1ActionPerformed(/*java.awt.event.ActionEvent evt*/);

  friend class FrmFixErrors_windowListener;
};

class FrmFixErrors_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmFixErrors* dlg;
 public:
  FrmFixErrors_windowListener(FrmFixErrors* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

#endif // FRMFIXERRORS_H
