#include "jsonlayoutblockservicefactory.h"
#include "jsonlayoutblock.h"
#include "jsonlayoutblockhttpservice.h"
#include "jsonlayoutblockservicefactory.h"
#include "jsonlayoutblocksocketservice.h"

JsonLayoutBlockServiceFactory::JsonLayoutBlockServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 *
 * @author mstevetodd Copyright (C) 2016 (copied from JsonMemoryServiceFactory)
 * @author Randall Wood
 */
///*public*/ class JsonLayoutBlockServiceFactory implements JsonServiceFactory {



//@Override
/*public*/ QStringList JsonLayoutBlockServiceFactory::getTypes() {
    //return new String[]{LAYOUTBLOCK, LAYOUTBLOCKS};
QStringList l = QStringList() << JsonLayoutBlock::LAYOUTBLOCK << JsonLayoutBlock::LAYOUTBLOCKS;
return l;
}

//@Override
/*public*/ JsonSocketService* JsonLayoutBlockServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonLayoutBlockSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonLayoutBlockServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonLayoutBlockHttpService(mapper);
}
