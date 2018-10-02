#include "hexfileserver.h"
#include "lnpacketizer.h"
#include "lnhexfileport.h"
#include "systemconnectionmemo.h"
#include "instancemanager.h"
#include "activeflag.h"
#include "debugprogrammermanager.h"
#include "debugthrottlemanager.h"

//HexFileServer::HexFileServer(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 *  copied from HexFileFrame, then all ui-related elements removed.  ConnectionConfigXml.load()
 *     calls HexFileServer instead of HexFileFrame if jmri is running in headless mode.
 * @author			Steve Todd  Copyright 2012
 * @version                     $Revision: 18841 $
 */
// /*public*/ class HexFileServer {

    // member declarations

    // to find and remember the log file
//    final javax.swing.JFileChooser inputFileChooser =
//            jmri.jmrit.XmlFile.userFileChooser("Hex files", "hex");

/*public*/ HexFileServer::HexFileServer(QObject *parent)
    :  QObject(parent)
{
 connected = false;
 packets = NULL;
 log = new Logger("HexFIleServer");
}

/*public*/ void HexFileServer::dispose() {
}

/*public*/ void HexFileServer::configure()
{
 if (port==NULL){
  log->error("initComponents called before adapter has been set");
        return;
    }
    // connect to a packetizing LnTrafficController
    packets = new LnPacketizer();
    packets->connectPort(port);
    connected = true;

    // create memo
    ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->setLnTrafficController(packets);

    // do the common manager config
    LnCommandStationType* type = new LnCommandStationType("DCS100 (Chief)",true,   false,  "LnThrottleManager",    "SlotManager", LnCommandStationType::COMMAND_STATION_DCS100);
    ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->configureCommandStation(type,   // full featured by default
            false, false);
    ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->configureManagers();

    // Install a debug programmer, replacing the existing LocoNet one
    ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->setProgrammerManager(
            new DebugProgrammerManager(port->getSystemConnectionMemo()));
    if (((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getProgrammerManager()->isAddressedModePossible())
    {
        InstanceManager::setAddressedProgrammerManager(((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getProgrammerManager());
    }
    if (((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getProgrammerManager()->isGlobalProgrammerAvailable()) {
        InstanceManager::store(((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getProgrammerManager(), "GlobalProgrammerManager");
    }

    // Install a debug throttle manager, replacing the existing LocoNet one
    ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->setThrottleManager(new DebugThrottleManager(port->getSystemConnectionMemo()));
    InstanceManager::setThrottleManager(
            ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getThrottleManager());

    // start operation of packetizer
    packets->startThreads();
    sourceThread = new QThread(port);
    sourceThread->start();

    ActiveFlag::setActive();

}

//private Thread sinkThread;

/*public*/ void HexFileServer::setAdapter(LnHexFilePort* adapter) { port = adapter; }
/*public*/ LnHexFilePort* HexFileServer::getAdapter() { return port; }
