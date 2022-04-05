#ifndef DEBUGGERMALEDIGITALEXPRESSIONSOCKET_H
#define DEBUGGERMALEDIGITALEXPRESSIONSOCKET_H

#include "abstractdebuggermalesocket.h"
#include "maledigitalexpressionsocket.h"

class DebuggerMaleDigitalExpressionSocket : public AbstractDebuggerMaleSocket, public MaleDigitalExpressionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalExpressionSocket)
 public:
  explicit DebuggerMaleDigitalExpressionSocket(BaseManager/*<MaleDigitalExpressionSocket>*/* manager, MaleDigitalExpressionSocket* maleSocket, QObject *parent = nullptr);
  /*public*/  void notifyChangedResult(bool oldResult, bool newResult)override;
  /*public*/  QString getBeforeInfo()override;
  /*public*/  QString getAfterInfo()override;
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  bool getLastResult()override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString describeState(int state)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType() override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.tools.debugger.DebuggerMaleDigitalExpressionSocket";}

  QObject* self() override {return (QObject*)this;}
 private:
  /*private*/ bool _lastResult;
};

#endif // DEBUGGERMALEDIGITALEXPRESSIONSOCKET_H
