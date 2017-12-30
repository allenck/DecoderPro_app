#include "jsonqt.h"


/* Collection of wrappers mapping Json functions to Qt

/**
 * @brief JsonNode::path
 * @param s key
 * @return JsonValue
 */
QMapIterator<QString, QVariant> JsonNode::fields()
{
 QVariantMap map = QJsonValue::toObject().toVariantMap();
 QMapIterator<QString, QVariant> iter(map);
 QMap<QString, QVariant> jMap = QMap<QString, QVariant>();
 while (iter.hasNext())
 {
   iter.next();
   jMap.insert(iter.key(), iter.value());
 }
  return QMapIterator<QString, QVariant>(jMap);
}
QString JsonNode::toString()
{
 QJsonDocument doc = QJsonDocument(QJsonValue::toObject());
 return QString(doc.toJson());
}


QJsonObject ObjectMapper::createObjectNode()
{
 return QJsonObject();
}
