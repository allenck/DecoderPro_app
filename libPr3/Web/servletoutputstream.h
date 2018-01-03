#ifndef SERVLETOUTPUTSTREAM_H
#define SERVLETOUTPUTSTREAM_H
#include <QTextStream>
#include "exceptions.h"

class CharConversionException : Exception
{
public:
 CharConversionException(QString msg) :Exception(msg) {}
};

class ServletOutputStream : public QTextStream
{
public:
 /*public*/ void print(QString s) throw (IOException);

protected:
 ServletOutputStream();
};

#endif // SERVLETOUTPUTSTREAM_H
