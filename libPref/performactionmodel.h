#ifndef PERFORMACTIONMODEL_H
#define PERFORMACTIONMODEL_H
#include "abstractactionmodel.h"
#include "libpref_global.h"
#include "action.h"

class ActionEvent;
class LIBPREFSHARED_EXPORT PerformActionModel : public AbstractActionModel
{
 Q_OBJECT
public:
    explicit PerformActionModel(QObject *parent = 0);
    ~PerformActionModel() {}
    PerformActionModel(const PerformActionModel&) : AbstractActionModel() {}
    static /*public*/ void rememberObject(PerformActionModel* m);
    static /*public*/ QList<PerformActionModel*> rememberedObjects() ;
    static QList<PerformActionModel*> l;// = QList<PerformActionModel*>();

signals:
 void actionPerformed(ActionEvent*);

public slots:
protected slots:
    /*protected*/ void performAction(Action* action) throw (JmriException) ;
};

#endif // PERFORMACTIONMODEL_H
