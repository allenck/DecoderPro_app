#include "loconetbluetoothadapter.h"
#include "loconetsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "connectionstatus.h"
#include "discoverylistener.h"

/**
 * Provide access to LocoNet via a LocoNet Bluetooth adapter.
 */
// /*public*/ class LocoNetBluetoothAdapter extends LnPortController {

/*public*/ LocoNetBluetoothAdapter::LocoNetBluetoothAdapter(QObject* parent) : LnPortController(new LocoNetSystemConnectionMemo(), parent)
{
}

/*public*/ LocoNetBluetoothAdapter::LocoNetBluetoothAdapter(LocoNetSystemConnectionMemo* adapterMemo, QObject* parent): LnPortController(adapterMemo, parent)
{
  portNameVector = QVector<QString>();

    option1Name = "CommandStation"; // NOI18N
    option2Name = "TurnoutHandle"; // NOI18N
    options.insert(option1Name, new Option(tr("Command station type:"), commandStationNames, false));
    options.insert(option2Name, new Option(tr("Turnout command handling:"),
            QStringList() << tr("Normal")<< tr("Spread")<< tr("One Only")<< tr("Both"))); // I18N
}


//@Overide
/*public*/ QVector<QString> LocoNetBluetoothAdapter::getPortNames() {
    portNameVector = QVector<QString>();
#if 0
    try {
        RemoteDevice[] devices = LocalDevice.getLocalDevice().getDiscoveryAgent().retrieveDevices(DiscoveryAgent.PREKNOWN);
        if (devices != null) {
            for (RemoteDevice device : devices) {
                portNameVector.add(device.getFriendlyName(false));
            }
        }
    } catch (IOException* ex) {
        log->error("Unable to use bluetooth device", ex);
    }
#endif
    return portNameVector;
}

//@Overide
/*public*/ QString LocoNetBluetoothAdapter::openPort(QString portName, QString appName) {
    QVector<int> responseCode =  QVector<int>(1,-1);
    QVector<Exception*> exception = QVector<Exception*>(1, nullptr);
#if 0
    try {
        // Find the RemoteDevice with this name.
        QVector<RemoteDevice*> devices = LocalDevice.getLocalDevice().getDiscoveryAgent().retrieveDevices(DiscoveryAgent.PREKNOWN);
        if (devices != null) {
            for (RemoteDevice device : devices) {
                if (device.getFriendlyName(false).equals(portName)) {
                    Object[] waitObj = new Object[0];
                    // Start a search for a serialport service (UUID 0x1101)
                    LocalDevice.getLocalDevice().getDiscoveryAgent().searchServices(new int[]{0x0100}, new UUID[]{new UUID(0x1101)}, device, new DiscoveryListener() {
                        //@Overide
                        /*public*/ void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
                            synchronized (waitObj) {
                                for (ServiceRecord service : servRecord) {
                                    // Service found, get url for connection.
                                    String url = service.getConnectionURL(ServiceRecord.NOAUTHENTICATE_NOENCRYPT, false);
                                    if (url == null) {
                                        continue;
                                    }
                                    try {
                                        // Open connection.
                                        Connection conn = Connector.open(url, Connector.READ_WRITE);
                                        if (conn instanceof StreamConnection) { // The connection should be a StreamConnection, otherwise it's a one way communication.
                                            StreamConnection stream = (StreamConnection) conn;
                                            in = stream.openInputStream();
                                            out = stream.openOutputStream();
                                            opened = true;
                                            // Port is open, let openPort continue.
                                            //waitObj.notify();
                                        } else {
                                            throw new IOException("Could not establish a two-way communication");
                                        }
                                    } catch (IOException* IOe) {
                                        exception[0] = IOe;
                                    }
                                }
                                if (!opened) {
                                    exception[0] = new IOException("No service found to connect to");
                                }
                            }
                        }

                        //@Overide
                        /*public*/ void serviceSearchCompleted(int transID, int respCode) {
                            synchronized (waitObj) {
                                // Search for services complete, if the port was not opened, save the response code for error analysis.
                                responseCode[0] = respCode;
                                // Search completer, let openPort continue.
                                waitObj.notify();
                            }
                        }

                        //@Overide
                        /*public*/ void inquiryCompleted(int discType) {
                        }

                        //@Overide
                        /*public*/ void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                        }
                    });
                    synchronized (waitObj) {
                        // Wait until either the port is open on the search has returned a response code.
                        while (!opened && responseCode[0] == -1) {
                            try {
                                // Wait for search to complete.
                                waitObj.wait();
                            } catch (InterruptedException ex) {
                                log.error("Thread unexpectedly interrupted", ex);
                            }
                        }
                    }
                    break;
                }
            }
        }
    } catch (BluetoothStateException BSe) {
        log.error("Exception when using bluetooth");
        return BSe->getLocalizedMessage();
    } catch (IOException* IOe) {
        log.error("Unknown IOException when establishing connection to " + portName);
        return IOe->getLocalizedMessage();
    }
