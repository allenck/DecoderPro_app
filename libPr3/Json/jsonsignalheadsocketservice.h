#ifndef JSONSIGNALHEADSOCKETSERVICE_H
#define JSONSIGNALHEADSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "propertychangelistener.h"
#include "signalhead.h"

class SignalHeadListener;
class JsonSignalHeadHttpService;
class JsonSignalHeadSocketService : public JsonSocketService
{
 Q_OBJECT
public:
 JsonSignalHeadSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();

private:
 /*private*/ /*final*/ JsonSignalHeadHttpService* service;
 /*private*/ /*final*/ QMap<QString, SignalHeadListener*>* signalHeads;// = new HashMap<>();
 /*private*/ QLocale locale;
 friend class SignalHeadListener;
};
/*private*/ class SignalHeadListener : public QObject,public PropertyChangeListener {
Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
    /*protected*/ /*final*/ SignalHead* signalHead;
private:
 JsonSignalHeadSocketService* jshss;
 public:
    /*public*/ SignalHeadListener(SignalHead* signalHead, JsonSignalHeadSocketService* jshss);
 QObject* self() override{return (QObject*)this;}
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
 friend class JsonSignalHeadSocketService;
};
#endif // JSONSIGNALHEADSOCKETSERVICE_H
