#include "simpleserver.h"
#include "loggerfactory.h"
#include "instancemanager.h"

/**
 * This is an implementation of a simple server for JMRI. There is currently no
 * handshaking in this server. You may just start sending commands.
 *
 * @author Paul Bender Copyright (C) 2010
 *
 */
// /*public*/ class SimpleServer extends JmriServer {

    //static ResourceBundle rb = ResourceBundle.getBundle("jmri.jmris.simpleserver.SimpleServerBundle");

/*
 * @deprecated since 4.7.1 use @link{InstanceManager.getDefault()} instead.
 */
//@Deprecated  // will be removed when superclass method is removed due to //@Override
//@SuppressWarnings("deprecation")  // temporary implementation of method
/*public*/ /*static*/ JmriServer* SimpleServer::instance() {
    if (InstanceManager::getNullableDefault("SimpleServer") == nullptr) {
        InstanceManager::store(new SimpleServer(),"SimpleServer");
    }
    return (JmriServer*)InstanceManager::getDefault("SimpleServer");
}

// Create a new server using the default port
/*public*/ SimpleServer::SimpleServer(QObject* parent ) : JmriServer(2048, parent){
    //this((tr("SimpleServerPort")));
 common(2048);
}

/*public*/ SimpleServer::SimpleServer(int port, QObject *parent) : JmriServer(port, parent){
 common(port);
}
void SimpleServer::common(int port)
{
    //super(port);
    InstanceManager::setDefault("SimpleServer",this);
    log->info("JMRI SimpleServer started on port " + QString::number(port));
}

//@Override
/*protected*/ void SimpleServer::advertise() {
    JmriServer::advertise(QString("_jmri-simple._tcp.local."));
}
#if 0
// Handle communication to a client through inStream and outStream
//@Override
/*public*/ void handleClient(DataInputStream inStream, DataOutputStream outStream) throws IOException {
    Scanner inputScanner = new Scanner(new InputStreamReader(inStream, "UTF-8"));
    // Listen for commands from the client until the connection closes
    String cmd;

    // interface components
    SimplePowerServer powerServer = new SimplePowerServer(inStream, outStream);
    SimpleTurnoutServer turnoutServer = new SimpleTurnoutServer(inStream, outStream);
    SimpleLightServer lightServer = new SimpleLightServer(inStream, outStream);
    SimpleSensorServer sensorServer = new SimpleSensorServer(inStream, outStream);
    SimpleSignalHeadServer signalHeadServer = new SimpleSignalHeadServer(inStream, outStream);
    SimpleReporterServer reporterServer = new SimpleReporterServer(inStream, outStream);
    SimpleOperationsServer operationsServer = new SimpleOperationsServer(inStream, outStream);

    // Start by sending a welcome message
    outStream.writeBytes("JMRI " + jmri.Version.name() + " \n");
    outStream.writeBytes("RAILROAD " + InstanceManager.getDefault(WebServerPreferences.class).getRailroadName() + " \n");
    outStream.writeBytes("NODE " + NodeIdentity.identity() + " \n");

    while (true) {
        inputScanner.skip("[\r\n]*");// skip any stray end of line characters.
        // Read the command from the client
        try {
            cmd = inputScanner.nextLine();
        } catch (NoSuchElementException nse) {
            // we get an nse when we are finished with this client
            // so break out of the loop.
            break;
        }

        if (log.isDebugEnabled()) {
            log.debug("Received from client: " + cmd);
        }
        if (cmd.startsWith("POWER")) {
            try {
                powerServer.parseStatus(cmd);
                powerServer.sendStatus(InstanceManager.getDefault(jmri.PowerManager.class).getPower());
            } catch (JmriException je) {
                outStream.writeBytes("not supported\n");
            }
        } else if (cmd.startsWith("TURNOUT")) {
            try {
                turnoutServer.parseStatus(cmd);
            } catch (JmriException je) {
                outStream.writeBytes("not supported\n");
            }
        } else if (cmd.startsWith("LIGHT")) {
            try {
                lightServer.parseStatus(cmd);
            } catch (JmriException je) {
                outStream.writeBytes("not supported\n");
            }
        } else if (cmd.startsWith("SENSOR")) {
            try {
                sensorServer.parseStatus(cmd);
            } catch (JmriException je) {
                outStream.writeBytes("not supported\n");
            }
        } else if (cmd.startsWith("SIGNALHEAD")) {
            try {
                signalHeadServer.parseStatus(cmd);
            } catch (JmriException je) {
                outStream.writeBytes("not supported\n");
            }
        } else if (cmd.startsWith("REPORTER")) {
            try {
                reporterServer.parseStatus(cmd);
            } catch (JmriException je) {
                outStream.writeBytes("not supported\n");
            }
        } else if (cmd.startsWith(SimpleOperationsServer.OPERATIONS)) {
            try {
                operationsServer.parseStatus(cmd);
            } catch (JmriException je) {
                outStream.writeBytes("not supported\n");
            }
        } else {
            outStream.writeBytes("Unknown Command " + cmd + "\n");
        }
    }
    inputScanner.close();

}
#endif
/*private*/ /*final*/ /*static*/ Logger* SimpleServer::log = LoggerFactory::getLogger("SimpleServer");
