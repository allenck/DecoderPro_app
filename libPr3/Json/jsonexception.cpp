#include "jsonexception.h"
#include "jsonqt.h"
#include "json.h"

JsonException::JsonException()
{
 code = 500;
}
/**
 * Throw an exception, but include an HTTP error code.
 *
 * @author Randall Wood Copyright (C) 2015, 2016
 */
//@SuppressWarnings("serial")
///*public*/ class JsonException extends Exception {

/**
 * {@value #ERROR}
 */
/*public*/ /*static*/ /*final*/ QString JsonException::ERROR = "error"; // NOI18N
/**
 * {@value #CODE}
 */
/*public*/ /*static*/ /*final*/ QString JsonException::CODE = "code"; // NOI18N
/**
 * {@value #MESSAGE}
 */
/*public*/ /*static*/ /*final*/ QString JsonException::MESSAGE = "message"; // NOI18N

/*private*/ /*static*/ /*final*/ ObjectMapper JsonException::MAPPER =  ObjectMapper();

/*public*/ JsonException::JsonException(int i, QString s) : Exception(s) {
    //super(s, t);
    code = 500;
    this->code = i;
}

/*public*/ JsonException::JsonException(int i) : Exception() {
    //super(t);
    code = 500;
    this->code = i;
}


/**
 * @return the code
 */
/*public*/ int JsonException::getCode() {
    return this->code;
}

/*public*/ QJsonObject JsonException::getJsonMessage() {
 #if 0
    ObjectNode root = MAPPER.createObjectNode();
    root.put(JSON::TYPE, ERROR);

    ObjectNode data = root.putObject(JSON::DATA);
    data.put(CODE, this->getCode());
    data.put(MESSAGE, this->getMessage());
    return root;
#else
 QJsonObject root =  QJsonObject();
 root.insert(JSON::TYPE, ERROR);
 QJsonObject data = QJsonObject();
 data.insert(CODE, this->getCode());
 data.insert(MESSAGE, this->getMessage());
 root.insert(JSON::DATA, data);
 return root;
#endif
}
JsonProcessingException::JsonProcessingException(QString s) {msg = s;}
