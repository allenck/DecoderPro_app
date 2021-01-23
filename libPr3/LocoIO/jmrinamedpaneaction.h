#ifndef JMRINAMEDPANEACTION_H
#define JMRINAMEDPANEACTION_H

#include "jmriabstractaction.h"
#include "logger.h"
#include "windowinterface.h"
#include "libPr3_global.h"

class JmriPanel;
class WindowInterface;
class LIBPR3SHARED_EXPORT JmriNamedPaneAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit JmriNamedPaneAction(QObject *parent = nullptr);
 /*public*/ JmriNamedPaneAction(QString s, WindowInterface* wi, QString paneClass);
 /*public*/ JmriNamedPaneAction(QString s, QIcon i, WindowInterface* wi, QString paneClass);
 /*public*/ JmriNamedPaneAction(QString s, QString p,QObject *parent = nullptr);
 /*public*/ JmriPanel* makePanel() override;

signals:

public slots:

private:
 Logger* log;
 void common();

protected:
 /*protected*/ QString paneClass;
 /*protected*/ WindowInterface::Hint hint;// = WindowInterface.Hint.DEFAULT;
};

#endif // JMRINAMEDPANEACTION_H
