#include "jsonlighthttpservice.h"
#include "light.h"
#include "proxylightmanager.h"
#include "json.h"

/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonLightHttpService extends JsonNamedBeanHttpService {

/*public*/ JsonLightHttpService::JsonLightHttpService(ObjectMapper mapper, QObject* parent) : JsonNamedBeanHttpService(mapper, parent)
{
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonLightHttpService::doGet(QString type, QString name, QLocale locale) throw (JsonException) {
    QJsonObject root = QJsonObject(); //mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::LIGHT);
    Light* light = ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->getLight(name);
    QJsonObject data = this->getNamedBean(light, name, type, locale);
    root.insert(JSON::DATA, data);
    if (light != NULL) {
        switch (light->getState()) {
            case Light::ON:
                data.insert(JSON::STATE, JSON::ON);
                break;
            case Light::OFF:
                data.insert(JSON::STATE, JSON::OFF);
                break;
            case Light::INCONSISTENT:
                data.insert(JSON::STATE, JSON::INCONSISTENT);
                break;
            case Light::UNKNOWN:
            default:
                data.insert(JSON::STATE, JSON::UNKNOWN);
                break;
        }
    }
    return root;
}

//@Override
/*public*/ QJsonObject JsonLightHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    Light* light = ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->getLight(name);
    if (light == NULL) {
        throw  JsonException(404, tr(/*locale, */"Unable to access %1 %2.").arg(JSON::LIGHT).arg( name));
    }
    if (data.value(JSON::USERNAME).isString()) {
        light->setUserName(data.value(JSON::USERNAME).toString());
    }
    if (data.value(JSON::COMMENT).isString()) {
        light->setComment(data.value(JSON::COMMENT).toString());
    }
    int state = data.value(JSON::STATE).toInt(JSON::UNKNOWN);
    if(state== JSON::ON)
    {
            light->setState(Light::ON);
    }
    else if( state == JSON::OFF)
    {
            light->setState(Light::OFF);
    }
    else if( state ==JSON::UNKNOWN)
    {
            // leave state alone in this case
    }
    else
    {
            throw JsonException(400, tr(/*locale,*/ "Attempting to set object type %1 to unknown state &2.").arg(JSON::LIGHT).arg(state));
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonObject JsonLightHttpService::doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    try {
        ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->provideLight(name);
    } catch (Exception ex) {
        throw JsonException(500, tr(/*locale, */"ErrorCreatingObject %1 %2").arg(JSON::LIGHT).arg(name));
    }
    return this->doPost(type, name, data, locale);
}

//@Override
/*public*/ QJsonValue JsonLightHttpService::doGetList(QString type, QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray(); //this->mapper.createArrayNode();
    foreach (QString name, ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->getSystemNameList()) {
        root.append(this->doGet(JSON::LIGHT, name, locale));
    }
    return root;

}
