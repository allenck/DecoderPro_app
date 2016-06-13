#include "lntcpdriveradapter.h"
#include "loconetsystemconnectionmemo.h"
#include "lnovertcppacketizer.h"
#include "activeflag.h"
#include <QTcpSocket>

//LnTcpDriverAdapter::LnTcpDriverAdapter(QObject *parent) :
//  LnNetworkPortController(parent)
//{
//}
/**
 * Implements SerialPortAdapter for the LocoNetOverTcp system network
 * connection.
 * <P>
 * This connects a Loconet via a telnet connection. Normally controlled by the
 * LnTcpDriverFrame class.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2002, 2003
 * @author Alex Shepherd Copyright (C) 2003, 2006
 * @version $Revision: 28746 $
 */
///*public*/ class LnTcpDriverAdapter extends LnNetworkPortController {

/*public*/ LnTcpDriverAdapter::LnTcpDriverAdapter(QObject *parent) :
LnNetworkPortController(new LocoNetSystemConnectionMemo(), parent)
{
 //super(new LocoNetSystemConnectionMemo());
 setObjectName("LnTcpDriverAdapter");
 log = new Logger("LnTcpDriverAdapter");
 opened = false;

 option2Name = "CommandStation";
 option3Name = "TurnoutHandle";
 options.insert(option2Name, new Option("Command station type:", commandStationNames, false));
 QStringList list = QStringList() << "Normal" << "Spread" << "One Only" << "Both";
 options.insert(option3Name, new Option("Turnout command handling:", /*new String[]{"Normal", "Spread", "One Only", "Both"}*/list));
}

/**
 * set up all of the other objects to operate with a LocoNet connected via
 * this class.
 */
/*public*/ void LnTcpDriverAdapter::configure()
{
 setCommandStationType(getOptionState(option2Name));
 setTurnoutHandling(getOptionState(option3Name));

 // connect to a packetizing traffic controller
 if(!getSocket()->waitForConnected())
 {
  // TODO: handle connection refused, etc.
 }

 LnOverTcpPacketizer* packets = new LnOverTcpPacketizer();
 packets->connectPort((LnNetworkPortController*)this);

 connect(packets->rcvHandler, SIGNAL(finished()), this, SLOT(on_rcvHandlerTerminated()));

 // create memo
 ((LocoNetSystemConnectionMemo*)getSystemConnectionMemo())->setLnTrafficController(packets);
 // do the common manager config
 ((LocoNetSystemConnectionMemo*)getSystemConnectionMemo())->configureCommandStation(commandStationType,
         mTurnoutNoRetry, mTurnoutExtraSpace);
 ((LocoNetSystemConnectionMemo*)getSystemConnectionMemo())->configureManagers();

 // start operation
 packets->startThreads();
 ActiveFlag::setActive();
}

void LnTcpDriverAdapter::on_rcvHandlerTerminated()
{
 LnOverTcpPacketizer* packets = new LnOverTcpPacketizer();
 packets->disconnectPort((LnNetworkPortController*)this);

 recover();
}

/*public*/ bool LnTcpDriverAdapter::status()
{
 return opened;
}


/*public*/ void LnTcpDriverAdapter::configureOption1(QString value)
{
 LnNetworkPortController::configureOption1(value);
 log->debug("configureOption1: " + value);
 setCommandStationType(value);
}
