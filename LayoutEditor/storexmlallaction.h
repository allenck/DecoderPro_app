#ifndef STOREXMLALLACTION_H
#define STOREXMLALLACTION_H
#include "storexmlconfigaction.h"

class ActionEvent;
class StoreXmlAllAction : public StoreXmlConfigAction
{
 Q_OBJECT
public:
 explicit StoreXmlAllAction(QObject *parent = 0);
 /*public*/ StoreXmlAllAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 Logger* log;
};

#endif // STOREXMLALLACTION_H
