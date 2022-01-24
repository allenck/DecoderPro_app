#include "jsonthrottlesocketservice.h"
#include "jsonthrottle.h"
#include "loggerfactory.h"
#include "httpservletresponse.h"
#include "json.h"

/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonThrottleSocketService extends JsonSocketService {

/*private*/ /*final*/ /*static*/ Logger* JsonThrottleSocketService::log = LoggerFactory::getLogger("JsonThrottleSocketService");

/*public*/ JsonThrottleSocketService::JsonThrottleSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent)
{
 // super(connection);
 throttles = new QMap<QString, JsonThrottle*>();
 throttleIds = new QMap<JsonThrottle*, QString>();
}

//@Override
/*public*/ void JsonThrottleSocketService::onMessage(QString /*type*/, QJsonObject data, QLocale locale) /*throw new (IOException, JmriException, JsonException)*/
{
 QJsonDocument doc = QJsonDocument(data);
    log->debug(tr("Processing %1").arg(QString(doc.toJson(QJsonDocument::Compact))));
    QString id = data.value(JSON::THROTTLE).toString();
    if (id.isEmpty()) {
        throw new JsonException(HttpServletResponse::SC_BAD_REQUEST, tr( "Throttles must be assigned a client ID.")); // NOI18N
    }
    JsonThrottle* throttle = this->throttles->value(id);
    if (!this->throttles->contains(id)) {
        throttle = JsonThrottle::getThrottle(id, data, this);
        this->throttles->insert(id, throttle);
        this->throttleIds->insert(throttle, id);
        throttle->sendStatus(this);
    }
    throttle->onMessage(locale, data, this);
}

//@Override
/*public*/ void JsonThrottleSocketService::onList(QString type, /*JsonNode*/QJsonObject /*data*/, QLocale /*locale*/) /*throw new (JsonException)*/ {
    throw new JsonException(HttpServletResponse::SC_BAD_REQUEST, /*tr(locale,*/ tr("%1 cannot be listed.").arg( type));
}

//@Override
/*public*/ void JsonThrottleSocketService::onClose() {
    foreach (QString throttleId, this->throttles->keys()) {
        this->throttles->value(throttleId)->close(this, false);
        this->throttles->remove(throttleId);
    }
    this->throttleIds->clear();
}

void JsonThrottleSocketService::release(JsonThrottle* throttle) {
    throttle->release(this, true);
    this->throttles->remove(this->throttleIds->value(throttle));
    this->throttleIds->remove(throttle);
}

/*public*/ void JsonThrottleSocketService::sendMessage(JsonThrottle* throttle, QJsonObject data) /*throw new (IOException)*/ {
    QString id = this->throttleIds->value(throttle);
    if (id != NULL) {
        QJsonObject root = QJsonObject(); //= this->connection->getObjectMapper().createObjectNode();
        root.insert(JSON::TYPE, JSON::THROTTLE);
        data.insert(JSON::THROTTLE, id);
        root.insert(JSON::DATA, data);
        this->connection->sendMessage(root);
    }
}
