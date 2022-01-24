#ifndef TURNOUTOPERATIONEDITORDIALOG_H
#define TURNOUTOPERATIONEDITORDIALOG_H

#include <jdialog.h>
#include "windowlistener.h"

class JComboBox;
class TurnoutOperation;
class Turnout;
class TurnoutOperationEditorDialog : public JDialog
{
  Q_OBJECT
 public:
  TurnoutOperationEditorDialog( /*@Nonnull*/ TurnoutOperation* op, Turnout* t, JComboBox* box);

 private:
  static Logger* log;
  /*private*/ TurnoutOperation* myOp;
  /*final*/ Turnout* myTurnout;
  /*final*/ TurnoutOperationEditorDialog* self;
  /*private*/ void init();
  /*private*/ void setTitle();
  static bool editingOps;
  friend class TOEDWindowListener;
};

class TOEDWindowListener : public WindowListener
{
  Q_OBJECT
  TurnoutOperationEditorDialog* dlg;
 public:
  TOEDWindowListener(TurnoutOperationEditorDialog* dlg) {this->dlg = dlg;}
  /*public*/ void windowClosing(QCloseEvent* /*e*/) {
//      dlg-> editingOps->set(false);
   TurnoutOperationEditorDialog::editingOps = false;
  }

};

#endif // TURNOUTOPERATIONEDITORDIALOG_H
