#include "jsonreportersocketservice.h"
#include "jsonreporter.h"
#include "jsonreporterhttpservice.h"
#include "json.h"
#include "instancemanager.h"
#include "reportermanager.h"

/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonReporterSocketService extends JsonSocketService {


 /*public*/ JsonReporterSocketService::JsonReporterSocketService(JsonConnection* connection, QObject* parent)
: JsonSocketService(connection, parent)
{
  //super(connection);
  this->service = new JsonReporterHttpService(connection->getObjectMapper());
  reporters = new QMap<QString, ReporterListener*>();
}

 //@Override
 /*public*/ void JsonReporterSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException)
{
 this->locale = locale;
 QString name = data.value(JSON::NAME).toString();
 if (data.value(JSON::METHOD).toString() == (JSON::PUT)) {
     this->connection->sendMessage(this->service->doPut(type, name, data, locale));
 } else {
     this->connection->sendMessage(this->service->doPost(type, name, data, locale));
 }
 if (!this->reporters->contains(name))
 {
  Reporter* reporter = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter(name);
  if (reporter != NULL)
  {
   ReporterListener* listener = new ReporterListener(reporter, this);
   //reporter.addPropertyChangeListener(listener);
   connect(reporter->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
   this->reporters->insert(name, listener);
  }
 }
}

 //@Override
 /*public*/ void JsonReporterSocketService::onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
     this->locale = locale;
     this->connection->sendMessage(this->service->doGetList(type, locale));
 }

 //@Override
 /*public*/ void JsonReporterSocketService::onClose() {
     //reporters.values().stream().forEach((reporter) ->
foreach(ReporterListener* reporter, reporters->values())
     {
         //reporter.reporter.removePropertyChangeListener(reporter);
disconnect(reporter->reporter->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), reporter, SLOT(propertyChange(PropertyChangeEvent*)));
     }//);
     reporters->clear();
 }

// /*/*private*/*/ class ReporterListener implements PropertyChangeListener {

// protected final Reporter reporter;

/*public*/ ReporterListener::ReporterListener(Reporter* reporter,JsonReporterSocketService* jrss) {
 this->reporter = reporter;
this->jrss = jrss;
}

//@Override
/*public*/ void ReporterListener::propertyChange(PropertyChangeEvent* e) {
 // If the Commanded State changes, show transition state as "<inconsistent>"
 if (e->getPropertyName() == ("currentReport")) {
     try {
         try {
             jrss->connection->sendMessage(jrss->service->doGet(JsonReporter::REPORTER, this->reporter->getSystemName(), jrss->locale));
         } catch (JsonException ex) {
             jrss->connection->sendMessage(ex.getJsonMessage());
         }
     } catch (IOException ex) {
         // if we get an error, de-register
         //reporter.removePropertyChangeListener(this);
   disconnect(reporter->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this,SLOT(propertyChange(PropertyChangeEvent*)));
         jrss->reporters->remove(this->reporter->getSystemName());
     }
 }
}

