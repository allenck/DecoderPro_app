#ifndef FILTEROUTPUTSTREAM_H
#define FILTEROUTPUTSTREAM_H
#include <QObject>
#include "qdatastream.h"

class FilterOutputStream : public QDataStream
{
public:
 FilterOutputStream(QObject* parent = nullptr);
 /*public*/ FilterOutputStream(QDataStream* out, QObject* parent = nullptr);

protected:
 /**
  * The underlying output stream to be filtered.
  */
 /*protected*/ QDataStream* out;

};

#endif // FILTEROUTPUTSTREAM_H
