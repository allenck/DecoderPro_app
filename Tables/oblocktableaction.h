#ifndef OBLOCKTABLEACTION_H
#define OBLOCKTABLEACTION_H
#include "abstractaction.h"
#include "libtables_global.h"

class TableFrames;
class LIBTABLESSHARED_EXPORT OBlockTableAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit OBlockTableAction(QObject *parent = 0);
 /*public*/ OBlockTableAction(QString actionName, QObject *parent);
 ~OBlockTableAction() {}
 OBlockTableAction(const OBlockTableAction&) : AbstractAction() {}

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};
Q_DECLARE_METATYPE(OBlockTableAction)
#endif // OBLOCKTABLEACTION_H
