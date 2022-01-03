#include "jsonoperationshttpservice.h"
#include "loggerfactory.h"
#include "jsonutil.h"
#include "json.h"
#include "carmanager.h"
#include "car.h"
#include "location.h"
#include "trainmanager.h"
#include "locationmanager.h"
#include "engine.h"
#include "enginemanager.h"
#include "jsonutil.h"
#include "instancemanager.h"
/**
 *
 * @author Randall Wood (C) 2016
 */
// /*public*/ class JsonOperationsHttpService extends JsonHttpService {

/*private*/ /*final*/ /*static*/ Logger* JsonOperationsHttpService::log = LoggerFactory::getLogger("JsonOperationsHttpService");
//    /*private*/ /*final*/ JsonUtil utilities;

/*public*/ JsonOperationsHttpService::JsonOperationsHttpService(ObjectMapper mapper, QObject* parent) : JsonHttpService(mapper, parent){
    //super(mapper);
    this->utilities = new JsonUtil(mapper);
}

//@Override
/*public*/ QJsonValue JsonOperationsHttpService::doGet(QString type, QString name, QLocale locale) throw (JsonException) {
    if(type == JSON::CAR)
            return JsonUtil::getCar(locale, name);
    else if(type == JSON::ENGINE)
            return JsonUtil::getEngine(locale, name);
    else if(type == JSON::LOCATION)
            return JsonUtil::getLocation(locale, name);
    else if(type == JSON::TRAIN || type == JSON::TRAINS)
            return JsonUtil::getTrain(locale, name);
    else
            throw new JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, tr("ErrorInternal %1").arg(type)); // NOI18N
}

//@Override
/*public*/ QJsonObject JsonOperationsHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException)
{
 if(type == JSON::TRAIN)
 {
  this->setTrain(locale, name, data);
  return JsonUtil::getTrain(locale, name);
 }
 else if(type == JSON::CAR || type == JSON::ENGINE || type == JSON::LOCATION || type == JSON::TRAINS)
         return this->doGet(type, name, locale).toObject();
 else
         throw new JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, tr( "ErrorInternal %1").arg(type)); // NOI18N
}

//@Override
/*public*/ QJsonValue JsonOperationsHttpService::doGetList(QString type, QLocale locale) throw (JsonException) {
    if(type == JSON::CARS)
            return this->getCars(locale);
    else if(type == JSON::ENGINES)
            return this->getEngines(locale);
    else if(type == JSON::LOCATIONS)
            return this->getLocations(locale);
    else if(type == JSON::TRAINS)
            return JsonUtil::getTrains(locale);
    else if(type == JSON::TRAIN)
            throw new JsonException(HttpServletResponse::SC_BAD_REQUEST, tr( "UnlistableService %1").arg(type)); // NOI18N
    else
            throw new JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, tr( "ErrorInternal %1").arg(type)); // NOI18N
}

/*public*/ QJsonArray JsonOperationsHttpService::getCars(QLocale locale) {
    QJsonArray root = QJsonArray(); //mapper.createArrayNode();
    //Operations::((CarManager*)InstanceManager::getDefault("Operations::CarManager")).getByIdList().forEach((rs) ->
    foreach (Operations::RollingStock* rs, *((Operations::CarManager*)InstanceManager::getDefault("Operations::CarManager"))->getByIdList()) {

        root.append(JsonUtil::getCar(locale, rs->getId()));
    }//);
    return root;
}

/*public*/ QJsonArray JsonOperationsHttpService::getEngines(QLocale locale) {
    QJsonArray root = QJsonArray();//mapper.createArrayNode();
    //Operations::EngineManager::instance()->getByIdList().forEach((rs) ->
    foreach(Operations::RollingStock* rs, *((Operations::EngineManager*)InstanceManager::getDefault("Operations::EngineManager"))->getByIdList())
    {
        root.append(JsonUtil::getEngine(locale, rs->getId()));
    }//);
    return root;
}

/*public*/ QJsonArray JsonOperationsHttpService::getLocations(QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray(); //mapper.createArrayNode();
    foreach (Operations::Location* location, ((Operations::LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getLocationsByIdList()) {
        root.append(JsonUtil::getLocation(locale, location->getId()));
    }
    return root;
}


/**
 * Sets the properties in the data parameter for the train with the given
 * id.
 *
 * Currently only moves the train to the location given with the key
 * {@value jmri.jmris.json.JSON#LOCATION}. If the move cannot be completed,
 * throw error code 428.
 *
 * @param locale The locale to throw exceptions in.
 * @param id     The id of the train.
 * @param data   Train data to change.
 * @throw jmri.server.json.JsonException if the train cannot move to the
 *                                        location in data.
 */
/*public*/ void JsonOperationsHttpService::setTrain(QLocale locale, QString id, QJsonObject data) throw (JsonException)
{
 Operations::Train* train = ((Operations::TrainManager*)InstanceManager::getDefault("OperationsTrainManager"))->getTrainById(id);
 if (!data.value(JSON::LOCATION).isUndefined())
 {
  QString location = data.value(JSON::LOCATION).toString();
  if (location==(NULL))
  {
   train->terminate();
  }
  else if (!train->move(location))
  {
   throw new JsonException(428, tr( "ErrorTrainMovement %1 %2").arg(id).arg( location));
  }
 }
}