#endif
    if (!opened) {
        ConnectionStatus::instance()->setConnectionState("", portName, ConnectionStatus::CONNECTION_DOWN);
        if (exception.at(0) != nullptr) {
            log->error("Exception when connecting to " + portName);
            return exception[0]->getLocalizedMessage();
        }
#if 1
        switch (responseCode[0]) {
            case DiscoveryListener::SERVICE_SEARCH_COMPLETED:
                log->error(tr("Bluetooth connection %1 not opened, unknown error").arg(portName));
                return "Unknown error: failed to connect to " + portName;
            case DiscoveryListener::SERVICE_SEARCH_DEVICE_NOT_REACHABLE:
                log->error(tr("Bluetooth device %1 could not be reached").arg(portName));
                return "Could not find " + portName;
            case DiscoveryListener::SERVICE_SEARCH_ERROR:
                log->error(tr("Error when searching for %1").arg(portName));
                return "Error when searching for " + portName;
            case DiscoveryListener::SERVICE_SEARCH_NO_RECORDS:
                log->error(tr("No serial service found on %1").arg(portName));
                return "Invalid bluetooth device: " + portName;
            case DiscoveryListener::SERVICE_SEARCH_TERMINATED:
                log->error(tr("Service search on %1 ended prematurely").arg(portName));
                return "Search for " + portName + " ended unexpectedly";
            default:
                log->warn(tr("Unhandled response code: %1").arg(responseCode[0]));
                break;
        }
#endif
        log->error(tr("Unknown error when connecting to %1").arg(portName));
        return "Unknown error when connecting to " + portName;
    }

    return ""; // normal operation
}

/**
 * Set up all of the other objects to operate.
 */
//@Overide
/*public*/ void LocoNetBluetoothAdapter::configure() {
    setCommandStationType(getOptionState(option1Name));
    setTurnoutHandling(getOptionState(option2Name));
    // connect to a packetizing traffic controller
    LnPacketizer* packets = new LnPacketizer((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo());
    packets->connectPort(this);

    // create memo
    ((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo())->setLnTrafficController(packets);
    // do the common manager config

    ((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo())->configureCommandStation(commandStationType,
            mTurnoutNoRetry, mTurnoutExtraSpace, mTranspondingAvailable);
    ((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo())->configureManagers();

    // start operation
    packets->startThreads();
}

// base class methods for the LnPortController interface
//@Overide
/*public*/ QDataStream* LocoNetBluetoothAdapter::getInputStream() {
    if (!opened) {
        log->error(tr("getInputStream called before load(), stream not available"));
        return nullptr;
    }
    return new QDataStream(/**in*/);
}

//@Overide
/*public*/ QDataStream* LocoNetBluetoothAdapter::getOutputStream() {
    if (!opened) {
        log->error(tr("getOutputStream called before load(), stream not available"));
    }
    return new QDataStream(/**out*/);
}

//@Overide
/*public*/ bool LocoNetBluetoothAdapter::status() {
    return opened;
}


/**
 * {@inheritDoc}
 */
//@Overide
/*public*/ QStringList LocoNetBluetoothAdapter::validBaudRates() {
    return  QStringList();
}

/**
 * {@inheritDoc}
 */
//@Overide
/*public*/ QVector<int> LocoNetBluetoothAdapter::validBaudNumbers() {
    return QVector<int>();
}

/*private*/ /*final*/ /*static*/ Logger* LocoNetBluetoothAdapter::log = LoggerFactory::getLogger("LocoNetBluetoothAdapter");
