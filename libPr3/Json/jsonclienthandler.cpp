#include "jsonclienthandler.h"
#include "loggerfactory.h"
#include "json.h"
#include "serviceloader.h"
// /*public*/ class JsonClientHandler {
#include "jsonservicefactory.h"
#include <QSet>
#include "jsonsocketservice.h"
#include "jsonthrottleservicefactory.h"
#include "jsonsensorservicefactory.h"
#include "jsonutilservicefactory.h"
#include "jsonpowerservicefactory.h"
#include "jsonturnoutservicefactory.h"
#include "jsonrosterservicefactory.h"
#include "jsonblockservicefactory.h"
#include "jsonlayoutblockservicefactory.h"
#include "jsonlightservicefactory.h"
#include "jsonmemoryservicefactory.h"
#include"jsonsignalmastservicefactory.h"
#include "jsonsignalheadservicefactory.h"
#include "jsonreporterservicefactory.h"
#include "jsonoperationsservicefactory.h"
#include "jsonconsistservicefactory.h"

/**
 * When used as a parameter to {@link #onMessage(java.lang.String)}, will
 * cause a {@value jmri.server.json.JSON#HELLO} message to be sent to the
 * client.
 */
/*public*/ /*static*/ /*final*/ QString JsonClientHandler::HELLO_MSG = QString("{\"") + /*JSON::TYPE*/"type" + "\":\"" + /*JSON::HELLO*/ "hello"+ "\"}";
/*private*/ /*static*/ /*final*/ Logger* JsonClientHandler::log = LoggerFactory::getLogger("JsonClientHandler");

/*public*/ JsonClientHandler::JsonClientHandler(JsonConnection* connection, QObject* parent) : QObject(parent)
{
 this->connection = connection;
 this->services = new QMap<QString,  QSet<JsonSocketService*>*>();
#if 0
 ServiceLoader<JsonServiceFactory*>* fact = ServiceLoader<JsonServiceFactory*>::load("JsonServiceFactory");
 foreach (JsonServiceFactory* factory, *ServiceLoader<JsonServiceFactory*>::load("JsonServiceFactory"))
#endif
  // cheating here. Manually load the necessary service classes.
 // "JsonThrottleServiceFactory" << "JsonSensorServiceFactory" << "JsonPowerServiceFactory";
 QList<JsonServiceFactory*> list = QList<JsonServiceFactory*>();
 list << new JsonThrottleServiceFactory() << new JsonSensorServiceFactory()
      << new JsonUtilServiceFactory() << new JsonThrottleServiceFactory()
      << new JsonPowerServiceFactory() << new JsonTurnoutServiceFactory()
      << new JsonRosterServiceFactory() << new JsonBlockServiceFactory()
      << new JsonLightServiceFactory() << new JsonLayoutBlockServiceFactory()
      << new JsonMemoryServiceFactory() << new JsonSignalHeadServiceFactory()
      << new JsonSignalMastServiceFactory() << new JsonReporterServiceFactory()
      << new JsonOperationsServiceFactory() << new JsonConsistServiceFactory();

 foreach(JsonServiceFactory* factory, list)
 {
  foreach (QString type, factory->getTypes())
  {
   JsonSocketService* service = factory->getSocketService(connection);
   if (service != NULL)
   {
    QSet<JsonSocketService*>* set = this->services->value(type);
    if (set == NULL)
    {
        this->services->insert(type,  new QSet<JsonSocketService*>());
        set = this->services->value(type);
    }
    set->insert(service);
   }
  }
 }
}

/*public*/ void JsonClientHandler::dispose()
{
 //services.values().stream().forEach((set) ->
 foreach(QSet<JsonSocketService*>* set, *services)
 {
  //set.stream().forEach((service) ->
  foreach(JsonSocketService* service, *set)
  {
   service->onClose();
  }//);
 }//);
}

/**
 * Process a JSON string and handle appropriately.
 *
 * Currently JSON strings in four different forms are handled by this
 * method:<ul> <li>list requests in the form:
 * <code>{"type":"list","list":"trains"}</code> or
 * <code>{"list":"trains"}</code> that are passed to the JsonUtil for
 * handling.</li> <li>individual item state requests in the form:
 * <code>{"type":"turnout","data":{"name":"LT14"}}</code> that are passed to
 * type-specific handlers. In addition to the initial response, these
 * requests will initiate "listeners", which will send updated responses
 * every time the item's state changes.<ul>
 * <li>an item's state can be set by adding a <strong>state</strong> node to
 * the <em>data</em> node:
 * <code>{"type":"turnout","data":{"name":"LT14","state":4}}</code>
 * <li>individual types can be created if a <strong>method</strong> node
 * with the value <em>put</em> is included in message:
 * <code>{"type":"turnout","method":"put","data":{"name":"LT14"}}</code>.
 * The <em>method</em> node may be included in the <em>data</em> node:
 * <code>{"type":"turnout","data":{"name":"LT14","method":"put"}}</code>
 * Note that not all types support this-></li></ul>
 * </li><li>a heartbeat in the form <code>{"type":"ping"}</code>. The
 * heartbeat gets a <code>{"type":"pong"}</code> response.</li> <li>a sign
 * off in the form: <code>{"type":"goodbye"}</code> to which an identical
 * response is sent before the connection gets closed.</li></ul>
 *
 * @param string the message
 * @throws java.io.IOException if communications with the client is broken
 */
