#ifndef READER_H
#define READER_H

#include <QObject>
#include "exceptions.h"
#include "charbuffer.h"

class Reader : public QObject
{
 Q_OBJECT
public:
 /*public*/ int read(CharBuffer* target) /*throw (IOException)*/;
 /*public*/ int read() /*throw (IOException)*/;
 /*public*/ int read(QByteArray cbuf) /*throw (IOException)*/;
 virtual/*abstract*/ /*public*/ int read(QByteArray cbuf, int off, int len) /*throw (IOException)*/;
 /*public*/ long skip(long n) /*throw (IOException)*/;
 /*public*/ bool ready() /*throw (IOException)*/;
 /*public*/ bool markSupported();
 /*public*/ void mark(int readAheadLimit) /*throw (IOException)*/;
 /*public*/ void reset() /*throw (IOException)*/;
 virtual /*abstract*/ /*public*/ void close() /*throw (IOException)*/;

signals:

public slots:

private:
 /**
  * The object used to synchronize operations on this stream.  For
  * efficiency, a character-stream object may use an object other than
  * itself to protect critical sections.  A subclass should therefore use
  * the object in this field rather than <tt>this</tt> or a synchronized
  * method.
  */
 QObject* lock;
 /*private*/ static /*final*/ int maxSkipBufferSize;// = 8192;
 /*private*/ QByteArray skipBuffer;// = NULL;

protected:
 Reader(QObject *parent = nullptr);
 /*protected*/ Reader(QObject* lock, QObject* parent = nullptr);

};

#endif // READER_H
