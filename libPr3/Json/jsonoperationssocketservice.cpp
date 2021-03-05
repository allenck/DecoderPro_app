#include "jsonoperationssocketservice.h"
#include "train.h"
#include "trainmanager.h"
#include "json.h"
#include "jsonoperationshttpservice.h"
#include "instancemanager.h"

/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonOperationsSocketService extends JsonSocketService {


/*public*/ JsonOperationsSocketService::JsonOperationsSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent)
{
 //super(connection);
 this->service = new JsonOperationsHttpService(connection->getObjectMapper());
 trains = QMap<QString, TrainListener*>();
}

//@Override
/*public*/ void JsonOperationsSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException)
{
 this->locale = locale;
 QString id;
 if(data.value(JSON::ID).isDouble())
  id = QString::number(data.value(JSON::ID).toDouble());
 else
  id = data.value(JSON::ID).toString(); // Operations uses ID attribute instead of name attribute
 Q_ASSERT(id != "");
 if(type == JSON::TRAIN)
 {
  this->connection->sendMessage(this->service->doPost(type, id, data, locale));
  if (!this->trains.contains(id)) {
   TrainListener* listener;
      this->trains.insert(id, listener = new TrainListener(id, this));
//         Operations::TrainManager::instance()->getTrainById(id).addPropertyChangeListener(this->trains.get(id));
   connect(((Operations::TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainById(id)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)) );
  }
 }
 else
 {
  this->connection->sendMessage(this->service->doPost(type, id, data, locale));
 }
}

//@Override
/*public*/ void JsonOperationsSocketService::onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonOperationsSocketService::onClose() {
//    this->trains.values().forEach((listener) ->
 foreach(TrainListener* listener, trains.values())
 {
        //listener.train.removePropertyChangeListener(listener);
  disconnect(listener->train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
    }//);
    this->trains.clear();
}

///*private*/ class TrainListener implements PropertyChangeListener {

//    protected /*final*/ Train train;

/*protected*/ TrainListener::TrainListener(QString id, JsonOperationsSocketService* joss)
{
 this->train = ((Operations::TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainById(id);
 this->joss = joss;
}

//@Override
/*public*/ void TrainListener::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName() == (Operations::Train::BUILT_CHANGED_PROPERTY)
            || e->getPropertyName()==(Operations::Train::TRAIN_MOVE_COMPLETE_CHANGED_PROPERTY))
 {
  try
  {
   try
   {
    joss->connection->sendMessage(joss->service->doGet(JSON::TRAIN, this->train->getId(), joss->locale));
   }
   catch (JsonException ex)
   {
       joss->connection->sendMessage(ex.getJsonMessage());
   }
  } catch (IOException ex)
  {
   // if we get an error, de-register
   //this->train.removePropertyChangeListener(this);
   disconnect(train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

   joss->trains.remove(this->train->getId());
  }
 }
}
//}
