#ifndef CREATEBUTTONMODEL_H
#define CREATEBUTTONMODEL_H
#include "abstractactionmodel.h"
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT CreateButtonModel : public AbstractActionModel
{
    Q_OBJECT
public:
    explicit CreateButtonModel(QObject *parent = 0);
    ~CreateButtonModel() {}
    CreateButtonModel(const CreateButtonModel&)
        : AbstractActionModel() {}
    static /*public*/ void rememberObject(CreateButtonModel* m) ;
    static /*public*/ QList<CreateButtonModel*> rememberedObjects();
    static QList<CreateButtonModel*> l;// = new QList<CreateButtonModel>();
signals:

public slots:
};
Q_DECLARE_METATYPE(CreateButtonModel)
#endif // CREATEBUTTONMODEL_H
