#include "jsonblockservicefactory.h"
#include "jsonblockhttpservice.h"
#include "jsonblock.h"
#include "jsonblocksocketservice.h"

JsonBlockServiceFactory::JsonBlockServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 *
 * @author mstevetodd Copyright (C) 2016 (copied from JsonMemoryServiceFactory)
 * @author Randall Wood
 */
///*public*/ class JsonBlockServiceFactory implements JsonServiceFactory {


//@Override
/*public*/ QStringList JsonBlockServiceFactory::getTypes()
{
    //return new String[]{BLOCK, BLOCKS};
 QStringList l = QStringList();
 l << JsonBlock::BLOCK << JsonBlock::BLOCKS;
 return l;
}

//@Override
/*public*/ JsonSocketService* JsonBlockServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonBlockSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonBlockServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonBlockHttpService(mapper);
}
