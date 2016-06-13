#ifndef PERFORMACTIONMODEL_H
#define PERFORMACTIONMODEL_H
#include "abstractactionmodel.h"
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT PerformActionModel : public AbstractActionModel
{
    Q_OBJECT
public:
    explicit PerformActionModel(QObject *parent = 0);
    ~PerformActionModel() {}
    PerformActionModel(const PerformActionModel&) {}
    static /*public*/ void rememberObject(PerformActionModel* m);
    static /*public*/ QList<PerformActionModel*> rememberedObjects() ;
    static QList<PerformActionModel*> l;// = QList<PerformActionModel*>();

signals:

public slots:

};

#endif // PERFORMACTIONMODEL_H
