#ifndef REGION_H
#define REGION_H

#include <QObject>
#include <QVector3D>
#include <QVector>
#include "generalpath.h"
#include "shape.h"

class Logger;
class Region : public QObject
{
 Q_OBJECT
public:
 explicit Region(QVector<QVector3D>* points, QObject *parent = nullptr);
 /*public*/ Region(QString s, QObject* parent  = 0);
 /*public*/ JShape* getPath();
 void initPath(QVector<QVector3D>* points);
 /*public*/ bool isInside(QVector3D p);

signals:

public slots:

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("Region");
 //@SuppressFBWarnings(value = "JCIP_FIELD_ISNT_FINAL_IN_IMMUTABLE_CLASS", justification = "internal state, not changeable from outside")
 GeneralPath* path;
 /*final*/ QVector<QVector3D>* points;

};

#endif // REGION_H
