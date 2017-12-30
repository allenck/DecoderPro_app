#ifndef JSONSIGNALMASTSOCKETSERVICE_H
#define JSONSIGNALMASTSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "propertychangelistener.h"
#include "signalmast.h"

class JsonSignalMastHttpService;
class SignalMastListener;
class JsonSignalMastSocketService : public JsonSocketService
{
 Q_OBJECT
public:
 JsonSignalMastSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();

private:
 /*private*/ /*final*/ JsonSignalMastHttpService* service;
 /*private*/ /*final*/QMap<QString, SignalMastListener*>* signalMasts;// = new HashMap<>();
 /*private*/ QLocale locale;
friend class SignalMastListener;
};
/*private*/ class SignalMastListener : public PropertyChangeListener {
Q_OBJECT
/*protected*/ /*final*/ SignalMast* signalMast;
private:
 JsonSignalMastSocketService* jsmss;
public:
/*public*/ SignalMastListener(SignalMast* signalMast, JsonSignalMastSocketService* jsmss);
public slots:
/*public*/ void propertyChange(PropertyChangeEvent* e);
 friend class JsonSignalMastSocketService;
};

#endif // JSONSIGNALMASTSOCKETSERVICE_H
