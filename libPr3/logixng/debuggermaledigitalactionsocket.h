#ifndef DEBUGGERMALEDIGITALACTIONSOCKET_H
#define DEBUGGERMALEDIGITALACTIONSOCKET_H

#include "abstractdebuggermalesocket.h"
#include "maledigitalactionsocket.h"

class MaleDigitalActionSocket;
class DebuggerMaleDigitalActionSocket : public AbstractDebuggerMaleSocket, public MaleDigitalActionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalActionSocket)
 public:
  explicit DebuggerMaleDigitalActionSocket(BaseManager/*<MaleDigitalActionSocket>*/* manager, /*MaleDigitalActionSocket*/NamedBean* maleSocket, QObject *parent = nullptr);
  /*public*/  QString getBeforeInfo()override;
  /*public*/  QString getAfterInfo()override;
  /*public*/  void execute() /*throws JmriException */override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString describeState(int state)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType()override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/  QString getClassName() override;

  QObject* self() override {return (QObject*)this;}
};

#endif // DEBUGGERMALEDIGITALACTIONSOCKET_H
