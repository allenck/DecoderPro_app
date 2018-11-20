#ifndef JSONQT_H
#define JSONQT_H
#include <QJsonDocument>
#include <QJsonObject>
#include <iterator>
#include "deviceserver.h"
#include <QJsonArray>

class JsonValue : QJsonValue
{
public:
 JsonValue(QString) {}
  bool isMissingNode(){  return QJsonValue::isNull() || QJsonValue::isUndefined(); }

 int asInt() {return QJsonValue::toInt();}
 //QString asText() {return QJsonValue::toString();}
 bool asBoolean() {return QJsonValue::toBool();}
 bool asBoolean(bool bDefault) {return QJsonValue::toBool(bDefault);}
 bool asDouble() {return QJsonValue::toDouble();}
 bool isTextual() {return QJsonValue::isString();}
 bool isBoolean() {return QJsonValue::isBool();}
 int asInt(int i) {return i;}
 bool isValueNode() {return QJsonValue::isObject();}
};

class JsonNode : public QJsonValue
{
public:
 JsonNode() : QJsonValue() {}
 JsonNode(QJsonArray) {}
 JsonValue path(QString s) {return JsonValue(QJsonValue::toObject().value(s).toString());}
 QMapIterator<QString, QVariant> fields();
 QString toString();
 bool isTextual() {return QJsonValue::isString();}
 bool isBoolean() {return QJsonValue::isBool();}
 int asInt() {return QJsonValue::toInt();}
 int asInt(int i) {return i;}

};



class ObjectNode :  public QJsonObject
{
public:
 ObjectNode put(const QString &key, const QJsonValue( value)) {insert(key, (value)); return *this; }
 ObjectNode putNull(QString &key) { insert(key, QJsonValue()); return *this;}
};

class ObjectMapper
{
 QJsonObject obj;
public:
 ObjectMapper() {}
 ObjectMapper(QJsonObject obj) { this->obj = obj;}
 //static ObjectMapper fromRawData(const char *data, int size, DataValidation validation);
 QJsonObject createObjectNode();
};

#endif // JSONQT_H
