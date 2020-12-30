#ifndef BLOCKBOSSACTION_H
#define BLOCKBOSSACTION_H
#include "abstractaction.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT BlockBossAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit BlockBossAction(QObject *parent = 0);
 /*public*/ BlockBossAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0) override;

private:
 void common();
};

#endif // BLOCKBOSSACTION_H
