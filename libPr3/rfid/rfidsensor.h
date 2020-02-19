#ifndef RFIDSENSOR_H
#define RFIDSENSOR_H
#include "abstractsensor.h"
#include "idtag.h"
#include <QVector>

class DefaultIdTag;
class RfidSensor : public AbstractSensor
{
    Q_OBJECT
public:
    explicit RfidSensor(QObject *parent = 0);
    /*public*/ RfidSensor(QString systemName,QObject *parent);
    /*public*/ RfidSensor(QString systemName, QString userName,QObject *parent);
    /*public*/ void notify(DefaultIdTag *r);
    /*public*/ void setOwnState(int state);
    QList<int> getContents();
    void notifyInRegion(int id);
    void notifyOutOfRegion(int id);
    void notifyLeaving(int id);
    void notifyArriving(int id);
    /*public*/ void dispose();

signals:
    
public slots:
private:
    //    transient Region region;
    QVector<int>* contents;// = new QVector<int>();

    /*private*/ static /*final*/const long serialVersionUID = 1L;

};

#endif // RFIDSENSOR_H
