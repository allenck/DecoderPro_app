#ifndef STRINGWRITER_H
#define STRINGWRITER_H

#include "writer.h"
#include <QObject>

class StringWriter : public QObject, public Writer
{
  Q_OBJECT

 public:
  StringWriter(QObject* parent=nullptr);
};

#endif // STRINGWRITER_H
