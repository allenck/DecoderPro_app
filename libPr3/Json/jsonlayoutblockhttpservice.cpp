#include "jsonlayoutblockhttpservice.h"
#include "jsonlayoutblock.h"
#include "json.h"
#include "layoutblock.h"
#include "layoutblockmanager.h"
#include "instancemanager.h"
#include "colorutil.h"
/**
 *
 * @author mstevetodd Copyright (C) 2016 (copied from JsonMemoryHttpService)
 * @author Randall Wood
 */
///*public*/ class JsonLayoutBlockHttpService extends JsonHttpService {

/*public*/ JsonLayoutBlockHttpService::JsonLayoutBlockHttpService(ObjectMapper mapper, QObject* parent) : JsonHttpService(mapper, parent){
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonLayoutBlockHttpService::doGet(QString type, QString name, QLocale locale) throw (JsonException) {
    QJsonObject root = QJsonObject(); //mapper.createQJsonObject();
    root.insert(JSON::TYPE, JsonLayoutBlock::LAYOUTBLOCK);
    QJsonObject data =  QJsonObject();//root.putObject(JSON::DATA);
    LayoutBlock* layoutBlock =((LayoutBlockManager*) InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(name);
    if (layoutBlock == NULL) {
        throw  JsonException(404, tr(/*locale,*/ "Unable to access %1 %2.").arg(JsonLayoutBlock::LAYOUTBLOCK).arg(name));
    }
    data.insert(JSON::NAME, layoutBlock->getSystemName());
    data.insert(JSON::USERNAME, layoutBlock->getUserName());
    data.insert(JSON::COMMENT, layoutBlock->getComment());
    data.insert(JSON::STATE, layoutBlock->getState());
    data.insert(JsonLayoutBlock::USE_EXTRA_COLOR, layoutBlock->getUseExtraColor());
    data.insert(JsonLayoutBlock::BLOCK_COLOR, ColorUtil::colorToColorName(layoutBlock->getBlockColor()));
    data.insert(JsonLayoutBlock::TRACK_COLOR, ColorUtil::colorToColorName(layoutBlock->getBlockTrackColor()));
    data.insert(JsonLayoutBlock::OCCUPIED_COLOR, ColorUtil::colorToColorName(layoutBlock->getBlockOccupiedColor()));
    data.insert(JsonLayoutBlock::EXTRA_COLOR, ColorUtil::colorToColorName(layoutBlock->getBlockExtraColor()));
    data.insert(JsonLayoutBlock::OCCUPANCY_SENSOR, layoutBlock->getOccupancySensorName());
    data.insert(JsonLayoutBlock::OCCUPIED_SENSE, layoutBlock->getOccupiedSense());
    root.insert(JSON::DATA, data);
    return root;
}

//@Override
/*public*/ QJsonObject JsonLayoutBlockHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    LayoutBlock* layoutBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(name);
    if (layoutBlock == NULL) {
        throw  JsonException(404, tr(/*locale,*/ "Unable to access %1 %2.").arg( JsonLayoutBlock::LAYOUTBLOCK).arg(name));
    }
    if (data.value(JSON::USERNAME).isString()) {
        layoutBlock->setUserName(data.value(JSON::USERNAME).toString());
    }
    if (data.value(JSON::COMMENT).isString()) {
        layoutBlock->setComment(data.value(JSON::COMMENT).toString());
    }
    //layoutBlock->state is a bogus construct, so don't expect valid results from this
    if (!data.value(JSON::STATE).isUndefined()) {
        layoutBlock->setState(data.value(JSON::STATE).toInt());
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonValue JsonLayoutBlockHttpService::doGetList(QString /*type*/, QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray(); //this.mapper.createArrayNode();
    foreach (QString name, ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getSystemNameList()) {
        root.append(this->doGet(JsonLayoutBlock::LAYOUTBLOCK, name, locale));
    }
    return root;

}
