#ifndef JSONUTILSOCKETSERVICE_H
#define JSONUTILSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "json.h"
#include "jmriexception.h"

class JsonUtilHttpService;
class JsonUtilSocketService : public JsonSocketService
{
public:
 JsonUtilSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);


 //@Override
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();

private:
 /*private*/ /*final*/ JsonUtilHttpService* service;
};
#endif // JSONUTILSOCKETSERVICE_H