/*public*/ void JsonClientHandler::onMessage(QString string) throw (IOException)
{
    log->debug(tr("Received from client: %1").arg(string));

    try {
        //this->onMessage(this->connection->getObjectMapper().readTree(string));
     QJsonDocument jdoc = QJsonDocument::fromJson(string.toUtf8());
     this->onMessage(jdoc.object());
    } catch (JsonProcessingException pe) {
        log->warn(tr("Exception processing \"%1\"\n%2").arg(string).arg(pe.getMessage()));
        this->sendErrorMessage(500, tr( "Unable to process JSON message with error: %1.").arg( pe.getLocalizedMessage()));
    }
}

/**
 * Process a JSON node and handle appropriately.
 *
 * See {@link #onMessage(java.lang.String)} for expected JSON objects.
 *
 * @param root the JSON node.
 * @throws java.io.IOException if communications is broken with the client.
 * @see #onMessage(java.lang.String)
 */
/*public*/ void JsonClientHandler::onMessage(/*JsonNode*/QJsonObject root) throw (IOException) {
 try
 {
  //QString type = root.path(JSON::TYPE).asText();
QString type = root.value(JSON::TYPE).toString();
  if (!root.contains(JSON::TYPE) && root.value(JSON::LIST).isString())
  {
      type = JSON::LIST;
  }

  //JsonNode data = root.path(JSON::DATA);
  QJsonObject data = root.value(JSON::DATA).toObject();

//        if (data.path(JSON::METHOD).isMissingNode() && root.path(JSON::METHOD).isValueNode())
  if(data.value(JSON::METHOD).toString().isEmpty() && root.value(JSON::METHOD).isString())
  {
   //((ObjectNode) data).put(JSON::METHOD, root.path(JSON::METHOD).asText());
   data.insert(JSON::METHOD, root.value(JSON::METHOD).toString());
  }
  QJsonDocument doc = QJsonDocument(data);
  log->debug(tr("Processing %1 with %2").arg(type).arg(QString(doc.toJson(QJsonDocument::Compact))));
  if(type == JSON::THROTTLE)
   qDebug() << "throttle";
  if(data.isEmpty())
//         qDebug() << "data is empty";
//        else
//         qDebug() << "data is not empty";

  if ((type == (JSON::HELLO) || type == (JSON::PING) || type== (JSON::GOODBYE))
          && /*data.isMissingNode()*/data.isEmpty())
  {
      // these messages are not required to have a data payload,
      // so create one if the message did not contain one to avoid
      // special casing later
      data = this->connection->getObjectMapper().createObjectNode();
      data.insert("",/*"null"*/QJsonValue());
  }
  if(type == JSON::POWER && data.isEmpty())
  {
   if (this->services->value(type) != NULL)
   {
    foreach (JsonSocketService* service, *this->services->value(type)) {
        service->onMessage(type, data, this->connection->getLocale());
    }
   }
  }
  else
  if (type == (JSON::LIST) )
  {
   QString list = root.value(JSON::LIST).toString();
   if (this->services->value(list) != NULL)
   {
    foreach (JsonSocketService* service, *this->services->value(list))
    {
     QLocale locale = this->connection->getLocale();
     service->onList(list, data, locale);
    }
    return;
   }
   else
   {
    log->warn(tr("Requested list type '%1' unknown.").arg(list));
    this->sendErrorMessage(404, tr("Unknown object type %1 was requested.").arg(list));
    return;
   }
  }
#if 1
  else if (!data.isEmpty())
  {
   //switch (type) {
   if(type == JSON::HELLO || type == JSON::LOCALE )
   {
    if (!data.value(JSON::LOCALE).isUndefined())
    {
        this->connection->setLocale(QLocale(data.value(JSON::LOCALE).toString()));
    }
       //$FALL-THROUGH$ to default action
   }
   else
   {
    if (this->services->value(type) != NULL)
    {
     foreach (JsonSocketService* service, *this->services->value(type)) {
         service->onMessage(type, data, this->connection->getLocale());
     }
    }
    else
    {
     log->warn(tr("Requested type '%1' unknown.").arg(type));
     this->sendErrorMessage(404, tr("Unknown object type %1 was requested.").arg(type));
    }
   }
  }
  else {
      this->sendErrorMessage(400, tr( "Data portion of JSON message missing."));
  }
  if (type == (JSON::GOODBYE)) {
      // close the connection if GOODBYE is received.
      this->connection->close();
  }
#endif
 } catch (JmriException je) {
     this->sendErrorMessage(500, tr("Unsupported operation attempted: %1.").arg( je.getLocalizedMessage()));
 } catch (JsonException je) {
     this->sendErrorMessage(je);
 }
}

/**
 *
 * @param heartbeat seconds until heartbeat must be received before breaking
 *                  connection to client; currently ignored
 * @throws IOException if communications broken with client
 * @deprecated since 4.5.2; use {@link #onMessage(java.lang.String)} with
 * the parameter {@link #HELLO_MSG} instead
 */
//@Deprecated
/*public*/ void JsonClientHandler::sendHello(int /*heartbeat*/) throw (IOException) {
    this->onMessage(HELLO_MSG);
}

/*private*/ void JsonClientHandler::sendErrorMessage(int code, QString message) throw (IOException) {
    JsonException ex =  JsonException(code, message);
    this->sendErrorMessage(ex);
}

/*private*/ void JsonClientHandler::sendErrorMessage(JsonException ex) throw (IOException) {
    this->connection->sendMessage(ex.getJsonMessage());
}
