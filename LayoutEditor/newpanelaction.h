#ifndef NEWPANELACTION_H
#define NEWPANELACTION_H
#include "abstractaction.h"

class NewPanelAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit NewPanelAction(QObject *parent );
 /*public*/ NewPanelAction(QString s,QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent * = 0) override;

private:
 void common();
};

#endif // NEWPANELACTION_H
