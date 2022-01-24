#ifndef SIMPLELIGHTCONTROLACTION_H
#define SIMPLELIGHTCONTROLACTION_H
#include "abstractaction.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT SimpleLightCtrlAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit SimpleLightCtrlAction(QObject *parent = 0);
 /*public*/ SimpleLightCtrlAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0)override;

private:
 void common();

};

#endif // SIMPLELIGHTCONTROLACTION_H
