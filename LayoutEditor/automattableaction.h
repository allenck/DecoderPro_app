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
 explicit AutomatTableAction(QObject *parent);
 /*public*/ AutomatTableAction(QString actionName, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 AutomatTableDataModel* m;

 AutomatTableFrame* f;
 void common();
};

#endif // AUTOMATTABLEACTION_H
