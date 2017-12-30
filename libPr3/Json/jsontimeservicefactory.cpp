#include "jsontimeservicefactory.h"

JsonTimeServiceFactory::JsonTimeServiceFactory(QObject* parent) :JsonServiceFactory(parent)
{

}
#if 0/**
 *
 * @author Randall Wood
 */
public class JsonTimeServiceFactory implements JsonServiceFactory {

    public final static String TIME = "time";

    @Override
    public String[] getTypes() {
        return new String[]{TIME};
    }

    @Override
    public JsonTimeSocketService getSocketService(JsonConnection connection) {
        return new JsonTimeSocketService(connection);
    }

    @Override
    public JsonTimeHttpService getHttpService(ObjectMapper mapper) {
        return new JsonTimeHttpService(mapper);
    }
#endif
