#ifndef JSONEXCPTION_H
#define JSONEXCPTION_H
#include "exceptions.h"
#include "jsonqt.h"

class ObjectMapper;
class JsonException : public Exception
{
public:
 JsonException();
 /*public*/ static /*final*/ QString ERROR;// = "error"; // NOI18N
 /**
  * {@value #CODE}
  */
 /*public*/ static /*final*/ QString CODE;// = "code"; // NOI18N
 /**
  * {@value #MESSAGE}
  */
 /*public*/ static /*final*/ QString MESSAGE;// = "message"; // NOI18N
 /*public*/ JsonException(int i, QString s);
 /*public*/ JsonException(int i);
 /*public*/ int getCode();
 /*public*/ QJsonObject getJsonMessage();

private:
 /*private*/ static /*final*/ ObjectMapper MAPPER;// = new ObjectMapper();
 /*private*/ int code;// = 500;


};
class JsonProcessingException : public Exception
{
public:
 JsonProcessingException(QString s = "");
 ~JsonProcessingException() throw() {}

};

#endif // JSONEXCPTION_H
