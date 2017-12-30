#ifndef JSONROSTERSOCKETSERVICE_H
#define JSONROSTERSOCKETSERVICE_H
#include "jsonsensorsocketservice.h"
#include "propertychangelistener.h"
#include "json.h"

class Logger;
class JsonRosterHttpService;
class JsonRosterSocketService;
/*private*/ class JsonRosterEntryListener : public PropertyChangeListener {
Q_OBJECT
 JsonRosterSocketService* jrss;
public:
 JsonRosterEntryListener( JsonRosterSocketService* jrss);
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
};

/*private*/ class JsonRosterListener : public PropertyChangeListener {
Q_OBJECT
    //@Override
 JsonRosterSocketService* jrss;
public:
 JsonRosterListener(JsonRosterSocketService* jrss);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
};
class JsonRosterSocketService : public JsonSocketService
{
public:
 /*public*/ JsonRosterSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void listen();
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(JsonRosterSocketService.class);
 /*private*/ /*final*/ JsonRosterListener* rosterListener;// = new JsonRosterListener(JsonRosterSocketService* jrss);
 /*private*/ /*final*/ JsonRosterEntryListener* rosterEntryListener;// = new JsonRosterEntryListener(JsonRosterSocketService* jrss);
 /*private*/ /*final*/ JsonRosterHttpService* service;
 /*private*/ bool listening = false;
 friend class JsonRosterEntryListener;
 friend class JsonRosterListener;
};
#endif // JSONROSTERSOCKETSERVICE_H
