#include "jsonnamedbeanhttpservice.h"
#include "json.h"
#include <QJsonArray>
#include <QObject>
/**
 * Abstract implementation of JsonHttpService with specific support for
 * {@link jmri.NamedBean} objects.
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ abstract class JsonNamedBeanHttpService extends JsonHttpService {

/*public*/ JsonNamedBeanHttpService::JsonNamedBeanHttpService(ObjectMapper mapper, QObject* parent) : JsonHttpService(mapper, parent) {
    //super(mapper);
}

/**
 * Create the JsonNode for a {@link jmri.NamedBean} object.
 *
 * @param bean   the bean to create the node for
 * @param name   the name of the bean; used only if the bean is null
 * @param type   the JSON type of the bean
 * @param locale the locale used for any error messages
 * @return a JSON node
 * @throws JsonException if the bean is null
 */
//@Nonnull
/*protected*/ QJsonObject JsonNamedBeanHttpService::getNamedBean(NamedBean* bean, /*@Nonnull*/ QString name, /*@Nonnull*/ QString type, /*@Nonnull*/ QLocale /*locale*/) throw (JsonException)
{
 if (bean == NULL)
 {
     throw JsonException(404, tr("Unable to access %1 %2.").arg(type).arg(name));
 }

 QJsonObject root = QJsonObject();//mapper.createObjectNode();
 root.insert(JSON::TYPE, type);
 //ObjectNode data = root.putObject(JSON::DATA);
 QJsonObject data = QJsonObject();
 data.insert(JSON::NAME, bean->getSystemName());
 data.insert(JSON::USERNAME, bean->getUserName());
 data.insert(JSON::COMMENT, bean->getComment());
 root.insert(JSON::DATA, data);
 //QJsonArray properties = root.putArray(JSON::PROPERTIES);
 QJsonArray properties = QJsonArray();
 root.insert(JSON::PROPERTIES, properties);
 //bean.getPropertyKeys().stream().forEach((key) ->
 foreach(QString key, bean->getPropertyKeys())
 {
  QVariant value = bean->getProperty(key);
  if (value != QVariant())
  {
   QJsonObject obj;
//         {
//          {key, value.toString()}
//         };
   obj.insert(key,value.toString());
      properties.append(obj);
  } else {
   QJsonObject obj;
//         {
//          {key, "null"}
//         };
     obj.insert(key, "null");
      properties.append(obj);
  }
 }//);
 return data;
}

/**
 * Handle the common elements of a NamedBean that can be changed in an POST
 * message.
 * <p>
 * <strong>Note:</strong> the system name of a NamedBean cannot be changed
 * using this method.
 *
 * @param bean   the bean to modify
 * @param data   the JsonNode containing the JSON representation of bean
 * @param name   the name of the bean; used only if the bean is null
 * @param type   the JSON type of the bean
 * @param locale the locale used for any error messages
 * @throws JsonException if the bean is null
 */
/*protected*/ void JsonNamedBeanHttpService::postNamedBean(NamedBean* bean, /*@Nonnull*/ QJsonObject data, /*@Nonnull*/ QString name, /*@Nonnull*/ QString type, /*@Nonnull*/ QLocale /*locale*/) throw (JsonException) {
    if (bean == NULL) {
        throw JsonException(404, tr("Unable to access %1 {%2.").arg(type).arg(name));
    }
    if (data.value(JSON::USERNAME).isString()) {
        bean->setUserName(data.value(JSON::USERNAME).toString());
    }
    if (data.value(JSON::COMMENT).isString()) {
        bean->setComment(data.value(JSON::COMMENT).toString());
    }
}
