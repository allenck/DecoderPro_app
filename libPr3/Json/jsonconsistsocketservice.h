#ifndef JSONCONSISTSOCKETSERVICE_H
#define JSONCONSISTSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "dcclocoaddress.h"
#include "consistlistener.h"
#include "consistlistlistener.h"

class JsonConsistHttpService;
class JsonConsistListener;
class JsonConsistListListener;
class JsonConsistSocketService : public JsonSocketService
{
 Q_OBJECT
public:
 JsonConsistSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();

private:
 /*private*/ /*final*/ JsonConsistHttpService* service;
 /*private*/ /*final*/ QSet<DccLocoAddress*> consists;// = new QSet<DccLocoAddress*>();
 /*private*/ QLocale locale;
 /*private*/ /*final*/ JsonConsistListener* consistListener;// = new JsonConsistListener();
 /*private*/ /*final*/ JsonConsistListListener* consistListListener;// = new JsonConsistListListener();
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("JsonConsistSocketService");
friend class JsonConsistListListener;
friend class JsonConsistListener;
};

/*private*/ class JsonConsistListener : public ConsistListener {
Q_OBJECT
 JsonConsistSocketService* jcss;
    //@Override
public:
 JsonConsistListener(JsonConsistSocketService* jcss);
    /*public*/ void consistReply(DccLocoAddress* locoaddress, int status);
};

/*private*/ class JsonConsistListListener : public ConsistListListener {
Q_OBJECT
 JsonConsistSocketService* jcss;
 public:
 JsonConsistListListener(JsonConsistSocketService* jcss);
    //@Override
    /*public*/ void notifyConsistListChanged() ;
};
#endif // JSONCONSISTSOCKETSERVICE_H
