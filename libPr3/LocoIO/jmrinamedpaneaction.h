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
 explicit JmriNamedPaneAction(QObject *parent = 0);
 /*public*/ JmriNamedPaneAction(QString s, WindowInterface* wi, QString paneClass);
 /*public*/ JmriNamedPaneAction(QString s, QIcon i, WindowInterface* wi, QString paneClass);
 /*public*/ JmriNamedPaneAction(QString s, QString p,QObject *parent = 0);
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
// /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 Logger* log;
 WindowInterface* wi;
 void common();
 JmriPanel* cache;

protected:
 /*protected*/ QString paneClass;
/*protected*/ QObject* context;// = NULL;
 /*protected*/ WindowInterface::Hint hint;// = WindowInterface.Hint.DEFAULT;
};

#endif // JMRINAMEDPANEACTION_H
