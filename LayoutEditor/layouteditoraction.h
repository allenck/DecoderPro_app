#ifndef LAYOUTEDITORACTION_H
#define LAYOUTEDITORACTION_H

#include "abstractaction.h"
#include "actionevent.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LayoutEditorAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit LayoutEditorAction(QObject *parent = 0);
 /*public*/ LayoutEditorAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0)override;
private:
 void common();
};

#endif // LAYOUTEDITORACTION_H
