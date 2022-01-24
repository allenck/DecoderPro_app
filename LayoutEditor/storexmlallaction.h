#ifndef STOREXMLALLACTION_H
#define STOREXMLALLACTION_H
#include "storexmlconfigaction.h"

class JActionEvent;
class StoreXmlAllAction : public StoreXmlConfigAction
{
 Q_OBJECT
public:
 explicit StoreXmlAllAction(QObject *parent = 0);
 /*public*/ StoreXmlAllAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0) override;
private:
 Logger* log;
};

#endif // STOREXMLALLACTION_H
