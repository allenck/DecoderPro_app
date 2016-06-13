#ifndef PERFORMSCRIPTMODEL_H
#define PERFORMSCRIPTMODEL_H

#include <QObject>
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT PerformScriptModel : public QObject
{
 Q_OBJECT
public:
 explicit PerformScriptModel(QObject *parent = 0);
 /*public*/ QString getFileName();
 /*public*/ void setFileName(QString n) ;
 static /*public*/ void rememberObject(PerformScriptModel* m);
 static /*public*/ QList<PerformScriptModel*> rememberedObjects() ;

signals:

public slots:
private:
 static QList<PerformScriptModel*> l;// = new QList<PerformScriptModel*>();
 QString fileName;

};

#endif // PERFORMSCRIPTMODEL_H
