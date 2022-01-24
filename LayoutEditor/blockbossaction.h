#ifndef BLOCKBOSSACTION_H
#define BLOCKBOSSACTION_H
#include "abstractaction.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT BlockBossAction : public AbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit BlockBossAction(QObject *parent = 0);
  ~BlockBossAction() {}
  BlockBossAction(const BlockBossAction&) : AbstractAction() {}
 /*public*/ BlockBossAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0) override;

private:
 void common();
};
Q_DECLARE_METATYPE(BlockBossAction);
#endif // BLOCKBOSSACTION_H
