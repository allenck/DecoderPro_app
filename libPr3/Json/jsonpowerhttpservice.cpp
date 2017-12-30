#include "jsonpowerhttpservice.h"
#include "loggerfactory.h"
#include "json.h"
#include "instancemanager.h"
#include "powermanager.h"

/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonPowerHttpService extends JsonHttpService {

/*private*/ /*static*/ /*final*/ Logger* JsonPowerHttpService::log = LoggerFactory::getLogger("JsonPowerHttpService");

/*public*/ JsonPowerHttpService::JsonPowerHttpService(ObjectMapper mapper, QObject* parent)
: JsonHttpService(mapper, parent){
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonPowerHttpService::doGet(QString /*type*/, QString /*name*/, QLocale /*locale*/) throw (JsonException) {
    QJsonObject root = QJsonObject();//mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::POWER);
    //QJsonObject data = root.putObject(DATA);
    QJsonObject data = QJsonObject();
    try {
        switch (((PowerManager*)InstanceManager::getDefault("PowerManager"))->getPower()) {
            case PowerManager::OFF:
                data.insert(JSON::STATE, JSON::OFF);
                break;
            case PowerManager::ON:
                data.insert(JSON::STATE, JSON::ON);
                break;
            default:
                data.insert(JSON::STATE, JSON::UNKNOWN);
                break;
        }
    } catch (JmriException e) {
        log->error("Unable to get Power state.", e.getMessage());
        throw  JsonException(500, tr("Error accessing power status."));
    } catch (NullPointerException e) {
        // No PowerManager is defined; just report it as UNKNOWN
        data.insert(JSON::STATE, JSON::UNKNOWN);
    }
    root.insert(JSON::DATA, data);

    return root;
}

//@Override
/*public*/ QJsonObject JsonPowerHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    int state = data.value(JSON::STATE).toInt(JSON::UNKNOWN);
    try {
        switch (state) {
            case JSON::OFF:
                ((PowerManager*)InstanceManager::getDefault("PowerManager"))->setPower(PowerManager::OFF);
                break;
            case JSON::ON:
                ((PowerManager*)InstanceManager::getDefault("PowerManager"))->setPower(PowerManager::ON);
                break;
            case JSON::UNKNOWN:
                // quietly ignore
                break;
            default:
                throw  JsonException(HttpServletResponse::SC_BAD_REQUEST, tr("Attempting to set object type %1 to unknown state %2.").arg(JSON::POWER).arg(state));
        }
    } catch (JmriException ex) {
        throw  JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, ex.getMessage());
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonValue JsonPowerHttpService::doGetList(QString /*type*/, QLocale /*locale*/) throw (JsonException) {
    throw  JsonException(HttpServletResponse::SC_METHOD_NOT_ALLOWED, tr("%1 cannot be listed.").arg(JSON::POWER));
}
