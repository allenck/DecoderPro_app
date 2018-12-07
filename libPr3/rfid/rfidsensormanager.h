#ifndef RFIDSENSORMANAGER_H
#define RFIDSENSORMANAGER_H
#include "abstractsensormanager.h"
#include "rfidtrafficcontroller.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT RfidSensorManager : public AbstractSensorManager
{
    Q_OBJECT
public:
    explicit RfidSensorManager(QObject *parent = 0);
    /*public*/ RfidSensorManager(QString prefix, QObject *parent = 0) ;
    /*public*/ QString getSystemPrefix();
    /*public*/ void dispose();
    /*public*/ void message(/*RfidMessage*/QString m);

signals:
    
public slots:
private:
 /*private*/ QString prefix;
 static Logger* log;
 Sensor* createNewSensor(QString systemName, QString userName);
 //RfidTrafficController* tc;
};

#endif // RFIDSENSORMANAGER_H
