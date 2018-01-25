#include "jsonmemoryhttpservice.h"
#include "memory.h"
#include "instancemanager.h"
#include "memorymanager.h"
#include "json.h"
#include "jsonmemory.h"
/**
 *
 * @author Randall Wood
 */
// /*public*/ class JsonMemoryHttpService extends JsonNamedBeanHttpService {

/*public*/ JsonMemoryHttpService::JsonMemoryHttpService(ObjectMapper mapper, QObject* parent) : JsonNamedBeanHttpService(mapper, parent)
{
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonMemoryHttpService::doGet(QString type, QString name, QLocale locale) throw (JsonException)
{
 Memory* memory = InstanceManager::memoryManagerInstance()->getMemory(name);
 qDebug() << "memory value: " << memory->getValue();
 QJsonObject data = this->getNamedBean(memory, name, type, locale);
 QJsonObject root = QJsonObject(); ////mapper.createQJsonObject();
 root.insert(JSON::TYPE, JsonMemory::MEMORY);
 if (memory != NULL)
 {
  if (memory->getValue() == QVariant())
  {
   data.insert(JSON::VALUE, /*"null"*/QJsonValue());
  }
  else
  {
   data.insert(JSON::VALUE, memory->getValue().toDateTime().toString(Qt::ISODate));
  }
 }
 root.insert(JSON::DATA, data);

 return root;
}

//@Override
/*public*/ QJsonObject JsonMemoryHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    Memory* memory = InstanceManager::memoryManagerInstance()->getMemory(name);
    if (memory == NULL) {
        throw  JsonException(404, tr(/*locale, */"Unable to access %1 %2.").arg(JSON::MEMORY).arg(name));
    }
    if (data.value(JSON::USERNAME).isString()) {
        memory->setUserName(data.value(JSON::USERNAME).toString());
    }
    if (data.value(JSON::COMMENT).isString()) {
        memory->setComment(data.value(JSON::COMMENT).toString());
    }
    if (!data.value(JSON::VALUE).isUndefined()) {
        if (data.value(JSON::VALUE).isNull()) {
            memory->setValue(QVariant());
        } else {
            memory->setValue(data.value(JSON::VALUE).toString());
        }
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonObject JsonMemoryHttpService::doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    try {
        InstanceManager::memoryManagerInstance()->provideMemory(name);
    } catch (Exception ex) {
        throw  JsonException(500, tr(/*locale,*/ "ErrorCreatingObject %1 %2").arg(JSON::MEMORY).arg( name));
    }
    return this->doPost(type, name, data, locale);
}

//@Override
/*public*/ QJsonValue JsonMemoryHttpService::doGetList(QString type, QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray(); //this->mapper.createQJsonArray();
    foreach (QString name, InstanceManager::memoryManagerInstance()->getSystemNameList()) {
        root.append(this->doGet(JSON::MEMORY, name, locale));
    }
    return root;

}
