#ifndef ERRORHANDLINGDIALOG_MULTILINE_H
#define ERRORHANDLINGDIALOG_MULTILINE_H

#include <QObject>
#include "base.h"
#include "jdialog.h"
#include "jcheckbox.h"
#include "windowadapter.h"
#include "actionevent.h"


class ErrorHandlingDialog_MultiLine : public QObject
{
  Q_OBJECT
 public:
  explicit ErrorHandlingDialog_MultiLine(QObject *parent = nullptr) {}
  /*public*/ bool showDialog(Base* item, QString errorMessage, QList<QString> errorMessageList);

 signals:

 private:
  /*private*/ Base* _item;
  /*private*/ JDialog* _errorDialog;

  /*private*/ /*final*/ JCheckBox* _disableConditionalNGCheckBox =
          new JCheckBox(tr("ErrorHandlingDialog_DisableConditionalNG"));   // NOI18N

  /*private*/ /*final*/ JCheckBox* _disableLogixNGCheckBox =
          new JCheckBox(tr("Disable this LogixNG"));   // NOI18N

  /*private*/ /*final*/ JCheckBox* _stopAllLogixNGCheckBox =
          new JCheckBox(tr("Stop all LogixNGs"));   // NOI18N

  /*private*/ bool _abortExecution = false;
  /*private*/ void handleCheckBoxes();
  /*private*/ void abortPressed(JActionEvent* e =0);
  /*private*/ void continuePressed(JActionEvent* e =0);

  friend class EHDMWindowListener;
};
class EHDMWindowListener : public WindowAdapter
{
  Q_OBJECT
  ErrorHandlingDialog_MultiLine* ehd;
  public:
  EHDMWindowListener(ErrorHandlingDialog_MultiLine* ehd) {this->ehd = ehd;}
  /*public*/  void windowClosing(QCloseEvent* e) {
      ehd->continuePressed(nullptr);
  }

};
#endif // ERRORHANDLINGDIALOG_MULTILINE_H
