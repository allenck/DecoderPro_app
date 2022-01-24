#ifndef LNNAMEDPANEACTION_H
#define LNNAMEDPANEACTION_H
#include "jmrinamedpaneaction.h"
#include "logger.h"
#include "libPr3_global.h"
#include "systemconnectionaction.h"
#include "loconetsystemconnectionmemo.h"

class JmriPanel;
class WindowInterface;
class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT LnNamedPaneAction : public JmriNamedPaneAction//, public SystemConnectionAction/*<LocoNetSystemConnectionMemo*>*/
{
  Q_OBJECT
  //Q_INTERFACES(SystemConnectionAction<LocoNetSystemConnectionMemo*>)
public:
 explicit LnNamedPaneAction(QObject *parent = 0);
 /*public*/ LnNamedPaneAction(QString s, WindowInterface* wi, QString paneClass, LocoNetSystemConnectionMemo* memo);
 /*public*/ LnNamedPaneAction(QString s, QIcon i, WindowInterface* wi, QString paneClass, LocoNetSystemConnectionMemo* memo);
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
private:
 LocoNetSystemConnectionMemo* memo;
 Logger* log;
};

#endif // LNNAMEDPANEACTION_H
