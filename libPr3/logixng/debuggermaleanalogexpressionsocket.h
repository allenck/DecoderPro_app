#ifndef DEBUGGERMALEANALOGEXPRESSIONSOCKET_H
#define DEBUGGERMALEANALOGEXPRESSIONSOCKET_H

#include "abstractdebuggermalesocket.h"
#include "maleanalogexpressionsocket.h"

class BaseManager;
class MaleAnalogExpressionSocket;
class DebuggerMaleAnalogExpressionSocket : public AbstractDebuggerMaleSocket, public MaleAnalogExpressionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleAnalogExpressionSocket)
 public:
  explicit DebuggerMaleAnalogExpressionSocket(BaseManager/*<MaleAnalogExpressionSocket>*/* manager,
                                              MaleSocket *maleSocket, QObject * parent = nullptr);
  /*public*/  QString getBeforeInfo()override;
  /*public*/  QString getAfterInfo()override;
  /*public*/  double evaluate() /*throws JmriException*/ override;
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

  QObject* self() override {return (QObject*)this;}

 private:
  /*private*/ double _lastResult;

};

#endif // DEBUGGERMALEANALOGEXPRESSIONSOCKET_H
