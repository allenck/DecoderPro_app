#ifndef DEBUGGERMALEANALOGACTIONSOCKET_H
#define DEBUGGERMALEANALOGACTIONSOCKET_H

#include "abstractdebuggermalesocket.h"
#include "maleanalogactionsocket.h"

class MaleAnalogActionSocket;
class DebuggerMaleAnalogActionSocket : public AbstractDebuggerMaleSocket, public MaleAnalogActionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleAnalogActionSocket)
 public:
  explicit DebuggerMaleAnalogActionSocket(BaseManager/*<MaleAnalogActionSocket>*/* manager, MaleAnalogActionSocket* maleSocket, QObject *parent = nullptr);
  /*public*/  QString getBeforeInfo()override;
  /*public*/  QString getAfterInfo()override;
  /*public*/  void setValue(double value) /*throws JmriException*/override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString describeState(int state)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType()override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.tools.debugger.DebuggerMaleAnalogActionSocket";}
    /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.tools.debugger.DebuggerMaleAnalogActionSocket";}


  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}


 private:
  double _nextValue;

};

#endif // DEBUGGERMALEANALOGACTIONSOCKET_H
