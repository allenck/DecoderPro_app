#ifndef AUTOMATTABLEACTION_H
#define AUTOMATTABLEACTION_H
#include "abstractaction.h"
#include "liblayouteditor_global.h"

class AutomatTableDataModel;
class AutomatTableFrame;
class LIBLAYOUTEDITORSHARED_EXPORT AutomatTableAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit AutomatTableAction(QObject *parent = 0);
 /*public*/ AutomatTableAction(QString actionName, QObject *parent);
 ~AutomatTableAction() {}
 AutomatTableAction(const AutomatTableAction&) : AbstractAction() {}
signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0);

private:
 AutomatTableDataModel* m;

 AutomatTableFrame* f;
 void common();
};
Q_DECLARE_METATYPE(AutomatTableAction)
#endif // AUTOMATTABLEACTION_H
