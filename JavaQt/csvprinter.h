#ifndef CSVPRINTER_H
#define CSVPRINTER_H

#include <QObject>
#include <QVariant>
#include "csvformat.h"
#include <QTextStream>

class CSVPrinter : public QObject
{
  Q_OBJECT
 public:
  explicit CSVPrinter(QTextStream* stream, CSVFormat* format, QObject *parent = nullptr);
  /*public*/ void printRecord(/*final*/ /*Iterable<?>*/QVariantList values) /*throws IOException*/;
  /*public*/ void print(/*final*/ QVariant value) /*throws IOException*/;
  /*public*/ void println() /*throws IOException*/;
  /*public*/ void flush() /*throws IOException*/;
  /*public*/ void close() /*throws IOException*/;
  /*public*/ void close(/*final*/ bool flush) /*throws IOException*/;

 signals:

 private:
  /** True if we just began a new record. */
  bool newRecord = false;

  /*private*/ /*final*/ CSVFormat* format;
  QTextStream* appendable;
};

#endif // CSVPRINTER_H
