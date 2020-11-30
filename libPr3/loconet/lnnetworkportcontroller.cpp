#include "lnnetworkportcontroller.h"
#include "dccmanufacturerlist.h"
#include "lncommandstationtype.h"
#include "exceptions.h"
#include "loconetsystemconnectionmemo.h"
#include "lnovertcppacketizer.h"
#include "sleeperthread.h"

//LnNetworkPortController::LnNetworkPortController(QObject *parent) :
//  AbstractNetworkPortController(parent)
//{
//}

/**
 * Base for classes representing a LocoNet communications port
 *
 * @author	Kevin Dickerson Copyright (C) 2011
 * @version $Revision: 1.24 $
 */
// /*public*/ abstract class LnNetworkPortController extends jmri.jmrix.AbstractNetworkPortController {
    // base class. Implementations will provide InputStream and OutputStream
    // objects to LnTrafficController classes, who in turn will deal in messages.

/*protected*/ LnNetworkPortController::LnNetworkPortController(LocoNetSystemConnectionMemo*  connectionMemo,QObject *parent)
 : AbstractNetworkPortController((SystemConnectionMemo*)connectionMemo, parent)
{
 //super(connectionMemo);
 log = new Logger("LnNetworkPortController");
 commandStationType = NULL;
 mTurnoutNoRetry = false;
 mTurnoutExtraSpace = false;

 commandStationTypes = QList<LnCommandStationType*>();
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS100));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS240));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS210));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS200));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS050));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS051));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS052));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DB150));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_IBX_TYPE_1));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_IBX_TYPE_2));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_LBPS));
 commandStationTypes.append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_MM));

 setManufacturer(DCCManufacturerList::DIGITRAX);
 commandStationNames =  QStringList();
 int i = 0;
 foreach (LnCommandStationType* type, commandStationTypes)
 {
  commandStationNames.append( type->getName());
 }
}

// There are also "PR3 standalone programmer" and "Stand-alone LocoNet"
// in pr3/PR3Adapter
/**
 * Set config info from a name, which needs to be one of the valid ones.
 */
/*public*/ void LnNetworkPortController::setCommandStationType(QString name)
{
 try
 {
  setCommandStationType(LnCommandStationType::getByName(name));
 } catch (IllegalArgumentException e)
 {
        // not a valid command station type, force
  log->error(tr("Invalid command station name: \"%1\", defaulting to %2").arg( name).arg(commandStationTypes[0]->getName()));
        setCommandStationType(commandStationTypes[0]);
 }
}

/**
 * Set config info from the command station type enum.
 */
/*public*/ void LnNetworkPortController::setCommandStationType(LnCommandStationType* value) {
    if (value == NULL) {
        return;  // can happen while switching protocols
    }
    log->debug("setCommandStationType: " + value->getName());
    commandStationType = value;
}

//@Override
/*public*/ SystemConnectionMemo* LnNetworkPortController::getSystemConnectionMemo()
{
 return (SystemConnectionMemo*) AbstractNetworkPortController::getSystemConnectionMemo();
}

/*public*/ void LnNetworkPortController::setTurnoutHandling(QString value)
{
 if (value==("One Only") || value==("Both"))
 {
     mTurnoutNoRetry = true;
 }
 if (value==("Spread") || value==("Both"))
 {
     mTurnoutExtraSpace = true;
 }
 log->debug(tr("turnout no retry: ") + (mTurnoutNoRetry?"true":"false"));
 log->debug(tr("turnout extra space: ") + (mTurnoutExtraSpace?"true":"false"));
}

/**
 * Set whether transponding is available.
 *
 * @param value either yes or no
 */
/*public*/ void LnNetworkPortController::setTranspondingAvailable(QString value) {
    // default (most common state) is off, so just check for Yes
    mTranspondingAvailable = (value==("Yes") || value==(tr("Yes")));
    log->debug(tr("transponding available: %1").arg(mTranspondingAvailable)); // NOI18N
}
/**
 * Set the third port option. Only to be used after construction, but before
 * the openPort call
 */
/*public*/ void LnNetworkPortController::configureOption3(QString value)
{
 AbstractNetworkPortController::configureOption3(value);
 log->debug("configureOption3: " + value);
 setTurnoutHandling(value);
}
QTcpSocket* LnNetworkPortController::getSocket() {return socketConn;}

/*public*/ void LnNetworkPortController::setServiceType(QString serviceType)
{
 this->serviceType = serviceType;
 if(zClient == nullptr)
  zClient = new ZeroConfClient();
 connect(zClient, SIGNAL(serviceAdded(QString)), this, SLOT(autoConfigure()));
 zClient->startServiceListener(serviceType);
 setMdnsConfigure(true);
 SleeperThread::msleep(100);
}
/*public*/ QString LnNetworkPortController::getServiceType() { return serviceType;}

/*public*/ void LnNetworkPortController::setMdnsConfigure(bool bMdnsConfigure)
{
 this->bMdnsConfigure = bMdnsConfigure;
}

/*public*/ bool LnNetworkPortController::getMdnsConfigure() { return bMdnsConfigure;}

/*public*/ void LnNetworkPortController::autoConfigure()
{
 if(zClient == nullptr)
  return;
 if(zClient->getServices().isEmpty())
 {
  qApp->processEvents(QEventLoop::AllEvents, 1000);
 }
 if(!zClient->getServices().isEmpty())
 {
  setHostName(zClient->getServices().at(0).host());
  setPort(zClient->getServices().at(0).port());
  emit updated();
 }
}
