#include "jsontimehttpservice.h"
#include "json.h"
#include <QDateTime>
#include "instancemanager.h"
#include "timebase.h"

/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonTimeHttpService extends JsonHttpService {

/*public*/ JsonTimeHttpService::JsonTimeHttpService(ObjectMapper mapper, QObject* parent) : JsonHttpService(mapper, parent) {
    //super(mapper);
}
#if 1
//@Override
/*public*/ QJsonValue JsonTimeHttpService::doGet(QString type, QString name, QLocale locale) throw (JsonException) {
    QJsonObject root = QJsonObject(); //this.mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::TIME);
    QJsonObject data = QJsonObject(); //root.putObject(DATA);
    data.insert(JSON::TIME, ((Timebase*)InstanceManager::getDefault("Timebase"))->getTime().toString(Qt::ISODate));
    data.insert(JSON::RATE, ((Timebase*)InstanceManager::getDefault("Timebase"))->getRate());
    data.insert(JSON::STATE, ((Timebase*)InstanceManager::getDefault("Timebase"))->getRun() ? JSON::ON : JSON::OFF);
    root.insert(JSON::DATA, data);
    return QJsonValue(root);
}

//@Override
/*public*/ QJsonObject JsonTimeHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    try {
        if (data.value(JSON::TIME).isString()) {
            ((Timebase*)InstanceManager::getDefault("Timebase"))->setTime(QDateTime::fromString(data.value(JSON::TIME).toString(),Qt::ISODate));
        }
        if (data.value(JSON::RATE).isDouble()) {
            ((Timebase*)InstanceManager::getDefault("Timebase"))->setRate(data.value(JSON::RATE).toDouble());
        }
        if (data.value(JSON::STATE).isDouble()) {
            ((Timebase*)InstanceManager::getDefault("Timebase"))->setRun(data.value(JSON::STATE).toInt() == JSON::ON);
        }
    } catch (ParseException ex) {
        throw JsonException(400, tr(/*locale,*/ "ErrorTimeFormat"));
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonValue JsonTimeHttpService::doGetList(QString type, QLocale locale) throw (JsonException) {
    return this->doGet(type, "", locale);
}
#endif
