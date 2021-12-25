#include "jsonblockhttpservice.h"
#include "instancemanager.h"
#include "blockmanager.h"
#include "block.h"
#include "jsonblock.h"
#include "json.h"

/**
 *
 * @author mstevetodd Copyright (C) 2016 (copied from JsonMemoryHttpService)
 * @author Randall Wood
 */
///*public*/ class JsonBlockHttpService extends JsonHttpService {

/*public*/ JsonBlockHttpService::JsonBlockHttpService(ObjectMapper mapper, QObject* parent) : JsonHttpService(mapper, parent){
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonBlockHttpService::doGet(QString /*type*/, QString name, QLocale locale) throw (JsonException) {
    QJsonObject root = QJsonObject(); //mapper.createObjectNode();
    root.insert(JSON::TYPE, JsonBlock::BLOCK);
    QJsonObject data = QJsonObject(); //root.putObject(DATA);
    Block* block = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(name);
    if (block == NULL) {
        throw  JsonException(404, tr(/*locale, */"ErrorObject%1 %2").arg(JsonBlock::BLOCK).arg(name));
    }
    data.insert(JSON::NAME, block->getSystemName());
    data.insert(JSON::USERNAME, block->getUserName());
    data.insert(JSON::COMMENT, block->getComment());
    if (block->getValue() == QVariant()) {
        data.insert(JSON::VALUE, /*"null"*/QJsonValue());
    } else {
        data.insert(JSON::VALUE, block->getValue().toString());
    }
    root.insert(JSON::DATA, data);
    return root;
}

//@Override
/*public*/ QJsonObject JsonBlockHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    Block* block = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(name);
    if (block == NULL) {
        throw  JsonException(404, tr(/*locale, */"ErrorObject %1 %2").arg(JsonBlock::BLOCK).arg(name));
    }
    if (data.value(JSON::USERNAME).isString()) {
        block->setUserName(data.value(JSON::USERNAME).toString());
    }
    if (data.value(JSON::COMMENT).toBool()) {
        block->setComment(data.value(JSON::COMMENT).toString());
    }
    if (!data.value(JSON::VALUE).isUndefined()) {
        if (data.value(JSON::VALUE).isNull()) {
            block->setValue(QVariant());
        } else {
            block->setValue(data.value(JSON::VALUE).toString());
        }
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonObject JsonBlockHttpService::doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    try {
    ((BlockManager*)InstanceManager::getDefault("BlockManager"))->provideBlock(name);
    } catch (Exception* ex) {
        throw  JsonException(500, tr(/*locale,*/ "ErrorCreatingObject %1 %2").arg(JsonBlock::BLOCK).arg(name));
    }
    return this->doPost(type, name, data, locale);
}

//@Override
/*public*/ QJsonValue JsonBlockHttpService::doGetList(QString /*type*/, QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray(); //this->mapper.createArrayNode();
    for (QString name : ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getSystemNameList()) {
        root.append(this->doGet(JsonBlock::BLOCK, name, locale));
    }
    return root;

}
