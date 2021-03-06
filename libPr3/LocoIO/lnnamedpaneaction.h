#ifndef LNNAMEDPANEACTION_H
#define LNNAMEDPANEACTION_H
#include "jmrinamedpaneaction.h"
#include "logger.h"
#include "libPr3_global.h"

class JmriPanel;
class WindowInterface;
class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT LnNamedPaneAction : public JmriNamedPaneAction
{
 Q_OBJECT
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
