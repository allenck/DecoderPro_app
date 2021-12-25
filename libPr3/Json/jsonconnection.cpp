#include "jsonconnection.h"

JsonConnection::JsonConnection(QObject* parent) : JmriConnection(parent)
{

}
/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonConnection extends JmriConnection {


///*public*/ JsonConnection::JsonConnection(Session* connection, QObject* parent): JmriConnection(connection, parent){
//    //super(connection);
//  objectMapper = ObjectMapper();
//}

/*public*/ JsonConnection::JsonConnection(QWebSocket* connection, QObject* parent): JmriConnection(connection, parent){
    //super(connection);
  objectMapper = ObjectMapper();
}

/*public*/ JsonConnection::JsonConnection(DataOutputStream* output, QObject* parent) : JmriConnection(output, parent) {
    //super(output);
 objectMapper = ObjectMapper();
}

/**
 * Get the ObjectMapper for this connection.
 *
 * @return the ObjectMapper
 */
/*public*/ ObjectMapper JsonConnection::getObjectMapper() {
    return this->objectMapper;
}

/**
 * Send a JsonNode to the instantiated connection.
 *
 * This method throws an IOException so the server or servlet holding the
 * connection open can respond to the exception.
 *
 * @param message the object or array to send as a message
 * @throws java.io.IOException if unable to send the message
 */
/*public*/ void JsonConnection::sendMessage(QJsonObject message) /*throw (IOException)*/
{
 //JmriConnection::sendMessage(this->getObjectMapper().writeValueAsString(message));
 QJsonDocument doc = QJsonDocument(message);
 JmriConnection::sendMessage(doc.toJson(QJsonDocument::Compact));
}

/*public*/ void JsonConnection::sendMessage(QJsonArray message) /*throw (IOException)*/
{
 //JmriConnection::sendMessage(this->getObjectMapper().writeValueAsString(message));
 QJsonDocument doc = QJsonDocument(message);
 JmriConnection::sendMessage(doc.toJson(QJsonDocument::Compact));
}
/*public*/ void JsonConnection::sendMessage(QJsonValue message) /*throw (IOException)*/
{
 //JmriConnection::sendMessage(this->getObjectMapper().writeValueAsString(message));
 QJsonDocument doc;
 if(message.isArray())
  doc = QJsonDocument(message.toArray());
 else
  doc = QJsonDocument(message.toObject());
 JmriConnection::sendMessage(doc.toJson(QJsonDocument::Compact));
}
