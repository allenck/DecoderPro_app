#ifndef CHECKFORUPDATEACTION_H
#define CHECKFORUPDATEACTION_H

#include "jmriabstractaction.h"
#include "actionlistener.h"

class CheckForUpdateAction : public JmriAbstractAction
{
 public:
  /*public*/ CheckForUpdateAction(/*@Nonnull*/  QString s, /*@Nonnull*/  WindowInterface* wi);
  /*public*/ CheckForUpdateAction(/*@Nonnull*/  QString s, /*@Nonnull*/  QIcon i, /*@Nonnull*/  WindowInterface* wi);
  /*public*/ CheckForUpdateAction(QWidget* parent);
  /*public*/ JmriPanel* makePanel()override;

 public slots:
  /*public*/ void actionPerformed(JActionEvent* ev)override;

 private:
  /*@Nonnull*/  QString getNumber(/*@Nonnull*/  /*BufferedReader*/QTextStream* reader) /*throw (IOException)*/;
  static Logger* log;
};

#endif // CHECKFORUPDATEACTION_H
