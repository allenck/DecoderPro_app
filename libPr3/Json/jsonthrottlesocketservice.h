#ifndef JSONTHROTTLESOCKETSERVICE_H
#define JSONTHROTTLESOCKETSERVICE_H
#include "jsonsocketservice.h"

class Logger;
class JsonThrottle;
class JsonThrottleSocketService : public JsonSocketService
{
 Q_OBJECT
public:
 JsonThrottleSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, /*JsonNode*/QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ void onClose();
 void release(JsonThrottle* throttle);
 /*public*/ void sendMessage(JsonThrottle* throttle, QJsonObject data) throw (IOException);

private:
 /*private*/ /*final*/ QMap<QString, JsonThrottle*>* throttles;// = new HashMap<>();
 /*private*/ /*final*/ QMap<JsonThrottle*, QString>* throttleIds;// = new HashMap<>();
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(JsonThrottleSocketService.class);

};

#endif // JSONTHROTTLESOCKETSERVICE_H
