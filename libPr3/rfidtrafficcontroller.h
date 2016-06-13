#ifndef RFIDTRAFFICCONTROLLER_H
#define RFIDTRAFFICCONTROLLER_H

#include <QObject>
#include "rfidlistener.h"
#include "abstractmrlistener.h"
#include "rfidsensormanager.h"
#include "rfidreportermanger.h"

class RfidSensorManager;
class RfidTrafficController : public QObject
{
    Q_OBJECT
public:
    explicit RfidTrafficController(QObject *parent = 0);
    /*public*/ /*synchronized*/ void addRfidListener(RfidListener* l);
    /*public*/ /*synchronized*/ void removeRfidListener(RfidListener* l);
    /*public*/ void sendRfidMessage(RfidMessage* m, RfidListener* reply);
    /*public*/ void setSensorManager(RfidSensorManager* m);
    /*public*/ RfidSensorManager* getSensorManager();

signals:
    
public slots:
private:
    RfidSensorManager* mSensorManager;// = NULL;

protected:
    /*protected*/ void forwardMessage(AbstractMRListener* client, /*AbstractMRMessage*/ QString m);

};

#endif // RFIDTRAFFICCONTROLLER_H
