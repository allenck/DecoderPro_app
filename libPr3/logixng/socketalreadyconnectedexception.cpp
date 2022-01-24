#include "socketalreadyconnectedexception.h"

/**
 * The FemaleSocket is already connected.
 * Before a FemaleSocket can accept a connect request, it must be disconnected.
 *
 * @author Daniel Bergqvist 2019
 */
//public class SocketAlreadyConnectedException extends JmriException {

    /**
     * Creates a new instance of <code>SocketAlreadyConnectedException</code> without detail message.
     */
    /*public*/ SocketAlreadyConnectedException::SocketAlreadyConnectedException() : JmriException() {
    }

    /**
     * Constructs an instance of <code>SocketAlreadyConnectedException</code> with the specified detail message.
     * @param msg the detail message.
     */
    /*public*/ SocketAlreadyConnectedException::SocketAlreadyConnectedException(QString msg) : JmriException(msg)  {
        //super(msg);
    }


