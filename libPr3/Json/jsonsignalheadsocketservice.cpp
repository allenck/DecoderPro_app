#include "jsonsignalheadsocketservice.h"
#include "jsonsignalheadhttpservice.h"
#include "jsonsignalheadservicefactory.h"
#include "jsonsignalhead.h"
#include "json.h"
#include "signalheadmanager.h"
#include "instancemanager.h"
/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonSignalHeadSocketService extends JsonSocketService {


/*public*/ JsonSignalHeadSocketService::JsonSignalHeadSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent){
    //super(connection);
 signalHeads = new QMap<QString, SignalHeadListener*>();
 this->service = new JsonSignalHeadHttpService(connection->getObjectMapper());
}

//@Override
/*public*/ void JsonSignalHeadSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException)
{
 this->locale = locale;
 QString name = data.value(JSON::NAME).toString();
 if (data.value(JSON::METHOD).toString() == (JSON::PUT))
 {
  this->connection->sendMessage(this->service->doPut(type, name, data, locale));
 }
 else
 {
  this->connection->sendMessage(this->service->doPost(type, name, data, locale));
 }
 if (!this->signalHeads->contains(name))
 {
  SignalHead* signalHead = ((SignalHeadManager*) InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name);
  if (signalHead != NULL)
  {
   SignalHeadListener* listener = new SignalHeadListener(signalHead, this);
   //signalHead.addPropertyChangeListener(listener);
   connect(signalHead->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),listener, SLOT(propertyChange(PropertyChangeEvent*)));
   this->signalHeads->insert(name, listener);
  }
 }
}

//@Override
/*public*/ void JsonSignalHeadSocketService::onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonSignalHeadSocketService::onClose()
{
 //signalHeads.values().stream().forEach((reporter) ->
 foreach(SignalHeadListener* reporter, signalHeads->values())
 {
  //reporter.signalHead.removePropertyChangeListener(reporter);
  disconnect(reporter->signalHead->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), reporter,SLOT(propertyChange(PropertyChangeEvent*)));
 }//);
 signalHeads->clear();
}

//    /*private*/ class SignalHeadListener implements PropertyChangeListener {

//        protected /*final*/ SignalHead signalHead;

/*public*/ SignalHeadListener::SignalHeadListener(SignalHead* signalHead, JsonSignalHeadSocketService* jshss) {
    this->signalHead = signalHead;
this->jshss = jshss;
}

//@Override
/*public*/ void SignalHeadListener::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("Appearance") || e->getPropertyName()==("Held"))
 {
  try
  {
   try
   {
    jshss->connection->sendMessage(jshss->service->doGet(JsonSignalHead::SIGNAL_HEAD, this->signalHead->getSystemName(), jshss->locale));
   }
   catch (JsonException ex)
   {
    jshss->connection->sendMessage(ex.getJsonMessage());
   }
  } catch (IOException ie)
  {
   // if we get an error, de-register
   //signalHead.removePropertyChangeListener(this);
disconnect(signalHead->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   jshss->signalHeads->remove(this->signalHead->getSystemName());
  }
 }
}

