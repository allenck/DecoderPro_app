#ifndef ERRORHANDLINGDIALOG_H
#define ERRORHANDLINGDIALOG_H

#include <QObject>
#include "base.h"
#include "jdialog.h"
#include <jcheckbox.h>
#include "windowadapter.h"
#include "actionevent.h"

class ErrorHandlingDialog : public QObject
{
  Q_OBJECT
 public:
  explicit ErrorHandlingDialog(QObject *parent = nullptr);
  /*public*/  bool showDialog(Base* item, QString errorMessage);

 signals:

 private:
  /*private*/ Base* _item;
  /*private*/ JDialog* _errorDialog;
  
  /*private*/ /*final*/ JCheckBox* _disableConditionalNGCheckBox =
          new JCheckBox(tr("Disable this ConditionalNG"));   // NOI18N
  
  /*private*/ /*final*/ JCheckBox* _disableLogixNGCheckBox =
          new JCheckBox(tr("Disable this LogixNG"));   // NOI18N
  
  /*private*/ /*final*/ JCheckBox* _stopAllLogixNGCheckBox =
          new JCheckBox(tr("Stop all LogixNGs"));   // NOI18N
  
  /*private*/ bool _abortExecution = false;
  /*private*/ void handleCheckBoxes();
  /*private*/ void abortPressed(JActionEvent* e =0);
  /*private*/ void continuePressed(JActionEvent* e=0);

  friend class EHDWindowListener;
};

class EHDWindowListener : public WindowAdapter
{
  Q_OBJECT
  ErrorHandlingDialog* ehd;
  public:
  EHDWindowListener(ErrorHandlingDialog* ehd) {this->ehd = ehd;}
  /*public*/  void windowClosing(QCloseEvent* e) {
      ehd->continuePressed(nullptr);
  }

};

#endif // ERRORHANDLINGDIALOG_H
