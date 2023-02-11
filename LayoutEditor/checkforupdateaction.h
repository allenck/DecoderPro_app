#ifndef CHECKFORUPDATEACTION_H
#define CHECKFORUPDATEACTION_H

#include "jmriabstractaction.h"
#include "actionlistener.h"

class CheckForUpdateAction : public JmriAbstractAction
{
  Q_OBJECT
 public:
  /*public*/ CheckForUpdateAction(/*@Nonnull*/  QString s, /*@Nonnull*/  WindowInterface* wi);
  /*public*/ CheckForUpdateAction(/*@Nonnull*/  QString s, /*@Nonnull*/  QIcon i, /*@Nonnull*/  WindowInterface* wi);
  Q_INVOKABLE/*public*/ CheckForUpdateAction(QWidget* parent = nullptr);
  ~CheckForUpdateAction() {}
  CheckForUpdateAction(const CheckForUpdateAction&) : JmriAbstractAction() {}

  /*public*/ JmriPanel* makePanel()override;

 public slots:
  /*public*/ void actionPerformed(JActionEvent* ev)override;

 private:
  /*@Nonnull*/  QString getNumber(/*@Nonnull*/  /*BufferedReader*/QTextStream* reader) /*throw (IOException)*/;
  static Logger* log;
};
Q_DECLARE_METATYPE(CheckForUpdateAction)
#endif // CHECKFORUPDATEACTION_H
