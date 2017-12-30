#include "jsonwebsocket.h"
#include "jsonconnection.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "json.h"

JsonWebSocket::JsonWebSocket(QObject *parent) : QObject(parent)
{

}
/**
 * @author Randall Wood Copyright (C) 2012, 2013, 2016
 */
//@WebSocket
///*public*/ class JsonWebSocket {

    /*private*/ /*final*/ /*static*/ Logger* JsonWebSocket::log = LoggerFactory::getLogger("JsonWebSocket");

    //@OnWebSocketConnect
/*public*/ void JsonWebSocket::onOpen(/*Session*/QWebSocket* sn)
{
    log->debug("Opening connection");
    try {
        this->connection = new JsonConnection(sn);
//        sn.setIdleTimeout((long) (JsonServerPreferences.getDefault().getHeartbeatInterval() * 1.1));
        this->handler = new JsonClientHandler(this->connection);
//        this->shutDownTask = new QuietShutDownTask("Close open web socket") { // NOI18N
//            @Override
//            /*public*/ boolean execute() {
//                try {
//                    JsonWebSocket.this->getConnection().sendMessage(JsonWebSocket.this->getConnection().getObjectMapper().createObjectNode().put(JSON.TYPE, JSON.GOODBYE));
//                } catch (IOException e) {
//                    log->warn("Unable to send goodbye while closing socket.\nError was {}", e.getMessage());
//                }
//                JsonWebSocket.this->getConnection().getSession().close();
//                return true;
//            }
//        };
        shutDownTask = new JWSShutdownTask("Close open web socket", this);
        log->debug("Sending hello");
        this->handler->onMessage(JsonClientHandler::HELLO_MSG);
    } catch (IOException e) {
        log->warn(tr("Error opening WebSocket:\n%1").arg(e.getMessage()));
        sn->close();
    }
    ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->_register(this->shutDownTask);
}

JWSShutdownTask::JWSShutdownTask(QString text, JsonWebSocket *jws) : QuietShutDownTask(text)
{
 this->jws = jws;
}

/*public*/ bool JWSShutdownTask::execute() {
    try {
  QJsonObject obj = QJsonObject();
  obj.insert(JSON::TYPE, JSON::GOODBYE);
        jws->getConnection()->sendMessage(QJsonValue(obj));
    } catch (IOException e) {
        jws->log->warn(tr("Unable to send goodbye while closing socket.\nError was %1").arg(e.getMessage()));
    }
    jws->getConnection()->getSocket()->close();
    return true;
}



//@OnWebSocketClose
/*public*/ void JsonWebSocket::onClose(int i, QString string) {
    log->debug(tr("Closing connection because %1 (%1)").arg(string).arg(i));
    this->handler->dispose();
    ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->deregister(this->shutDownTask);
}

//@OnWebSocketError
/*public*/ void JsonWebSocket::onError(Throwable* thrwbl) {
    if (static_cast<SocketTimeoutException*>(thrwbl) != NULL) {
        this->connection->getSocket()->close(/*StatusCode::NO_CLOSE*/QWebSocketProtocol::CloseCodeAbnormalDisconnection, thrwbl->getMessage());
    } else {
        log->error(thrwbl->getMessage());
    }
}

//@OnWebSocketMessage
/*public*/ void JsonWebSocket::onMessage(QString string) {
    try {
        this->handler->onMessage(string);
    } catch (IOException e) {
        log->error("Error on WebSocket message:\n{}", e.getMessage());
        this->connection->getSocket()->close();
        ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->deregister(this->shutDownTask);
    }
}

/**
 * @return the connection
 */
/*protected*/ JsonConnection* JsonWebSocket::getConnection() {
    return connection;
}
