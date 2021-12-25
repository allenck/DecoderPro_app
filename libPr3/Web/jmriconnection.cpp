#include "jmriconnection.h"
#include "loggerfactory.h"
#include <QLocale>

JmriConnection::JmriConnection(QObject *parent) : QObject(parent)
{
 session = NULL;
 webSocket = NULL;
 dataOutputStream = NULL;
}
/**
 * Abstraction of DataOutputStream and WebSocket.Connection classes.
 *
 * Used so that that server objects need only to use a single object/method to
 * send data to any supported object type.
 *
 * @author rhwood Randall Wood Copyright (C) 2012, 2014
 */
///*public*/ class JmriConnection {

/**
 * Create a JmriConnection that sends output to a WebSocket.
 *
 * @param connection WebSocket Session to use.
 */
/*public*/ JmriConnection::JmriConnection(QWebSocket* connection, QObject *parent) : QObject(parent) {
common();
    this->webSocket = connection;
 connect(webSocket, SIGNAL(disconnected()), this, SLOT(on_socketDisconnected()));
}

void JmriConnection::on_socketDisconnected()
{
 this->webSocket = NULL;
}

/**
 * Create a JmriConnection that sends output to a DataOutputStream.
 *
 * @param output DataOutputStream to use
 */
/*public*/ JmriConnection::JmriConnection(DataOutputStream* output, QObject *parent)  : QObject(parent)
{
    this->dataOutputStream = output;
}

/*private*/ /*final*/ /*static*/ Logger* JmriConnection::log = LoggerFactory::getLogger("JmriConnection");

void JmriConnection::common()
{
// session = NULL;
 dataOutputStream = NULL;
 locale = QLocale();

}
/**
 * Get the WebSocket session.
 *
 * @return the WebSocket session
 */
///*public*/ Session* JmriConnection::getSession() {
//    return this->session;
//}

/**
 * @deprecated see {@link #getSession() }
 * @return the WebSocket session
 */
//@Deprecated
///*public*/ Session* JmriConnection::getWebSocketConnection() {
//    return this->getSession();
//}
/*public*/ QWebSocket* JmriConnection::getSocket() { return this->webSocket;}

/**
 * Set the WebSocket session.
 *
 * @param session the WebSocket session
 */
///*public*/ void JmriConnection::setSession(Session* session) {
//    this->session = session;
//}

/**
 * @deprecated see {@link #setSession(org.eclipse.jetty.websocket.api.Session)
 * }
 *
 * @param webSocketConnection the WebSocket session
 */
////@Deprecated
///*public*/ void JmriConnection::setWebSocketConnection(Session* webSocketConnection) {
//    this>setSession(session);
//}

/*public*/ DataOutputStream* JmriConnection::getDataOutputStream() {
    return dataOutputStream;
}

/*public*/ void JmriConnection::setDataOutputStream(DataOutputStream* dataOutputStream) {
    this->dataOutputStream = dataOutputStream;
}

/**
 * Send a String to the instantiated connection.
 *
 * This method throws an IOException so the server or servlet holding the
 * connection open can respond to the exception if there is an immediate
 * failure. If there is an asynchronous failure, the connection is closed.
 *
 * @param message message to send
 * @throws IOException if problem sending message
 */
/*public*/ void JmriConnection::sendMessage(QString message) /*throw (IOException)*/ {
    if (this->dataOutputStream != NULL) {
        //this->dataOutputStream->writeBytes(message);
     *dataOutputStream << message;
    }
    qDebug() << "send:" << message;
    if(this->webSocket != NULL   && this->webSocket->isValid())
    {
     webSocket->sendTextMessage(message);
    }
#if 0
    else if (this->session != NULL && this->session.isOpen()) {
        try {
            this->session.getRemote().sendString(message, new WriteCallback() {
                @Override
                /*public*/ void writeFailed(Throwable thrwbl) {
                    log.error("Exception \"{}\" sending {}", thrwbl->getMessage(), message);
                    JmriConnection.this->getSession().close(StatusCode.NO_CODE, thrwbl->getMessage());
                }

                @Override
                /*public*/ void writeSuccess() {
                    log.debug("Sent {}", message);
                }
            });
        } catch (WebSocketException ex) {
            log.debug("Exception sending message", ex);
            // A WebSocketException is most likely a broken socket,
            // so rethrow it as an IOException
            throw new IOException(ex);
        }
    }
#endif
}

/**
 * Close the connection.
 *
 * Note: Objects using JmriConnection with a
 * {@link org.eclipse.jetty.websocket.api.Session} may prefer to use
 * <code>getSession().close()</code> since Session.close() does not throw an
 * IOException.
 *
 * @throws IOException if problem closing connection
 */
/*public*/ void JmriConnection::close() /*throw (IOException)*/ {
    if (this->dataOutputStream != NULL) {
        //this->dataOutputStream->close();
     this->dataOutputStream->device()->close();
    }
#if 0
    else if (this->session != NULL) {
        this->session.close();
    }
#endif
}

/**
 * @return the locale
 */
/*public*/ QLocale JmriConnection::getLocale() {
    return locale;
}

/**
 * @param locale the locale to set
 */
/*public*/ void JmriConnection::setLocale(QLocale locale) {
    this->locale = locale;
}
