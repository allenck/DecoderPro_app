#ifndef DEBUGGERMALESTRINGEXPRESSIONSOCKET_H
#define DEBUGGERMALESTRINGEXPRESSIONSOCKET_H

#include "abstractdebuggermalesocket.h"
#include "malestringexpressionsocket.h"

class DebuggerMaleStringExpressionSocket : public AbstractDebuggerMaleSocket, public MaleStringExpressionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleStringExpressionSocket)
 public:
  explicit DebuggerMaleStringExpressionSocket(BaseManager/*<MaleStringExpressionSocket>*/* manager, MaleStringExpressionSocket* maleSocket, QObject *parent = nullptr);
  /*public*/  QString getBeforeInfo()override;
  /*public*/  QString getAfterInfo()override;
  /*public*/  QString evaluate() /*throws JmriException*/override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString describeState(int state)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType()override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/  void setTriggerOnChange(bool triggerOnChange)override;
  /*public*/  bool getTriggerOnChange()override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.tools.debugger.DebuggerMaleStringExpressionSocket";}

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 private:
  /*private*/ QString _lastResult;

};

#endif // DEBUGGERMALESTRINGEXPRESSIONSOCKET_H
