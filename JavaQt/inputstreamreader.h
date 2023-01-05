#ifndef INPUTSTREAMREADER_H
#define INPUTSTREAMREADER_H
#include "reader.h"

class UnsupportedEncodingException : public Exception
{
public:
 UnsupportedEncodingException(QString msg) : Exception(msg) {}
};
class StreamDecoder;
class InputStreamReader : public Reader
{
public:
 /*public*/ InputStreamReader(QDataStream* in, QObject* parent = nullptr);
 /*public*/ InputStreamReader(QDataStream* in, QString charsetName, QObject* parent = nullptr) /*throw (UnsupportedEncodingException)*/;
 QString readLine();


private:
 /*private*/ /*final*/ StreamDecoder* sd;

};

#endif // INPUTSTREAMREADER_H
