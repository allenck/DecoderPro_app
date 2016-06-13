#ifndef PERFORMFILEMODEL_H
#define PERFORMFILEMODEL_H

#include <QObject>
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT PerformFileModel : public QObject
{
    Q_OBJECT
public:
    explicit PerformFileModel(QObject *parent = 0);
    /*public*/ QString getFileName();
    /*public*/ void setFileName(QString n) ;
    static /*public*/ void rememberObject(PerformFileModel* m) ;
    static /*public*/ QList<PerformFileModel*> rememberedObjects();
signals:

public slots:
private:
    QString fileName;
    static QList<PerformFileModel*> l;// = new QList<PerformFileModel*>();

};

#endif // PERFORMFILEMODEL_H
