#include "jsonmemoryservicefactory.h"
#include "jsonmemory.h"
#include "jsonmemoryhttpservice.h"
#include "jsonmemorysocketservice.h"

JsonMemoryServiceFactory::JsonMemoryServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{
}
/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonMemoryServiceFactory implements JsonServiceFactory {


//@Override
/*public*/ QStringList JsonMemoryServiceFactory::getTypes() {
    //return new String[]{MEMORY, MEMORIES};
 QStringList l = QStringList();
 l << JsonMemory::MEMORY << JsonMemory::MEMORIES;
 return l;
}

//@Override
/*public*/ JsonSocketService* JsonMemoryServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonMemorySocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonMemoryServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonMemoryHttpService(mapper);
}
