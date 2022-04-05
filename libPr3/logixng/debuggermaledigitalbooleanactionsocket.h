#ifndef DEBUGGERMALEDIGITALBOOLEANACTIONSOCKET_H
#define DEBUGGERMALEDIGITALBOOLEANACTIONSOCKET_H

#include "abstractdebuggermalesocket.h"
#include "maledigitalbooleanactionsocket.h"

class DebuggerMaleDigitalBooleanActionSocket : public AbstractDebuggerMaleSocket, public MaleDigitalBooleanActionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalBooleanActionSocket)
 public:
  explicit DebuggerMaleDigitalBooleanActionSocket(BaseManager/*<MaleDigitalBooleanActionSocket>*/* manager, MaleDigitalBooleanActionSocket* maleSocket,QObject *parent = nullptr);
  /*public*/  QString getBeforeInfo()override;
  /*public*/  QString getAfterInfo()override;
  /*public*/  void execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/ override;
  /*public*/  void setState(int s) /*throws JmriException*/ override;
  /*public*/  int getState()override;
  /*public*/  QString describeState(int state)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType()override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.tools.debugger.DebuggerMaleDigitalBooleanActionSocket";}

  QObject* self() override {return (QObject*)this;}
 private:
  /*private*/ bool _nextHasChangedToTrue;
  /*private*/ bool _nextHasChangedToFalse;

};

#endif // DEBUGGERMALEDIGITALBOOLEANACTIONSOCKET_H
