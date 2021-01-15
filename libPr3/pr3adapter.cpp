#include "pr3adapter.h"
#include "pr3systemconnectionmemo.h"
#include "lnpacketizer.h"
#include "LocoIO/lncommandstationtype.h"
#include "loconet/PR2/lnpr2packtizer.h"
#include "instancemanager.h"

PR3Adapter::PR3Adapter(QObject* parent)
    : LocoBufferAdapter(new PR3SystemConnectionMemo(), parent)
{
 setObjectName("PR3Adapter");
 myParent = parent;
 log = new Logger("PR3Adapter");

 options.remove(option2Name);
 options.insert(option2Name,  new Option("Command station type:", commandStationOptions(), false));

 //InstanceManager::instance()->store(this, "PortAdapter");
}
void PR3Adapter::setSerialPort(SerialPort* activeSerialPort) throw(UnsupportedCommOperationException)
{
 // find the baud rate value, configure comm options
 int baud = 57600;  // default, but also defaulted in the initial value of selectedSpeed
 for (int i = 0; i<validBaudNumbers().size(); i++ )
  if (validBaudRates()[i]==(mBaudRate))
   baud = validBaudNumbers()[i];
  activeSerialPort->setSerialPortParams(baud, SerialPort::DATABITS_8, SerialPort::STOPBITS_1, SerialPort::PARITY_NONE);

  // set RTS high, DTR high - done early, so flow control can be configured after
  activeSerialPort->setRTS(true);		// not connected in some serial ports and adapters
  activeSerialPort->setDTR(true);		// pin 1 in Mac DIN8; on main connector, this is DTR

 // configure flow control to always on
 int flow = SerialPort::FLOWCONTROL_RTSCTS_OUT;
 if (getOptionState(option1Name)==(validOption1[1]))
  flow = SerialPort::FLOWCONTROL_NONE;
 activeSerialPort->setFlowControlMode(flow);
 log->debug("Found flow control "+QString("%1").arg(activeSerialPort->getFlowControlMode())
              +" RTSCTS_OUT="+QString("%1").arg(SerialPort::FLOWCONTROL_RTSCTS_OUT)
              +" RTSCTS_IN= "+QString("%1").arg(SerialPort::FLOWCONTROL_RTSCTS_IN));
 //commandStationOptions();
}

void PR3Adapter::configure()
{
 setCommandStationType(getOptionState(option2Name));
 setTurnoutHandling(getOptionState(option3Name));

 if(commandStationType->getType() == LnCommandStationType::COMMAND_STATION_PR3_ALONE)
 {
  // PR3 standalone case
  // connect to a packetizing traffic controller
  // that does echoing
  packets = new LnPr2Packetizer((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo());
  packets->connectPort(this);

  // create memo
  /*PR3SystemConnectionMemo memo
                  = new PR3SystemConnectionMemo(packets, new SlotManager(packets));*/
  ((PR3SystemConnectionMemo*)this->getSystemConnectionMemo())->setLnTrafficController(packets);
  // do the common manager config
  ((PR3SystemConnectionMemo*)this->getSystemConnectionMemo())->configureCommandStation(commandStationType,
                                                  mTurnoutNoRetry, mTurnoutExtraSpace, mTranspondingAvailable);
  ((PR3SystemConnectionMemo*) this->getSystemConnectionMemo())->configureManagersPR2();

  // start operation
  //packets->startThreads();
  ActiveFlag::setActive();

  // set mode
  LocoNetMessage* msg = new LocoNetMessage( 6 ) ;
  msg->setOpCode( 0xD3 );
  msg->setElement( 1, 0x10 );
  msg->setElement( 2, 1 );  // set PR2
  msg->setElement( 3, 0 );
  msg->setElement( 4, 0 );
  packets->sendLocoNetMessage(msg);

 }
 else
 {
  // MS100 modes - connecting to a separate command station
  // get transponding option
  setTranspondingAvailable(getOptionState("TranspondingPresent"));
  // connect to a packetizing traffic controller
  LnPacketizer* packets = getPacketizer(getOptionState(option4Name));
  packets->connectPort(this);

  // create memo
  /*PR3SystemConnectionMemo memo
                  = new PR3SystemConnectionMemo(packets, new SlotManager(packets));*/
  ((PR3SystemConnectionMemo*)this->getSystemConnectionMemo())->setLnTrafficController(packets);
  // do the common manager config
  ((PR3SystemConnectionMemo*)this->getSystemConnectionMemo())->configureCommandStation(commandStationType,
                                              mTurnoutNoRetry, mTurnoutExtraSpace, mTranspondingAvailable);

  ((PR3SystemConnectionMemo*)this->getSystemConnectionMemo())->configureManagersMS100();

  // start operation
  //packets->startThreads();
  ActiveFlag::setActive();// set mode

  LocoNetMessage* msg = new LocoNetMessage( 6 ) ;
  msg->setOpCode( 0xD3 );
  msg->setElement( 1, 0x10 );
  msg->setElement( 2, 0 );  // set MS100, no power
  //if (commandStationName.startsWith("Stand-alone"))
  //if (commandStationName.startsWith("PR3 standalone"))
  //if(!this->LnPortController::mProgPowersOff)
  if (commandStationType->getType() == LnCommandStationType::COMMAND_STATION_STANDALONE)
  {
   msg->setElement( 2, 3 );  // set MS100, with power
  }
  msg->setElement( 3, 0 );
  msg->setElement( 4, 0 );
  packets->sendLocoNetMessage(msg);
 }
}

/**
 * Get an array of valid baud rates.
 */
/*public*/ QStringList PR3Adapter::validBaudRates() {
    QStringList l;
    l << "57,600 baud";
    return l;
}

/**
 * Get an array of valid baud rates as integers. This allows subclasses
 * to change the arrays of speeds.
 */
/*public*/ QVector<int> PR3Adapter::validBaudNumbers() {
    QVector<int> l;
    l << 57600;
    return l;
}

// Option 1 does flow control, inherited from LocoBufferAdapter

/**
 * The PR3 can be used in numerous modes, so handle that
 */
/*public*/ QStringList PR3Adapter::commandStationOptions()
{
// QStringList retval;
// retval << "PR3 standalone programmer" << "Stand-alone LocoNet";
// foreach(QString str, commandStationNames)
//  retval << str;
// return retval;
 QVector<QString> retval =  QVector<QString>(commandStationNames.length()+2);
 retval.replace(0, "PR3 standalone programmer");
 for (int i=0; i<commandStationNames.length(); i++)
 {
  retval.replace(i+1,commandStationNames[i]);
 }
 retval.replace(retval.size()-1, "Stand-alone LocoNet");
 return (QStringList)retval.toList();
}

/*public*/ void PR3Adapter::setTranspondingAvailable(QString value) {
    // default (most common state) is off, so just check for Yes
    mTranspondingAvailable = (value == ("Yes") || value == ("Yes"));
    log->debug(tr("transponding available: %1").arg(mTranspondingAvailable)); // NOI18N
}

//@Override
/*public*/ SystemConnectionMemo *PR3Adapter::getSystemConnectionMemo()
{
    SystemConnectionMemo* m = LocoBufferAdapter::getSystemConnectionMemo();
    if (qobject_cast<PR3SystemConnectionMemo*>(m->self())) {
        return (PR3SystemConnectionMemo*) m;
    }
    log->error("Cannot cast the system connection memo to a PR3SystemConnection Memo.");
    return nullptr;
}

/*public*/ QString PR3Adapter::className()
{
 return "jmri.jmrix.loconet.pr3.PR3Adapter";
}
