#include "jsonsensorhttpservice.h"
#include "sensor.h"
#include "proxysensormanager.h"
#include "instancemanager.h"
#include "jsonsensor.h"
#include "json.h"
#include "httpservletresponse.h"
#include "jsonqt.h"

/**
 * JSON HTTP Service for {@link jmri.Sensor}s.
 *
 * @author Randall Wood
 */
///*public*/ class JsonSensorHttpService extends JsonNamedBeanHttpService {

/*public*/ JsonSensorHttpService::JsonSensorHttpService(ObjectMapper mapper, QObject* parent) : JsonNamedBeanHttpService(mapper, parent){
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonSensorHttpService::doGet(QString type, QString name, QLocale locale) throw (JsonException)
{
 //ObjectNode root = mapper.createObjectNode();
 QJsonObject root = QJsonObject();
 root.insert(JSON::TYPE, JSON::SENSOR);
 Sensor* sensor = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor(name);
 QJsonObject data = this->getNamedBean(sensor, name, type, locale); // throws JsonException if sensor == NULL
 if (sensor != NULL)
 {
  switch (sensor->getKnownState()) {
      case Sensor::ACTIVE:
          data.insert(JSON::STATE, JSON::ACTIVE);
          break;
      case Sensor::INACTIVE:
          data.insert(JSON::STATE, JSON::INACTIVE);
          break;
      case Sensor::INCONSISTENT:
          data.insert(JSON::STATE, JSON::INCONSISTENT);
          break;
      case Sensor::UNKNOWN:
          data.insert(JSON::STATE, JSON::UNKNOWN);
          break;
      default:
          throw  JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, tr("Internal %1 handling error. See JMRI logs for information.").arg(type)); // NOI18N
  }
  root.insert(JSON::DATA, data);
 }
 return QJsonValue(root);
}

//@Override
/*public*/ QJsonObject JsonSensorHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
 Sensor* sensor = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor(name);
    if (sensor == NULL) {
        throw  JsonException(404, tr("Unable to access %1 %2.").arg(JSON::SENSOR, name));
    }
    if (data.value(JSON::USERNAME).isString()) {
        sensor->setUserName(data.value(JSON::USERNAME).toString());
    }
    if (data.value(JSON::INVERTED).isBool()) {
        sensor->setInverted(data.value(JSON::INVERTED).toBool());
    }
    if (data.value(JSON::COMMENT).isString()) {
        sensor->setComment(data.value(JSON::COMMENT).toString());
    }
    int state = data.value(JSON::STATE).toInt(JSON::UNKNOWN);
    try {
        //switch (state) {
            if(state == JSON::ACTIVE)
            {
                sensor->setKnownState(Sensor::ACTIVE);
            }
            else if(state == JSON::INACTIVE)
            {
                sensor->setKnownState(Sensor::INACTIVE);
            }
            else if(state == JSON::INCONSISTENT || state == JSON::UNKNOWN)
            {
                // silently ignore
            }
            else
                throw  JsonException(400, tr("Attempting to set object type %1 to unknown state %2.").arg(JSON::SENSOR).arg(state));
//        }
    } catch (JmriException* ex) {
        throw new JsonException(500, ex->getMessage());
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonObject JsonSensorHttpService::doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    try {
        ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor(name);
    } catch (Exception* ex) {
        throw new JsonException(500, tr("ErrorCreatingObject %1 %2").arg(JSON::SENSOR).arg(name));
    }
    return this->doPost(type, name, data, locale);
}

//@Override
/*public*/ QJsonValue JsonSensorHttpService::doGetList(QString /*type*/, QLocale locale) throw (JsonException) {
    //ArrayNode root = this.mapper.createArrayNode();
 QJsonArray root = QJsonArray();
    foreach (QString name, ((ProxySensorManager*) InstanceManager::getDefault("SensorManager"))->getSystemNameList()) {
        root.append(this->doGet(JSON::SENSOR, name, locale));
    }
    return QJsonValue(root);
 }
