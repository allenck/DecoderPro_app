#include "jsonreporterhttpservice.h"
#include "json.h"
#include "jsonreporter.h"
#include "reportermanager.h"
#include "instancemanager.h"
#include "reportervariant.h"
/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonReporterHttpService extends JsonHttpService {

/*public*/ JsonReporterHttpService::JsonReporterHttpService(ObjectMapper mapper, QObject* parent)
: JsonHttpService(mapper, parent)
{
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonReporterHttpService::doGet(QString /*type*/, QString name, QLocale /*locale*/) throw (JsonException) {
    QJsonObject root = QJsonObject(); //mapper.createObjectNode();
    root.insert(JSON::TYPE, JsonReporter::REPORTER);
    QJsonObject data = QJsonObject(); //root.putObject(JSON::DATA);
    Reporter* reporter = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter(name);
    if (reporter == NULL) {
        throw new JsonException(404, tr(/*locale,*/ "Unable to access %1 %2.").arg(JsonReporter::REPORTER).arg(name));
    }
    data.insert(JSON::NAME, reporter->getSystemName());
    data.insert(JSON::USERNAME, reporter->getUserName());
    data.insert(JSON::STATE, reporter->getState());
    data.insert(JSON::COMMENT, reporter->getComment());
    if (reporter->getCurrentReport() != QVariant()) {
        data.insert(JSON::REPORT, reporter->getCurrentReport().toString());
    } else {
        data.insert(JSON::REPORT, /*"null"*/QJsonValue());
    }
    if (reporter->getLastReport() != QVariant()) {
        data.insert(JsonReporter::LAST_REPORT, reporter->getLastReport().toString());
    } else {
        data.insert(JsonReporter::LAST_REPORT, /*"null"*/QJsonValue());
    }
    root.insert(JSON::DATA, data);
    return root;
}

//@Override
/*public*/ QJsonObject JsonReporterHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    Reporter* reporter = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getBySystemName(name);
    if (reporter == NULL) {
        throw new JsonException(404, tr(/*locale,*/ "Unable to access %1 %2.").arg(JsonReporter::REPORTER).arg(name));
    }
    if (data.value(JSON::USERNAME).isString()) {
        reporter->setUserName(data.value(JSON::USERNAME).toString());
    }
    if (data.value(JSON::COMMENT).isString()) {
        reporter->setComment(data.value(JSON::COMMENT).toString());
    }
    if (!data.value(JSON::REPORT).isUndefined()) {
        if (data.value(JSON::REPORT).isNull()) {
            reporter->setReport(QVariant());
        } else {
            reporter->setReport(data.value(JSON::REPORT).toString());
        }
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonObject JsonReporterHttpService::doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    try {
        ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->provideReporter(name);
    } catch (Exception ex) {
        throw new JsonException(500, tr(/*locale,*/ "ErrorCreatingObject").arg(JsonReporter::REPORTER).arg(name));
    }
    return this->doPost(type, name, data, locale);
}

//@Override
/*public*/ QJsonValue JsonReporterHttpService::doGetList(QString /*type*/, QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray(); //this.mapper.createArrayNode();
    foreach (QString name, ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getSystemNameList()) {
        root.append(this->doGet(JsonReporter::REPORTER, name, locale));
    }
    return root;
}
