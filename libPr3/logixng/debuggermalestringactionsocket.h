#ifndef DEBUGGERMALESTRINGACTIONSOCKET_H
#define DEBUGGERMALESTRINGACTIONSOCKET_H

#include "abstractdebuggermalesocket.h"
#include "malestringactionsocket.h"

class DebuggerMaleStringActionSocket : public AbstractDebuggerMaleSocket, public MaleStringActionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleStringActionSocket)
 public:
  explicit DebuggerMaleStringActionSocket(BaseManager/*<MaleStringActionSocket>*/* manager, MaleStringActionSocket* maleSocket, QObject *parent = nullptr);
  /*public*/  QString getBeforeInfo()override;
  /*public*/  QString getAfterInfo()override;
  /*public*/  void setValue(/*@Nonnull*/ QString value) /*throws JmriException*/ override;
  /*public*/  void setState(int s) /*throws JmriException */override;
  /*public*/  int getState()override;
  /*public*/  QString describeState(int state)override;
  /*public*/  void setProperty(QString key, QVariant value) override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key) override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType()override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.tools.debugger.DebuggerMaleStringActionSocket";}

  QObject* self() override {return (QObject*)this;}

 private:
  /*private*/ QString _nextValue;

};

#endif // DEBUGGERMALESTRINGACTIONSOCKET_H
