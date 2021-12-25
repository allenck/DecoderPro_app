#ifndef JSONNAMEDBEANHTTPSERVICE_H
#define JSONNAMEDBEANHTTPSERVICE_H
#include "jsonhttpservice.h"
#include "namedbean.h"

class JsonNamedBeanHttpService : public JsonHttpService
{
public:
 /*public*/ JsonNamedBeanHttpService(ObjectMapper mapper, QObject* parent = 0);

protected:
 /*protected*/ QJsonObject getNamedBean(NamedBean* bean, /*@Nonnull*/ QString name, /*@Nonnull*/ QString type, /*@Nonnull*/ QLocale locale) /*throw (JsonException)*/;
 /*protected*/ void postNamedBean(NamedBean* bean, /*@Nonnull*/ QJsonObject data, /*@Nonnull*/ QString name, /*@Nonnull*/ QString type, /*@Nonnull*/ QLocale locale) /*throw (JsonException)*/;

};

#endif // JSONNAMEDBEANHTTPSERVICE_H
