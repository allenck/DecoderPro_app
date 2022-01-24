#ifndef FRMABOUT_H
#define FRMABOUT_H
#include "jframe.h"
#include "awtwindowproperties.h"
#include "jlabel.h"
#include "jbutton.h"
#include "windowadapter.h"

class FrmAbout : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmAbout(AwtWindowProperties* awtWindowProperties, QWidget* parent = nullptr);

 private:
  // Variables declaration - do not modify
  /*private*/ JLabel* _mHelpTitle;
  /*private*/ JButton* _mOK;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel2;
  /*private*/ JLabel* jLabel3;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  /*private*/ JLabel* jLabel6;
  // End of variables declaration
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "dlgAbout";
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ void initComponents();

 private slots:
  /*private*/ void formWindowClosing(QCloseEvent* evt);
  /*private*/ void _mOKActionPerformed(/*java.awt.event.ActionEvent evt*/);


  friend class FrmAbout_windowListener;
};

class FrmAbout_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmAbout* dlg;
 public:
  FrmAbout_windowListener(FrmAbout* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

#endif // FRMABOUT_H
