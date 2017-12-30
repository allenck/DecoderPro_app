#include "jsonutilsocketservice.h"
#include "jsonutilhttpservice.h"
/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonUtilSocketService extends JsonSocketService {


/*public*/ JsonUtilSocketService::JsonUtilSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent) {
    //super(connection);
    this->service = new JsonUtilHttpService(connection->getObjectMapper());
}

//@Override
/*public*/ void JsonUtilSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException )
{
 QString name = data.value(JSON::NAME).toString();
//     switch (type) {
if(type ==  JSON::LOCALE)
{
      // do nothing - we only want to prevent an error at this point
}
else if(type ==  JSON::PING)
  {
      //this->connection->sendMessage(this->connection->getObjectMapper().createObjectNode().insert(JSON::TYPE, JSON::PONG));
 QJsonObject obj = QJsonObject();
 obj.insert(JSON::TYPE, JSON::PONG);
 this->connection->sendMessage(obj);
 }
 else if(type == JSON::GOODBYE)
  {
      //this->connection->sendMessage(this->connection->getObjectMapper().createObjectNode().insert(JSON::TYPE, JSON::GOODBYE));
 QJsonObject obj = QJsonObject();
 obj.insert(JSON::TYPE, JSON::GOODBYE);
 this->connection->sendMessage(obj);
  }
  else
  {
   this->connection->sendMessage(this->service->doPost(type, name, data, locale));
  }
}

//@Override
/*public*/ void JsonUtilSocketService::onList(QString type, QJsonObject /*data*/, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonUtilSocketService::onClose() {
    // nothing to cleanup
}
