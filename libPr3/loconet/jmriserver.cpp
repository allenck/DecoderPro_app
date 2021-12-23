#include "jmriserver.h"
#include "exceptions.h"
#include <QTcpSocket>
#include "zeroconfservice.h"
#include "loggerfactory.h"

/*private*/ /*static*/ JmriServer* JmriServer::_instance = nullptr;


/**
 * This is the main JMRI Server implementation.
 *
 * It starts a thread for each client.
 *
 */
///*public*/ class JmriServer {


/*public*/ /*synchronized*/ /*static*/ JmriServer* JmriServer::instance() {
    if (_instance == nullptr) {
        _instance = new JmriServer();
    }
    return _instance;
}

// Create a new server using the default port
/*public*/ JmriServer::JmriServer(QObject* parent) : QTcpServer(parent) {
    common(3000, 0);
}

// Create a new server using a given port and no timeout
/*public*/ JmriServer::JmriServer(int port, QObject* parent) : QTcpServer(parent){
    common(port, 0);
}

// Create a new server using a given port with a timeout
// A timeout of 0 is infinite
/*public*/ JmriServer::JmriServer(int port, int timeout, QObject* parent) : QTcpServer(parent)
{
common(port, timeout);
}

void JmriServer::common(int port, int timeout)
{
    //super();
    // Try registering the server on the given port
#if 0
    try {
        this.connectSocket = new ServerSocket(port);
    } catch (IOException e) {
        log.error("Failed to connect to port " + port);
    }
#endif
    this->portNo = port;
    this->timeout = timeout;
}
#if 0
// Maintain a vector of connected clients
// Add a new client
/*private*/ synchronized void addClient(ClientListener client) {
    if (!connectedClientThreads.contains(client)) {
        connectedClientThreads.add(client);
        client.start();
    }
}

//Remove a client
/*private*/ synchronized void removeClient(ClientListener client) {
    if (connectedClientThreads.contains(client)) {
        client.stop(this);
        connectedClientThreads.remove(client);
    }
}

/*public*/ void start() {
    /* Start the server thread */
    if (this.listenThread == NULL) {
        this.listenThread = new Thread(new newClientListener(connectSocket));
        this.listenThread.start();
        this.advertise();
    }
    if (this.shutDownTask != NULL && InstanceManager.shutDownManagerInstance() != NULL) {
        InstanceManager.shutDownManagerInstance().register(this.shutDownTask);
    }
}
#endif
/*public*/ void JmriServer::start()
{
 listen(QHostAddress::Any, portNo);
 connect(this, SIGNAL(newConnection()), this, SLOT(on_newConnection()));
}
// Advertise the service with ZeroConf
/*protected*/ void JmriServer::advertise() {
    this->advertise("_jmri._tcp.local.");
}

/*protected*/ void JmriServer::advertise(QString type) {
    this->advertise(type, QMap<QString, QVariant>());
}

/*protected*/ void JmriServer::advertise(QString type, QMap<QString, QVariant> properties) {
    if (this->service == nullptr) {
        this->service = ZeroConfService::create(type, this->portNo, properties);
    }
    this->service->publish();
}
#if 0
/*public*/ void stop() {
    for (ClientListener client : this.connectedClientThreads) {
        client.stop(this);
    }
    this.listenThread = NULL;
    this.service.stop();
    if (this.shutDownTask != NULL && InstanceManager.shutDownManagerInstance() != NULL) {
        InstanceManager.shutDownManagerInstance().deregister(this.shutDownTask);
    }
}
#endif
/*public*/ void JmriServer::stop()
{
 close();
}
#if 0
// Internal thread to listen for new connections
class newClientListener implements Runnable {

    ServerSocket listenSocket = NULL;
    boolean running = true;

    /*public*/ newClientListener(ServerSocket socket) {

        listenSocket = socket;
    }

    @Override
    /*public*/ void run() {
        // Listen for connection requests
        try {
            while (running) {
                Socket clientSocket = listenSocket.accept();
                clientSocket.setSoTimeout(timeout);
                log.debug(" Client Connected from IP {} port {}", clientSocket.getInetAddress(), clientSocket.getPort());
                addClient(new ClientListener(clientSocket));
            }
        } catch (IOException e) {
            log.error("IOException while Listening for clients");
        }
    }

    /*public*/ void stop() {
        //super.stop();
        running = false;
        try {
            listenSocket.close();
            log.debug("Listen Socket closed");
        } catch (IOException e) {
            log.error("socket in ThreadedServer won't close");
        }
    }
} // end of newClientListener class
#endif
#if 0
// Internal class to handle a client
//    /*protected*/ class ClientListener implements Runnable {

//        Socket clientSocket = NULL;
//        DataInputStream inStream = NULL;
//        DataOutputStream outStream = NULL;
//        Thread clientThread = NULL;

/*public*/ ClientListener::ClientListener(QTcpSocket* socket) {
log->debug("Starting new Client");
clientSocket = NULL;
inStream = NULL;
outStream = NULL;
clientThread = NULL;

clientSocket = socket;
try {
    inStream = new DataInputStream(clientSocket.getInputStream());

    outStream = new DataOutputStream(clientSocket.getOutputStream());
} catch (IOException e) {
    log->error("Error obtaining I/O Stream from socket.");
}
}

/*public*/ void ClientListener::start() {
clientThread = new Thread(this);
clientThread->start();
}

/*public*/ void ClientListener::stop(JmriServer* server) {
try {
    server->stopClient(inStream, outStream);
    clientSocket.close();
} catch (IOException e) {
    // silently ignore, since we may be reacting to a closed socket
}
clientThread = NULL;
}

//@Override
/*public*/ void ClientListener::run() {
// handle a client.
try {
    handleClient(inStream, outStream);
} catch (IOException* ex) {
    // When we get an IO exception here, we're done
    log->debug("Server Exiting");
    // Unregister with the server
    removeClient(this);
} catch (NullPointerException* ex) {
    // When we get an IO exception here, we're done with this client
    log->debug("Client Disconnect", ex.getMessage());
    // Unregister with the server
    removeClient(this);
}
}
#endif
//} // end of ClientListener class.
#if 0
// Handle communication to a client through inStream and outStream
/*public*/ void handleClient(DataInputStream inStream, DataOutputStream outStream) throws IOException {
    // Listen for commands from the client until the connection closes
    byte cmd[] = new byte[100];
    int count;
    while (true) {
        // Read the command from the client
        count = inStream.read(cmd);
        // Echo the input back to the client
        if (count != 0) {
            outStream.write(cmd);
        }
    }
}

// Send a stop message to the client if applicable
/*public*/ void stopClient(DataInputStream inStream, DataOutputStream outStream) throws IOException {
    outStream.writeBytes("");
}
//};
#endif
/*private*/ /*static*/ Logger* JmriServer::log = LoggerFactory::getLogger("JmriServer");
