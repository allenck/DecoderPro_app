#ifndef LISTENINGSPOT_H
#define LISTENINGSPOT_H

#include <QObject>
#include <QtXml>
#include <QVector3D>

class PhysicalLocation;
class Logger;
class ListeningSpot : public QObject
{
 Q_OBJECT
public:
 explicit ListeningSpot(QObject *parent = 0);

 /*public*/ ListeningSpot(QDomElement e);
 /*public*/ ListeningSpot(QVector3D position);
 /*public*/ ListeningSpot(QString name, QVector3D position);
 /*public*/ ListeningSpot(QString name, QVector3D loc, QVector3D up, QVector3D at);
 /*public*/ QString getName();
 /*public*/ QVector3D getLocation();
 /*public*/ PhysicalLocation* getPhysicalLocation();


 /*private*/ QVector3D parseVector3d(QString pos);
 /*public*/ QString toString();
 /*public*/ QDomElement getXml(QString elementName);
 /*public*/ void setXml(QDomElement e);

signals:

public slots:
private:
 Logger* log;
 /*private*/ QVector3D _location;
 /*private*/ QVector3D _up;
 /*private*/ QVector3D _lookAt;
 /*private*/ QString _name;
 /*private*/ static /*final*/ QVector3D _rightVector;// = new Vector3d(0.0d, 1.0d, 0.0d);
 /*private*/ static /*final*/ QVector3D _upVector;// = new Vector3d(0.0d, 0.0d, 1.0d);
 QDomDocument doc;
};

#endif // LISTENINGSPOT_H
