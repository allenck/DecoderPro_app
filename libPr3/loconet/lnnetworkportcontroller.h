#ifndef LNNETWORKPORTCONTROLLER_H
#define LNNETWORKPORTCONTROLLER_H
#include "abstractnetworkportcontroller.h"

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
 /*public*/ void configureOption3(QString value);
 QTcpSocket* getSocket();
signals:

public slots:
private:
 Logger* log;
protected:
 /*protected*/ LnCommandStationType* commandStationType;// = null;

 /*protected*/ bool mTurnoutNoRetry;// = false;
 /*protected*/ bool mTurnoutExtraSpace;// = false;

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
