#ifndef STRINGWRITER_H
#define STRINGWRITER_H

#include "writer.h"
#include <QObject>
#include <QByteArray>

class StringWriter : public QByteArray
{
  //Q_OBJECT

 public:
  StringWriter();
  /*public*/ QString toString();
  /*public*/ void flush() {}
 private:

};

#endif // STRINGWRITER_H
