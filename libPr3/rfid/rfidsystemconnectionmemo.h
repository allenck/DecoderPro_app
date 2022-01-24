#ifndef RFIDSYSTEMCONNECTIONMEMO_H
#define RFIDSYSTEMCONNECTIONMEMO_H
#include "defaultsystemconnectionmemo.h"

class RfidTrafficController;
class RfidProtocol;
class RfidSensorManager;
class RfidReporterManager;
class RfidSystemConnectionMemo : public DefaultSystemConnectionMemo
{
public:
 RfidSystemConnectionMemo(RfidTrafficController* rt, QObject* parent = nullptr);
 /*public*/ RfidSystemConnectionMemo( QObject *parent = nullptr);

 /*public*/ RfidTrafficController* getTrafficController();
 /*public*/ /*final*/ void setRfidTrafficController(RfidTrafficController* rt);
 /*public*/ void configureManagers(RfidSensorManager* sensorManager, RfidReporterManager* reporterManager);
 /*public*/ RfidProtocol* getProtocol();
 /*public*/ /*final*/ void setProtocol(RfidProtocol* protocol);
 /*public*/ RfidSensorManager* getSensorManager();
 /*public*/ RfidReporterManager* getReporterManager();
 /*public*/ bool provides(/*Class<?> */QString type);
 /*public*/ /*<T> */Manager* get(/*Class<?>*/QString T);
 /*public*/ void dispose();


private:
 static Logger* log;
 /*private*/ RfidTrafficController* rt;
 /*private*/ RfidProtocol* protocol;

protected:
 /*protected*/ RfidSensorManager* sensorManager;
 /*protected*/ RfidReporterManager* reporterManager;


};

#endif // RFIDSYSTEMCONNECTIONMEMO_H
