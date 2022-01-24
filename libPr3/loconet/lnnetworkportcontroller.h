#ifndef LNNETWORKPORTCONTROLLER_H
#define LNNETWORKPORTCONTROLLER_H
#include "abstractnetworkportcontroller.h"
#include "zeroconfclient.h"

class ZeroConfClient;
class LocoNetSystemConnectionMemo;
class LnCommandStationType;
class LnNetworkPortController : public AbstractNetworkPortController
{
 Q_OBJECT
public:
 explicit LnNetworkPortController(QObject *parent = 0);
 /*public*/ void setCommandStationType(QString name);
 /*public*/ void setCommandStationType(LnCommandStationType* value);
 /*public*/ SystemConnectionMemo* getSystemConnectionMemo();
 /*public*/ void setTurnoutHandling(QString value);
 /*public*/ void setTranspondingAvailable(QString value);
 /*public*/ void configureOption3(QString value) override;
 QTcpSocket* getSocket();

 /*public*/ void setServiceType(QString) override;
 /*public*/ QString getServiceType() override;
 /*public*/ void setMdnsConfigure(bool bMdnsConfigure) override;
 /*public*/ bool getMdnsConfigure() override;

signals:
 void updated();

public slots:
 /*public*/ void autoConfigure();

private:
 Logger* log;
 ZeroConfClient* zClient = nullptr;
 bool bMdnsConfigure = false;
 QString serviceType; // ZeroConf service type

protected:
 /*protected*/ LnCommandStationType* commandStationType = nullptr;

 /*protected*/ bool mTurnoutNoRetry = false;
 /*protected*/ bool mTurnoutExtraSpace = false;
 /*protected*/ bool mTranspondingAvailable = false;

 /*protected*/ QList<LnCommandStationType*> commandStationTypes;// = {
//     LnCommandStationType.COMMAND_STATION_DCS100,
//     LnCommandStationType.COMMAND_STATION_DCS200,
//     LnCommandStationType.COMMAND_STATION_DCS050,
//     LnCommandStationType.COMMAND_STATION_DCS051,
//     LnCommandStationType.COMMAND_STATION_DB150,
//     LnCommandStationType.COMMAND_STATION_IBX_TYPE_1,
//     LnCommandStationType.COMMAND_STATION_IBX_TYPE_2,
//     LnCommandStationType.COMMAND_STATION_LBPS,
//     LnCommandStationType.COMMAND_STATION_MM};

 /*protected*/ QStringList commandStationNames;
 /*protected*/ LnNetworkPortController(LocoNetSystemConnectionMemo*  connectionMemo,QObject *parent);

};

#endif // LNNETWORKPORTCONTROLLER_H
